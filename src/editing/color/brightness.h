#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Modifie la luminosité dans la selection selec de l'image p.
 * Le coefficient de liminosité est compris dans un char signé.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short brightness(struct picture* p,  const struct selection* selec, char coeff);

/*
 * Modifie la luminosité dans la selection selec de l'image select_pic.
 * Le coefficient de liminosité est compris dans un char signé.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short brightness_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);

#endif /*BRIGHTNESS_H*/
