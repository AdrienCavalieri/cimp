#include "fill.h"

#include "../../utils/printer.h"
#include "../../ui/userReader.h"

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

short fill(struct picture* p, const struct selection* selec, const struct color* color){
	if (selec==NULL)
		return 0;
    
	int x,y;
	int minx, miny, maxx, maxy;

    get_select_bounds(selec, &minx, &miny, &maxx, &maxy);

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
				change_pixel_color(p,x,y,color); 
			}
		}
	}	
	return 1;
}

short fill_command(int argc, const char* args[], struct picture* select_pic,const struct selection* selection ){

    if (argc < 2) {
        print_notEnoughArgs("fill");
        return 0;
    }
    
    if (argc > 5) {
        print_toManyArgs("fill");
        return 0;
    }

    if (select_pic == NULL) {
        print_no_pic();
        return 0;
    }
    
    struct color* color = read_color(args+1, argc-1);
    if(color == NULL)
        return 0;
    
    int res = fill(select_pic,selection,color);
    if( !res ) print_emptySelec();
    
    destroy_color(color);
    
	return res;
}
