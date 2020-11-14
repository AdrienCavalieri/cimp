#include "picture.h"
#include "color.h"
#include "../utils/printer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <malloc.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_FORMAT_SIZE 4
#define MAX_PATH_LENGTH 256
#define DEFAULT_COLOR 0

/*************************************************/
/*                   Structure                   */
/*************************************************/

struct picture {
    enum FORMAT format;
    struct SDL_Surface *surface;
    char path[MAX_PATH_LENGTH];
};

/*************************************************/
/*            Constructeur/Destructeur           */
/*************************************************/


struct picture* create_picture_from_image(const char* path) {
    if(path == NULL) {
		printf("Empty path\n");
		return NULL;
	}

    struct picture* p;
    char* dot;
    int path_len; int set_len;

    // picture

    p = malloc(sizeof(struct picture));
    if(p == NULL) {
        fprintf(stderr, "malloc() failed.\n");
        return NULL;
    }

    memset(p, 0, sizeof(struct picture));

    // surface

    p->surface = IMG_Load(path);
    if(p->surface == NULL) {
        free(p);
        fprintf(stderr, "%s.\n", IMG_GetError());
        return NULL;
    }

    // format

    dot = strrchr(path, '.');
    if( strcmp(dot, ".bmp") == 0 || strcmp(dot, ".BMP") == 0 )
        p->format = BMP;
    
    else if( strcmp(dot, ".jpg") == 0 || strcmp(dot, ".JPG") == 0 ||
               strcmp(dot, ".jpeg") == 0 || strcmp(dot, ".JPEG") == 0 )
        p->format = JPG;
    
    else if( strcmp(dot, ".png") == 0 || strcmp(dot, ".PNG") == 0 )
        p->format = PNG;

    else {
        print_note("Le format %s n'est pas supporté par cimp, cette image sera considérée comme une image bmp.", dot);
        p->format = DEFAULT_FORMAT;
    }
        
    // path

    path_len = strlen(path);
    set_len = MAX_PATH_LENGTH-1 < path_len ? MAX_PATH_LENGTH-1 : path_len;

    memmove( p->path, path, set_len );
    p->path[set_len] = '\0';

    // Conversion de la surface

    SDL_Surface* tmp = p->surface;
    p->surface = SDL_ConvertSurfaceFormat(p->surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(tmp);    

    return p;
}

static SDL_Surface *create_surface(int width, int height) {

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        return NULL;
    }

    return surface;
}

struct picture* create_picture(int width, int height) {

    struct picture* p;

    // picture

    p = malloc(sizeof(struct picture));
    if(p == NULL) {
        fprintf(stderr, "malloc() failed.\n");
        return NULL;
    }

    memset(p, 0, sizeof(struct picture));

    // surface

    p->surface = create_surface(width, height);
    if (p->surface == NULL) {
        free(p);
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        return NULL;
    }

    // format

    p->format = DEFAULT_FORMAT;
    
    // path

    if( getcwd(p->path, MAX_PATH_LENGTH) == NULL ) {
        fprintf(stderr, "getcwd: %s\n", strerror(errno));
        SDL_FreeSurface(p->surface);
        free(p);
        return NULL;
    }
    memmove( p->path + strlen(p->path), "/\0", 2 );

    return p;
}

void destroy_picture( struct picture* p ) {
    SDL_FreeSurface(p->surface);
    free(p);
}


/*************************************************/
/*                    Getters                    */
/*************************************************/


int get_picture_width( const struct picture* p ) {
    if( p == NULL ) return -1;
    return p->surface->w;
}

int get_picture_height( const struct picture* p ) {
    if( p == NULL ) return -1;
    return p->surface->h;
}

enum FORMAT get_picture_format( const struct picture* p ) {
    if( p == NULL ) return -1;

    return p->format;
}

char* get_picture_path( const struct picture* p ) {
    if( p == NULL ) return NULL;

    char* path = strndup(p->path, MAX_PATH_LENGTH);
    if(path == NULL) {
        fprintf(stderr, "Get picture path: %s.\n", strerror(errno));
        return NULL;
    }

    return path;
}

int get_pitch(const struct picture* p) {
    return p->surface->pitch;
}

int get_pixelFormat(const struct picture* p) {
    return p->surface->format->format;
}

unsigned char* get_pixels(const struct picture* p) {
    int size = get_pitch(p) * get_picture_height(p);
    unsigned char* copy = malloc(size);
    memmove(copy, p->surface->pixels, size);
    return copy;
}

/*************************************************/
/*             Modification de pixels            */
/*************************************************/

short set_size(struct picture* p, int w, int h) {
    // Création d'une variable Rectangle pour les dimensions.
    SDL_Rect surface_rect;

    surface_rect.w = w;
    surface_rect.h = h;
    surface_rect.x = 0;
    surface_rect.y = 0;

    // Création d'une nouvelle surface selon les dimensions demandées.
    SDL_Surface *new_surface = create_surface(w, h);
    if (new_surface == NULL) {
        return 0;
    }

    // Copie toute la surface de l'image sur la nouvelle surface en respectant les dimensions.
    if ((SDL_BlitScaled(p->surface, NULL, new_surface, &surface_rect)) < 0) {
      fprintf(stderr,"Error! SDL_BlitScaled failed: %s\n", SDL_GetError());
      return 0;
    }

    SDL_FreeSurface(p->surface); // Libération de l'ancienne surface de l'image.
    p->surface = new_surface; // Assignation de la nouvelle surface en tant que surface de l'image.

    return 1;
}

short crop_picture(struct picture* p, const struct selection* selec) {
    // Création d'une variable Rectangle pour les dimensions.
    SDL_Rect crop_rect;
    int min_x, min_y, max_x, max_y;

    get_select_bounds(selec, &min_x, &min_y, &max_x, &max_y);

    // max_x = min( max_x, get_picture_width(pic)-1 )
    if( max_x > get_picture_width(p)-1 )
        max_x = get_picture_width(p)-1;

    // max_y = min( max_y, get_picture_height(pic)-1 )
    if( max_y > get_picture_height(p)-1 )
        max_y = get_picture_height(p)-1;
    
    crop_rect.w = max_x - min_x;
    crop_rect.h = max_y - min_y;
    crop_rect.x = min_x;
    crop_rect.y = min_y;

    // Création d'une nouvelle surface selon les dimensions demandées.
    SDL_Surface *new_surface = create_surface(crop_rect.w, crop_rect.h);
    if (new_surface == NULL) {
        return 0;
    }    

    // Copie la région de l'image à couper sur l'ensemble de la nouvelle surface.
    if ((SDL_BlitSurface(p->surface, &crop_rect, new_surface, NULL)) < 0) {
      fprintf(stderr,"Error! SDL_BlitScaled failed: %s\n", SDL_GetError());
      return 0;
    }

    SDL_FreeSurface(p->surface); // Libération de l'ancienne surface de l'image.
    p->surface = new_surface; // Assignation de la nouvelle surface en tant que surface de l'image.
    
    // Suppression de cellules non selectionnées

    struct color* c = create_color_hex(DEFAULT_COLOR);
    if(c == NULL)
        return 0;
    
    int i,j;
    for(i=0; i < crop_rect.w; i++) {
        for(j=0; j < crop_rect.h; j++) {
            if( !is_selected(selec, i + min_x, j + min_y) )
                change_pixel_color(p, i, j, c);
        }
    }

    destroy_color(c);
    return 1;
}


short change_pixel_color(const struct picture* p, int x, int y, const struct color* new_color) {
    if(p == NULL || new_color == NULL) return 0;

    unsigned char r,g,b,a;
    int w = get_picture_width(p);

    // On recupere les valeurs rgba.
    get_rgba(new_color, &r, &g, &b, &a);

    ((Uint32*)p->surface->pixels)[y * w + x] = SDL_MapRGBA(p->surface->format, r, g, b, a);

    return 1;
}

struct color* get_pixel_color(const struct picture* p, int x, int y) {
    unsigned char r,g,b,a;
    Uint32 pixel;
    int w = get_picture_width(p);

    pixel = ((Uint32*)p->surface->pixels)[y * w + x];
    SDL_GetRGBA(pixel, p->surface->format, &r, &g, &b, &a);

    return create_color(r,g,b,a);
}
