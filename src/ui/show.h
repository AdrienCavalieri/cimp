#ifndef SHOW_H
#define SHOW_H

#include "../data/picture.h"
#include "../data/selection.h"

#include "window.h"

/*
 * Affiche l'image selectionnée dans une nouvelle fenêtre ou bien dans une fenêtre préselectionnée.
 * Nécessite la selection courante pour la dessiner sur l'image.
 */
short show_command(int argc, const char* args[],
                   const struct picture* selected_pic,
                   struct window* windows[],
                   const struct picture* const loaded_pictures[], int size,
                   const struct selection* selection);
    
#endif /* SHOW_H */
