/**
* @file main.c
* @author Mathieu CHANTOT et Clément LE STRAT
* @date 7 Mai 2021
* @brief Programme principal qui gère le projet EFREI Rubik's Cube
*/

#include <stdlib.h>
#include <signal.h>
#include <locale.h>

#include "draw.h"
#include "rubiks.h"
#include "Menu.h"

/**
 * Définie si nous réalisons les affichages en mode texte (true) ou en mode nCurses (false)
 */
#define PRINT_TEXT_ONLY true

/**
 * Fonction principale du programme. Elle se contente d'afficher les menus. Soit en mode nCurses (non implémenté pour le moment)
 * soit en mode "texte" avec des couleurs ANSI.
 * @return 0
 */
int main()
{
    int term_error_type;
    int detected_nb_lines, detected_nb_cols, detected_color_pairs;

    signal(SIGWINCH, detect_resize); // Détection du changement de taille du terminal
    setlocale(LC_ALL, "fr_FR.UTF-8"); // Gestion des caractères accentués

    if (PRINT_TEXT_ONLY)
    {
        printf("Mode non graphique--------------------------------\n");
        rubiks_side rubiks[6];
        rubiks_creation(rubiks);

        show_menu(rubiks);
        //choose_color(rubiks);
        //rubiks_display(rubiks);
        // alterner les couleurs
        //alternate_color(rubiks);
        //mix_rubiks(rubiks);
        draw_rubiks(rubiks);
        //solve_rubiks(rubiks);
        //draw_rubiks(rubiks);
    }
    else
    {
        /* Mode nCurses */
        /* Initialisation ncurses */
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        /* Vérification de la taille du terminal, et la possibilité d'utiliser des couleurs */
        detected_nb_lines = LINES;
        detected_nb_cols = COLS;
        detected_color_pairs = COLOR_PAIRS;
        if ((term_error_type = check_and_set_term()) > 0) {
            clear();
            refresh();
            endwin();
            switch (term_error_type) {
                case TERM_NOT_BIG_ENOUGH:
                    printf("Votre terminal doit faire au moins %d colonnes x %d lignes\n", NB_COLS, NB_LINES);
                    printf("Actuellement, il fait,  %d colonnes x %d lignes\n", detected_nb_cols, detected_nb_lines);
                    break;
                case TERM_HAS_NO_COLORS:
                    printf("Votre terminal ne supporte pas les couleurs\n");
                    break;
                case TERM_HAS_NOT_ENOUGH_COLORS:
                    printf("Votre terminal ne supporte pas assez de couleurs (%d au lieux de %d minimum)",
                           detected_color_pairs, MIN_COLORS_NUMBER);
                    break;
                default:
                    printf("Erreur non gérée...");
                    break;
            }
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
    }
    exit(0);
}