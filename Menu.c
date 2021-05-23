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
        printf("Faites votre choix (attention vous ne pouvez rentrer que des chiffes comme choix).\n");
        printf("1->Mélanger le rubiks.\n");
        printf("2->Résoudre le rubiks.\n");
        printf("3->Faire vos propre mouvements.\n");
        printf("4->Placer les couleurs.\n");
        printf("5->Afficher le rubiks\n");
        printf("6->Quitter le programme\n");
        //printf("Rentrez votre choix: ");
        /*do
        {
            start_choice = getchar();
        } while (start_choice != '1' && start_choice != '2' && start_choice != '3' && start_choice != '4' && start_choice != '5');*/
        char tab[6] = {1, 2, 3, 4, 5, 6};
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
                printf("1->Mouvement horaire.\n");
                printf("2->Mouvement antihoraire.\n");
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

                        move_side_clockwise(rubiks, side_choice - 1, false);
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

                        move_side_anticlockwise(rubiks, side_choice - 1, false);
                        draw_rubiks(rubiks);

                        printf("--------------------------------\n");
                        break;

                    default:
                        break;
                }
                break;

            case 4:
                choose_color(rubiks);
                break;

            case 5:
                draw_rubiks(rubiks);
                break;

            case 6:
                end_choice = FALSE;
                break;

            default:
                break;
        }
    }
}

/**
 * Cette fonction permet à l'utilisateur de remplir un cube
 */
void choose_color(rubiks_side *rubiks){
    // liste des cubie disponibles pour êtres positioner
    cubies liste_corner[24], liste_edge[24];
    int len_liste_corner = 0, len_liste_edge = 0;

    // création d'un rubiks cube de référence (déjà résolu
    rubiks_side reference_rubiks[6];
    rubiks_creation(reference_rubiks);
    //initialisation avec la couleur grise
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            // si le cubie est un centre, il est déjà correctement positionné
            if(rubiks[i].cubie[j].type != CENTER) {
                // on lui retire sa couleur
                rubiks[i].cubie[j].color = NO_COLOR;
            }
        }
    }
    // on complète la liste des edge et des corners à l'aide du rubiks de référence
    len_liste_corner = creation_liste_cubie(reference_rubiks,liste_corner, CORNER);
    len_liste_edge = creation_liste_cubie(reference_rubiks, liste_edge, EDGE);
    //remplir le rubiks
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            if(rubiks[i].cubie[j].type != CENTER && rubiks[i].cubie[j].color == NO_COLOR){
                // changer la couleur du cubie sélectionné
                rubiks[i].cubie[j].color = GREY;
                // dessiner le rubiks
                draw_rubiks(rubiks);

                //Si le cubie est une arête on donne les liste d'arête à choice_cubie
                if(rubiks[i].cubie[j].type == EDGE){
                    choice_cubie(reference_rubiks, rubiks, rubiks[i].cubie[j].type, liste_edge, len_liste_edge, i,j);
                    // mettre à jour les cubies disponibles
                    len_liste_edge = creation_liste_cubie(reference_rubiks,liste_edge, EDGE);
                }
                if(rubiks[i].cubie[j].type == CORNER){
                    choice_cubie(reference_rubiks, rubiks, rubiks[i].cubie[j].type, liste_corner, len_liste_corner, i,j);
                    // mettre à jour les cubies disponibles
                    len_liste_corner = creation_liste_cubie(reference_rubiks,liste_corner, CORNER);
                }
            }
        }
    }
}

/**
 * permet de récupérer le choix de l'utilisateur
 * @param reference_rubiks pointeur sur un rubiks
 * @param rubiks pointeur sur un rubiks
 * @param type type de cubie à placer
 * @param liste des cubie disponibles
 * @param longueur de la liste
 * @param face du cubie à modifier
 * @param numéro du cubie à modifier
 */
void choice_cubie(rubiks_side *reference_rubiks, rubiks_side *rubiks, T_CUBIE_TYPE type, cubies *liste_cubie, int len_liste, int face, int num_cubie)
{
    char tabcolor[][30] = {WHT "W" RESET, ORG "O" RESET, GRN "G" RESET, ARED "R" RESET, BLU "B" RESET, YEL "Y" RESET};
    int choice;

    // imprimer la liste des possibilités des cubies disponibles
    for(int i = 0; i < len_liste ;i++){
        printf("Choix %d : %s, %s", i, tabcolor[liste_cubie[i].color],
               tabcolor[reference_rubiks[liste_cubie[i].neighbours[0].num_side].cubie[liste_cubie[i].neighbours[0].num_cubie].color]);
        if(type == CORNER)
            printf(", %s",
                   tabcolor[reference_rubiks[liste_cubie[i].neighbours[1].num_side].cubie[liste_cubie[i].neighbours[1].num_cubie].color]);
        printf(" | ");
        if(i % 6 == 0 && i != 0){
            printf("\n");
        }
    }
    printf("\n");
    // récupérer le choix de l'utilisateur
    do
    {
        printf("Rentrez votre choix:");
        scanf("%d", &choice);
        // Vérifier qu'on n'a bien que des chiffres, et qu'ils sont entre 0 et x
    } while (choice < 0 || choice > len_liste);


    // mettre à jour le rubiks
    rubiks[face].cubie[num_cubie].color = liste_cubie[choice].color;
    rubiks[rubiks[face].cubie[num_cubie].neighbours[0].num_side].cubie[rubiks[face].cubie[num_cubie].neighbours[0].num_cubie].color =
            reference_rubiks[liste_cubie[choice].neighbours[0].num_side].cubie[liste_cubie[choice].neighbours[0].num_cubie].color;

    // mettre à jour le rubiks cube de référence
    reference_rubiks[liste_cubie[choice].cubie_side].cubie[liste_cubie[choice].num].color = NO_COLOR;
    reference_rubiks[liste_cubie[choice].neighbours[0].num_side].cubie[liste_cubie[choice].neighbours[0].num_cubie].color = NO_COLOR;

    // dans le cas d'un corner
    if(type == CORNER) {
        rubiks[rubiks[face].cubie[num_cubie].neighbours[1].num_side].cubie[rubiks[face].cubie[num_cubie].neighbours[1].num_cubie].color =
                reference_rubiks[liste_cubie[choice].neighbours[1].num_side].cubie[liste_cubie[choice].neighbours[1].num_cubie].color;
        reference_rubiks[liste_cubie[choice].neighbours[1].num_side].cubie[liste_cubie[choice].neighbours[1].num_cubie].color = NO_COLOR;
    }
}

/**
 *
 *
 * */
int creation_liste_cubie(rubiks_side * rubiks,cubies * liste, T_CUBIE_TYPE type){

    int len_liste = 0;
    for(int i = WHITE ; i <= YELLOW ; i++) {
        for (int j = 0; j < 9; j++) {
            if(rubiks[i].cubie[j].color != NO_COLOR)
                // on complète la liste des edge et des corners à l'aide du rubiks de référence
                if (rubiks[i].cubie[j].type == type) {
                    liste[len_liste] = rubiks[i].cubie[j];
                    len_liste++;
            }
        }
    }
    return len_liste;
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