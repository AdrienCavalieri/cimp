#include "load.h"

#include "../../utils/printer.h"

#include <unistd.h>
#include <stdio.h>

short load(const char* path, struct picture** pic) {
    if(path == NULL) return 0;

    *pic = create_picture_from_image(path);
    return *pic != NULL;
}


short load_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length) {
    if(argc < 2) {
        print_error("Aucune image à charger.");
        return 0;
    }

    int next, i, return_value;

    return_value = 1;
    next = 0;

    for(i=1; i<argc; i++) {
        // On cherche le premier emplacement de libre
        while(pics_list[next] != NULL && next < pics_list_length)
            next++;

        // Si on atteind la fin du tableau
        if(next == pics_list_length) {
            print_error("Le nombre maximum d'images chargées à été atteind (%d). Veuillez décharger des images avec la commande 'unload' pour pouvoir en cherger d'autres.", next);
            return 0;
        }

        // On essaie de charger l'image
        if( load(args[i], &pics_list[next]) ) {
            printf("L'image '%s' a été chargée et peut être appelée avec l'id '%d'.\n", args[i], next);
            next++;
        } else
            return_value = 0;
    }

    printf("Vous pouvez lister les images chargées avec la commande 'list'.\n");
    return return_value;
}
