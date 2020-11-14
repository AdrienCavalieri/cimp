#ifndef WINDOW_H
#define WINDOW_H

#include "../data/picture.h"
#include "../data/selection.h"

struct window;


/****************/
/* Constructeur */
/****************/

/*
 * Crée une nouvelle fenêtre.
 */
struct window* create_window(int width, int height, const char* name);


/*****************/
/*  Destructeur  */
/*****************/

/*
 * Ferme la fenêtre et la libère.
 */
void destroy_window(struct window* win);


/*****************/
/*   Affichage   */
/*****************/

/*
 * Affiche l'image et la fenêtre est redimensionnée selon la taille de celle-ci.
 */
void show_picture(struct window* win, const struct picture* pic, const struct selection* selec);

/*
 * Enlève l'image de la fenêtre.
 */
void clear_window(struct window* win);


/****************/
/*  Visibilité  */
/****************/

/*
 * Affiche la fenêtre.
 */
void show_window(struct window* win);

/*
 * Fait passer la fenêtre au premier plan et lui donne le focus.
 */
void raise_window(struct window* win);

/*
 * Ferme la fenêtre.
 */
void close_window(struct window* win);


/****************/
/*    Getters   */
/****************/

/*
 * Retourne l'ID de la fenêtre.
 */
int get_window_id(const struct window* win);


/****************/
/*    Events    */
/****************/

/*
 * Vérifie si l'utilisateur a fermé une fenêtre. Renvoie l'id de la fenêtre fermée et 0 sinon.
 */
int is_closed();

/*
 * Séléctionne une zone de l'image à l'aide des mouements de la souris.
 * La sélection à été allouée, destroy_selection nécessaire.
 */
struct selection* trace_selection(struct window* win, const struct picture* pic);

/*
 * Attend tant que l'utilisateur n'appuie pas un des boutons de la souris.
 */
void waiting_for_press(int* x, int* y);

/*
 * Attend tant que l'utilisateur ne relâche pas un des boutons de la souris.
 */
void waiting_for_release(int* x, int* y);

#endif /* WINDOW_H */
