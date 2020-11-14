#ifndef COMMAND_READER_H
#define COMMAND_READER_H

#include "../data/picture.h"
#include "window.h"

// Ce module contient la liste des images chargées.

/*
 * Donne l'id d'une image et -1 si elle ne fait pas partie des images chargées.
 */
int get_picture_id(const struct picture* pic);

/*
 * Renvoie la fenêtre affichant l'image et NULL si il n'y en a pas.
 */
struct window* get_picture_window(const struct picture* pic);

/*
 * Affiche les images chargees avec leur id.
 */
void print_pictures_details();

/*
 * Execute une commande en fonction d'un liste d'argument (args[0] etant
 * le nom de la commande).
 */
short exec_command(int argc, const char* args[]);

/*
 * Initialise le lecteur de commande.
 */
void init_commandReader();

/*
 * Lit l'entree de l'utilisateur et la traite.
 */
void read_commandLine();

#endif /* COMMAND_READER_H */
