#ifndef UNLOAD_H
#define UNLOAD_H

#include "../../data/picture.h"
#include "../../data/selection.h"
#include "../window.h"

/*
 * Décharge l'image pic_id en modifiant les structures/tableaux nécessaire.
 */
short unload(int pic_id, struct window* windows_list[], struct picture* pics_list[], int pics_list_length, struct picture** selected_pic, struct selection** selection);

/*
 * Décharge les images données dans args (représentées par leur id) en modifiant les 
 * structures/tableaux nécessaire.
 */
short unload_command(int argc, const char* args[], struct window* windows_list[], struct picture* pics_list[], int pics_list_length, struct picture** selected_pic, struct selection** selec);

#endif /* UNLOAD_H */
