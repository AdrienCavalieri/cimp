#ifndef SELECTION_H
#define SELECTION_H

/*
 * Structure représenatant une selection.
 * Une sélection est semblable à une image, à la difference
 * qu'au lieu de stocker des pixels, stocke des id permetant de determiner
 * si un pixel est selectionné et quand il l'a été.
 */
struct selection;


/********************/
/*   Constructeur   */
/********************/

/*
 * Construit une sélection.
 */
struct selection* create_selection(int w, int h);

/********************/
/*   Destructeur    */
/********************/

/*
 * Détruit une sélection.
 */
void destroy_selection(struct selection* selec);

/********************/
/*      Getters     */
/********************/

/*
 * Renvoie la largeur de la sélection.
 */
int get_selection_width(const struct selection* selec);

/*
 * Renvoie la hauteur de la sélection.
 */
int get_selection_height(const struct selection* selec);

/*
 * Renvoie les bornes de la sélection. Utiles pour faire des parcours
 * plus efficaces.
 */
void get_select_bounds(const struct selection* selec, int* min_x, int* min_y, int* max_x, int* max_y);

/*
 * Renvoie la distance, en nombre de pixels sélectionnés, entre deux pixels.
 */
int distance(struct selection* selec, int x1, int y1, int x2, int y2);

/********************/
/*     Selection    */
/********************/

/*
 * Sélectionne le pixel en (x,y). 
 */
short select_pixel(struct selection* selec, int x, int y);

/*
 * Sélectionne les pixels sur la ligne (x1,y)(x2,y2). La ligne s'arrette si elle atteind
 * (x2,y2) ou si elle coupe un pixel dejà selectionné, stocke les coordonné de ce dernier
 * pixel dans x2 et y2.
 */
short select_line_no_cross(struct selection* selec, int x1, int y1, int* x2, int* y2);

/*
 * Désélectionne le pixel en (x,y). 
 */
short unselect(struct selection* selec, int x, int y);

/*
 * Renvoie 1 si le pixel (x,y) est sélectionné et 0 sinon.
 */
short is_selected(const struct selection* selec, int x, int y);

/*
 * Déselectionne tous les pixels ayant été sélectionné avant (x,y).
 */
short unselect_all_before(struct selection* selec, int x, int y);

/*
 * Cherche une zone délimitée par des pixels sélectionnés et la selectionne.
 */
short select_area(struct selection* selec, int startX, int startY);


#endif /* SELECTION_H */

