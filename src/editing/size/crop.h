#ifndef CROP_H
#define CROP_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Effectue un recadrage de l'image p en fonction de la selection selec.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short crop(struct picture* p, const struct selection* selec);

/*
 * Effectue un recadrage de l'image select_pic en fonction de la selection selec.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short crop_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection);

#endif /*CROP_H*/
