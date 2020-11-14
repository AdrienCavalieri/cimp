#ifndef SELECT_H
#define SELECT_H

#include "../data/picture.h"
#include "../data/selection.h"
#include "window.h"

/*
 * Selectionne un rectangle, construit à partir de 2 points,
 *  dans l'image pic et le stocke dans *selection. 
 */
short selectR(int x1, int y1, int x2, int y2, const struct picture* pic, struct selection** selection);

/*
 * Commande de selection d'images et de zones.
 */
short select_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length, struct selection** selection, struct picture** pic);

/*
 * Déselectionne la sélection courante.
 */
short unselect_command(int argc, struct selection** selection);

#endif /*SELECT_H*/
