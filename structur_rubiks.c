//
// Created by clestrat on 04/05/2021.
//

#include <stdio.h>
#include "structur_rubiks.h"

enum color
{
    VERT, JAUNE, BLANC, BLEU, ORANGE, ROUGE
};

struct cubies{
    int x;
    int y;
    char type;
    char color;
    enum color toto;
    struct cubies *next;
};

struct rubiks_side{
    char side;
    struct cubies cubie[9];
};

struct rubiks_side rubiks[6];

int rubiks_creation(struct rubiks_side rubiks[])
{
    char side;
    char type;
    char color;
    short i, j;

    for(i = 0; i < 6; i++)
    {
        rubiks[i].side = side;
        switch (i)
        {
            case 0:
                side = 'U';
                color = 'B';
                break;
            case 1:
                side = 'L';
                color = 'O';
                break;
            case 2:
                side = 'F';
                color = 'V';
                break;
            case 3:
                side = 'D';
                color = 'J';
                break;
            case 4:
                side = 'R';
                color = 'R';
                break;
            case 5:
                side = 'B';
                color = 'B';
                break;
            default:
                printf("OUPS !!!\n");
                return -1;
        }
        rubiks[i].cubie[j].type = type;
        for (j = 0; j < 9; j++)
        {
            rubiks[i].cubie[j].color = color;
            //rubiks[i].cubie[j].type = 1;
            switch (j)
            {
                case 0:
                    type = 'C';
                    break;
                case 1:
                    type = 'A';
                    break;
                case 2:
                    type = 'C';
                    break;
                case 3:
                    type = 'A';
                    break;
                case 4:
                    type = 'M';
                    break;
                case 5:
                    type = 'A';
                    break;
                case 6:
                    type = 'C';
                    break;
                case 7:
                    type = 'A';
                    break;
                case 8:
                    type = 'C';
                    break;
                default:
                    printf("OUPS !!!\n");
                    return -1;
            }
        }
    }
    return 0;
}