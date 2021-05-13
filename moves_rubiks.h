//
// Created by clestrat on 06/05/2021.
//

#ifndef RUBIKS_EFREI_MOVES_RUBIKS_H
#define RUBIKS_EFREI_MOVES_RUBIKS_H
#include "rubiks.h"

void move_side(rubiks_side *, int);
void mix_rubiks(rubiks_side * );
void alternate_color(rubiks_side * );
void solve_rubiks(rubiks_side *);
void white_side(rubiks_side *);
cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_COLOR neighbour2, T_CUBIE_TYPE cubie_type);

#endif //RUBIKS_EFREI_MOVES_RUBIKS_H
