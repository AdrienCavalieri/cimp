#ifndef ROTATE_H
#define ROTATE_H

#include "../../data/picture.h"

/*
 * Effectue une rotation sur l'image p (rotation de 90, 180 ou 270 degrés.)
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short rotate(struct picture* p, int angle);


/*
 * Effectue une rotation sur l'image select_pic (rotation de 90, 180 ou 270 degrés.)
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short rotate_command(int argc, const char* args[], struct picture* select_pic );

#endif /*ROTATE_H*/
