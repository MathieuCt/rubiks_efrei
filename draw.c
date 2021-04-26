//
// Created by clestrat on 26/04/2021.
//
#include <stdlib.h>
#include "draw.h"

WINDOW *BOARD[SQUARES];
const short BLACK_ON_GREEN = 1;
const short BLACK_ON_BLUE = 2;

void detect_resize(int dummy)
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
    init_pair(BLACK_ON_GREEN, COLOR_BLACK, COLOR_GREEN); /* create couleur écriture, couleur background */
    init_pair(BLACK_ON_BLUE, COLOR_BLACK, COLOR_BLUE);
    return true;
}

bool check_term(void)
{
    // Il faudra que l'on calcule la taille de la fenêtre que nous attendons.
    if ((LINES < 24) || (COLS < 80))
    {
        clear();
        endwin();
        printf("Votre terminal doit faire au moins 80x24\n");
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

void create_board(void)
{
    int i;
    int start_y, start_x;

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
            wbkgd(BOARD[i],COLOR_PAIR(1));
        else
            wbkgd(BOARD[i],COLOR_PAIR(2));
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