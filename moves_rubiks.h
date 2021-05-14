/**
 * @file moves_rubiks.h
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on trouve les Headers utilisés partout dans le code. Définitions dans moves_rubiks.c.
 */

#ifndef RUBIKS_EFREI_MOVES_RUBIKS_H
#define RUBIKS_EFREI_MOVES_RUBIKS_H
#include "rubiks.h"

void move_side_clockwise(rubiks_side *rubiks, int side);
void move_side_anticlockwise(rubiks_side *rubiks, int side);
void move_coin(rubiks_side *rubiks, int side, int from, int to);
void move_edge(rubiks_side *rubiks, int side, int from, int to);
void mix_rubiks(rubiks_side * );
void alternate_color(rubiks_side * );
void solve_rubiks(rubiks_side *);
void solve_white_side(rubiks_side *rubiks);
cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_CUBIE_TYPE cubie_type);

#endif //RUBIKS_EFREI_MOVES_RUBIKS_H
