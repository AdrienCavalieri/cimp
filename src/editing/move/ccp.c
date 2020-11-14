#include "ccp.h"

#include "../../utils/printer.h"
#include "../../data/color.h"
#include "erase.h"

#include <stdio.h>

static struct picture * mem;

short copy(const struct picture* p, const struct selection* selec) {
    if(selec == NULL)
        return 0;
    
    if(mem != NULL)
        destroy_picture(mem);

    struct color* arbi = create_color(100,100,100,0);
    int x,y;
    int minx, miny, maxx, maxy;
    struct color* c;
    
    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);
    mem = create_picture( maxx-minx+1, maxy-miny+1 );
    
    for(y = miny; y <= maxy; y++){
        for(x = minx; x <= maxx; x++){

            if(is_selected(selec, x, y) ) {
                c = get_pixel_color(p,x,y);
                change_pixel_color(mem, x-minx, y-miny, c);
                destroy_color(c);

            }else{
                change_pixel_color(mem, x-minx, y-miny, arbi);   				
            }
        }
    }
    
    if(arbi!=NULL)
        destroy_color(arbi);

    return 1;
}


short cut(struct picture* p, const struct selection* selec) {
    if( !copy(p,selec) )
        return 0;
    
    erase(p,selec);

    return 1;
}


short paste(struct picture* p, const struct selection* selec) {
    if(selec == NULL || mem == NULL)
        return 0;
    
    int x,y;
    int minx, miny, maxx, maxy;
    struct color* c;
    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);
    struct color* arbi = create_color(100,100,100,0);
    
    maxx = (minx+get_picture_width(mem)-1 < maxx) ? minx+get_picture_width(mem)-1 : maxx;
    maxy = (miny+get_picture_height(mem)-1 < maxy) ? miny+get_picture_height(mem)-1 : maxy;

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
                c = get_pixel_color(mem, x-minx, y-miny);
                
                if( (equalsColor(c,arbi)) == 0 )
                    change_pixel_color(p,x,y,c);

                destroy_color(c);
            }
        }
    }
    
    if(arbi!=NULL)
   	    destroy_color(arbi);

    return 1;
}


short cut_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection ) {
    if(argc > 1) {
        print_toManyArgs("cut");
        return 0;
    }
    
    if (select_pic == NULL) {
        print_no_pic();   
        return 0;
    }    

    int res = cut(select_pic,selection);
    if( !res ) print_emptySelec();
    
    return res;
}
 
short copy_command(int argc, const char* args[], const struct picture* select_pic, const struct selection* selection ) {
    if(argc > 1) {
        print_toManyArgs("copy");
        return 0;
    }

    if (select_pic == NULL) {
        print_no_pic();
        return 0;
    }
    
    int res = copy(select_pic,selection);
    if( !res ) print_emptySelec();

    return 1;
}
 
short paste_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection ) {
    if(argc > 1) {
        print_toManyArgs("paste");
        return 0;
    }

    if (select_pic == NULL) {
        print_no_pic();
        return 0;
    }
    
    int res = paste(select_pic,selection);
    if( !res ) {
        if(mem == NULL)
            print_error("Rien à coller.");
        else
            print_emptySelec();
    }
    
    return 1;
}
