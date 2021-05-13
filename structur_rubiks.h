//
// Created by clestrat on 04/05/2021.
//

#ifndef RUBIKS_EFREI_STRUCTUR_RUBIKS_H
#define RUBIKS_EFREI_STRUCTUR_RUBIKS_H




typedef enum {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW} T_COLOR;
typedef enum {UP,  RIGHT, DOWN, LEFT} T_SIDE;
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
    T_COLOR neighbour_side[4];
    T_COLOR opposite_side;
    T_COLOR side;
    cubies cubie[9];
}rubiks_side;

int rubiks_creation();
int rubiks_display();
int draw_rubiks();
int research_side(rubiks_side *,int, int);
int research_num(int, int, int);
void rubiks_neighbour(rubiks_side *);


#endif //RUBIKS_EFREI_STRUCTUR_RUBIKS_H

