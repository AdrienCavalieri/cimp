#include "resize.h"

#include "../../ui/userReader.h"
#include "../../utils/printer.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


short resize(struct picture* p, int newWidth, int newHeight) {
    if (set_size(p, newWidth, newHeight)) {
        return 0;
    }
    return 1;
}


short resize_command(int argc, const char* args[], struct picture* select_pic) {
    if (argc > 3) {
        print_toManyArgs("resize");
        return 0;    
    }

    if (argc < 3){
        print_notEnoughArgs("resize");
        return 0;
    }

    if (select_pic == NULL) {
        print_no_pic();
        return 0;
    }

    // Vérification de la validité de la largeur et de la hauteur
    long w = read_whole_int(args[1]);
    if(w < 0) return 0;
    
    long h = read_whole_int(args[2]);
    if(h < 0) return 0;

    resize(select_pic, w, h);

    return 1;
}
