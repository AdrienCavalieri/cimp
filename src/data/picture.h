#ifndef PICTURE_H
#define PICTURE_H

#include "color.h"
#include "selection.h"

enum FORMAT {BMP, JPG, PNG};

#define DEFAULT_FORMAT BMP

/*************************************************/
/*                   Structure                   */
/*************************************************/

/*
 * Structure représentant une image.
 */
struct picture;


/*************************************************/
/*            Constructeur/Destructeur           */
/*************************************************/

/*
 * Créé une image à partir d'une image une existante.
 */
struct picture* create_picture_from_image(const char* path);

/*
 * Créé une image vide de dimension width*height.
 */
struct picture* create_picture(int width, int height);

/*
 * Supprime une image en liberant tous l'espace allouée pour celle-ci.
 */
void destroy_picture( struct picture* p);

/*************************************************/
/*                    Getters                    */
/*************************************************/


/*
 * Renvoie la largeur d'une image.
 */
int get_picture_width(const struct picture* p);

/*
 * Renvoie la hauteur d'une image.
 */
int get_picture_height(const struct picture* p);

/*
 * Renvoie le format d'une image.
 */
enum FORMAT get_picture_format(const struct picture* p);

/*
 * Renvoie le chemin d'une image. La chaine renvoyée est une
 * copie, un appel à free() est nécéssaire.
 */
char* get_picture_path(const struct picture* p);

/*
 * Renvoie la largeur d'une ligne (peut être différent de la
 * largeur pour des raison d'optimisation).
 */
int get_pitch(const struct picture* p);

/*
 * Renvoie le format utilisé pour le codage des pixels.
 */
int get_pixelFormat(const struct picture* p);


/*
 * Renvoie le tableau de pixels de picture.
 * La copie est obtenue avec malloc, free nécessaire.
 */
unsigned char* get_pixels(const struct picture* p);


/*************************************************/
/*             Modification de pixels            */
/*************************************************/


/*
 * Change la couleur du pixel en (x,y) par la couleur new_color.
 */
short change_pixel_color(const struct picture* p, int x, int y, const struct color* new_color);

/*
 * Renvoie la couleur du pixel en (x,y). La couleur renvoyée est une
 * copie, un appel à free() est nécéssaire.
 */
struct color* get_pixel_color(const struct picture* p, int x, int y);

/*
 * Change la taille de la surface de l'image.
 */
short set_size(struct picture* p, int w, int h);

/*
 * Coupe une partie de l'image.
 */
short crop_picture(struct picture* p, const struct selection* selec);

#endif /* PICTURE_H */
