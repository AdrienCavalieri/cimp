#include "unload.h"

#include "../userReader.h"
#include "../../utils/printer.h"

#include <stdio.h>
#include <stdlib.h>

short unload(int pic_id, struct window* windows_list[],
             struct picture* pics_list[], int pics_list_length,
             struct picture** selected_pic, struct selection** selection) {

    if(pic_id < 0 || pic_id >= pics_list_length || pics_list[pic_id] == NULL)
        return 0;

    // Si il s'agit de l'image selectionnée, on la désélectionne.
    if( *selected_pic == pics_list[pic_id] ) {
        *selected_pic = NULL;

        // On supprimme le rectangle si il y en a un.
        if( *selection != NULL) {
            destroy_selection(*selection);
            *selection = NULL;
        }

        // Si elle est affichée, on ferme la fenêtre associée.
        if( windows_list[pic_id] != NULL ) {
            close_window(windows_list[pic_id]);
            windows_list[pic_id] = NULL;
        }
    }

    destroy_picture(pics_list[pic_id]);
    pics_list[pic_id] = NULL;
    return 1;
}

short unload_command(int argc, const char* args[], struct window* windows_list[], struct picture* pics_list[], int pics_list_length, struct picture** selected_pic, struct selection** selec) {

    int pic_id = -1;
    int return_value = 1;
    char* path = NULL;

    for(int i=1; i<argc; i++) {

        // On vérifie qu'il s'agit bien d'un nombre.
        pic_id = read_whole_int(args[i]);
        if( pic_id < 0 )
            continue;

        // On vérifie que l'index est dans le tableau.
        if( pic_id >= pics_list_length ) {
            print_error("L'id '%d' est plus grand que le plus grand id possible (%d).", pic_id, pics_list_length-1);
            return_value = 0;
            continue;
        }

        // On verifie que l'image existe.
        if( pics_list[pic_id] == NULL ) {
            print_error("Aucune image dont l'id est '%d' n'est chargée.", pic_id);
            return_value = 0;
            continue;
        }

        // Feedback
        path = get_picture_path(pics_list[pic_id]);
        printf("L'image '%s' (%d) a été déchargée.\n", path, pic_id);
        free(path);
        path = NULL;

        // On supprime l'image
        unload(pic_id, windows_list, pics_list, pics_list_length, selected_pic, selec);
    }

    return return_value;
}
