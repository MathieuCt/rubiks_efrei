/**
 * @file Menu.h
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on trouve les headers des fonction définies dans Menu.c.
 */

#ifndef RUBIKS_EFREI_MENU_H
#define RUBIKS_EFREI_MENU_H
#include "rubiks.h"
#include "moves_rubiks.h"
#include "draw.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void show_menu(rubiks_side *);
void choose_color(rubiks_side *);
int choice_menu(int);
int read_ints(void);
void choice_cubie(rubiks_side *,rubiks_side *, T_CUBIE_TYPE, cubies *, int, int, int);
int creation_liste_cubie(rubiks_side *,cubies *, T_CUBIE_TYPE);

#endif //RUBIKS_EFREI_MENU_H