//
// Created by clestrat on 04/05/2021.
//

#ifndef RUBIKS_EFREI_RUBIKS_H
#define RUBIKS_EFREI_RUBIKS_H




typedef enum {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW} T_COLOR;
typedef enum {UP,  RIGHT, DOWN, LEFT} T_SIDE;
typedef enum {CORNER, EDGE, CENTER} T_CUBIE_TYPE;

typedef struct {
    T_COLOR num_side;
    int num_cubie;
} neighbour;

typedef struct {
    int x;
    int y;
    int num;
    T_CUBIE_TYPE type;
    T_COLOR color;
    T_COLOR cubie_side;
    neighbour neighbours[2];
} cubies;

typedef struct {
    T_COLOR neighbour_side[4];
    T_COLOR opposite_side;
    T_COLOR side;
    cubies cubie[9];
} rubiks_side;

int rubiks_creation(rubiks_side *rubiks);
int research_side(rubiks_side *,int, int);
int research_num(int, int, int);
void rubiks_neighbour(rubiks_side *);


#endif //RUBIKS_EFREI_RUBIKS_H
