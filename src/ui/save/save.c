#include "save.h"
#include "../userReader.h"
#include "../../utils/printer.h"

#include <turbojpeg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

static short saveBMP(const char* filename, const struct picture* pic) {
    unsigned char* data = get_pixels(pic);
     
    SDL_Surface* s =
        SDL_CreateRGBSurfaceWithFormatFrom( data, get_picture_width(pic), get_picture_height(pic),
                                           4, get_pitch(pic), get_pixelFormat(pic));
    
    SDL_SaveBMP(s, filename);

    SDL_FreeSurface(s);   
    free(data);
    
	return 1;
}
    
static short saveJPG(const char* filename, const struct picture* pic) {
    unsigned char* data = get_pixels(pic);
    
	const int JPEG_QUALITY = 100;
	long unsigned int size = 0;
	unsigned char* output = NULL;
    
	tjhandle handleCompress = tjInitCompress();
	if( tjCompress2(handleCompress, data, get_picture_width(pic), get_pitch(pic), get_picture_height(pic), TJPF_RGBA,
                    &output, &size, TJSAMP_444, JPEG_QUALITY, TJFLAG_FASTDCT) < 0)
        printf("%s\n", tjGetErrorStr());
	
	FILE * file = fopen(filename, "wb");
	if (!file) {
		fprintf(stderr, "open file %s failed!\n", filename);

        tjDestroy(handleCompress);
        free(data);
		return 0;
	}

	fwrite (output, 1, size, file);
	fclose(file);

	tjDestroy(handleCompress);
	tjFree(output);

    free(data);
	return 1;
}

static short savePNG(const char* filename, const struct picture* pic) {
    unsigned char* data = get_pixels(pic);
    
    SDL_Surface* s =
        SDL_CreateRGBSurfaceWithFormatFrom( data, get_picture_width(pic), get_picture_height(pic),
                                           4, get_pitch(pic), get_pixelFormat(pic));
    
    IMG_SavePNG(s, filename);

    SDL_FreeSurface(s);
    
    free(data);
	return 1;
}


// donne le format de p si format==null
short save(const struct picture* pic, const char* filename, enum FORMAT format) {
    
    switch(format) {

    case BMP:
        saveBMP(filename, pic);
        break;
    case JPG:
        saveJPG(filename, pic);
        break;
    case PNG:
        savePNG(filename, pic);
        break;

    default:
        return 0;
    }
    
    return 1;
}

short save_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length) {
    if (argc < 3){
        print_error("Argument(s) manquant(s) pour la commande 'save' (save IMG_ID [PATH]NAME [FORMAT]).");
        return 0;
	}

    if (argc > 4){
        print_toManyArgs("save");
        return 0;
	}

    int id = read_whole_int(args[1]);
    if(id < 0)
        return 0;
    
    if (id >= pics_list_length || pics_list[id] == NULL) {
        print_error("Aucune image n'a l'id '%d'.", id);
        return 0;
    }
    
    if(argc == 4) {

        if( strcmp(args[3], "BMP") == 0 )
            save( pics_list[id], args[2], BMP );

        else if( strcmp(args[3], "JPG") == 0 )
            save( pics_list[id], args[2], JPG );

        else if( strcmp(args[3], "PNG") == 0 )
            save( pics_list[id], args[2], PNG );
        
        else {
            print_error("Format inconnu: '%s'. Les formats acceptés sont: 'BMP', 'JPG' et 'PNG'", args[2]);
            return 0;
            }
    } else
        save( pics_list[id], args[2], get_picture_format(pics_list[id]) );
        

    return 1;
}
