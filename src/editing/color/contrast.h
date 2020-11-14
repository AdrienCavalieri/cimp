#ifndef CONTRAST_H
#define CONTRAST_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Modifie le contraste dans la selection selec de l'image p.
 * Le coefficient de contraste est compris dans un char signé.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short contrast(struct picture* p,  const struct selection* selec, char contrastAmount);

/*
 * Modifie la luminosité dans la selection selec de l'image select_pic.
 * Le coefficient de contrast est compris dans un char signé.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short contrast_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);

#endif /*CONSTRAST_H*/
