#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Met en niveau de gris la selection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short grayscale(struct picture* p, const struct selection* selec);

/*
 * Met en niveau de gris la selection selec de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short grayscale_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec );

#endif /*GRAYSCALE_H*/
