#ifndef SYMMETRY_H
#define SYMMETRY_H

#include "../../data/picture.h"

/*
 * enum représentant un axe de symétrie.
 */
enum symmetry_type {HORIZONTAL, VERTICAL};

/*
 * Effectue une symétrie sur l'image p, son type est donné par 'type'.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short symmetry(struct picture* p, enum symmetry_type type);

/*
 * Effectue une symétrie sur l'image select_pic, son type est donné par '-v' ou '-h' dans args.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short symmetry_command(int argc, const char* args[], struct picture* select_pic );

#endif /*SYMMETRY_H*/
