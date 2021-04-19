#include <ncurses.h>
#include <locale.h>
#include <menu.h>
#include <stdlib.h>

//int main(void)
//{
//    setlocale(LC_ALL, "fr_FR.UTF-8");
//    initscr();              // Initialise la structure WINDOW et autres paramètres
//    printw("Test pour voir ce que ça donne\n");  // Écrit Hello World à l'endroit où le curseur logique est positionné
//    refresh();              // Rafraîchit la fenêtre courante afin de voir le message apparaître
//    getch();                // On attend que l'utilisateur appuie sur une touche pour quitter
//    endwin();               // Restore les paramètres par défaut du terminal
//
//    return 0;
//}

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
};

int main()
{	ITEM **my_items;
    int c;
    bool choice;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;

    setlocale(LC_ALL, "fr_FR.UTF-8");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 25, "F1 to Exit");
    post_menu(my_menu);
    refresh();

    choice = false;
    while((c = getch()) != KEY_F(1))
    {
        switch(c)
        {	case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case KEY_ENTER:
                mvprintw(LINES - 2, 50, "Enter...");
                refresh();
                choice = true;
        }
        if(choice)
        {
            printf("* %d *", c);
            break;
        }
    }

    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();
}
