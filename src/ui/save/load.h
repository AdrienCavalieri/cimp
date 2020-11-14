#ifndef IMPORT_H
#define IMPORT_H

#include "../../data/picture.h"

/*
 * Charge une image se trouvant au chemin path et la stocke dans *pic.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short load(const char* path, struct picture** pic);


/*
 * Charge les images se trouvant aux cheminx donnés dans args et les stockent dans *pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short load_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length);

#endif /* IMPORT_H */
