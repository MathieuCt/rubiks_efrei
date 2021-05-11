//
// Created by clestrat on 04/05/2021.
//

#include <stdio.h>
#include "structur_rubiks.h"


int rubiks_creation(rubiks_side *rubiks) {
//    char side;
//    char type;
//    char color;
    int face, cubie;

    for (face = UP; face <= DOWN; face++) {
        rubiks[face].side = face;
        switch (face) {
            case WHITE:
                rubiks[face].neighbour_side[0] = 1;
                rubiks[face].neighbour_side[1] = 2;
                rubiks[face].neighbour_side[2] = 3;
                rubiks[face].neighbour_side[3] = 4;
                break;
            case ORANGE:
                rubiks[face].neighbour_side[0] = 0;
                rubiks[face].neighbour_side[1] = 2;
                rubiks[face].neighbour_side[2] = 5;
                rubiks[face].neighbour_side[3] = 4;
                break;
            case GREEN:
                rubiks[face].neighbour_side[0] = 0;
                rubiks[face].neighbour_side[1] = 3;
                rubiks[face].neighbour_side[2] = 5;
                rubiks[face].neighbour_side[3] = 1;
                break;
            case RED:
                rubiks[face].neighbour_side[0] = 0;
                rubiks[face].neighbour_side[1] = 4;
                rubiks[face].neighbour_side[2] = 5;
                rubiks[face].neighbour_side[3] = 2;
                break;
            case BLUE:
                rubiks[face].neighbour_side[0] = 0;
                rubiks[face].neighbour_side[1] = 1;
                rubiks[face].neighbour_side[2] = 5;
                rubiks[face].neighbour_side[3] = 3;
                break;
            case YELLOW:
                rubiks[face].neighbour_side[0] = 2;
                rubiks[face].neighbour_side[1] = 3;
                rubiks[face].neighbour_side[2] = 4;
                rubiks[face].neighbour_side[3] = 1;
                break;
            default:
                printf("OUPS !!!\n");
                return -1;

        }
        for (cubie = 0; cubie < 9; cubie++) {
            switch (rubiks[face].side) {
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
            if (cubie == 0 || cubie == 2 || cubie == 6 || cubie == 8) {
                rubiks[face].cubie[cubie].type = CORNER;
                rubiks[face].cubie[cubie].nb_neighbours = 1;
            }
            if (cubie == 4) {
                rubiks[face].cubie[cubie].type = CENTER;
                rubiks[face].cubie[cubie].nb_neighbours = 1;
            }
            if (cubie == 1 || cubie == 3 || cubie == 5 || cubie == 7) {
                rubiks[face].cubie[cubie].type = EDGE;
                rubiks[face].cubie[cubie].nb_neighbours = 2;
            }
            rubiks[face].cubie[cubie].num = cubie;
            //      rubiks[face].cubie[cubie].type = type;
            rubiks[face].cubie[cubie].x = rubiks[face].cubie[cubie].num % 3;
            rubiks[face].cubie[cubie].y = (rubiks[face].cubie[cubie].num - rubiks[face].cubie[cubie].x) / 3;

        }
    }
    rubiks_neighbour(rubiks);
    return 0;
}

void rubiks_neighbour(rubiks_side *rubiks) {
    // initiliser les voisins
    int face, cubie;
    for (face = UP; face <= DOWN; face++) {
        for (cubie = 0; cubie < 9; cubie++) {
            // si le cubie est de type edge, un seul voisin
            if (rubiks[face].cubie[cubie].type == EDGE){
                //position relative de la face voisine, position absolu
                int side_relative, side_abs;
                // trouver a cote de quelle face (relative) le cubie est en fonction de ses coordonnees
                // soit il a y = 0 (en haut)
                if (rubiks[face].cubie[cubie].y == 0){
                    side_relative = 0;
                }
                // en bas
                else if(rubiks[face].cubie[cubie].y == 2){
                    side_relative = 2;

                }
                    // au milieu : 2 possibilites
                else{
                    // il est a gauche
                    if(rubiks[face].cubie[cubie].x == 0){
                        side_relative = 3;
                    }
                        // il est a droite
                    else{
                        side_relative =1 ;
                    }
                }

                side_abs = rubiks[face].neighbour_side[side_relative];
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = side_abs;
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = research_num(research_side(rubiks,face, side_abs), EDGE);
                // position initiale
            }
            if (rubiks[face].cubie[cubie].type == EDGE){
                int a = 2;
            }
        }
    }

}

int research_side(rubiks_side *rubiks,int side, int neighbour_face){
    // neighbour_face ( pos abs de la face voisine)
    // side : face principale
    // face : variable locale pour parcourirs la liste de voisin de neighbour side
    for(int face = 0 ; face < 4 ; face++){

        if (rubiks[neighbour_face].neighbour_side[face] == side) {
            return face ;
        }
    }
}
//retourne le numéro du cubie selon la position relative de la face de son voisin
int research_num( int side, int type ){
    if (type == 1){
        switch (side) {
            case 0 :
                return 1;
            case 1 :
                return 5;
            case 2 :
                return 7 ;
            case 3 :
                return 3;
            default:
                return -1;

        }
    }
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