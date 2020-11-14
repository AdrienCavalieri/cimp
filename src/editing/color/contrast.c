#include "contrast.h"

#include "../../utils/printer.h"
#include "../../ui/userReader.h"
#include "../../data/color.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static unsigned char calcConstrast(double factor,unsigned char c){
	int res = factor*(c-128)+128;

    if (res < 0)
		res = 0;

    if (res > 255)
		res = 255;

    return res;
}


short contrast(struct picture* p,  const struct selection* selec, char contrastAmount){
	if (selec==NULL){
		return 0;
	}

	double factor = (259.0*(contrastAmount+255.0)) / (255.0*(259.0 - contrastAmount));
	int x,y;
    struct color * tmp,*new;
    unsigned char tab[4];
	int minx, miny, maxx, maxy;

	get_select_bounds(selec, &minx, &miny, &maxx, &maxy);

    for(y=miny; y < maxy; y++){
        for(x=minx; x < maxx; x++){
            tmp=get_pixel_color(p,x,y);
            get_rgba(tmp, &tab[0], &tab[1], &tab[2], &tab[3]);

            for (int k=0;k<3;k++){
                tab[k] = calcConstrast(factor,tab[k]);
            }

            new = create_color(tab[0],tab[1],tab[2],tab[3]);
            change_pixel_color(p,x,y,new);

            destroy_color(tmp);
            destroy_color(new);
        }
    }
	return 1;
}


short contrast_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection){
	if(argc > 2) {
        print_toManyArgs("contrast");
        return 0;
    }

    if (argc<2){
		print_notEnoughArgs("contrast");
        return 0;
	}

	if (select_pic == NULL) {
		print_no_pic();
        return 0;
	}

	char val ;
	short res = read_signed_char(args[1],&val);
	if(res < 0)
        return 0;

    res = contrast(select_pic,selection,val);
    if( !res ) print_emptySelec();
        
    return res;
}
