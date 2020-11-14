#include "show.h"

#include "../utils/printer.h"

#include <stdio.h>
#include <stdlib.h>


static int get_picture_id(const struct picture* pic, const struct picture* const loaded_pictures[], int size) {
    for(int i=0; i<size; i++) {
        if(pic == loaded_pictures[i])
            return i;
    }
    return -1;
}


short show_command(int argc, const char* args[],
                   const struct picture* selected_pic,
                   struct window* windows[],
                   const struct picture* const loaded_pictures[],
                   int size, const struct selection* selection) {

    // Si aucune image n'est selectionnée.
    if(selected_pic == NULL) {
        print_no_pic();
        return 0;
    }

    
    int pic_id = get_picture_id(selected_pic, loaded_pictures, size);
    if(pic_id < 0) {
        print_error("Image d'id %d inexistante.", pic_id);
        return 0;
    }
    // S'il n'y a pas d'arguments, on affiche dans la fenêtre liée à l'image selectionnée.
    if(argc < 2) {

        // Si la fenêtre n'existe pas, on la créée et on l'affiche, sinon
        // on la met juste en premier plan. 
        if(windows[pic_id] == NULL) {
            windows[pic_id] = create_window(get_picture_width(selected_pic),get_picture_height(selected_pic), NULL);
            show_window(windows[pic_id]);
            show_picture(windows[pic_id], selected_pic, selection);
        }
        else
            raise_window(windows[pic_id]);
        
        return 1;
    }

    if(argc == 2) {
        print_error("Option invalide: '%s'.", args[1]);
        return 0;
    }
    
    int id_index = 1;
    // Si il l'y a deux arguments alors il doit y avoir une option.
    if(args[1][0] == '-') {
        // Si l'option n'est pas "-w".
        if(args[1][1] != 'w' || args[1][2] != '\0') {
            print_error("Option invalide: '%s'.", args[1]);
            return 0;
        }

        // Si il n'y a pas l'id de la fenêtre après l'option.
        if(argc == 2) {
            print_error("Argument manquant, veuillez donner l'id de la fenêtre qui doit afficher l'image.");
            return 0;
        }

        id_index = 2;
    }

    
    char* end;
    long id = strtol(args[id_index], &end, 10);
    // Si l'id donné n'est pas un nombre.
    if(*end != '\0') {
        print_error("L'id donné n'est pas un nombre: '%s'.", args[id_index]);
        return 0;
    }

    // On cherche la fenêtre ciblée, et si on la trouve, on affiche l'image.
    for(int i=0; i<size; i++) {

        if(windows[i] != NULL && get_window_id(windows[i]) == id) {
            if(windows[pic_id] != NULL) {
                destroy_window(windows[pic_id]);
                windows[pic_id] = NULL;
            }
            
            windows[pic_id] = windows[i];
            windows[i] = NULL;
            show_picture(windows[pic_id], selected_pic, selection);
            return 1;
        }
        
    }

    //Si la fenêtre n'a pas été trouvée.
    print_error("Aucune fenêtre dont l'id est %d n'a été touvé.", id_index);
    return 0;
   
}
