#ifndef BW_CONVERSION_H
#define BW_CONVERSION_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Met en noir et blanc la selection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short bw_conversion(struct picture* p, const struct selection* selec);

/*
 * Met en noir et blanc la selection selec de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short bw_conversion_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec );

#endif /*BW_CONVERSION_H*/
