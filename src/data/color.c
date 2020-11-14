#include "color.h"

#include <malloc.h>

struct color {
    uint32_t value;
};

struct color* create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return create_color_hex(a + (b << 8) + (g << 16) + (r << 24));
}

struct color* create_color_hex(uint32_t hexa_value) {
    struct color* c = malloc(sizeof(struct color));
    if(c == NULL) {
        fprintf(stderr, "malloc() failed.\n");
        return NULL;
    }

    c->value = hexa_value;
    return c;
}

void destroy_color(struct color* color) {
    free(color);
}

void get_rgba(const struct color* color, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a) {
    *r = color->value >> 24;
    *g = (color->value >> 16) & 0xff;
    *b = (color->value >> 8) & 0xff;
    *a = color->value & 0xff;
}
//Vérifie l'égalité des couleurs oldColor et newColor
short equalsColor(const struct color* oldColor, const struct color* newColor){
    unsigned char or,og,ob,oa,nr,ng,nb,na;
    get_rgba(oldColor,&or,&og,&ob,&oa);
    get_rgba(newColor,&nr,&ng,&nb,&na);
    return or == nr && og==ng && ob==nb && oa==na;
}
