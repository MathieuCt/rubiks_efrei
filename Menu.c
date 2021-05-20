//
// Created by clestrat on 20/05/2021.
//

#include "Menu.h"

void show_menu(rubiks_side *rubiks)
{
    draw_rubiks(rubiks);
    int start_choice, end_choice = 1, move_choice, side_choice;

    while (end_choice)
    {
        printf("Fates votre choix (attention vous ne pouvez rezntrez que 1 ou 2 comme choix).\n");
        printf("1->Mélanger le rubiks.\n");
        printf("2->Résoudre le rubiks.\n");
        printf("3->Faire vos propre mouvements.\n");
        printf("Rentrez votre choix: ");
        scanf("%d", &start_choice);
        while (start_choice != 1 && start_choice != 2 && start_choice != 3)
        {
            printf("Rentrez votre choix: ");
            scanf("%d", &start_choice);
        }

        printf("--------------------------------\n");

        if (start_choice == 1)
        {
            mix_rubiks(rubiks);
            draw_rubiks(rubiks);
        }
        else if (start_choice == 2)
        {
            solve_rubiks(rubiks);
            draw_rubiks(rubiks);
        }
        else
        {
            printf("1->'move_side_clockwise'.\n");
            printf("2->'move_side_anticlockwise'.\n");
            printf("Rentrez votre choix: ");
            scanf("%d", &move_choice);
            while (move_choice != 1 && move_choice != 2)
            {
                printf("Rentrez votre choix: ");
                scanf("%d", &move_choice);
            }

            printf("--------------------------------\n");

            if (move_choice == 1)
            {
                printf("1->blanc.\n");
                printf("2->orange.\n");
                printf("3->vert.\n");
                printf("4->rouge.\n");
                printf("5->bleu.\n");
                printf("6->jaune.\n");
                printf("Rentrez votre choix: ");
                scanf("%d", &side_choice);
                while (side_choice != 1 && side_choice != 2 && side_choice != 3 && side_choice != 4 &&
                       side_choice != 5 && side_choice != 6)
                {
                    printf("Rentrez votre choix: ");
                    scanf("%d", &side_choice);
                }

                move_side_clockwise(rubiks, side_choice - 1);
                draw_rubiks(rubiks);
                printf("--------------------------------\n");
            }
            else
            {
                printf("1->blanc.\n");
                printf("2->orange.\n");
                printf("3->vert.\n");
                printf("4->rouge.\n");
                printf("5->bleu.\n");
                printf("6->jaune.\n");
                printf("Rentrez votre choix: ");
                scanf("%d", &side_choice);
                while (side_choice != 1 && side_choice != 2 && side_choice != 3 && side_choice != 4 &&
                       side_choice != 5 && side_choice != 6)
                {
                    printf("Rentrez votre choix: ");
                    scanf("%d", &side_choice);
                }

                move_side_anticlockwise(rubiks, side_choice - 1);
                draw_rubiks(rubiks);
                printf("--------------------------------\n");
            }
        }

        printf("Voulez vous continuer? (1/0): ");
        scanf("%d", &end_choice);
    }
}