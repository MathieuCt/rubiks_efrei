//
// Created by clestrat on 04/05/2021.
//

#include <stdio.h>
#include "structur_rubiks.h"


int rubiks_creation(struct rubiks_side *rubiks)
{
//    char side;
//    char type;
//    char color;
    int face, cubie;

    for(face = UP; face <= DOWN; face++)
    {
        rubiks[face].side = face;
//        if (face == LEFT)
//        {
//            printf("face: %d left : %d", face, LEFT);
//        }
//        switch (face)
//        {
//            case 0:
//                side = 'U';
//                color = 'B';
//                break;
//            case 1:
//                side = 'L';
//                color = 'O';
//                break;
//            case 2:
//                side = 'F';
//                color = 'V';
//                break;
//            case 3:
//                side = 'D';
//                color = 'J';
//                break;
//            case 4:
//                side = 'R';
//                color = 'R';
//                break;
//            case 5:
//                side = 'B';
//                color = 'B';
//                break;
//            default:
//                printf("OUPS !!!\n");
//                return -1;
//        }
//        rubiks[face].cubie[cubie].type = type;
        for (cubie = 0; cubie < 9; cubie++)
        {
            switch (rubiks[face].side)
            {
                case UP:
                    rubiks[face].cubie[cubie].color = WHITE;
                    break;
                case LEFT:
                    rubiks[face].cubie[cubie].color = ORANGE;
                    break;
                case FRONT:
                    rubiks[face].cubie[cubie].color = GREEN;
                    break;
                case RIGHT:
                    rubiks[face].cubie[cubie].color = RED;
                    break;
                case BACK:
                    rubiks[face].cubie[cubie].color = BLUE;
                    break;
                case DOWN:
                    rubiks[face].cubie[cubie].color = YELLOW;
                    break;
            }
            // rubiks[face].cubie[cubie].color = cubie;
            // rubiks[face].cubie[cubie].type = 1;
            if (cubie == 0 || cubie == 2 || cubie == 6 || cubie == 8)
            {
                rubiks[face].cubie[cubie].type = CORNER;
            }
            if (cubie == 4)
            {
                rubiks[face].cubie[cubie].type = CENTER;
            }
            if (cubie == 1 || cubie == 3 || cubie == 5 || cubie == 7)
            {
                rubiks[face].cubie[cubie].type = EDGE;
            }
//            switch (cubie)
//            {
//                case 0:
//                    type = 'C';
//                    break;
//                case 1:
//                    type = 'A';
//                    break;
//                case 2:
//                    type = 'C';
//                    break;
//                case 3:
//                    type = 'A';
//                    break;
//                case 4:
//                    type = 'M';
//                    break;
//                case 5:
//                    type = 'A';
//                    break;
//                case 6:
//                    type = 'C';
//                    break;
//                case 7:
//                    type = 'A';
//                    break;
//                case 8:
//                    type = 'C';
//                    break;
//                default:
//                    printf("OUPS !!!\n");
//                    return -1;
//            }
            rubiks[face].cubie[cubie].num = cubie;
//          rubiks[face].cubie[cubie].type = type;
            rubiks[face].cubie[cubie].x = rubiks[face].cubie[cubie].num % 3;
            rubiks[face].cubie[cubie].y = (rubiks[face].cubie[cubie].num - rubiks[face].cubie[cubie].x) / 3;
        }
    }
    return 0;
}

int rubiks_display(struct rubiks_side *rubiks){
    int face, cubie;
    for(face = 0; face < 6 ; face++){
        printf("\n\n\n");
        rubiks[face].side;
        for(cubie = 0 ; cubie < 9 ; cubie++){
            printf("num :%d, x : %d, y : %d, type : %d, color : %d\n",
                   rubiks[face].cubie[cubie].num,
                   rubiks[face].cubie[cubie].x,
                   rubiks[face].cubie[cubie].y,
                   rubiks[face].cubie[cubie].type,
                   rubiks[face].cubie[cubie].color);
        }
    }
    return 0;
}

int draw_rubiks(struct rubiks_side *rubiks)
{
    char tabcolor[] = {'W', 'O', 'G', 'R', 'B', 'Y'};

    printf("--------------\n");
    printf("    %c%c%c       \n", tabcolor[rubiks[0].cubie[0].color], tabcolor[rubiks[0].cubie[1].color],tabcolor[rubiks[0].cubie[2].color]);
    printf("    %c%c%c       \n", tabcolor[rubiks[0].cubie[3].color], tabcolor[rubiks[0].cubie[4].color],tabcolor[rubiks[0].cubie[5].color]);
    printf("    %c%c%c       \n", tabcolor[rubiks[0].cubie[6].color], tabcolor[rubiks[0].cubie[7].color],tabcolor[rubiks[0].cubie[8].color]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", tabcolor[rubiks[1].cubie[0].color], tabcolor[rubiks[1].cubie[1].color],tabcolor[rubiks[1].cubie[2].color], tabcolor[rubiks[2].cubie[0].color], tabcolor[rubiks[2].cubie[1].color],tabcolor[rubiks[2].cubie[2].color], tabcolor[rubiks[3].cubie[0].color], tabcolor[rubiks[3].cubie[1].color],tabcolor[rubiks[3].cubie[2].color], tabcolor[rubiks[4].cubie[0].color], tabcolor[rubiks[4].cubie[1].color],tabcolor[rubiks[4].cubie[2].color]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", tabcolor[rubiks[1].cubie[3].color], tabcolor[rubiks[1].cubie[4].color],tabcolor[rubiks[1].cubie[5].color], tabcolor[rubiks[2].cubie[3].color], tabcolor[rubiks[2].cubie[4].color],tabcolor[rubiks[2].cubie[5].color], tabcolor[rubiks[3].cubie[3].color], tabcolor[rubiks[3].cubie[4].color],tabcolor[rubiks[3].cubie[5].color], tabcolor[rubiks[4].cubie[3].color], tabcolor[rubiks[4].cubie[4].color],tabcolor[rubiks[4].cubie[5].color]);
    printf("%c%c%c %c%c%c %c%c%c %c%c%c\n", tabcolor[rubiks[1].cubie[6].color], tabcolor[rubiks[1].cubie[7].color],tabcolor[rubiks[1].cubie[8].color], tabcolor[rubiks[2].cubie[6].color], tabcolor[rubiks[2].cubie[7].color],tabcolor[rubiks[2].cubie[8].color], tabcolor[rubiks[3].cubie[6].color], tabcolor[rubiks[3].cubie[7].color],tabcolor[rubiks[3].cubie[8].color], tabcolor[rubiks[4].cubie[6].color], tabcolor[rubiks[4].cubie[7].color],tabcolor[rubiks[4].cubie[8].color]);
    printf("    %c%c%c       \n", tabcolor[rubiks[5].cubie[0].color], tabcolor[rubiks[5].cubie[1].color],tabcolor[rubiks[5].cubie[2].color]);
    printf("    %c%c%c       \n", tabcolor[rubiks[5].cubie[3].color], tabcolor[rubiks[5].cubie[4].color],tabcolor[rubiks[5].cubie[5].color]);
    printf("    %c%c%c       \n", tabcolor[rubiks[5].cubie[6].color], tabcolor[rubiks[5].cubie[7].color],tabcolor[rubiks[5].cubie[8].color]);
    printf("--------------\n");
    return 0;
}