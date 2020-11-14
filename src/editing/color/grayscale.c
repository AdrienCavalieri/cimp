#include "grayscale.h"

#include "../../utils/printer.h"
#include "../../data/color.h"

#include <stdio.h>
#include <stdlib.h>


short grayscale(struct picture* p, const struct selection* selec){
	if (selec==NULL)
		return 0;
    
	int x,y;
	struct color * tmp,*new;
	unsigned char r,g,b,a;
    int minx, miny, maxx, maxy;
    unsigned char grey;
    
    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);
    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
                tmp = get_pixel_color(p,x,y);
                get_rgba(tmp,&r,&g,&b,&a);
                //Celui utiliser par gimp et photoshop
                grey = r*0.3 + g*0.59 + b*0.11;
                r = grey;
                g = grey;
                b = grey;

                new = create_color(r,g,b,a);
                change_pixel_color(p,x,y,new);

                destroy_color(tmp);
                destroy_color(new);
            }
        }
    }
    return 1;
}


short grayscale_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection ){

    if(argc > 1) {
        print_toManyArgs("grayscale");
        return 0;
    }
        
    if (select_pic == NULL) {
		print_no_pic();
		return 0;
	}

    int res = grayscale(select_pic,selection);    
    if( !res ) print_emptySelec();

	return res;
}
