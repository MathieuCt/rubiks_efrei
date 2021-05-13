//
// Created by clestrat on 06/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h"
#include "moves_rubiks.h"
#include "rubiks.h"

void move_side(rubiks_side *rubiks, int side){
    // faire tourner une face
    int tmp1, tmp2, tmp3;
    // var tmp des couleurs ecrasees pour faire tourner les arretes
    tmp1 = rubiks[side].cubie[0].color;
    tmp2 = rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color;
    tmp3 = rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color;
    // faire tourner les coins
    rubiks[side].cubie[0].color = rubiks[side].cubie[6].color;
    // faire tourner les voisins des coins
    rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[6].neighbours[0].num_side].cubie[rubiks[side].cubie[6].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color = rubiks[rubiks[side].cubie[6].neighbours[1].num_side].cubie[rubiks[side].cubie[6].neighbours[1].num_cubie].color ;

    rubiks[side].cubie[6].color = rubiks[side].cubie[8].color;
    rubiks[rubiks[side].cubie[6].neighbours[0].num_side].cubie[rubiks[side].cubie[6].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[8].neighbours[0].num_side].cubie[rubiks[side].cubie[8].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[6].neighbours[1].num_side].cubie[rubiks[side].cubie[6].neighbours[1].num_cubie].color = rubiks[rubiks[side].cubie[8].neighbours[1].num_side].cubie[rubiks[side].cubie[8].neighbours[1].num_cubie].color ;

    rubiks[side].cubie[8].color = rubiks[side].cubie[2].color;
    rubiks[rubiks[side].cubie[8].neighbours[0].num_side].cubie[rubiks[side].cubie[8].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[2].neighbours[0].num_side].cubie[rubiks[side].cubie[2].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[8].neighbours[1].num_side].cubie[rubiks[side].cubie[8].neighbours[1].num_cubie].color = rubiks[rubiks[side].cubie[2].neighbours[1].num_side].cubie[rubiks[side].cubie[2].neighbours[1].num_cubie].color ;

    rubiks[side].cubie[2].color = tmp1;
    rubiks[rubiks[side].cubie[2].neighbours[0].num_side].cubie[rubiks[side].cubie[2].neighbours[0].num_cubie].color = tmp2 ;
    rubiks[rubiks[side].cubie[2].neighbours[1].num_side].cubie[rubiks[side].cubie[2].neighbours[1].num_cubie].color = tmp3 ;
    // faire tourner les arretes
    // recuperer les couleurs ecrasees
    tmp1 = rubiks[side].cubie[1].color;
    tmp2 = rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color;
    // faire tourner le voisin
    rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color ;
    //faire tourner l'arrete
    rubiks[side].cubie[1].color = rubiks[side].cubie[3].color;

    rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[3].color = rubiks[side].cubie[7].color;

    rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[7].color = rubiks[side].cubie[5].color;

    rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color = tmp2;
    rubiks[side].cubie[5].color = tmp1;

}

//melange le rubiks cube
void mix_rubiks(rubiks_side *rubiks){
    // initialiser le hasard en fonction de l'heure
    srand(time(NULL));
    // choisir un nombre de mouvement entre 20 et 30
    int nbr_mouv = 20 + rand() % (30 + 1 -20);
    for (int i = 0 ; i < nbr_mouv; i++){
        // realiser nbr_mouv nombre de mouvement aleatoire
        move_side(rubiks,rand() % (5 + 1));
    }
}
// pour créer un damier de couleurs
void alternate_color(rubiks_side * rubiks){
    move_side(rubiks,0);
    move_side(rubiks,0);
    move_side(rubiks,5);
    move_side(rubiks,5);
    move_side(rubiks,1);
    move_side(rubiks,1);
    move_side(rubiks,3);
    move_side(rubiks,3);
    move_side(rubiks,2);
    move_side(rubiks,2);
    move_side(rubiks,4);
    move_side(rubiks,4);
}

// algo de resolution
void solve_rubiks(rubiks_side *rubiks){
    // resoudre la face blanche
    white_side(rubiks);
}

void white_side(rubiks_side * rubiks){
    // la croix blanche
    cubies cubie;
    // boucle sur les arretes blanche
    for(T_COLOR i = ORANGE ; i < YELLOW ; i++ ){
        cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);

        // le mettre sur la face jaune
        //si le cubie se trouve sur la 1ER
        if ((cubie.num == 7) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, YELLOW);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT]);
            draw_rubiks(rubiks);

            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        //si le cubie est sur la 1eme couronne
        else if ((cubie.num == 1) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side(rubiks, YELLOW);
            move_side(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT]);
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, cubie.cubie_side);
            move_side(rubiks, cubie.cubie_side);
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        // si le cubie se trouve sur une arrete de la 2nd courronne
        else if ((cubie.num == 3 || cubie.num == 5) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            // un mouve pour arriver sur le jaune
            if( cubie.num == 5) {
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, YELLOW);
                move_side(rubiks, cubie.neighbours[0].num_side);
            }
            else {
            // 3 mouvs pour arriver sur le jaune
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, YELLOW);
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, cubie.neighbours[0].num_side);
                move_side(rubiks, cubie.neighbours[0].num_side);
            }
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
        else if (cubie.cubie_side == WHITE) {
            move_side(rubiks, cubie.neighbours[0].num_side);
            move_side(rubiks, cubie.neighbours[0].num_side);
            // trouver sa nouvelle position
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);

        }

        // tant que le voisin n'est pas sur la bonne face
       while(cubie.neighbours[0].num_side != i ){
            move_side(rubiks, YELLOW);
            cubie = search_cubie(rubiks, WHITE, i, WHITE, EDGE);
        }
            move_side(rubiks, cubie.neighbours[0].num_side);
            move_side(rubiks, cubie.neighbours[0].num_side);
    }
    // Coins blancs
    for(T_COLOR i = ORANGE ; i < YELLOW ; i++ ){

    }
}
// trouvrer un cubie en fonction de sa couleur et celle de ses voisins
cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_COLOR neighbour2, T_CUBIE_TYPE cubie_type){
    for(int face = WHITE; face <= YELLOW; face++){
        for (int cubie = 0; cubie < 9; cubie++) {
            // si la couleur et celle de son premier voisin correspondent
            if(cubie_color == rubiks[face].cubie[cubie].color && neighbour1 == rubiks[rubiks[face].cubie[cubie].neighbours[0].num_side].cubie[rubiks[face].cubie[cubie].neighbours[0].num_cubie].color){
                // si le cubie est une arrete un cas possible
                if(cubie_type == rubiks[face].cubie[cubie].type) {

                    return rubiks[face].cubie[cubie] ;
                }
                // si le cubie est un corner, controle du 2em voisin
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