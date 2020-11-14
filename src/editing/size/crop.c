#include "crop.h"
#include "../../utils/printer.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

short crop(struct picture* p, const struct selection* selec) {
    if (selec == NULL)
        return 0;

    if (crop_picture(p, selec))
        return 0;

    return 1;
}

short crop_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection) {
    if (argc > 1) {
        print_toManyArgs("crop");
        return 0;

    }if (select_pic == NULL) {
        print_no_pic();
        return 0;
	}
    
    int res = crop(select_pic, selection);
    if( !res && selection == NULL)
        print_emptySelec();
    
    return res;
}
