//
// Created by clestrat on 20/05/2021.
//

#include "Menu.h"

/**
 * Cette fonction affiche le menu principal et tous les sous-menus.
 *
 * @param rubiks Un pointeur vers le rubik's cube actuellement en cours d'utilisation
 */
void show_menu(rubiks_side *rubiks)
{
    int start_choice, end_choice = true, move_choice, side_choice;

    // A chaque fois qu'on affiche le menu, on commence par ré-afficher l'état actuel du cube.
    draw_rubiks(rubiks);

    // Gestion des choix du menu principal
    while (end_choice)
    {
        printf("Faites votre choix (attention vous ne pouvez rentrer que des chiffes comme choix).\n");
        printf("1-> Mélanger le rubiks.\n");
        printf("2-> Résoudre le rubiks.\n");
        printf("3-> Faire vos propre mouvements.\n");
        printf("4-> Placer les couleurs.\n");
        printf("5-> Afficher le rubiks\n");
        printf("6-> Quitter le programme\n");
        char tab[6] = {1, 2, 3, 4, 5, 6};
        start_choice = choice_menu(tab);

        printf("--------------------------------\n");
        // Choix des différents sous-menus.
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
                printf("1-> Mouvement horaire.\n");
                printf("2-> Mouvement antihoraire.\n");
                char tab2[2] = {1, 2};
                move_choice = choice_menu(tab2);

                printf("\n--------------------------------\n");

                switch (move_choice)
                {
                    case 1:
                        printf("1-> blanc.\n");
                        printf("2-> orange.\n");
                        printf("3-> vert.\n");
                        printf("4-> rouge.\n");
                        printf("5-> bleu.\n");
                        printf("6-> jaune.\n");

                        char tab3[6] = {1, 2, 3, 4, 5, 6};
                        side_choice = choice_menu(tab3);

                        move_side_clockwise(rubiks, side_choice - 1, false);
                        draw_rubiks(rubiks);

                        printf("\n--------------------------------\n");
                        break;

                    case 2:
                        printf("1-> blanc.\n");
                        printf("2-> orange.\n");
                        printf("3-> vert.\n");
                        printf("4-> rouge.\n");
                        printf("5-> bleu.\n");
                        printf("6-> jaune.\n");

                        char tab4[6] = {1, 2, 3, 4, 5, 6};
                        side_choice = choice_menu(tab4);

                        move_side_anticlockwise(rubiks, side_choice - 1, false);
                        draw_rubiks(rubiks);

                        printf("\n--------------------------------\n");
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
 *
 * @param rubiks Un pointeur vers le rubik's en cours de traitement.
 */

void choose_color(rubiks_side *rubiks){
    // liste des cubies disponibles pour être positionnés correctement.
    cubies liste_corner[24], liste_edge[24];
    int len_liste_corner = 0, len_liste_edge = 0;

    // création d'un rubiks cube de référence (déjà résolu, et que nous modifierons en fonction des étapes de la saisie)
    rubiks_side reference_rubiks[6];
    rubiks_creation(reference_rubiks);

    // On intialise tout le Rubik's avec la couleur grise, sauf les centres qui ne bougeront pas.
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            // si le cubie est un centre, il est déjà correctement positionné
            if(rubiks[i].cubie[j].type != CENTER) {
                // on lui retire sa couleur, pour ne plus la traiter par la suite.
                rubiks[i].cubie[j].color = NO_COLOR;
            }
        }
    }

    // on complète la liste des edge et des corners à l'aide du rubiks de référence
    len_liste_corner = creation_liste_cubie(reference_rubiks,liste_corner, CORNER);
    len_liste_edge = creation_liste_cubie(reference_rubiks, liste_edge, EDGE);

    // A partir d'ici, on va demander à l'utilisateur de  remplir le rubiks
    // On ne propose que les états disponibles à être entrés.
    for(int i = WHITE ; i <= YELLOW ; i++){
        for(int j = 0 ; j < 9 ; j++) {
            if(rubiks[i].cubie[j].type != CENTER && rubiks[i].cubie[j].color == NO_COLOR){
                // changer la couleur du cubie sélectionné
                rubiks[i].cubie[j].color = GREY;
                // dessiner le rubiks
                draw_rubiks(rubiks);

                //Si le cubie est une arête on donne les listes d'arêtes à choice_cubie
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
 * Cette fonction permet de récupérer le choix de l'utilisateur en fonction des cubies disponibles.
 * @param reference_rubiks Pointeur sur un rubik's de référence
 * @param rubiks Pointeur sur le rubik's de travail
 * @param type Type de cubie à placer
 * @param liste_cubie Liste des cubie disponibles
 * @param len_liste Longueur de la liste précédente
 * @param face Face du cubie à modifier
 * @param num_cubie Numéro du cubie à modifier
 */
void choice_cubie(rubiks_side *reference_rubiks, rubiks_side *rubiks, T_CUBIE_TYPE type, cubies *liste_cubie, int len_liste, int face, int num_cubie)
{
    char tabcolor[][30] = {WHT "W" RESET, ORG "O" RESET, GRN "G" RESET, ARED "R" RESET, BLU "B" RESET, YEL "Y" RESET};
    int choice;

    // imprimer la liste des cubies encore disponibles
    for(int i = 0; i < len_liste ;i++){
        printf("Choix %d : %s, %s", i, tabcolor[liste_cubie[i].color],
               tabcolor[reference_rubiks[liste_cubie[i].neighbours[0].num_side].cubie[liste_cubie[i].neighbours[0].num_cubie].color]);
        if(type == CORNER)
            printf(", %s",
                   tabcolor[reference_rubiks[liste_cubie[i].neighbours[1].num_side].cubie[liste_cubie[i].neighbours[1].num_cubie].color]);
        printf(" | ");
        // On regroupe les choix de menus, par 6 pour éclairer un peu les menus.
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
 * Cette fonction va créer la liste des cubies disponibles à la saisie utilisateur
 * @param rubiks Pointeur vers le rubik's de travail
 * @param liste Liste des cubies disponibles en sortie
 * @param type Type de cubie à travailler, soit EDGE, soit CORNER dans notre cas, puisque les centres sont placés d'avance.
 * @return
 */
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

/**
 * Purge des buffers de getchar(), car elle conserve les return du clavier. On les supprime donc.
 */
void clear_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/**
 * Cette fonction va laisser l'utilisateur choisir des entrées du menu parmi une liste de choix passée en paramètre.
 *
 * @param list_of_choices Liste de choix disponibles à la saisie
 * @return L'entrée choisit par l'utilisateur
 */
int choice_menu(char * list_of_choices)
{
    int choice = 0, good_choice = false;

    do
    {
        printf("Rentrez votre choix: ");
        choice = getchar();
        // On vide les buffers, sinon on prend minimum deux caractères.
        clear_buffer();
        // getchar renvoie le code ascii du caractère saisie. 0 est égal à 48, 1 = 49, etc. Donc, on retranche 48 au code ascii récupéré
        choice -= 48;

        for (int i = 0; i < sizeof(list_of_choices); i++)
        {
            if (list_of_choices[i] == choice)
            {
                good_choice = true;
            }
        }

//        if (!good_choice)
//        {
//            printf("\b");
//        }
    } while (!good_choice);
    return choice;
}