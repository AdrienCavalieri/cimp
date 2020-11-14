#ifndef NEGATE_H
#define NEGATE_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Met la selection selec de l'image p en négatif.
 * 
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short negate(struct picture* p, const struct selection* selec);

/*
 * Met la selection selec de l'image select_pic en négatif.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short negate_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);

#endif /*NEGATE_H*/
