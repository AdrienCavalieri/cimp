#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

struct color;

/*
 * Construit une couleur rgba (red, green, blue, alpha). 
 */
struct color* create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

/*
 * Construit une couleur rgba (red, green, blue, alpha) à partir d'une valeur hexadecimal 
 * (0x????????). 
 */
struct color* create_color_hex(uint32_t hexa_value);

/*
 * Libere la memoire occupee par une structure color. 
 */
void destroy_color(struct color* color);

/*
 * Remplis les unsigned char passes en parametre avec les valeurs rgba de color.
 */
void get_rgba(const struct color* color, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
/*
 * Vérifie que les couleurs oldColor et newColor sont égales.
 */
short equalsColor(const struct color* oldColor, const struct color* newColor);
#endif /* COLOR_H */
