//
// Created by clestrat on 06/05/2021.
//
#include <stdio.h>
#include "movement_functions.h"

int move(cubies *side){
    // faire tourner une face
    int tmp;
    // corner donc 2 voisins
    tmp = side[0].color;
    side[0].color = side[6].color;
    side[6].color = side[8].color;
    side[8].color = side[2].color;
    side[2].color = tmp;
    //edge donc 1 voisin
    tmp = side[1].color;
    side[1].color = side[3].color;
    side[3].color = side[7].color;
    side[7].color = side[5].color;
    side[5].color = tmp;
    return 0;
}
/*
int move_front(rubiks_side *rubiks){
    int tmp;
    return 0;

}
 */