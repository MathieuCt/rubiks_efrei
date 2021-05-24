/**
 * @file draw.h
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on trouve les headers utilisés dans draw.c.
 */

#ifndef RUBIKS_EFREI_DRAW_H
#define RUBIKS_EFREI_DRAW_H
#include <ncurses.h>
#include "rubiks.h"

// Configurations nCurses
// Nombre de lignes graphique pour les faces du cube (La première pour U, la troisième pour D, la deuxième pour le reste.
/**
 * @def RUBIK_LINES
 * @brief Permet de déterminer le nombre de lignes dans la grande matrice nCurses. Il y a trois lignes.
 */
#define RUBIK_LINES 3
// Nombre de colonnes. La deuxième ligne comporte 4 faces.
/**
 * @def RUBIK_COLS
 * @brief Permet de déterminer le nombre de colonnes dans la grande matrice nCurses. Il y a quatre colonnes.
 */
#define RUBIK_COLS 4

/** @def SQ_HEIGHT
    @brief Hauteur en nombre de caractères d'un cubie avec nCurses
*/
#define SQ_HEIGHT 4
/** @def SQ_WIDTH
    @brief Largeur en nombre de caractères d'un cubie avec nCurses
*/
#define SQ_WIDTH 8

/** @def SQUARES
     @brief Nombre de carrés nCurses dans un Rubik's cube. Ne servira probablement pas.
*/
#define SQUARES ((RUBIK_LINES * 3) * (RUBIK_COLS * 3))

// Gestion des erreurs nCurses
/** @def MIN_COLORS_NUMBER
    @brief Nombre de couleurs gérés par le terminal (nCurses), nécessaire pour faire tourner le programme.
*/
#define MIN_COLORS_NUMBER 256

// Les erreurs possibles lors de la vérification du terminal.
/** @def TERM_NOT_BIG_ENOUGH
    @brief Le terminal (nCurses) n'est pas assez grand pour afficher le Rubik's cube avec nCurses
*/
#define TERM_NOT_BIG_ENOUGH 1
/** @def TERM_HAS_NO_COLORS
    @brief Le terminal (nCurses) ne gère pas les couleurs.
*/
#define TERM_HAS_NO_COLORS 2
/** @def TERM_HAS_NOT_ENOUGH_COLORS
    @brief Le terminal (nCurses) ne gère pas assez de couleurs.
*/
#define TERM_HAS_NOT_ENOUGH_COLORS 3

// Ne servira probablement pas, c'est juste un test (nCurses).
extern WINDOW *BOARD[SQUARES];

// La définition des couleurs nCurses possibles, gérées dans draw.c
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

/**
 * Les couleurs ANSI pour l'affichage du cube au format texte (non nCurses)
 * Références : https://en.wikipedia.org/wiki/ANSI_escape_code
 */
#define ARED   "\x1B[31m"
//    #define GRN   "\x1B[32m"
#define GRN   "\033[38;2;0;175;0m"
//    #define YEL   "\x1B[33m"
#define YEL "\033[38;2;255;255;0m"
#define BLU   "\x1B[34m"
//    #define WHT   "\x1B[37m"
#define WHT "\033[38;2;255;255;255m"
#define ORG "\033[38;2;255;165;0m"
#define GRY "\033[38;2;80;80m"
#define RESET "\x1B[0m"

// Les fonctions
int check_and_set_term(void);
void set_colors(void);
void change_color(short, short, short, short, short);
void create_rubik_side(short, short, short, char);
void create_board(void);
void destroy_board(void);
void detect_resize(__attribute__((unused)) int);
void rubiks_display(rubiks_side *rubiks);
void draw_rubiks(rubiks_side *rubiks);

#endif //RUBIKS_EFREI_DRAW_H
