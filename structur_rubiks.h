//
// Created by clestrat on 04/05/2021.
//

#ifndef RUBIKS_EFREI_STRUCTUR_RUBIKS_H
#define RUBIKS_EFREI_STRUCTUR_RUBIKS_H

#endif //RUBIKS_EFREI_STRUCTUR_RUBIKS_H


int rubiks_creation();
int rubiks_display();

typedef enum {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW} T_COLOR;
typedef enum {UP, LEFT, FRONT, RIGHT, BACK, DOWN} T_SIDE;
typedef enum {CORNER, EDGE, CENTER} T_CUBIE_TYPE;

struct cubies{
    int x;
    int y;
    int num;
    T_CUBIE_TYPE type;
    T_COLOR color;
    //int nb_neighbours;
    //struct cubies neighbours[3];
};

struct rubiks_side{
    T_SIDE side;
    // conserver le cubie central, ici ?
    struct cubies cubie[9];
};

