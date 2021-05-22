//
// Created by clestrat on 20/05/2021.
//

#ifndef RUBIKS_EFREI_MENU_H
#define RUBIKS_EFREI_MENU_H
#include "rubiks.h"
#include "moves_rubiks.h"
#include "draw.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void show_menu(rubiks_side *);
void choose_color(rubiks_side *);
int choice_menu(char *);
void choice_cubie(rubiks_side *, T_CUBIE_TYPE, cubies *, int);

#endif //RUBIKS_EFREI_MENU_H