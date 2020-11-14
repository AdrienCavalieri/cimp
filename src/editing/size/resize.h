#ifndef RESIZE_H
#define RESIZE_H

#include "../../data/picture.h"

/*
 * Redimensionne l'image p avec les dimensions newWidth et newHeight.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short resize(struct picture* p, int newWidth, int newHeight);


/*
 * Redimensionne l'image select_pic avec les dimensions données dans args (largeur et hauteur).
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short resize_command(int argc, const char* args[], struct picture* select_pic);

#endif /*RESIZE_H*/
