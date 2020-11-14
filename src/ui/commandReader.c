#include "commandReader.h"

#include "../data/selection.h"

#include "../editing/color/brightness.h"
#include "../editing/color/bwconversion.h"
#include "../editing/color/contrast.h"
#include "../editing/color/fill.h"
#include "../editing/color/grayscale.h"
#include "../editing/color/negate.h"
#include "../editing/color/replaceColor.h"

#include "../editing/move/ccp.h"
#include "../editing/move/erase.h"
#include "../editing/move/symmetry.h"
#include "../editing/move/rotate.h"

#include "../editing/size/resize.h"
#include "../editing/size/crop.h"

#include "../utils/printer.h"

#include "save/load.h"
#include "save/save.h"
#include "save/unload.h"

#include "select.h"
#include "show.h"

#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#define BOLD "\001\e[1m\002"
#define GREEN "\001\e[32m\002"
#define DEFAULT "\001\e[0m\002"

#define MAX_ARGS 32
#define MAX_NB_OF_PICS 32

/*
 * Prompt qui sera affiche au debut de chaque ligne.
 */
static char prompt[] = BOLD GREEN "cimp > " DEFAULT;

/*
 * Tableau contenant la liste des commandes.
 */
static const char* cmd[] =
    {
        "brightness",
        "bwconversion",
        "contrast",
        "copy",
        "crop",
        "cut",
        "erase",
        "fill",
        "grayscale",
        "invert",
        "list",
        "load",
        "paste",
        "quit",
        "replace",
        "rotate",
        "resize",
        "save",
        "select",
        "show",
        "symmetry",
        "unload",
        "unselect",
        NULL
    };

/*
 * Tableau contenant la liste des images chargees.
 */
static struct picture* loaded_pictures[MAX_NB_OF_PICS] = {0};

/*
 * Tableau contenant la liste des fenetres.
 */
static struct window* windows[MAX_NB_OF_PICS] = {0};

/*
 * Rectangle representant le selection courante.
 */
static struct selection* selection = NULL;

/*
 * Picture representant l'image en cours d'edition.
 */
static struct picture* selected_pic = NULL;


/*********************************/
/*           Execution           */
/*********************************/


/******************/
/*     Getter     */
/******************/

int get_picture_id(const struct picture* pic) {
    for(int i=0; i<MAX_NB_OF_PICS; i++)
        if(loaded_pictures[i] == pic)
            return i;

    return -1;
}

struct window* get_picture_window(const struct picture* pic) {
    return windows[get_picture_id(pic)];
}

/*****************/
/* Commande List */
/*****************/


void print_pictures_data() {
    for(int i=0; i<MAX_NB_OF_PICS; i++)
        if( loaded_pictures[i] != NULL )
            printf("%d - %s\n", i, get_picture_path(loaded_pictures[i]));
}

static short list_command(int argc, const char* args[]){
    print_pictures_data();
	
	if(argc > 1)
		print_note("Arguments inutiles pour la commande 'list'.");
	
	return 1;
}


/*****************/
/*   Commandes   */
/*****************/


/*
 * Remplis le tableau des arguments a partir de la commande.
 * Renvoie le nombre d'éléments.
 */
static int fill_args(char* s, char* args[]) {
    char* token = strtok(s, " ");
    int i = 0;

    while( token != NULL && i < MAX_ARGS-1 ) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i;
}


short exec_command(int argc, const char* args[]) {
	if( !strcmp(args[0], "brightness") )
        brightness_command(argc, args, selected_pic, selection);
	
    else if( !strcmp(args[0], "bwconversion") )
        bw_conversion_command(argc, args, selected_pic, selection);
	
    else if( !strcmp(args[0], "contrast") )
        contrast_command(argc, args, selected_pic, selection);

    else if( !strcmp(args[0], "copy") ) {
        copy_command(argc, args, selected_pic, selection);
        return 1;
        
    }else if( !strcmp(args[0], "crop") ) {
        crop_command(argc, args, selected_pic, selection);
        destroy_selection(selection);
        selection = NULL;
        
    }else if( !strcmp(args[0], "cut") ) {
        cut_command(argc, args, selected_pic, selection);
        return 1;
        
    }else if( !strcmp(args[0], "erase") )
        erase_command(argc, args, selected_pic, selection);

    else if( !strcmp(args[0], "fill") )
        fill_command(argc, args, selected_pic, selection);
	
    else if( !strcmp(args[0], "grayscale") )
        grayscale_command(argc, args, selected_pic, selection);

    else if( !strcmp(args[0], "invert") )
        negate_command(argc, args, selected_pic, selection);
          
	else if( !strcmp(args[0], "list") ) {
        list_command(argc, args);
        return 1;
        
    }else if( !strcmp(args[0], "load") ) {
        load_command(argc, args, loaded_pictures, MAX_NB_OF_PICS);
        return 1;
        
    }else if( !strcmp(args[0], "paste") )
        paste_command(argc, args, selected_pic, selection);
 
    else if( !strcmp(args[0], "quit") )
        exit(EXIT_SUCCESS);

    else if( !strcmp(args[0], "replace") )
        replace_color_command(argc, args, selected_pic, selection);

    else if( !strcmp(args[0], "rotate") )
        rotate_command(argc, args, selected_pic);

    else if( !strcmp(args[0], "resize") ) {
        resize_command(argc, args, selected_pic);
        destroy_selection(selection);
        selection = NULL;
        
    }else if( !strcmp(args[0], "save") ) {
        save_command(argc, args, loaded_pictures, MAX_NB_OF_PICS);
        return 1;
       
    }else if( !strcmp(args[0], "select") ) {
        select_command(argc, args, loaded_pictures, MAX_NB_OF_PICS, &selection, &selected_pic);
        
    }else if( !strcmp(args[0], "show") ) {
        show_command(argc, args, selected_pic, windows, (const struct picture **)loaded_pictures, MAX_NB_OF_PICS, selection);
        return 1;
        
    }else if( !strcmp(args[0], "symmetry") )
        symmetry_command(argc, args, selected_pic);

    else if( !strcmp(args[0], "unload") ) {
        unload_command(argc, args, windows, loaded_pictures, MAX_NB_OF_PICS, &selected_pic, &selection);
        return 1;
    }
    
    else if( !strcmp(args[0], "unselect") )
        unselect_command(argc, &selection);

    else
        return 0;

    // Met à jour l'image après modification
    for(int i=0; i<MAX_NB_OF_PICS; i++) {
        if(loaded_pictures[i] == selected_pic) {
            if(windows[i] != NULL){
                clear_window(windows[i]);
                show_picture(windows[i], selected_pic, selection);
            }
            break;
        }
    }

    return 1;
}


/**********************************/
/*    Lecture et interpretation   */
/**********************************/

/*
 * Retire tous les espaces inutiles de la chaine de caractère.
 */
static char* normalize(char* s) {
    if( s == NULL)
        return NULL;
    
    if( *s == '\0' )
        return s;

    // Position ou on ecrit.
    char* addPos = s;

    // Position ou on lit.
    char* copyPos = s;

    // Flag permetant de virifier si on se trouve
    // dans une sequence de carateres blancs.
    short hasSpace = 0;

    // On passe les caracteres blancs du debut.
    while( isspace( *copyPos ) && *copyPos != '\0')
        copyPos++;

    // Si la chaine ne contenait que des caracteres blancs,
    // on renvoie la chaine vide.
    if(*copyPos == '\0') {
        s[0] = '\0';
        return s;
    }

    // On parcours la chaine caractere par caractere.
    while(*copyPos != '\0') {

        if( isspace(*copyPos) ) {

            // Si on commence une sequence de caracteres blancs
            // on ajoute le seul espaces qui sera garde.
            if( !hasSpace ) {
                addPos[0] = ' ';
                addPos++;
                hasSpace = 1;
            }

            copyPos++;

        } else {

            // On place le caractre a la bonne position,
            // et on incremente les deux pointeurs.
            addPos[0] = copyPos[0];
            addPos++;
            copyPos++;
            hasSpace = 0;
        }
    }

    // On ajoute le caractere null a la fin.
    // Si il y avait des blancs a la fin, alors
    // il ont ete reduis a un espace, on remplace
    // cet epace par le caractere null.
    if(addPos[-1] == ' ')
        addPos[-1] = '\0';
    else
        addPos[0] = '\0';

    return s;
}


/******************/
/* Interpretation */
/******************/


void read_command(char* line) {

    if( *line == '\0' ) return;
    
	char* args[MAX_ARGS];
    int argc = fill_args(line, args);

    if(!exec_command(argc, (const char**)args)) {
        printf("Commande inconnue : \"%s\"\n", args[0]);
        return;
    }
}


/******************/
/*   Evènements   */
/******************/

static void event_hook() {
    int closed_window_id = is_closed();

    if(closed_window_id) {

        for(int i=0; i<MAX_NB_OF_PICS; i++)
            
            if(windows[i] != NULL && get_window_id(windows[i]) == closed_window_id) {
                close_window(windows[i]);
                windows[i] = NULL;
                return;
            }
    }
}


/******************/
/* Autocomplétion */
/******************/

/*
 * Fonction donnant la num-ieme commande ayant un nom
 * commençant par text.
 */
static char* command_generator(const char *text, int num){
    static int index, len;
    const char *completion;
    
    if (num == 0){
        index = 0;
        len = strlen(text);
    }

    ;
    while( (completion = cmd[index++]) ) {
        if( !strncmp(completion, text, len) )
            return strdup(completion);
    }
    
    return NULL;
}

/*
 * Essaie de completer le mot contenu dans *text compris entre start et end. 
 */
static char ** fileman_completion (const char *text, int start, int end){
    // Completion possible.
    char **matches = (char **)NULL;

    // Si on est au debut de la ligne, on cherche une commande. 
    if (start == 0)      
        matches = rl_completion_matches (text, command_generator);
        
    // On renvoie le mot trouve (par default cherche les fichier et repertoires
    // du repertoire courant).
    return matches;
}


/******************/
/* Initialisation */
/******************/

void init_commandReader() {
    rl_attempted_completion_function = fileman_completion;
    rl_event_hook = (rl_hook_func_t* )(&event_hook);
}

/******************/
/*     Lecture    */
/******************/

void read_commandLine() { 
    char* line;

    // On lit l'entrée
    line =  readline(prompt);

    //On l'ajoute à l'historique
    add_history(line);
    
    // Si EOF (Ctrl-d).
    if(line == NULL ) {
        printf("\n");
        exit(EXIT_SUCCESS);
    }
					
    line = normalize(line);
			
    read_command( line );
    free(line);
}
