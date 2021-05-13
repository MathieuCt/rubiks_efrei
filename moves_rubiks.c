//
// Created by clestrat on 06/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h"
#include "moves_rubiks.h"
#include "rubiks.h"

void move_coin(rubiks_side *rubiks, int side, int from, int to) {
    /*
     * Cette fonction permet de déplacer un coin du cube, depuis "from" vers "to"
     */

    // On commence par faire tourner le coin.
    rubiks[side].cubie[to].color = rubiks[side].cubie[from].color;
    // Et on fait tourner les coins voisins.
    rubiks[rubiks[side].cubie[to].neighbours[0].num_side].cubie[rubiks[side].cubie[to].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[0].num_side].cubie[rubiks[side].cubie[from].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[to].neighbours[1].num_side].cubie[rubiks[side].cubie[to].neighbours[1].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[1].num_side].cubie[rubiks[side].cubie[from].neighbours[1].num_cubie].color ;

}

void move_edge(rubiks_side *rubiks, int side, int from, int to) {
    /*
     * Cette fonction permet de déplacer une arête depuis "from" vers "to"
     */

    rubiks[side].cubie[to].color = rubiks[side].cubie[from].color;
    rubiks[rubiks[side].cubie[to].neighbours[0].num_side].cubie[rubiks[side].cubie[to].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[0].num_side].cubie[rubiks[side].cubie[from].neighbours[0].num_cubie].color;
}

void move_side_clockwise(rubiks_side *rubiks, int side){
    /* cette fonction permet de faire tourner la face side du cube
     * dans le sens horaire
     */

    int tmp1, tmp2, tmp3;
    // On sauvegarde les données du coin 0 pour pouvoir les utiliser à la fin de l'algorithme, pour écraser le coin 2
    // todo: renommer ces variables pour qu'elles aient un sens
    tmp1 = rubiks[side].cubie[0].color;
    tmp2 = rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color;
    tmp3 = rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color;
    // On commence par faire tourner les coins.
    move_coin(rubiks, side, 6, 0);
    move_coin(rubiks, side, 8, 6);
    move_coin(rubiks, side, 2, 8);

    /*    rubiks[side].cubie[0].color = rubiks[side].cubie[6].color;
    // faire tourner les voisins des coins
    rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[6].neighbours[0].num_side].cubie[rubiks[side].cubie[6].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color =
            rubiks[rubiks[side].cubie[6].neighbours[1].num_side].cubie[rubiks[side].cubie[6].neighbours[1].num_cubie].color ;

    rubiks[side].cubie[6].color = rubiks[side].cubie[8].color;
    rubiks[rubiks[side].cubie[6].neighbours[0].num_side].cubie[rubiks[side].cubie[6].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[8].neighbours[0].num_side].cubie[rubiks[side].cubie[8].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[6].neighbours[1].num_side].cubie[rubiks[side].cubie[6].neighbours[1].num_cubie].color =
            rubiks[rubiks[side].cubie[8].neighbours[1].num_side].cubie[rubiks[side].cubie[8].neighbours[1].num_cubie].color ;

    rubiks[side].cubie[8].color = rubiks[side].cubie[2].color;
    rubiks[rubiks[side].cubie[8].neighbours[0].num_side].cubie[rubiks[side].cubie[8].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[2].neighbours[0].num_side].cubie[rubiks[side].cubie[2].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[8].neighbours[1].num_side].cubie[rubiks[side].cubie[8].neighbours[1].num_cubie].color =
            rubiks[rubiks[side].cubie[2].neighbours[1].num_side].cubie[rubiks[side].cubie[2].neighbours[1].num_cubie].color ;
    */
    // Et on finit par récupérer les données sauvegardées pour faire "tourner" le cubie[2]
    rubiks[side].cubie[2].color = tmp1;
    rubiks[rubiks[side].cubie[2].neighbours[0].num_side].cubie[rubiks[side].cubie[2].neighbours[0].num_cubie].color = tmp2 ;
    rubiks[rubiks[side].cubie[2].neighbours[1].num_side].cubie[rubiks[side].cubie[2].neighbours[1].num_cubie].color = tmp3 ;

    // Maintenant, on fait tourner les arêtes
    // On sauvegarde les données de l'arête 1 pour pouvoir les utiliser à la fin de l'algorithme, pour écraser l'arête 5
    tmp1 = rubiks[side].cubie[1].color;
    tmp2 = rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color;

    move_edge(rubiks, side, 3, 1);
    move_edge(rubiks, side, 7, 3);
    move_edge(rubiks, side, 5, 7);

    /*    // faire tourner le voisin
    rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color ;
    //faire tourner l'arête
    rubiks[side].cubie[1].color = rubiks[side].cubie[3].color;

    rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[3].color = rubiks[side].cubie[7].color;

    rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[7].color = rubiks[side].cubie[5].color;
    */

    // Et enfin l'arête restante 5, deviens 0.
    rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color = tmp2;
    rubiks[side].cubie[5].color = tmp1;

}

void move_side_anticlockwise(rubiks_side *rubiks, int side){
    /*
     * Cette fonction fait tourner la face side dans le sens anti-horaire. En réalité, cela revient à tourner trois
     * fois dans le sens horaire
     */

    for (int i = 0; i < 3; i++)
    {
        move_side_clockwise(rubiks, side);
    }
}

//melange le rubiks cube
void mix_rubiks(rubiks_side *rubiks){
    /*
     * Cette fonction permet de mélanger le cube de manière aléatoire. Elle choisit entre 20 et 30 mouvements à réaliser
     * tout en choisissant une face à déplacer, au hasard.
     */

    // On initialise le système de hasard en fonction de l'heure
    srand(time(NULL));

    // On choisit un nombre de mouvements entre 20 et 30
    int nbr_moves = 20 + rand() % (30 + 1 - 20);
    for (int i = 0 ; i < nbr_moves; i++){
        // Réalise "nbr_moves" nombre de mouvements aléatoires
        move_side_clockwise(rubiks, rand() % (5 + 1));
    }
}
void alternate_color(rubiks_side * rubiks){
    /*
     * Cette fonction permet de créer un damier de couleurs
     */

    move_side_clockwise(rubiks, 0);
    move_side_clockwise(rubiks, 0);
    move_side_clockwise(rubiks, 5);
    move_side_clockwise(rubiks, 5);
    move_side_clockwise(rubiks, 1);
    move_side_clockwise(rubiks, 1);
    move_side_clockwise(rubiks, 3);
    move_side_clockwise(rubiks, 3);
    move_side_clockwise(rubiks, 2);
    move_side_clockwise(rubiks, 2);
    move_side_clockwise(rubiks, 4);
    move_side_clockwise(rubiks, 4);
}

void solve_rubiks(rubiks_side *rubiks){
    /*
     * Cette fonction permet de résoudre le cube.
     */

    // On commence par la résolution de la face blanche
    solve_white_side(rubiks);
}

void solve_white_side(rubiks_side * rubiks){
    /*
     * Cette fonction cherche à résoudre la face blanche du Rubik's Cube
     */

    // todo: commenter cette fonction, elle n'est pas claire.
    // On commence par la croix blanche
    cubies cubie;
    // boucle sur les arêtes blanches
    for (T_COLOR i = ORANGE ; i < YELLOW ; i++ ){
        cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);

        // le mettre sur la face jaune
        //si le cubie se trouve sur la 1ER
        if ((cubie.num == 7) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side_anticlockwise(rubiks, cubie.cubie_side);
            /*
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_clockwise(rubiks, cubie.cubie_side);
            */
            move_side_clockwise(rubiks, YELLOW);
            move_side_anticlockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            /*
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            */
            // todo: ne surtout pas faire de draw dans cette fonction !
            draw_rubiks(rubiks);
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        //si le cubie est sur la 1eme couronne
        else if ((cubie.num == 1) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_anticlockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            /*
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            */
            move_side_clockwise(rubiks, YELLOW);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side_anticlockwise(rubiks, cubie.cubie_side);
            /*
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_clockwise(rubiks, cubie.cubie_side);
            move_side_clockwise(rubiks, cubie.cubie_side);
            */
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        // si le cubie se trouve sur une arête de la seconde couronne
        else if ((cubie.num == 3 || cubie.num == 5) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            // un mouvement pour arriver sur le jaune
            if( cubie.num == 5) {
                move_side_anticlockwise(rubiks, cubie.neighbours[0].num_side);
                /*
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                */
                move_side_clockwise(rubiks, YELLOW);
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
            }
            else {
                // 3 mouvements pour arriver sur le jaune
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                move_side_clockwise(rubiks, YELLOW);
                move_side_anticlockwise(rubiks, cubie.neighbours[0].num_side);
                /*
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
                 */
            }
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        else if (cubie.cubie_side == WHITE) {
            move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
            move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
            // trouver sa nouvelle position
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }

        // tant que le voisin n'est pas sur la bonne face
       while(cubie.neighbours[0].num_side != i ){
           move_side_clockwise(rubiks, YELLOW);
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
        move_side_clockwise(rubiks, cubie.neighbours[0].num_side);
    }
    // Coins blancs
    for(T_COLOR i = ORANGE ; i < YELLOW ; i++ ){

    }
}

cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_COLOR neighbour2, T_CUBIE_TYPE cubie_type){
    /*
     * Cette fonction permet de trouver un cubie en fonction de sa couleur et celle de ses voisins
     */

    for(int face = WHITE; face <= YELLOW; face++){
        for (int cubie = 0; cubie < 9; cubie++) {
            // si la couleur et celle de son premier voisin correspondent
            if(cubie_color == rubiks[face].cubie[cubie].color && neighbour1 == rubiks[rubiks[face].cubie[cubie].neighbours[0].num_side].cubie[rubiks[face].cubie[cubie].neighbours[0].num_cubie].color){
                // si le cubie est une arête un cas possible
                if(cubie_type == rubiks[face].cubie[cubie].type) {

                    return rubiks[face].cubie[cubie] ;
                }
                // si le cubie est un coin, contrôle du 2em voisin
                /*else if (cubie_type == rubiks[face].cubie[cubie].type){
                    if(neighbour2 == rubiks[rubiks[face].cubie[cubie].neighbours[1].num_side].cubie[rubiks[face].cubie[cubie].neighbours[1].num_cubie].color){
                        return rubiks[face].cubie[cubie];
                    }
                }*/

            }
        }
    }
    return rubiks[0].cubie[0];
}