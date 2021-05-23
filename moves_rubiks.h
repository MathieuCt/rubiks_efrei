/**
 * @file moves_rubiks.h
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on trouve les headers utilisés partout dans le code. Définitions dans moves_rubiks.c.
 */

#ifndef RUBIKS_EFREI_MOVES_RUBIKS_H
#define RUBIKS_EFREI_MOVES_RUBIKS_H
#include "rubiks.h"

#define SIZE_MOVE 20
typedef struct solutions_steps solutions_steps;
struct solutions_steps{
    char solution_step[SIZE_MOVE];
    solutions_steps *next_step;
};

void move_side_clockwise(rubiks_side *rubiks, int side, int add_to_history);
void move_side_anticlockwise(rubiks_side *rubiks, int side, int add_to_history);
void move_corner(rubiks_side *rubiks, int side, int from, int to);
void move_edge(rubiks_side *rubiks, int side, int from, int to);
void mix_rubiks(rubiks_side * );
void alternate_color(rubiks_side * );
void solve_rubiks(rubiks_side *);
void solve_white_side(rubiks_side *rubiks);
void solve_middle_row(rubiks_side *rubiks);
void solve_yellow_cross(rubiks_side *rubiks);
void solve_yellow_corner(rubiks_side *rubiks);
void turn_three_corner(rubiks_side *rubiks);
cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_CUBIE_TYPE cubie_type);
void right_move(rubiks_side *rubiks, cubies cubie);
void left_move(rubiks_side *rubiks, cubies cubie);
solutions_steps * init_solution(char new_step[SIZE_MOVE]);
void add_step_to_solution(solutions_steps *first_step, char new_step[SIZE_MOVE]);
void print_solution(solutions_steps *first_step);
void clear_solution(solutions_steps *first_step);

#endif //RUBIKS_EFREI_MOVES_RUBIKS_H
