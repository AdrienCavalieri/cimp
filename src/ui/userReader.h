#ifndef USER_READER_H
#define USER_READER_H

#include "../data/color.h"

/*
 * Convertit la chaine de charactère en entier avec l'affichage d'erreurs adaptées.
 * Renvoie -1 en cas d'erreur.
 */
int read_whole_int(const char* s);

/*
 * Convertit la chaine de charactère en partie de couleur (0-255) avec l'affichage 
 * d'erreurs adaptées. *field est utilisé pour stocker le résultat.
 * Renvoie -1 en cas d'erreur.
 */
short read_color_field(const char* s, unsigned char* field);

/*
 * Convertit la chaine de charactère en un caratère signé avec l'affichage 
 * d'erreurs adaptées. *res est utilisé pour stocker le résultat.
 * Renvoie -1 en cas d'erreur.
 */
short read_signed_char(const char* s, char* res);

/*
 * Convertit la chaine de charactère en une couleur (destroy_color nécessaire) 
 * avec l'affichage d'erreurs adaptées. Renvoie NULL en cas d'erreur.
 */
struct color* read_color(const char** args, int size);

/*
 * Convertit la chaine de charactère en valeurs rgba (0-255) avec l'affichage 
 * d'erreurs adaptées. Renvoie -1 en cas d'erreur.
 */
short read_color_vals(const char** args, int size, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);

#endif /* USER_READER_H */
