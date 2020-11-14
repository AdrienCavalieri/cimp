#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"

struct window {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

static int windows_created = 0; // Compte le nombre de fenêtres crées.


/****************/
/* Constructeur */
/****************/

struct window* create_window(int width, int height, const char* name) {
    // Alloue de la mémoire pour la structure fenêtre.
    struct window *win = malloc(sizeof(struct window));
    if (win == NULL) {
        fprintf(stderr, "Error! malloc failed.\n");
        return NULL;
    }

    // Initialise le sous-sytème vidéo SDL si c'est la première crée.
    if (windows_created == 0) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr,"Error! SDL_Init failed: %s\n", SDL_GetError());
            exit(1);
        }

        windows_created++;
    }

    // Créé la fenêtre SDL.
    win->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN);
    if (win->window == NULL) {
      fprintf(stderr,"Error! SDL_CreateWindow failed: %s\n", SDL_GetError());
      SDL_Quit();
      return NULL;
    }

    if (name == NULL) {
        char id[11];
        sprintf(id, "%d", get_window_id(win));
        SDL_SetWindowTitle(win->window, id);
    }

    // Crée l'outil de rendu pour dessiner la fenêtre.
    win->renderer = SDL_CreateRenderer(win->window, -1, SDL_RENDERER_ACCELERATED);
    if (win->renderer == NULL) {
      fprintf(stderr,"Error! SDL_CreateRenderer failed: %s\n", SDL_GetError());
      SDL_DestroyWindow(win->window);
      SDL_Quit();
      return NULL;
    }

    SDL_SetRenderDrawBlendMode(win->renderer, SDL_BLENDMODE_BLEND);

    return win;
}


/*****************/
/*  Destructeur  */
/*****************/

void destroy_window(struct window* win) {
    if (win != NULL) {
        SDL_DestroyRenderer(win->renderer); // Libère l'outil de restitution.
        SDL_DestroyWindow(win->window); // Libère la fenêtre SDL.
        free(win); // Libère la structure fenêtre toute entière.
    }
}

/*****************/
/*   Affichage   */
/*****************/

void show_picture(struct window* win, const struct picture* pic, const struct selection* selec) {
    // Récupère la taille de l'écran.
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        fprintf(stderr,"Error! SDL_GetDesktopDisplayMode failed: %s\n", SDL_GetError());
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Redimensionne la fenêtre pour correspondre à la taille de l'image (si elle ne dépasse pas de l'écran).
    int w = get_picture_width(pic) > dm.w ? dm.w : get_picture_width(pic);
    int h = get_picture_height(pic) > dm.h ? dm.h : get_picture_height(pic);

    int wh, ww;
    SDL_GetWindowSize(win->window, &ww, &wh);
    if(ww !=  w || h != wh) {
        SDL_HideWindow(win->window);
        SDL_SetWindowSize(win->window, w, h);
        SDL_ShowWindow(win->window);
    }
    
    // Crée la texture depuis la surface de l'image.
    SDL_Texture* texture = SDL_CreateTexture(win->renderer, get_pixelFormat(pic),
        SDL_TEXTUREACCESS_STATIC, get_picture_width(pic), get_picture_height(pic));
    if (texture == NULL) {
        fprintf(stderr,"Error! SDL_Texture failed: %s\n", SDL_GetError());
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Gère la transparence
    if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0) {
        fprintf(stderr,"Error! SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Met à jour la texture avec l'image.
    Uint32* pixels = (Uint32*)get_pixels(pic);
    if (SDL_UpdateTexture(texture, NULL, pixels, get_pitch(pic)) != 0) {
        fprintf(stderr,"Error! SDL_UpdateTexture failed: %s\n", SDL_GetError());
        free(pixels);
        SDL_DestroyTexture(texture);
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Nettoye l'outil de rendu.
    if (SDL_RenderClear(win->renderer) != 0) {
        fprintf(stderr,"Error! SDL_RenderClear failed: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Copie l'image sur l'outil de rendu.
    if (SDL_RenderCopy(win->renderer, texture, NULL, NULL) != 0) {
        fprintf(stderr,"Error! SDL_RenderCopy failed: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Dessinne la sélection. 
    if( selec != NULL ) {
        int x,y;
        int sw = get_selection_width(selec);
        int sh = get_selection_height(selec);
        int minx, miny, maxx, maxy;

        get_select_bounds(selec, &minx, &miny, &maxx, &maxy);
        for(y=miny; y <= maxy; y++)
            for(x=minx; x <= maxx; x++)
                if( is_selected(selec, x, y) ) {
                    if( x == 0 || y == 0 || x == sw-1 || y == sh-1 ||
                        !is_selected(selec, x-1, y) ||
                        !is_selected(selec, x+1, y) ||
                        !is_selected(selec, x, y-1) ||
                        !is_selected(selec, x, y+1) )
                        SDL_SetRenderDrawColor(win->renderer, 34, 87, 134, 255);
                    else
                        SDL_SetRenderDrawColor(win->renderer, 94, 158, 214, 128);
                    
                    SDL_RenderDrawPoint(win->renderer, x, y);
                }
    }

    SDL_RenderPresent(win->renderer); // Actualise l'écran.

    SDL_DestroyTexture(texture); // Libére la texture.
    free(pixels); // Libère les pixels.
}


void clear_window(struct window* win) {
    // Sélectionne la couleur de l'outil de rendu.
    if(SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255) != 0){
        fprintf(stderr,"Error! SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
        destroy_window(win);
        SDL_Quit();
        return;
    }

    // Colorie l'outil de rendu en blanc.
    if(SDL_RenderClear(win->renderer) != 0){
        fprintf(stderr,"Error! SDL_RenderClear failed: %s\n", SDL_GetError());
        destroy_window(win);
        SDL_Quit();
        return;
    }

    SDL_RenderPresent(win->renderer); // Actualise l'écran.
}


/****************/
/*  Visibilité  */
/****************/

void show_window(struct window* win) {
    SDL_ShowWindow(win->window);
}

void raise_window(struct window* win) {
    SDL_RaiseWindow(win->window);
}

void close_window(struct window* win) {
    SDL_HideWindow(win->window);
    destroy_window(win);
}

/****************/
/*    Getters   */
/****************/

int get_window_id(const struct window* win) {
    return SDL_GetWindowID(win->window);
}

/****************/
/*    Events    */
/****************/

int is_closed() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
            return e.window.windowID;
        }
    }
    return 0;
}


struct selection* trace_selection(struct window* win, const struct picture* pic) {
    int w = get_picture_width(pic);
    int h = get_picture_height(pic);

    struct selection* selec = create_selection(w, h);
    
    if( SDL_SetRenderDrawColor(win->renderer, 34, 87, 134, 255) != 0){
        fprintf(stderr,"Error! SDL_RenderClear failed: %s\n", SDL_GetError());
        destroy_window(win);
        SDL_Quit();
        return NULL;
    }
    
    char listening = 0;
    SDL_Event e;
    int x, y;
    int lastX = -1, lastY = -1;
    
    while(1) {
        if (SDL_PollEvent(&e)) {
            if( e.type == SDL_MOUSEBUTTONDOWN ) {
                listening = 1;
            }

            if( listening && e.type == SDL_MOUSEMOTION ) {
                x = e.motion.x;
                y = e.motion.y;

                // Si la boucle est bouclée, on accepte arbitrairement que les selection
                // dont le périmètre est plus grand que 50 (pour éviter les selection "sur place").
                if( lastX > -1 && !select_line_no_cross(selec, lastX, lastY, &x, &y) && distance(selec, x,y,lastX,lastY) > 50 ) {

                    // Si il était déjà sélectionné. 
                    if( is_selected(selec, x, y) ) {
                        unselect_all_before(selec, x, y);
                        select_area(selec, x, y);
                        return selec;
                    }

                    destroy_selection(selec);
                    show_picture(win, pic, NULL);
                    return NULL;
                }

                if( lastX > -1 )
                    SDL_RenderDrawLine(win->renderer, lastX, lastY, x, y);
                
                lastX = x;
                lastY = y;
                
                SDL_RenderPresent(win->renderer); // Actualise l'écran.
                    
            }
            
            if( listening && e.type == SDL_MOUSEBUTTONUP ) {
                listening = 0;
                destroy_selection(selec);
                show_picture(win, pic, NULL);
                return NULL;             
            }

        }
    }
}


void waiting_for_press(int* x, int* y) {
    while(1) {
        SDL_Event e;

        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                printf("Coordonnées enfoncement du clic : %d %d\n", e.button.x, e.button.y); // Debug.
                *x = e.button.x;
                *y = e.button.y;
                return;
            }
        }
    }
}

void waiting_for_release(int* x, int* y) {
    while (1) {
        SDL_Event e;

        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONUP) {
                printf("Coordonnées relâchement du clic : %d %d\n", e.button.x, e.button.y); // Debug.
                *x = e.button.x;
                *y = e.button.y;
                return;
            }
        }
    }
}
