//
// Created by clestrat on 06/05/2021.
//
#include <stdio.h>
#include "stdlib.h"
#include "movement_functions.h"
#include "structur_rubiks.h"
#include <time.h>

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