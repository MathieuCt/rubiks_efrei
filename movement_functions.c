//
// Created by clestrat on 06/05/2021.
//
#include <stdio.h>
#include "movement_functions.h"
#include "structur_rubiks.h"

int move_side(rubiks_side *rubiks, int side){
    // faire tourner une face
    int tmp1, tmp2, tmp3;
    // var tmp des couleurs ecrasees
    tmp1 = rubiks[side].cubie[0].color;
    tmp2 = rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color;
    tmp3 = rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color;
    // faire tourner les coins
    rubiks[side].cubie[0].color = rubiks[side].cubie[6].color;
    //printf(" side :%d nm:%d",)
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

    tmp1 = rubiks[side].cubie[1].color;
    tmp2 = rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color;

    rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[1].color = rubiks[side].cubie[3].color;

    rubiks[rubiks[side].cubie[3].neighbours[0].num_side].cubie[rubiks[side].cubie[3].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[3].color = rubiks[side].cubie[7].color;

    rubiks[rubiks[side].cubie[7].neighbours[0].num_side].cubie[rubiks[side].cubie[7].neighbours[0].num_cubie].color = rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color ;
    rubiks[side].cubie[7].color = rubiks[side].cubie[5].color;

    rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color = tmp2;
    rubiks[side].cubie[5].color = tmp1;

    // corner donc 2 voisins
    /*rubiks[side].cubie[0].color = side[6].color;

    side[6].color = side[8].color;
    side[8].color = side[2].color;
    side[2].color = tmp;
    //edge donc 1 voisin
    tmp = side[1].color;
    side[1].color = side[3].color;
    side[3].color = side[7].color;
    side[7].color = side[5].color;
    side[5].color = tmp; */
    return 0;
}
/*
int move_front(rubiks_side *rubiks){
    int tmp;
    return 0;

}
 */