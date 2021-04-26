//
// Created by clestrat on 19/04/2021.
//
#include <stdlib.h>
#include <signal.h>
#include <locale.h>

#include "draw.h"

int main()
{
    signal(SIGWINCH, detect_resize); // Détection du changement de taille du terminal

    /* Initialisation ncurses */
    setlocale(LC_ALL, "fr_FR.UTF-8"); // Gestion des caractères accentués
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Vérification de la taille du terminal, et la possibilité d'utiliser des couleurs */
    if (!check_term())
    {
        clear();
        refresh();
        endwin();
        exit(1);
    }

    attron(COLOR_PAIR(BLACK_ON_GREEN)); /* use the above combination */
    printw("   \n 1 \n   \n");
    attroff(COLOR_PAIR(BLACK_ON_GREEN)); /* turn color off */
    getch();
    clear();
    refresh();

    /* On créé le board Rubiks */
    create_board();
    mvwaddch(BOARD[14], 2, 2, 'F');
    curs_set(0); // Curseur invisible
    wrefresh(BOARD[14]);
    getch();
    destroy_board();
    clear();

    // On libère les fenêtres ncurses
    endwin();
    exit(0);
}