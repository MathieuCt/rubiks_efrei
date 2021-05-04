//
// Created by clestrat on 04/05/2021.
//

#include <stdio.h>
enum Test
{
    VERT, JAUNE, BLANC
};

struct cubies{
    int x;
    int y;
    int type;
    int color;
    enum Test toto;
    struct cubies *next;
};

struct rubiks_side {
    char side;
    struct cubies cubie[9];
};

int main() {
    struct rubiks_side rubiks[6];
    char side;
    short i, j;

    for(i = 0; i < 6; i++)
    {
        switch (i) {
            case 0:
                side = 'U';
                break;
            case 1:
                side = 'L';
                break;
            case 2:
                side = 'F';
                break;
            case 3:
                side = 'D';
                break;
            case 4:
                side = 'R';
                break;
            case 5:
                side = 'B';
                break;
            default:
                printf("OUPS !!!\n");
                return -1;
        }
        rubiks[i].side = side;
        for (j = 0; j < 9; j++)
        {
            rubiks[i].cubie[j].type = 1;
        }
    }
    printf("Type du cubie : %d\n", rubiks[0].cubie[0].type);
    return 0;
}