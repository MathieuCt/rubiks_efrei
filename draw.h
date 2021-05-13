//
// Created by clestrat on 26/04/2021.
//

#ifndef RUBIKS_EFREI_DRAW_H
#define RUBIKS_EFREI_DRAW_H
#include <ncurses.h>
#include "rubiks.h"

// Nombre de lignes graphique pour les faces du cube (La première pour U, la troisième pour D, la deuxième pour le reste.
#define RUBIK_LINES 3
// Nombre de colonnes. La deuxième ligne comporte 4 faces.
#define RUBIK_COLS 4

// Taille d'un carré du Rubik's cube
#define SQ_HEIGHT 4
#define SQ_WIDTH 8

// Nombre de carrés dans un Rubik's cube. A mon avis, ne servira pas.
#define SQUARES ((RUBIK_LINES * 3) * (RUBIK_COLS * 3))

// Nombre de couleurs gérés par le terminal, nécessaire pour faire tourner le programme.
#define MIN_COLORS_NUMBER 256

// Les erreurs possibles lors de la vérification du terminal.
#define TERM_NOT_BIG_ENOUGH 1
#define TERM_HAS_NO_COLORS 2
#define TERM_HAS_NOT_ENOUGH_COLORS 3

// Ne servira probablement pas, c'est juste un test.
extern WINDOW *BOARD[SQUARES];

// La définition des couleurs possibles, gérées dans draw.c
extern const short BLACK_ON_WHITE;
extern const short BLACK_ON_ORANGE;
extern const short BLACK_ON_GREEN;
extern const short BLACK_ON_RED;
extern const short BLACK_ON_BLUE;
extern const short BLACK_ON_YELLOW;

// Nombre de lignes détectées dans le terminal
extern short NB_LINES;
// Nombre de colonnes détectées dans le terminal
extern short NB_COLS;

int check_and_set_term(void);

void set_colors(void);

void create_board(void);

void destroy_board(void);

void detect_resize(__attribute__((unused)) int);

void rubiks_display(struct rubiks_side *rubiks);

void draw_rubiks(struct rubiks_side *rubiks);

#endif //RUBIKS_EFREI_DRAW_H
