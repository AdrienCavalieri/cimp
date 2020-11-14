#include "symmetry.h"

#include "../../utils/printer.h"

#include <string.h>

short symmetry(struct picture* p, enum symmetry_type type) {
    
    struct color *color, *colorOp;

    int pic_w = get_picture_width(p);
    int pic_h = get_picture_height(p);

    int max_x = (type == VERTICAL) ? pic_w/2 : pic_w;
    int max_y = (type == VERTICAL) ? pic_h : pic_h/2;
    
    int i, j, op_i, op_j;
    for(i=0; i < max_x; i++){
        for(j=0; j < max_y; j++){

            op_i = (type == VERTICAL) ? pic_w-1-i : i;
            op_j = (type == VERTICAL) ? j : pic_h-1-j;
            
            color = get_pixel_color(p,i,j);
            colorOp = get_pixel_color(p, op_i, op_j);
                
            change_pixel_color(p, i, j, colorOp);
            change_pixel_color(p, op_i, op_j, color);

            destroy_color(color);
            destroy_color(colorOp);
        }
    }

    return 1;
}


short symmetry_command(int argc, const char* args[], struct picture* select_pic ) {
    if(argc < 2){
        print_notEnoughArgs("symmetry");
        return 0;
    }
    
    if(select_pic == NULL){
        print_no_pic();
        return 0;
    }
    
    if(strcmp(args[1],"-v") == 0){
        symmetry(select_pic,VERTICAL);

    }else if(strcmp(args[1],"-h") == 0){
        symmetry(select_pic,HORIZONTAL);

    }else{
        print_error("L'argument n'est pas valide (ni -v ,ni -h).");
        return 0;
    }

    return 1;
}
