#ifndef CCP_H
#define CCP_H

#include "../../data/picture.h"
#include "../../data/selection.h"

/*
 * Stocke la sélection selec de l'image p, puis efface celle-ci
 * dans p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short cut(struct picture* p, const struct selection* selec);


/*
 * Stocke la sélection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short copy(const struct picture* p, const struct selection* selec);


/*
 * Ajoute la sélection stockée dans la selection selec de l'image p. 
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short paste(struct picture* p, const struct selection* selec);


/*
 * Stocke la sélection 'selection' de l'image select_pic, puis efface celle-ci
 * dans select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short cut_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );


/*
 * Stocke la sélection 'selection' de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */ 
short copy_command(int argc, const char* args[], const struct picture* select_pic, const struct selection* selection );


/*
 * Ajoute la sélection stockée dans la selection 'selection' de l'image select_pic. 
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short paste_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );

#endif /*CCP_H*/
