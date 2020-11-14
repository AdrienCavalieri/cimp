#ifndef REPLACE_COLOR_H
#define REPLACE_COLOR_H

#include "../../data/picture.h"
#include "../../data/color.h"
#include "../../data/selection.h"

/*
 * Echange la couleur oldColor par newColor dans la selection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short replace_color(struct picture* p, const struct selection* selec, const struct color* oldColor, const struct color* newColor);

/*
 * Echange deux couleurs dans la selection selec de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short replace_color_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);

#endif /*REPLACE_COLOR_H*/
