Interface
============================================================
**cimp**

```C
int main(int argc, char* args[]);
```

## UI

**window.h**

```C
struct window;


/****************/
/* Constructeur */
/****************/

/*
 * Crée une nouvelle fenêtre.
 */
struct window* create_window(int width, int height, const char* name);


/*****************/
/*  Destructeur  */
/*****************/

/*
 * Ferme la fenêtre et la libère.
 */
void destroy_window(struct window* win);


/*****************/
/*   Affichage   */
/*****************/

/*
 * Affiche l'image et la fenêtre est redimensionnée selon la taille de celle-ci.
 */
void show_picture(struct window* win, const struct picture* pic, const struct selection* selec);

/*
 * Enlève l'image de la fenêtre.
 */
void clear_window(struct window* win);


/****************/
/*  Visibilité  */
/****************/

/*
 * Affiche la fenêtre.
 */
void show_window(struct window* win);

/*
 * Fait passer la fenêtre au premier plan et lui donne le focus.
 */
void raise_window(struct window* win);

/*
 * Ferme la fenêtre.
 */
void close_window(struct window* win);


/****************/
/*    Getters   */
/****************/

/*
 * Retourne l'ID de la fenêtre.
 */
int get_window_id(const struct window* win);


/****************/
/*    Events    */
/****************/

/*
 * Vérifie si l'utilisateur a fermé une fenêtre. Renvoie l'id de la fenêtre fermée et 0 sinon.
 */
int is_closed();

/*
 * Séléctionne une zone de l'image à l'aide des mouements de la souris.
 * La sélection à été allouée, destroy_selection nécessaire.
 */
struct selection* trace_selection(struct window* win, const struct picture* pic);

/*
 * Attend tant que l'utilisateur n'appuie pas un des boutons de la souris.
 */
void waiting_for_press(int* x, int* y);

/*
 * Attend tant que l'utilisateur ne relâche pas un des boutons de la souris.
 */
void waiting_for_release(int* x, int* y);
```

**commandReader.h**

```C
// Ce module contient la liste des images chargées.

/*
 * Donne l'id d'une image et -1 si elle ne fait pas partie des images chargées.
 */
int get_picture_id(const struct picture* pic);

/*
 * Renvoie la fenêtre affichant l'image et NULL si il n'y en a pas.
 */
struct window* get_picture_window(const struct picture* pic);

/*
 * Affiche les images chargees avec leur id.
 */
void print_pictures_details();

/*
 * Execute une commande en fonction d'un liste d'argument (args[0] etant
 * le nom de la commande).
 */
short exec_command(int argc, const char* args[]);

/*
 * Initialise le lecteur de commande.
 */
void init_commandReader();

/*
 * Lit l'entree de l'utilisateur et la traite.
 */
void read_commandLine();
```

**select.h**

```C
/*
 * Selectionne un rectangle, construit à partir de 2 points,
 *  dans l'image pic et le stocke dans *selection. 
 */
short selectR(int x1, int y1, int x2, int y2, const struct picture* pic, struct selection** selection);

/*
 * Commande de selection d'images et de zones.
 */
short select_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length, struct selection** selection, struct picture** pic);

/*
 * Déselectionne la sélection courante.
 */
short unselect_command(int argc, struct selection** selection);
```

**show.h**

```C
/*
 * Affiche l'image selectionnée dans une nouvelle fenêtre ou bien dans une fenêtre préselectionnée.
 * Nécessite la selection courante pour la dessiner sur l'image.
 */
short show_command(int argc, const char* args[],
                   const struct picture* selected_pic,
                   struct window* windows[],
                   const struct picture* const loaded_pictures[], int size,
                   const struct selection* selection);

```

**userReader.h**

```C
//Convertit la chaine de charactère en entier avec l'affichage d'erreurs adaptées. Renvoie -1 en cas d'erreur.
int read_whole_int(const char* s);

/*
 * Convertit la chaine de charactère en partie de couleur (0-255) avec l'affichage 
 * d'erreurs adaptées. *field est utilisé pour stocker le résultat.
 * Renvoie -1 en cas d'erreur.
 */
short read_color_field(const char* s, unsigned char* field);

/*
 * Convertit la chaine de charactère en indice (-128 à 127) avec l'affichage 
 * d'erreurs adaptées. *res est utilisé pour stocker le résultat.
 * Renvoie -1 en cas d'erreur.
 */
short read_signed_char(const char* s, char* res);

/*
 * Convertit la chaine de charactère en entier avec l'affichage 
 * d'erreurs adaptées. *res est utilisé pour stocker le résultat.
 * Renvoie -1 en cas d'erreur.
 */
int read_whole_int(const char* s);

/*
 * Convertit la chaine de charactère en une couleur (destroy_color nécessaire) 
 * avec l'affichage d'erreurs adaptées. Renvoie NULL en cas d'erreur.
 */
struct color* read_color(const char** args, int size);

/*
 * Convertit la chaine de charactère en valeurs rgba (0-255) avec l'affichage 
 * d'erreurs adaptées. Renvoie -1 en cas d'erreur.
 */
short read_color_vals(const char** args, int size, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
```

## Save
**save.h**

```C
/*
 * Sauvegarde une image au chemin 'filename' avec le format 'format'.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short save(const struct picture* p, const char* filename, enum FORMAT format);

/*
 * Sauvegarde une image. Recupère l'id de l'image à sauvegarder dans args puis
 * récupère cette image dans picsl_list.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short save_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length);
```

**load.h**

```C
/*
 * Charge une image se trouvant au chemin path et la stocke dans *pic.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short load(const char* path, struct picture** pic);


/*
 * Charge les images se trouvant aux cheminx donnés dans args et les stockent dans *pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short load_command(int argc, const char* args[], struct picture* pics_list[], int pics_list_length);
```

**unload.h**

```C
/*
 * Décharge l'image pic_id en modifiant les structures/tableaux nécessaire.
 */
short unload(int pic_id, struct window* windows_list[], struct picture* pics_list[], int pics_list_length, struct picture** selected_pic, struct selection** selection);

/*
 * Décharge les images données dans args (représentées par leur id) en modifiant les 
 * structures/tableaux nécessaire.
 */
short unload_command(int argc, const char* args[], struct window* windows_list[], 
    				struct picture* pics_list[], int pics_list_length, 
					struct picture** selected_pic, struct selection** selec);
```

## Data
**picture.h**

```C
enum FORMAT {BMP, JPG, PNG};

#define DEFAULT_FORMAT BMP

/*************************************************/
/*                   Structure                   */
/*************************************************/

/*
 * Structure représentant une image.
 */
struct picture;


/*************************************************/
/*            Constructeur/Destructeur           */
/*************************************************/

/*
 * Créé une image à partir d'une image une existante.
 */
struct picture* create_picture_from_image(const char* path);

/*
 * Créé une image vide de dimension width*height.
 */
struct picture* create_picture(int width, int height);

/*
 * Supprime une image en liberant tous l'espace allouée pour celle-ci.
 */
void destroy_picture( struct picture* p);

/*************************************************/
/*                    Getters                    */
/*************************************************/


/*
 * Renvoie la largeur d'une image.
 */
int get_picture_width(const struct picture* p);

/*
 * Renvoie la hauteur d'une image.
 */
int get_picture_height(const struct picture* p);

/*
 * Renvoie le format d'une image.
 */
enum FORMAT get_picture_format(const struct picture* p);

/*
 * Renvoie le chemin d'une image. La chaine renvoyée est une
 * copie, un appel à free() est nécéssaire.
 */
char* get_picture_path(const struct picture* p);

/*
 * Renvoie la largeur d'une ligne (peut être différent de la
 * largeur pour des raison d'optimisation).
 */
int get_pitch(const struct picture* p);

/*
 * Renvoie le format utilisé pour le codage des pixels.
 */
int get_pixelFormat(const struct picture* p);


/*
 * Renvoie le tableau de pixels de picture.
 * La copie est obtenue avec malloc, free nécessaire.
 */
unsigned char* get_pixels(const struct picture* p);


/*************************************************/
/*             Modification de pixels            */
/*************************************************/


/*
 * Change la couleur du pixel en (x,y) par la couleur new_color.
 */
short change_pixel_color(const struct picture* p, int x, int y, const struct color* new_color);

/*
 * Renvoie la couleur du pixel en (x,y). La couleur renvoyée est une
 * copie, un appel à free() est nécéssaire.
 */
struct color* get_pixel_color(const struct picture* p, int x, int y);

/*
 * Change la taille de la surface de l'image.
 */
short set_size(struct picture* p, int w, int h);

/*
 * Coupe une partie de l'image.
 */
short crop_picture(struct picture* p, const struct selection* selec);
```

**color.h**

```C
struct color;

/*
 * Construit une couleur rgba (red, green, blue, alpha). 
 */
struct color* create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

/*
 * Construit une couleur rgba (red, green, blue, alpha) à partir d'une valeur hexadecimal 
 * (0x????????). 
 */
struct color* create_color_hex(uint32_t hexa_value);

/*
 * Libere la memoire occupee par une structure color. 
 */
void destroy_color(struct color* color);

/*
 * Remplis les unsigned char passes en parametre avec les valeurs rgba de color.
 */
void get_rgba(const struct color* color, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);

/*
 * Vérifie que les couleurs oldColor et newColor sont égales.
 */
short equalsColor(const struct color* oldColor, const struct color* newColor);
```
**selection.h**

```C
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
```

## Editing
### Move
**ccp.h**

```C
/*
 * Stocke la sélection selec de l'image p, puis efface celle-ci
 * dans p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short cut(struct picture* p, const struct selection* selec);


/*
 * Stocke la sélection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short copy(const struct picture* p, const struct selection* selec);


/*
 * Ajoute la sélection stockée dans la selection selec de l'image p. 
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short paste(struct picture* p, const struct selection* selec);


/*
 * Stocke la sélection 'selection' de l'image select_pic, puis efface celle-ci
 * dans select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short cut_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );


/*
 * Stocke la sélection 'selection' de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */ 
short copy_command(int argc, const char* args[], const struct picture* select_pic, const struct selection* selection );


/*
 * Ajoute la sélection stockée dans la selection 'selection' de l'image select_pic. 
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short paste_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );
```

**erase.h**

```C
/*
 * Efface la sélection selec dans l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short erase(struct picture* p, const struct selection* selec);


/*
 * Efface la sélection 'selection' dans l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short erase_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection );
```

**rotate.h**

```C
/*
 * Effectue une rotation sur l'image p (rotation de 90, 180 ou 270 degrés.)
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short rotate(struct picture* p, int angle);


/*
 * Effectue une rotation sur l'image select_pic (rotation de 90, 180 ou 270 degrés.)
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short rotate_command(int argc, const char* args[], struct picture* select_pic );
```

**symmetry.h**

```C
/*
 * enum représentant un axe de symétrie.
 */
enum symmetry_type {HORIZONTAL, VERTICAL};

/*
 * Effectue une symétrie sur l'image p, son type est donné par 'type'.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short symmetry(struct picture* p, enum symmetry_type type);

/*
 * Effectue une symétrie sur l'image select_pic, son type est donné par '-v' ou '-h' dans args.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short symmetry_command(int argc, const char* args[], struct picture* select_pic );
```

### Color

**negate.h**

```C
/*
 * Met la selection selec de l'image p en négatif.
 * 
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short negate(struct picture* p, const struct selection* selec);

/*
 * Met la selection selec de l'image select_pic en négatif.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short negate_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);
```

**bwconversion.h**

```C
/*
 * Met en noir et blanc la selection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short bw_conversion(struct picture* p, const struct selection* selec);

/*
 * Met en noir et blanc la selection selec de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short bw_conversion_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec );
```

**grayscale.h**

```C
/*
 * Met en niveau de gris la selection selec de l'image p.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short grayscale(struct picture* p, const struct selection* selec);

/*
 * Met en niveau de gris la selection selec de l'image select_pic.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short grayscale_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec );
```

**fill.h**

```C
/*
 * Remplit la selection selec de l'image p avec la couleur color.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short fill(struct picture* p, const struct selection* selec, const struct color* color);


/*
 * Remplit la selection selec de l'image select_pic avec la couleur donnée en argument (r g b a ou #rrggbbaa).
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short fill_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);```

**replaceColor.h**

```C
short replace_color(struct picture* p, const struct selection* select, const struct color* oldColor, const struct color* newColor);
short replace_color_command(int argc, const char* args[], struct picture* select_pic,const struct selection* selection);
```

**brightness.h**

```C
/*
 * Modifie la luminosité dans la selection selec de l'image p.
 * Le coefficient de liminosité est compris dans un char signé.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short brightness(struct picture* p,  const struct selection* selec, char coeff);

/*
 * Modifie la luminosité dans la selection selec de l'image select_pic.
 * Le coefficient de liminosité est compris dans un char signé.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short brightness_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);
```

**contrast.h**

```C
/*
 * Modifie le contraste dans la selection selec de l'image p.
 * Le coefficient de contraste est compris dans un char signé.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short contrast(struct picture* p,  const struct selection* selec, char contrastAmount);

/*
 * Modifie la luminosité dans la selection selec de l'image select_pic.
 * Le coefficient de contrast est compris dans un char signé.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short contrast_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selec);
```

### Size
**resize.h**

```C
/*
 * Redimensionne l'image p avec les dimensions newWidth et newHeight.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short resize(struct picture* p, int newWidth, int newHeight);


/*
 * Redimensionne l'image select_pic avec les dimensions données dans args (largeur et hauteur).
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short resize_command(int argc, const char* args[], struct picture* select_pic);
```

**crop.h**

```C
/*
 * Effectue un recadrage de l'image p en fonction de la selection selec.
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short crop(struct picture* p, const struct selection* selec);

/*
 * Effectue un recadrage de l'image select_pic en fonction de la selection selec.
 * argc et args représentent les arguments de la commande (similaire au main).
 *
 * Renvoie 0 en cas d'erreur et 1 sinon.
 */
short crop_command(int argc, const char* args[], struct picture* select_pic, const struct selection* selection);
```

## Utils
**printer.h**

```C
/*
 * Affiche une erreur avec fprintf(stderr,...) et ajoute 
 * le sigle "<Erreur> " en début de ligne et un '\n' en fin de ligne.
 */
void print_error(const char* format, ...);

/*
 * Affiche une erreur avec fprintf(stderr,...) et ajoute 
 * le sigle "<Note> " en début de ligne et un '\n' en fin de ligne.
 */
void print_note(const char* format, ...);

/*
 * Affiche un message d'erreur indiquant qu'il y a trop d'arguments.
 */
void print_toManyArgs(const char* command_name);

/*
 * Affiche un message d'erreur indiquant qu'il n'y a pas assez d'arguments.
 */
void print_notEnoughArgs(const char* command_name);

/*
 * Affiche un message d'erreur indiquant qu'aucune image n'est sélectionnée.
 */
void print_no_pic();

/*
 * Affiche un message d'erreur indiquant que la selection courante est vide.
 */
void print_emptySelec();
```