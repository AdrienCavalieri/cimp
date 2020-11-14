#include "select.h"

#include "../utils/printer.h"

#include "commandReader.h"
#include "userReader.h"

#include <malloc.h>

enum SELECTION_TYPE {RESELECT, ADD, REMOVE};


/*
 * Opération de sélection sur deux sélections. src et dest peuvent être désalloués dans cette fonction.
 */
static void selectionOperation(struct selection** src, struct selection** dest, enum SELECTION_TYPE type) {

    if( *dest == NULL && type != REMOVE ) {
        *dest = *src;
        return;
    }
    
    // On supprime une partie sur une partie vide, donc on ne fait rien
    if(*dest == NULL) {
        destroy_selection(*src);
        return;
    }
        
    // RESELECT
    if( type != ADD && type != REMOVE) {
        destroy_selection(*dest);
        *dest = *src;
        return;
    }
    
    int minx, miny, maxx, maxy;
    get_select_bounds(*src, &minx, &miny, &maxx, &maxy);

    int x,y;
    for(y = miny; y < maxy; y++) {
        for(x = minx; x < maxx; x++)
            if( is_selected(*src, x, y) ) {
                if( type == REMOVE ) unselect(*dest, x, y);
                // type == ADD
                else select_pixel(*dest, x, y);
            }
    }

    destroy_selection(*src);
}

/***************/
/*  Rectangle  */
/***************/

short selectR(int x1, int y1, int x2, int y2, const struct picture* pic, struct selection** selection){
	int topLeftX, topLeftY, bottomRightX, bottomRightY;

    topLeftX = ( x1 < x2 ) ? x1 : x2;
	topLeftY = ( y1 < y2 ) ? y1 : y2; 

    bottomRightX = ( x1 > x2 ) ? x1 : x2;
	bottomRightY = ( y1 > y2 ) ? y1 : y2;

    int pic_w = get_picture_width(pic);
    int pic_h = get_picture_height(pic);
        
    if(bottomRightX > pic_w-1) {
        print_error("'%d' est en dehors de l'image de dimension '%dx%d'.", bottomRightX, pic_w, pic_h);
        return 0;
    }
    
    if(bottomRightY > pic_h-1) {
        print_error("'%d' est en dehors de l'image de dimension '%dx%d'.", bottomRightY, pic_w, pic_h);
        return 0;
    }
    
    int w = bottomRightX-topLeftX;
    int h = bottomRightY-topLeftY;
    
    *selection = create_selection( pic_w, pic_h );
    if( *selection == NULL )
        return 0;
    
    int y,x;
    for(y=topLeftY; y < h+topLeftY; y++)
        for(x=topLeftX; x < w+topLeftX; x++)
            select_pixel(*selection, x, y);

    return 1;
}


/*
 * Selection de la zone avec des coordonnés
 */
static short rectangleSelection(int argc,  const char* args[], struct picture* pic, struct selection** selection, enum SELECTION_TYPE type) {
    struct selection* tmp = NULL;
        
    if (argc < 3) {
        print_error("Arguments manquants, vous devez donner deux points pour effectuer la sélection.");
        return 0;
    }
    
    int x1 = read_whole_int(args[2]);
    if( x1 < 0 ) return 0;

    if (argc==3) {
        print_error("Argument manquant, vous devez donner un ou trois autres entiers pour effectuer une selection.");
        return 0;
    }

    int y1 = read_whole_int(args[3]);
    if( y1 < 0 ) return 0;

    //Creer le rectangle avec 1 point
    if (argc==4){
        if( !selectR( x1, y1, x1, y1, pic, &tmp) )
            return 0;
        selectionOperation(&tmp, selection, type);     
        return 1;
    }
    
    int x2 = read_whole_int(args[4]);
    if( x2 < 0 ) return 0;
    
    if (argc==5) {
        print_error("Argument manquant, vous devez donner un autre entier pour effectuer une selection.");
        return 0;
    }

    int y2 = read_whole_int(args[5]);
    if( y2 < 0 ) return 0;
    
    //Creer le rectangle avec 2 points
    if( argc == 6 ){
        if( !selectR( x1, y1, x2, y2, pic, &tmp) )
            return 0;
        selectionOperation(&tmp, selection, type);
        return 1;
    }

    print_toManyArgs("select -r");
    return 0;
}


/***************/
/*    Color    */
/***************/

/*
 * Selection de la zone avec une couleur
 */
static short colorSelection(int argc,  const char* args[], struct picture* pic, struct selection** selection, enum SELECTION_TYPE type) {

    struct color* pc;
    struct color* c = read_color(args+2, argc-2);
    printf("%s\n", c == NULL ? "c null" : "c pas null");
    if(c == NULL)
        return 0;

    int x, y;
    int w = get_picture_width(pic);
    int h = get_picture_width(pic);

    struct selection* tmp = create_selection(w,h);

    for(y = 0; y < h; y++)
        for(x = 0; x < w; x++) {

            pc = get_pixel_color(pic,x,y);

            if( equalsColor(pc,c) )
                select_pixel(tmp,x,y);

            destroy_color(pc);
        }
    selectionOperation(&tmp, selection, type);
    return 1;
}


/***************/
/*    Mouse    */
/***************/

/*
 * Selection de la zone à la souris
 */
static short mouseSelection(int argc, struct selection** selection, const struct picture* pic, struct window* pic_win, enum SELECTION_TYPE type) {

    struct selection* tmp = NULL;
    
    if(argc > 2) print_note("Arguments inutiles après l'options.");
    
    printf("Selection une zone de l'image à l'aide de la souris, le trait doit se toucher pour que la selection soit acceptée.\n");

    tmp = trace_selection(pic_win, pic);
    if(tmp == NULL)
        return 0;
    
    selectionOperation(&tmp, selection, type);
    
    return 1;
}


/***************/
/*   Command   */
/***************/

short select_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length, struct selection** selection, struct picture** pic){

    // Affiche le chemin de l'image sélectionnée.
	if (argc<2){

        if( *pic == NULL ){
			printf("Aucune image n'a été sélectionée, sélectionnez une image avec 'select [ID]'.\n");
			return 1;
		}

        char * path = get_picture_path(*pic);
		printf("Path = %s\n",path);
		free(path);
        
		return 1;
	}
    
    // Si il y a qu'un arugument (hors nom), alors ce doit être l'id d'une image.
    if ( argc == 2 && args[1][0] != '-'){   

        int img = read_whole_int(args[1]);

        if(img < 0)
            return 0;
        
        if(img>pics_list_length || pics_list[img]==NULL){
            print_error("Il n'existe aucune image dont l'id est %d.",img);
            return 0;
        }
        *pic=pics_list[img];
        printf("Image %d séléctionée.\n", img);

        if(*selection != NULL) {
            destroy_selection(*selection);
            *selection = NULL;
        }
        
        return 1;
    }


    if( *pic == NULL ){
        print_error("Impossible d'effectuer une sélection, sélectionnez d'abord une image avec 'select [ID]'.");
        return 0;
    }
    
    // argc > 2

    // Si il y a plus de 2 arguments alors on sélectionne une zone (donc avec une option)
    if( args[1][0] != '-' ) {
        print_error("Le premier argument devrait être une option.");
        return 0;
    }

    // args[1][0] == '-'

    if( args[1][1] == '-' &&
        args[1][2] == 'a' &&
        args[1][3] == 'l' &&
        args[1][4] == 'l' &&
        args[1][5] == '\0') {

        int w = get_picture_width(*pic);
        int h = get_picture_height(*pic);
        
        if( *selection == NULL )
            *selection = create_selection(w,h);
        
        for(int i=0; i < h; i++)
            for(int j=0; j < w; j++)
                select_pixel(*selection, j, i);

        return 1;
    }
    
    
    int type = args[1][1] == 'a' ? ADD : (args[1][1] == 'd' ? REMOVE : RESELECT); 

    // Selection d'un rectangle
    if( (args[1][1] == 'r' && args[1][2] == '\0') ||
        ( type != RESELECT && args[1][2] == 'r' && args[1][3] == '\0')) {

        return rectangleSelection(argc, args, *pic, selection, type);        
    }

    // Selection par couleur
    if( (args[1][1] == 'c' && args[1][2] == '\0') ||
        ( type != RESELECT && args[1][2] == 'c' && args[1][3] == '\0')) {
        
        return colorSelection(argc, args, *pic, selection, type);        
    }
        
    // Selection en 'lasso'
    if( (args[1][1] == 'm' && args[1][2] == '\0') ||
        ( type != RESELECT && args[1][2] == 'm' && args[1][3] == '\0')) {

        struct window* win = get_picture_window(*pic);
        if(win != NULL)
            return mouseSelection(argc, selection, *pic, win, type);

        else
            print_error("Aucune fenêtre n'est ouverte pour cette image, ouvrez en une ou deplacez cette image vers une fenêtre déjà ouverte avec la commande 'show'.");
        return 0;
    }
    
    print_error("L'option '%s' n'est pas reconnue.", args[1]);
    return 0;
}


short unselect_command(int argc, struct selection** selection){
	// Affiche le chemin de l'image sélectionnée.
	if (argc > 1){
        print_note("Arguments inutiles.");
        return 1;
    }

    if( *selection == NULL ) {
        print_error("Aucune sélection à déselectionner.");
        return 0;
    }

    destroy_selection(*selection);
    *selection = NULL;
    
    return 1;
}
