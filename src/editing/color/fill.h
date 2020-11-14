#ifndef FILL_H
#define FILL_H

#include "../../data/picture.h"
#include "../../data/selection.h"
#include "../../data/color.h"

/*
 * Remplit la selection selec de l'image p avec la couleur color.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short fill(struct picture* p, const struct selection* selec, const struct color* color);


/*
 * Remplit la selection selec de l'image select_pic avec la couleur donnée en argument (r g b a ou #rrggbbaa).
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short fill_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);

#endif /*FILL_H*/
