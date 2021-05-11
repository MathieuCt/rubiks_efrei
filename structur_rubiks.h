//
// Created by clestrat on 04/05/2021.
//

#ifndef RUBIKS_EFREI_STRUCTUR_RUBIKS_H
#define RUBIKS_EFREI_STRUCTUR_RUBIKS_H



int rubiks_creation();
int rubiks_display();
int draw_rubiks();
int research_side();
int research_num();

typedef enum {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW} T_COLOR;
typedef enum {UP, LEFT, FRONT, RIGHT, BACK, DOWN} T_SIDE;
typedef enum {CORNER, EDGE, CENTER} T_CUBIE_TYPE;

typedef struct neighbour{
    T_SIDE num_side;
    int num_cubie;
}neighbour;

typedef struct cubies{
    int x;
    int y;
    int num;
    T_CUBIE_TYPE type;
    T_COLOR color;
    int nb_neighbours;
    neighbour neighbours[3];
}cubies;

typedef struct rubiks_side{
    T_SIDE side;
    int neighbour_side[4];
    // conserver le cubie central, ici ?
    cubies cubie[9];
}rubiks_side;



#endif //RUBIKS_EFREI_STRUCTUR_RUBIKS_H

