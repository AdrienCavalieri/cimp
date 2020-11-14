#include "printer.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define RED "\e[31m"
#define YELLOW "\e[33m"
#define DEFAULT "\e[0m"

void print_error(const char* format, ...) {

    char sig[] = "<Erreur> ";
    char buff[strlen(RED) + strlen(sig) + strlen(format) + strlen(DEFAULT) + 1];
    sprintf(buff, "%s%s%s%s", RED, sig, format, DEFAULT);
    
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, buff, vargs);
    va_end(vargs);
    printf("\n");
   
}

void print_note(const char* format, ...) {

    char sig[] = "<Note> ";
    char buff[strlen(YELLOW) + strlen(sig) + strlen(format) + strlen(DEFAULT) + 1];
    sprintf(buff, "%s%s%s%s", YELLOW, sig, format, DEFAULT);
    
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, buff, vargs);
    va_end(vargs);
    printf("\n");
   
}

void print_toManyArgs(const char* command_name) {
    print_error("Trop d'arguments pour la commande \"%s\".", command_name);
}

void print_notEnoughArgs(const char* command_name) {
    print_error("Arguments manquant pour la commande \"%s\".", command_name);
}

void print_no_pic() {
    print_error("Aucune image n'est selectionnée, utilisez la commande \"select\" pour selectionner une image.");
}

void print_emptySelec() {
    print_error("La sélection est vide.");
}
                        
