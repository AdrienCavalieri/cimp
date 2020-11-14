#include "bwconversion.h"

#include "../../utils/printer.h"
#include "../../data/color.h"

#include <stdio.h>
#include <stdlib.h>


short bw_conversion(struct picture* p, const struct selection* selec){
	if (selec == NULL) {
    	return 0;
	}
    
	int x,y;
    struct color * tmp,*new;
	unsigned char r,g,b,a;
	int minx, miny, maxx, maxy;
    int res;
    
    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
				tmp = get_pixel_color(p,x,y);
				get_rgba(tmp,&r,&g,&b,&a);
				res = ((r+g+b)/3 >= 128) ? 255 : 0;
				r = res;
				g = res;
				b = res;			
				new = create_color(r,g,b,a);
				change_pixel_color(p,x,y,new);
				destroy_color(tmp);
				destroy_color(new);
			}
		}
	}

    return 1;
}


short bw_conversion_command(int argc, const char* args[], struct picture* select_pic,const struct selection* selection ){
	if(argc > 1) {
        print_toManyArgs("bwconversion");
        return 0;
    }
        
    if (select_pic == NULL) {
		print_no_pic();
		return 0;
	}

    int res = bw_conversion(select_pic,selection);    
    if( !res ) print_emptySelec();
    
	return res;
}
