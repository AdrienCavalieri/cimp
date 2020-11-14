#include "replaceColor.h"

#include "../../utils/printer.h"
#include "../../ui/userReader.h"

#include <stdio.h>
#include <stdlib.h>

short replace_color(struct picture* p, const struct selection* selec, const struct color* oldColor, const struct color* newColor){
	if (selec==NULL)
        return 0;

    int x,y;
    int minx, miny, maxx, maxy;

	get_select_bounds(selec, &minx, &miny, &maxx, &maxy);

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            if( is_selected(selec, x, y) ) {
					if( equalsColor( get_pixel_color(p,x,y), oldColor ) )
						change_pixel_color(p,x,y,newColor); 
			}
		}
	}	
	return 1;
}
short replace_color_command(int argc, const char* args[], struct picture* select_pic,const struct selection* selection){
	if (argc < 3) {
		print_notEnoughArgs("replace");
        return 0;    
    }

    if (argc > 9) {
        print_toManyArgs("replace");
		return 0;
    }
    
	if (select_pic == NULL) {
        print_no_pic();
        return 0;
	}

    // Si c'est unreprésentation en hexadécimal, la longueur est de 1.
    // Sinon elle est de 4, en prend argc-1 si plus petit que 4 pour la gestion d'erreurs.
    int size = args[1][0] == '#' ? 1 : ( argc-1 < 4 ? argc-1 : 4);

	struct color* oldColor = read_color(args+1, size);
    if(oldColor == NULL)
        return 0;

    int step = args[1][0] == '#' ? 2 : 5;

	struct color* newColor = read_color(args+step, argc-step);
    if(newColor == NULL)
        return 0;
    
    int res = replace_color(select_pic,selection,oldColor,newColor);

    destroy_color(oldColor);
	destroy_color(newColor);

    if( !res ) print_emptySelec();
    
    return res;
}
