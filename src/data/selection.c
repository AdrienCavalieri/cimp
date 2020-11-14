#include "selection.h"

#include "picture.h"

#include "../utils/printer.h"

#include <malloc.h>
#include <string.h>


// pixels -> pixels selectionné != 0
struct selection {
    int w;
    int h;
    unsigned int* pixels;
    unsigned int selected_pixels_count;
    int min_x;
    int min_y;
    int max_x;
    int max_y;
};

/********************/
/* Structure locale */
/********************/


struct elmt {
    int x;
    int y;
    struct elmt* next;
};

struct stack {
    struct elmt* head;
};

/*
 * Empile
 */
static void add(struct stack* s, int x, int y) {
    struct elmt* e = malloc(sizeof(struct elmt));
    e->x = x;
    e->y = y;
    e->next = s->head;
    s->head = e;
}

/*
 * Dépile
 */
static void get(struct stack* s, int *x, int *y) {
    *x = s->head->x;
    *y = s->head->y;
    struct elmt* tmp = s->head->next;
    s->head->next = NULL;
    free(s->head);
    s->head = tmp;
}

/********************/
/*   Constructeur   */
/********************/

struct selection* create_selection(int w, int h) {
    struct selection *selec = malloc(sizeof(struct selection));
    if (selec == NULL) {
        print_error("Mémoire saturée.");
        return NULL;
    }

    selec->w = w;
    selec->h = h;
    selec->pixels = malloc( sizeof(unsigned int) * w*h );
    memset(selec->pixels, 0, sizeof(unsigned int) * w*h);
    selec->selected_pixels_count = 0;
    selec->min_x = w;
    selec->min_y = h;
    selec->max_x = -1;
    selec->max_y = -1;
   
    return selec;
}


/********************/
/*   Destructeur    */
/********************/

void destroy_selection(struct selection* selec) {
    if(selec != NULL) {
        free(selec->pixels);
        free(selec);
    }
}

/*********************/
/* Getters / Setters */
/*********************/

static int get_id(const struct selection* selec, int x, int y) {
    return selec->pixels[y*selec->w + x];
}

static int set_id(const struct selection* selec, int x, int y, int id) {
    return selec->pixels[y*selec->w + x] = id;
}

int get_selection_width(const struct selection* selec) {
    return selec->w;
}

int get_selection_height(const struct selection* selec) {
    return selec->h;
}

void get_select_bounds(const struct selection* selec, int* min_x, int* min_y, int* max_x, int* max_y) {
    *min_x = selec->min_x;
    *min_y = selec->min_y;
    *max_x = selec->max_x;
    *max_y = selec->max_y;
}
                                

int distance(struct selection* selec, int x1, int y1, int x2, int y2) {
    int p1 = get_id(selec, x1, y1);
    int p2 = get_id(selec, x2, y2);
    if( p1 > p2 )
        return p1 - p2;
    else
        return p2 - p1;
}

/********************/
/*     Selection    */
/********************/

short select_pixel(struct selection* selec, int x, int y) {
    if( x > selec->w || y > selec->h || x < 0 || y < 0 || get_id(selec,x,y) != 0)
        return 0;

    // On vérifie si les bornes changent
    if( x < selec->min_x )
        selec->min_x = x;

    if( y < selec->min_y )
        selec->min_y = y;

    if( x > selec->max_x )
        selec->max_x = x;
    
    if( y > selec->max_y )
        selec->max_y = y;

    // On compte
    selec->selected_pixels_count++;
    
    // On change la valeur
    set_id(selec, x, y, selec->selected_pixels_count);

    return 1;
}

/*
 * Algorithme de Bresenham
 */
short select_line_no_cross(struct selection* selec, int x1, int y1, int *x2, int *y2) {
    
    // Iterators, counters required by algorithm
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    
    // Calculate line deltas
    dx = *x2 - x1;
    dy = *y2 - y1;
    
    // Create a positive copy of deltas (makes iterating easier)
    dx1 = dx > 0 ? dx : -dx;
    dy1 = dy > 0 ? dy : -dy;

    // Calculate error intervals for both axis
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    // The line is X-axis dominant
    if(dy1 <= dx1) {

        // Line is drawn left to right
        if (dx >= 0) {
            x = x1; y = y1; xe = *x2;
        } else { // Line is drawn right to left (swap ends)
            x = *x2; y = *y2; xe = x1;
        }

        if( x != x1 && !select_pixel(selec, x, y) ) {
            *x2 = x;
            *y2 = y;
            return 0;
        }
    
        // Rasterize the line
        for (i = 0; x < xe; i++) {
            x = x + 1;
            
            // Deal with octants...
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }

            // Draw pixel from line span at
            // currently rasterized position
            if( !select_pixel(selec, x, y) ) {
                *x2 = x;
                *y2 = y;
                return 0;
            }
 
        }

    } else { // The line is Y-axis dominant

        // Line is drawn bottom to top
        if (dy >= 0) {
            x = x1; y = y1; ye = *y2;
        } else { // Line is drawn top to bottom
            x = *x2; y = *y2; ye = y1;
        }

        if( x != x1 && !select_pixel(selec, x, y) ) {
            *x2 = x;
            *y2 = y;
            return 0;
        }
 
        // Rasterize the line
        for (i = 0; y < ye; i++) {
            y = y + 1;

            // Deal with octants...
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }

            // Draw pixel from line span at
            // currently rasterized position
            if( !select_pixel(selec, x, y) ) {
                *x2 = x;
                *y2 = y;
                return 0;
            }
        }
    }
    return 1;
 }

short unselect(struct selection* selec, int x, int y) {
    if( x > selec->w || y > selec->h || x < 0 || y < 0 || get_id(selec, x, y) == 0)
        return 0;

    set_id(selec, x, y, 0);
    return 1;
}

short is_selected(const struct selection* selec, int x, int y) {
    if( x > selec->w || y > selec->h || x < 0 || y < 0 ) {
        fprintf(stderr, "debug info: is_selected out of bounds: x=%d y=%d.\n", x, y);
        return 0;
    }

    return get_id(selec, x, y) != 0;
}


short unselect_all_before(struct selection* selec, int x, int y) {
    if( x > selec->w || y > selec->h || x < 0 || y < 0 ) {
        fprintf(stderr, "debug info: unselect_all_before out of bounds: x=%d y=%d.\n", x, y);
        return 0;
    }

    int size = selec->w * selec->h;
    int id = get_id(selec, x, y);
    
    for(int i=0; i<size; i++) {
        if( selec->pixels[i] < id )
            selec->pixels[i] = 0;
    }

    return 1;
}

/*
 * Selectionne toutes les pixels, délimités par les pixels déjà selectionnés. 
 */
static void selection_expansion(struct selection* selec, int startX, int startY) {

    struct stack stack;
    stack.head = NULL;
    add(&stack, startX, startY);

    int x, y;
    
    while(stack.head != NULL) {
        get(&stack, &x, &y);

        if( x >= selec->w || y >= selec->h || x < 0 || y < 0 || is_selected(selec, x, y))
            continue;

        select_pixel(selec, x, y);
        add(&stack, x, y-1);
        add(&stack, x, y+1);
        add(&stack, x-1, y);
        add(&stack, x+1, y);
        
    }

    //printf("Expand %d %d\n", x, y);
  
}

short select_area(struct selection* selec, int startX, int startY) {
    if( startX > selec->w || startY > selec->h || startX < 0 || startY < 0 ) {
        fprintf(stderr, "debug info: select_area out of bounds: x=%d y=%d.\n", startX, startY);
        return 0;
    }

    int x = startX;
    int y = startY;

    char entered = 0;
    
    // On sonde au dessus
    if(startY >= 0) {
        for(y = startY; y >= 0; y--) {
            for(x = 0; x < selec->w; x++)
                if( is_selected(selec, x, y) ) {
                    if(!entered) {
                        entered = 1;
                        while(x < selec->w && is_selected(selec, x, y) )
                            x++;
                    
                    } else {
                        x--;
                        selection_expansion(selec, x, y);
                        return 1;
                    }
                }
            // Si on a croisé une ligne, on continue (si on arrive ici on
            // est passé sur une ligne sans croisement)
            if(entered)
                entered = 0;
            // Si la ligne était vide, on s'arrette
            else
                break;
        }
    }

    // On sonde en dessous
    if(startY < (selec->h)-1) {
        for(y = startY+1; y < selec->h; y++) {
            for(x = 0; x < selec->w; x++)
                if( is_selected(selec, x, y) ) {
                    if(!entered) {
                        entered = 1;
                        while(x < selec->w && is_selected(selec, x, y) )
                            x++;
                    
                    } else {
                        x--;
                        selection_expansion(selec, x, y);
                        return 1;
                    }
                }
            // Si on a croisé une ligne, on continue (si on arrive ici on
            // est passé sur une ligne sans croisement)
            if(entered)
                entered = 0;
            // Si la ligne était vide, on s'arrette
            else
                break;
        }
    }

    fprintf(stderr, "debug: select_area failed.\n");
    
    return 0;
}
