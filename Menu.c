//
// Created by clestrat on 20/05/2021.
//

#include "Menu.h"

void show_menu(rubiks_side *rubiks)
{
    draw_rubiks(rubiks);
    int start_choice, end_choice = TRUE, move_choice, side_choice;

    while (end_choice)
    {
        printf("Fates votre choix (attention vous ne pouvez rentrer que des chiffes comme choix).\n");
        printf("1->Mélanger le rubiks.\n");
        printf("2->Résoudre le rubiks.\n");
        printf("3->Faire vos propre mouvements.\n");
        printf("4->Placer les couleurs.\n");
        printf("5->Quitter le programme\n");
        //printf("Rentrez votre choix: ");
        /*do
        {
            start_choice = getchar();
        } while (start_choice != '1' && start_choice != '2' && start_choice != '3' && start_choice != '4' && start_choice != '5');*/
        char tab[5] = {1, 2, 3, 4, 5};
        start_choice = choice_menu(tab);

        printf("--------------------------------\n");

        switch (start_choice)
        {
            case 1:
                mix_rubiks(rubiks);
                draw_rubiks(rubiks);
                break;
            case 2:
                solve_rubiks(rubiks);
                draw_rubiks(rubiks);
                break;
            case 3:
                printf("1->'move_side_clockwise'.\n");
                printf("2->'move_side_anticlockwise'.\n");
                //printf("Rentrez votre choix: ");
                /*do
                {
                    move_choice  = getchar();
                }while (move_choice != '1' && move_choice != '2');*/
                char tab2[2] = {1, 2};
                move_choice = choice_menu(tab2);

                printf("--------------------------------\n");

                switch (move_choice)
                {
                    case 1:
                        printf("1->blanc.\n");
                        printf("2->orange.\n");
                        printf("3->vert.\n");
                        printf("4->rouge.\n");
                        printf("5->bleu.\n");
                        printf("6->jaune.\n");
                        //printf("Rentrez votre choix: ");
                        /*do
                        {
                            side_choice = getchar();
                        }while (side_choice != '1' && side_choice != '2' && side_choice != '3' && side_choice != '4' &&
                                  side_choice != '5' && side_choice != '6');*/
                        char tab3[6] = {1, 2, 3, 4, 5, 6};
                        side_choice = choice_menu(tab3);

                        move_side_clockwise(rubiks, side_choice - 1);
                        draw_rubiks(rubiks);

                        printf("--------------------------------\n");
                        break;

                    case 2:
                        printf("1->blanc.\n");
                        printf("2->orange.\n");
                        printf("3->vert.\n");
                        printf("4->rouge.\n");
                        printf("5->bleu.\n");
                        printf("6->jaune.\n");
                        //printf("Rentrez votre choix: ");
                        /*do
                        {
                            side_choice = getchar();
                        }while (side_choice != '1' && side_choice != '2' && side_choice != '3' && side_choice != '4' &&
                                   side_choice != '5' && side_choice != '6');*/
                        char tab4[6] = {1, 2, 3, 4, 5, 6};
                        side_choice = choice_menu(tab4);

                        move_side_anticlockwise(rubiks, side_choice - 1);
                        draw_rubiks(rubiks);

                        printf("--------------------------------\n");
                        break;
                }
                break;

            case 4:
                choose_color(rubiks);
                break;

            case 5:
                end_choice = FALSE;
                break;
        }
    }
}

/**
 * Cette fonction permet à l'utilisateur de remplir un cube
 */
void choose_color(rubiks_side *rubiks){
    // pour enregistrer la couleur choisie
    int color_choose;
    //initialisation avec la couleur grise
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            rubiks[i].cubie[j].color = GREY;
        }
    }
    //remplir le rubiks
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            // dessiner le rubiks
            draw_rubiks(rubiks);
            do{
                //demander une couleur
                printf("Choisir la couleur sur la face %d, numéro %d:", i, j);
                scanf("%d",&color_choose);
                // si la couleur est valide
            }while(color_choose > YELLOW || color_choose < WHITE);
            rubiks[i].cubie[j].color = color_choose;
        }
    }
}

void clear_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int choice_menu(char * soluce)
{
    int presence = false, choice = 0, good_choice = false;

    do
    {
        printf("Rentrez votre choix: ");
        choice = getchar();
        // On vide les buffers, sinon on prend minimum deux caractères.
        clear_buffer();
        // getchar renvoie le code ascii du caractère saisie. 0 est égal à 48, 1 = 49, etc. Donc, on retranche 48 au code ascii récupéré
        choice -= 48;

        for (int i = 0; i < sizeof(soluce); i++)
        {
            if (soluce[i] == choice)
            {
                good_choice = true;
            }
        }

        if (!good_choice)
        {
            printf("\b");
        }
    } while (!good_choice);
    return choice;
}