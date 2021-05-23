/**
* @file draw.c
* @author Mathieu CHANTOT et Clément LE STRAT
* @date 7 Mai 2021
* @brief Dans ce fichier, on gère les différents affichages du Rubik's Cube.
*/

#include "draw.h"
#include "rubiks.h"

// Définitions pour nCurses
WINDOW *BOARD[SQUARES];
// Définition des indices des couleurs utilisées avec nCurses
/**
 * Écriture noire sur blanc, pour nCurses
 */
const short BLACK_ON_WHITE = 1;
/**
 * Écriture noire sur orange, pour nCurses
 */
const short BLACK_ON_ORANGE = 2;
/**
 * Écriture noire sur vert, pour nCurses
 */
const short BLACK_ON_GREEN = 3;
/**
 * Écriture noire sur rouge, pour nCurses
 */
const short BLACK_ON_RED = 4;
/**
 * Écriture noire sur bleu, pour nCurses
 */
const short BLACK_ON_BLUE = 5;
/**
 * Écriture noire sur jaune, pour nCurses
 */
const short BLACK_ON_YELLOW = 6;

/**
 * Taille de l'écran nCurses
 */
short NB_LINES;
short NB_COLS;

/**
 * Détection de l'événement de changement de taille d'une fenêtre. L'évenement est non géré, pour le moment.
 *
 * @param dummy Paramètre inutilisé. Il est passé par la fonction d'appel des évènements sur une fenêtre
 */
void detect_resize(__attribute__((unused)) int dummy)
{
    printf("Resized...\n");
}

/**
 * Définitions des couleurs pour nCurses
 */
void set_colors(void)
{
    /* Création des couleurs écriture, couleur background */
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLACK_ON_ORANGE, COLOR_BLACK, 208); // Orange n'est pas franchement défini...
    init_pair(BLACK_ON_GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLACK_ON_RED, COLOR_BLACK, COLOR_RED);
    init_pair(BLACK_ON_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLACK_ON_YELLOW, COLOR_BLACK, 226); // Le COLOR_YELLOW n'est pas du jaune...
}

/**
 * Vérification du terminal, pour voir si il pourra faire tourner le programme avec nCurses
 *
 * @return 0 si OK, sinon retourne une erreur différente de 0
 */
int check_and_set_term(void)
{
    // Il faudra vérifier que l'on calcule correctement la taille de la fenêtre que nous attendons.
    NB_LINES = SQ_HEIGHT * RUBIK_LINES * 3; // Il faut calculer la taille du menu, après.
    NB_COLS = SQ_WIDTH * RUBIK_COLS * 3;

    // Vérification de la taille de la console
    if ((LINES < NB_LINES) || (COLS < NB_COLS))
    {
        return TERM_NOT_BIG_ENOUGH;
    }

    // Vérifie si le terminal sait gérer les couleurs
    if (!has_colors()) {
        return TERM_HAS_NO_COLORS;
    }

    // Vérifie combien de couleur sont supportées
    start_color();
    if (COLOR_PAIRS < MIN_COLORS_NUMBER)
    {
        return TERM_HAS_NOT_ENOUGH_COLORS;
    }

    // Initialise les couleurs
    set_colors();

    return 0;
}

/**
 * Fonction de test pour nCurses, qui permet de déplacer une couleur à partir de :
 * - line, col coordonnées du cube à modifier dans la matrice de l'écran
 * - cube_x, cube_y coordonnées x, y du cube à modifier
 * - color : Nouvelle couleur à appliquer
 * @param line Ligne de la matrices nCurses
 * @param col Colonne de la matrice nCurses
 * @param cube_x Coordonnée X du cube à modifier
 * @param cube_y Coordonnée Y du cube à modifier
 * @param color Nouvelle couleur à appliquer
 */
void change_color(short line, short col, short cube_x, short cube_y, short color)
{
    WINDOW *sub[3 * 3];
    int x, y, orig_x, orig_y, start_y, start_x;
    orig_x = col * 3 * SQ_WIDTH;
    orig_y = line * 3 * SQ_HEIGHT;

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if ((x == cube_x) && (y == cube_y))
            {
                start_x = orig_x + (x * SQ_WIDTH);
                start_y = orig_y + (y * SQ_HEIGHT);
                wbkgd(sub[x + y], COLOR_PAIR(color));
                wrefresh(sub[x + y]);
            }
        }
    }
}

/**
 * Fonction de test nCurses pour créer la face uniforme d'un cube dans une couleur donnée
 * @param line Ligne de la matrice nCurses dans laquelle dessiner le cube
 * @param col Colonne de la matrice nCurses dans laquelle dessiner le cube
 * @param color Couleur à appliquer sur le cube
 * @param name Nom de la face, à afficher dans le cubie central
 */
void create_rubik_side(short line, short col, short color, char name)
{
    int x, y, i, j;
    int orig_x, orig_y, start_y, start_x;
//    WINDOW *test;
    WINDOW *sub[3 * 3];

    orig_x = col * 3 * SQ_WIDTH;
    orig_y = line * 3 * SQ_HEIGHT;
//    test = newwin(3 * SQ_HEIGHT, 3 * SQ_WIDTH, start_y, start_x);
    for (x = 0; x < 3; x++)
    {
        start_x = orig_x + (x * SQ_WIDTH);
        for (y = 0; y < 3; y++)
        {
            start_y = orig_y + (y * SQ_HEIGHT);
            sub[x + y] = newwin(SQ_HEIGHT, SQ_WIDTH, start_y, start_x);
            box(sub[x + y], 0, 0);
            wbkgd(sub[x + y], COLOR_PAIR(color));
            if (x == 1 && y ==1)
            {
                for (i = 0; i < SQ_HEIGHT - 2; i++) {
                    for (j = 0; j < SQ_WIDTH - 2; j++)
                    {
                        mvwaddch(sub[x + y], i + 1, j + 1, name);
                    }
                }
            }
            wrefresh(sub[x + y]);
        }

    }
    curs_set(0); // Curseur invisible
//    box(test, 0, 0);
//    wbkgd(sub[1 + 1],COLOR_PAIR(color));
//    mvwaddch(sub[1 + 1], 2, 2, 'F');
//    wrefresh(test);
}

/**
 * Fonction de test qui permet d'afficher diverses choses sur l'écran nCurses
 */
void create_board(void)
{
    int i;
    int start_y, start_x;

    create_rubik_side(0, 1, BLACK_ON_WHITE, 'U');
    create_rubik_side(1, 0, BLACK_ON_ORANGE, 'L');
    create_rubik_side(1, 1, BLACK_ON_GREEN, 'F');
    create_rubik_side(1, 2, BLACK_ON_RED, 'R');
    create_rubik_side(1, 3, BLACK_ON_BLUE, 'B');
    create_rubik_side(2, 1, BLACK_ON_YELLOW, 'D');
    change_color(1, 0, 0, 0,BLACK_ON_RED);
    getch();
    clear();
    refresh();

    start_y = 0;
    for (i = 0; i < 10; i++) {
        start_x = i * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, start_y, start_x);
    }

    start_y = SQ_HEIGHT;
    for (i = 10; i < 20; i++) {
        start_x = (19 - i) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, start_y, start_x);
    }

    start_y = 2 * SQ_HEIGHT;
    for (i = 20; i < SQUARES; i++) {
        start_x = (i - 20) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, start_y, start_x);
    }

    for (i = 0; i < SQUARES; i++) {
        box(BOARD[i], 0, 0);
        if(i % 2 == 0)
            wbkgd(BOARD[i],COLOR_PAIR(BLACK_ON_ORANGE));
        else
            wbkgd(BOARD[i],COLOR_PAIR(BLACK_ON_WHITE));
        wrefresh(BOARD[i]);
    }
}

/**
 * Fonction de test liée à create_board, qui permet de libérer les ressources et la mémoire.
 * <br><em><b>Attention, cette fonction n'est pas à jour et ne libère pas correctement les choses</b></em>
 */
void destroy_board(void)
{
    int i;

    /* erase every box and delete each window */
    for (i = 0; i < 30; i++) {
        wborder(BOARD[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(BOARD[i]);
        delwin(BOARD[i]);
    }
}

/**
 * Fonction de débuggage, permet d'afficher les positions après des mouvements.
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void rubiks_display(rubiks_side *rubiks){
    int face, cubie;
    for(face = 0; face < 6 ; face++){
        printf("\n\n\n");
        rubiks[face].side;
        for(cubie = 0 ; cubie < 9 ; cubie++){
            printf("num :%d, x : %d, y : %d, type : %d, color : %d, voisin1(side): %d, voisin1(num) : %d voisin2(side): %d, voisin2(num) : %d\n",
                   rubiks[face].cubie[cubie].num,
                   rubiks[face].cubie[cubie].x,
                   rubiks[face].cubie[cubie].y,
                   rubiks[face].cubie[cubie].type,
                   rubiks[face].cubie[cubie].color,
                   rubiks[face].cubie[cubie].neighbours[0].num_side,
                   rubiks[face].cubie[cubie].neighbours[0].num_cubie,
                   rubiks[face].cubie[cubie].neighbours[1].num_side,
                   rubiks[face].cubie[cubie].neighbours[1].num_cubie);
        }
    }

}

/**
 * Dessine le rubik's Cube au format texte ANSI (pas au format nCurses)
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void draw_rubiks(rubiks_side *rubiks)
{
    // Définition des couleurs "ANSI" pour pouvoir écrire les cubies en couleur
    // A chaque fois, on défini la couleur à utiliser, suivi de la lettre du cubie, suivi d'un reset pour que la couleur
    // revienne à celle par défaut.
    char tabcolor[][30] = {WHT "W" RESET, ORG "O" RESET, GRN "G" RESET, ARED "R" RESET, BLU "B" RESET, YEL "Y" RESET, GRY "?", " "};

    printf("\n--------------\n");
    // On "imprime" face par face, et cubie par cubie.
    printf("    %s%s%s       \n",
           tabcolor[rubiks[WHITE].cubie[0].color],
           tabcolor[rubiks[WHITE].cubie[1].color],
           tabcolor[rubiks[WHITE].cubie[2].color]);
    printf("    %s%s%s       \n",
           tabcolor[rubiks[WHITE].cubie[3].color],
           tabcolor[rubiks[WHITE].cubie[4].color],
           tabcolor[rubiks[WHITE].cubie[5].color]);
    printf("    %s%s%s       \n",
           tabcolor[rubiks[WHITE].cubie[6].color],
           tabcolor[rubiks[WHITE].cubie[7].color],
           tabcolor[rubiks[WHITE].cubie[8].color]);
/* On aurait pu faire des boucles plutôt que des tableaux en dur, mais ça ne change pas grand-chose et c'est moins clair.
      int i, j;
      for (i = WHITE; i <= BLUE; i++) {
        for (j = 0; j <= 2; j++) {
            printf("%s", tabcolor[rubiks[i].cubie[j].color]);
            if (j == 2) printf(" ");
            if (i * j == 8) printf("\n");
        }
    }*/
    printf("%s%s%s %s%s%s %s%s%s %s%s%s\n",
           tabcolor[rubiks[ORANGE].cubie[0].color],
           tabcolor[rubiks[ORANGE].cubie[1].color],
           tabcolor[rubiks[ORANGE].cubie[2].color],
           tabcolor[rubiks[GREEN].cubie[0].color],
           tabcolor[rubiks[GREEN].cubie[1].color],
           tabcolor[rubiks[GREEN].cubie[2].color],
           tabcolor[rubiks[RED].cubie[0].color],
           tabcolor[rubiks[RED].cubie[1].color],
           tabcolor[rubiks[RED].cubie[2].color],
           tabcolor[rubiks[BLUE].cubie[0].color],
           tabcolor[rubiks[BLUE].cubie[1].color],
           tabcolor[rubiks[BLUE].cubie[2].color]);
    printf("%s%s%s %s%s%s %s%s%s %s%s%s\n",
           tabcolor[rubiks[ORANGE].cubie[3].color],
           tabcolor[rubiks[ORANGE].cubie[4].color],
           tabcolor[rubiks[ORANGE].cubie[5].color],
           tabcolor[rubiks[GREEN].cubie[3].color],
           tabcolor[rubiks[GREEN].cubie[4].color],
           tabcolor[rubiks[GREEN].cubie[5].color],
           tabcolor[rubiks[RED].cubie[3].color],
           tabcolor[rubiks[RED].cubie[4].color],
           tabcolor[rubiks[RED].cubie[5].color],
           tabcolor[rubiks[BLUE].cubie[3].color],
           tabcolor[rubiks[BLUE].cubie[4].color],
           tabcolor[rubiks[BLUE].cubie[5].color]);
    printf("%s%s%s %s%s%s %s%s%s %s%s%s\n",
           tabcolor[rubiks[ORANGE].cubie[6].color],
           tabcolor[rubiks[ORANGE].cubie[7].color],
           tabcolor[rubiks[ORANGE].cubie[8].color],
           tabcolor[rubiks[GREEN].cubie[6].color],
           tabcolor[rubiks[GREEN].cubie[7].color],
           tabcolor[rubiks[GREEN].cubie[8].color],
           tabcolor[rubiks[RED].cubie[6].color],
           tabcolor[rubiks[RED].cubie[7].color],
           tabcolor[rubiks[RED].cubie[8].color],
           tabcolor[rubiks[BLUE].cubie[6].color],
           tabcolor[rubiks[BLUE].cubie[7].color],
           tabcolor[rubiks[BLUE].cubie[8].color]);
    printf("    %s%s%s       \n",
           tabcolor[rubiks[YELLOW].cubie[0].color],
           tabcolor[rubiks[YELLOW].cubie[1].color],
           tabcolor[rubiks[YELLOW].cubie[2].color]);
    printf("    %s%s%s       \n",
           tabcolor[rubiks[YELLOW].cubie[3].color],
           tabcolor[rubiks[YELLOW].cubie[4].color],
           tabcolor[rubiks[YELLOW].cubie[5].color]);
    printf("    %s%s%s       \n",
           tabcolor[rubiks[YELLOW].cubie[6].color],
           tabcolor[rubiks[YELLOW].cubie[7].color],
           tabcolor[rubiks[YELLOW].cubie[8].color]);
    printf("--------------\n");
}