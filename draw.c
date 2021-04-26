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

void detect_resize(__attribute__((unused)) int dummy)
{
    printf("Resized...\n");
}

bool colors(void)
{
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        return false;
    }

    start_color();
    /* create couleur écriture, couleur background */
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLACK_ON_ORANGE, COLOR_BLACK, COLOR_RED | COLOR_YELLOW); // Orange, c'est du jaune mélangé à du rouge
    init_pair(BLACK_ON_GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLACK_ON_RED, COLOR_BLACK, COLOR_RED);
    init_pair(BLACK_ON_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLACK_ON_YELLOW, COLOR_BLACK, COLOR_YELLOW);
    return true;
}

bool check_term(void)
{
    // Il faudra que l'on calcule la taille de la fenêtre que nous attendons.
    short nb_lines = SQ_HEIGHT * (RUBIK_LINES + (RUBIK_LINES * 2)) + 20; // Il faut calculer la taille du menu, après.
    short nb_cols = SQ_WIDTH * (RUBIK_COLS + (RUBIK_COLS * 2));
    if ((LINES < nb_lines) || (COLS < nb_cols))
    {
        clear();
        endwin();
        printf("Votre terminal doit faire au moins %d colonnes x %d lignes\n", nb_cols, nb_lines);
        printf("Actuellement LINES : %d et COLS : %d\n", LINES, COLS);
        return false;
    }

    /* Gestion des couleurs */
    if (!colors())
    {
        return false;
    }
    return true;
}

void create_rubik_side(short line, short col, short color, char name)
{
    int x, y;
    int start_y, start_x;
    WINDOW *test;
    WINDOW *sub[3 * 3];

    start_x = col * SQ_WIDTH;
    start_y = line * SQ_HEIGHT;
    test = newwin(3 * SQ_HEIGHT, 3 * SQ_WIDTH, start_y, start_x);
    for (x = 0; x < 3; x++)
    {
        start_x = x * SQ_WIDTH;
        for (y = 0; y < 3; y++)
        {
            start_y = y * SQ_HEIGHT;
            sub[x + y] = newwin(SQ_HEIGHT, SQ_WIDTH, start_y, start_x);
            box(sub[x + y], 0, 0);
            wbkgd(sub[x + y],COLOR_PAIR(color));
            wrefresh(sub[x + y]);
        }

    }
    box(test, 0, 0);
    wbkgd(sub[1 + 1],COLOR_PAIR(color));
    mvwaddch(sub[1 + 1], 2, 2, 'F');
    wrefresh(test);
}

void create_board(void)
{
    int i;
    int start_y, start_x;

    create_rubik_side(0, 1, BLACK_ON_YELLOW, 'L');
    getch();

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