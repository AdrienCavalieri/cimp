#ifndef ERASE_H
#define ERASE_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Efface la sélection selec dans l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short erase(struct picture* p, const struct selection* selec);


/*
 * Efface la sélection 'selection' dans l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short erase_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );

#endif /*ERASE_H*/
