#include "rotate.h"
#include "../../data/color.h"
#include "../../ui/userReader.h"
#include "../../utils/printer.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Change la couleur d'un point après de rotation de angle degré.
 */
static void change_pixel_from_angle(struct picture* p, int x, int y, int w, int h, int angle, const struct color* c) {
    int nx, ny;
    
    if(angle == 90) {
        nx = h-1 - y;
        ny = x;

    }else if(angle == 180) {
        nx = w-1 - x;
        ny = h-1 - y;
        
    }else if(angle == 270) {
        nx = y;
        ny = w-1 - x;
        
    }
    
    change_pixel_color(p, nx, ny, c);
}

short rotate(struct picture* p, int angle) {
    if( p == NULL || (angle != 90 && angle != 180 && angle != 270) )
        return 0;

    int w = get_pitch(p)/4;
    int h = get_picture_height(p);

    struct picture* tmp = create_picture(w, h);
    int x, y;
    struct color* c;

    // On créé une image temporaire
    for(y=0; y<h; y++) {
        for(x=0; x<w; x++) {
            c = get_pixel_color(p, x, y);
            change_pixel_color(tmp, x, y, c);
            destroy_color(c);
        }
    }

    // Si la rotation n'est de 180 degrés, on inverse la hauteur et la largeur
    if(angle != 180)
        set_size(p, h, w);
    
    for(y=0; y<h; y++) {
        for(x=0; x<w; x++) {
            c = get_pixel_color(tmp, x, y);
            change_pixel_from_angle(p, x, y, w, h, angle, c);
            destroy_color(c);
        }
    }
        
    destroy_picture(tmp);
    
    return 1;
}

short rotate_command(int argc, const char* args[], struct picture* select_pic ) {
    long degree = -1;
    if( argc < 2 ) {
        print_error("Argument manquant, vous devez donner le degré de rotation.");
        return 0;
    }

    if( argc > 2 ) {
        print_toManyArgs("rotate");
        return 0;
    }

    if(select_pic == NULL) {
        print_no_pic();
        return 0;
    }
        
    degree = read_whole_int(args[1]);

    // On vérifie c'est une valeur supportée.
    if( degree != 90 && degree != 180 && degree != 270 ) {
        print_error("Le degree '%d' n'est pas supporté, les degrés supportés sont: 90, 180 et 270.", degree);
        return 0;
    }

    rotate(select_pic, degree);
    return 1;
}
