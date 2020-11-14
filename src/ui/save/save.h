#ifndef SAVE_H
#define SAVE_H

#include "../../data/picture.h"

/*
 * Sauvegarde une image au chemin 'filename' avec le format 'format'.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short save(const struct picture* p, const char* filename, enum FORMAT format);

/*
 * Sauvegarde une image. Recupère l'id de l'image à sauvegarder dans args puis
 * récupère cette image dans picsl_list.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short save_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length);

#endif /* SAVE_H */
