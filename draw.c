//
// Created by clestrat on 26/04/2021.
//
#include "draw.h"

WINDOW *BOARD[SQUARES];
const short BLACK_ON_WHITE = 1;
const short BLACK_ON_ORANGE = 2;
const short BLACK_ON_GREEN = 3;
const short BLACK_ON_RED = 4;
const short BLACK_ON_BLUE = 5;
const short BLACK_ON_YELLOW = 6;

short NB_LINES;
short NB_COLS;

void detect_resize(__attribute__((unused)) int dummy)
{
    printf("Resized...\n");
}

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

    /* put border on each window and refresh */

    for (i = 0; i < SQUARES; i++) {
        box(BOARD[i], 0, 0);
        if(i % 2 == 0)
            wbkgd(BOARD[i],COLOR_PAIR(BLACK_ON_ORANGE));
        else
            wbkgd(BOARD[i],COLOR_PAIR(BLACK_ON_WHITE));
        wrefresh(BOARD[i]);
    }
}

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