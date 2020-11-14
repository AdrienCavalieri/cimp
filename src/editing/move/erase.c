#include "erase.h"

#include "../../data/color.h"
#include "../../utils/printer.h"

#include <stdio.h>


short erase(struct picture* p, const struct selection* selec) {
    if (selec==NULL)
        return 0;
    
    int x,y;
    int minx, miny, maxx, maxy;
    struct color * ers = create_color(0,0,0,0);
    
    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
                change_pixel_color(p,x,y,ers);
            }
        }
    }
    destroy_color(ers);
    return 1;
}


short erase_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection ) {
    if(argc > 1) {
        print_toManyArgs("erase");
        return 0;
    }
    
    if (select_pic == NULL) {
        print_no_pic();   
        return 0;
    }    

    int res = erase(select_pic,selection);
    if( !res ) print_emptySelec();
    
    return res;
}
