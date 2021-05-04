//
// Created by clestrat on 04/05/2021.
//

#ifndef RUBIKS_EFREI_STRUCTUR_RUBIKS_H
#define RUBIKS_EFREI_STRUCTUR_RUBIKS_H

#endif //RUBIKS_EFREI_STRUCTUR_RUBIKS_H


int rubiks_creation();

enum color
{
    VERT, JAUNE, BLANC, BLEU, ORANGE, ROUGE
};

struct cubies{
    int x;
    int y;
    int num;
    char type;
    char color;
    //int nb_neighbours;
    //struct cubies neighbours[3];
};

struct rubiks_side{
    char side;
    struct cubies cubie[9];
};

