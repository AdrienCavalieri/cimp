#ifndef PRINTER_H
#define PRINTER_H

#include <stdarg.h>

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

#endif /* PRINTER_H */
