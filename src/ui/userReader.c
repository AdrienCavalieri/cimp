#include "userReader.h"

#include "../utils/printer.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*************/
/*   Number  */
/*************/

static short read_long(const char* s, int base, long* res) {
    char* endt;
	long x = strtol(s, &endt, base);
    
    if( *endt != '\0' ) {
		print_error("\'%s\' n'est pas un nombre.", s);
		return -1;
	}

    *res = x;
    
    return 0;
}


static short read_bounded_number(const char* s, int base, long min, long max, long* res) {
    long x;

    if( read_long(s, base, &x) < 0 ) {
        return -1;
    }
    
	if( x < min || x > max ) {
		print_error("Le nombre '%s' n'est pas un nombre compris entre %d et %d.", s, min, max);
		return -1;
	}

    *res = x;
    return 0;
}


static long read_number(const char* s, int base, long max) {
	long x;

    if( read_long(s, base, &x) < 0 ) {
        return -1;
    }
    
	if( x > max ) {
		print_error("%s est trop grand.", s);
		return -1;
	}
    
	if( x < 0 ) {
		print_error("%s doit être supérieur à 0.", s);
		return -1;
	}

    return x;
}


int read_whole_int(const char* s) {
	return (int)read_number(s, 10, INT_MAX);
}


short read_signed_char(const char* s, char* res) {
    long val;
    if( read_bounded_number(s, 10, CHAR_MIN, CHAR_MAX, &val) < 0 )
        return -1;

    *res = (char)val;
    return 0;
}

/*************/
/*   Color   */
/*************/


short read_color_field(const char* s, unsigned char* field) {
    int val = read_whole_int(s);
    if(val < 0)
        return -1;

    if(val > 255) {
        print_error("'%s' doit être dans l'intervalle 0-255.", s);
        return -1;
    }

    *field = (unsigned char)val;
    return 0;
}


struct color* read_color(const char** args, int size) {
   
    if(size == 1 && args[0][0] != '#') {
        print_error("Format incorrecte, une couleur doit être entrée sous forme rgba (0-255 0-255 0-255 0-255') ou bien sous forme hexadécimal '#rrggbbaa'.");
        return NULL;
    }

    // hexadecimal
    if(args[0][0] == '#') {
        if( strlen(args[0]) > 9 ) {
            print_error("Valeur hexadécimale incorrecte pour '%s', le nombre doit contenir au plus 8 chiffres.", args[0]);
            return NULL;
        }
        
        unsigned int val = read_number(args[0]+1, 16, UINT_MAX);
        if(val < 0) return NULL;
        
        if(size > 1)
            print_note("Argument(s) inutile(s) après '%s'.", args[0]);
        
        return create_color_hex(val);
    }

    // rgba
    if(size != 4) {
        print_error("Nombre d'arguments incorrecte, une couleur n'est représentée que par 4 nombres.");
        return NULL;
    }

    unsigned char rgba[4];
    for(int i=0; i<4; i++)
        if( read_color_field(args[i], &rgba[i]) < 0 )
            return NULL;
    
    return create_color(rgba[0], rgba[1], rgba[2], rgba[3]);
}


short read_color_vals(const char** args, int size, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a) {
    struct color* c = read_color(args, size);

    if( c == NULL )
        return -1;
    
    get_rgba(c,r,g,b,a);
    destroy_color(c);
    c = NULL;

    return -1;
}
