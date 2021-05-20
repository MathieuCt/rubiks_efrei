//
// Created by clestrat on 20/05/2021.
//

#include "Menu.h"

void show_menu(rubiks_side *rubiks)
{
    draw_rubiks(rubiks);
    int choice = 0, choice2 = TRUE;

    printf("Fates votre choix (attention vous ne pouvez rezntrez que 1 ou 2 comme choix).\n");
    printf("Mélanger le rubiks = 1.\n");
    printf("Résoudre le rubiks = 2.\n");
    while (choice != 1 && choice != 2)
    {
        printf("Rentrez votre choix: ");
        scanf("%d", &choice);
    }

    if (choice == 1)
    {
        mix_rubiks(rubiks);
        draw_rubiks(rubiks);
    }
    else
    {
        solve_rubiks(rubiks);
        draw_rubiks(rubiks);
    }

    printf("Voulez vous continuer? (1/0): ");
    scanf("%d", &choice2);

    if (choice2 == 1)
    {
        show_menu(rubiks);
    }
    else
    {
        exit(0);
    }
}