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

    for (face = WHITE; face <= YELLOW; face++) {
        rubiks[face].side = face;
        // donner a chaque face ses voisins (image en annexe)
        switch (face) {
            case WHITE:
                rubiks[face].neighbour_side[UP] = BLUE;
                rubiks[face].neighbour_side[RIGHT] = RED;
                rubiks[face].neighbour_side[DOWN] = GREEN;
                rubiks[face].neighbour_side[LEFT] = ORANGE;
                rubiks[face].opposite_side = YELLOW;
                break;
            case ORANGE:
                rubiks[face].neighbour_side[UP] = WHITE;
                rubiks[face].neighbour_side[RIGHT] = GREEN;
                rubiks[face].neighbour_side[DOWN] = YELLOW;
                rubiks[face].neighbour_side[LEFT] = BLUE;
                rubiks[face].opposite_side = RED;
                break;
            case GREEN:
                rubiks[face].neighbour_side[UP] = WHITE;
                rubiks[face].neighbour_side[RIGHT] = RED;
                rubiks[face].neighbour_side[DOWN] = YELLOW;
                rubiks[face].neighbour_side[LEFT] = ORANGE;
                rubiks[face].opposite_side = BLUE;
                break;
            case RED:
                rubiks[face].neighbour_side[UP] = WHITE;
                rubiks[face].neighbour_side[RIGHT] = BLUE;
                rubiks[face].neighbour_side[DOWN] = YELLOW;
                rubiks[face].neighbour_side[LEFT] = GREEN;
                rubiks[face].opposite_side = ORANGE;
                break;
            case BLUE:
                rubiks[face].neighbour_side[UP] = WHITE;
                rubiks[face].neighbour_side[RIGHT] = ORANGE;
                rubiks[face].neighbour_side[DOWN] = YELLOW;
                rubiks[face].neighbour_side[LEFT] = RED;
                rubiks[face].opposite_side = GREEN;
                break;
            case YELLOW:
                rubiks[face].neighbour_side[UP] = GREEN;
                rubiks[face].neighbour_side[RIGHT] = RED;
                rubiks[face].neighbour_side[DOWN] = BLUE;
                rubiks[face].neighbour_side[LEFT] = ORANGE;
                rubiks[face].opposite_side = WHITE;
                break;
            default:
                printf("OUPS !!!\n");
                return -1;

        }
        for (cubie = 0; cubie < 9; cubie++) {
            // donner a chaque cubie la couleur de sa face
            rubiks[face].cubie[cubie].color = rubiks[face].side;

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
    int side_relative, side_abs;
    for (face = WHITE; face <= YELLOW; face++) {
        for (cubie = 0; cubie < 9; cubie++) {
            // si le cubie est de type edge, un seul voisin
            if (rubiks[face].cubie[cubie].type == EDGE){
                //position relative de la face voisine, position absolu
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
                        side_relative = 1 ;
                    }
                }
                // recuperer la side absolu
                side_abs = rubiks[face].neighbour_side[side_relative];
                // on met la side absolu comme side voisine du cubie
                rubiks[face].cubie[cubie].neighbours[0].num_side = side_abs;
                // recuperer le num du cubie voisin
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = research_num(research_side(rubiks,face, side_abs), EDGE,0);
                // mise a -1 du 2nd voisin
                rubiks[face].cubie[cubie].neighbours[1].num_side = -1;
                rubiks[face].cubie[cubie].neighbours[1].num_cubie = -1;
                // position initiale

            }
            if (rubiks[face].cubie[cubie].type == CORNER){
                // 2 voisins pour un corner
                int side_relative2, side_abs2;
                if(rubiks[face].cubie[cubie].y == 0) {
                    if (rubiks[face].cubie[cubie].x == 0) {
                        side_relative = 3;
                        side_relative2 = 0;
                    } else {
                        side_relative = 0;
                        side_relative2 = 1;
                    }
                }
                else{
                    if (rubiks[face].cubie[cubie].x == 0) {
                        side_relative = 2;
                        side_relative2 = 3;
                    } else {
                        side_relative = 1;
                        side_relative2 = 2;
                    }
                }
                side_abs = rubiks[face].neighbour_side[side_relative];
                side_abs2 = rubiks[face].neighbour_side[side_relative2];
                rubiks[face].cubie[cubie].neighbours[0].num_side = side_abs;
                rubiks[face].cubie[cubie].neighbours[1].num_side = side_abs2;
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = research_num(research_side(rubiks,face, side_abs), CORNER,research_side(rubiks,side_abs2, side_abs));
                rubiks[face].cubie[cubie].neighbours[1].num_cubie = research_num(research_side(rubiks,face, side_abs2), CORNER,research_side(rubiks,side_abs, side_abs2));

            }
            if (rubiks[face].cubie[cubie].type == CENTER){

                rubiks[face].cubie[cubie].neighbours[0].num_side = rubiks[face].opposite_side;
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = 4;
                // mise a -1 du 2nd voisin
                rubiks[face].cubie[cubie].neighbours[1].num_side = -1;
                rubiks[face].cubie[cubie].neighbours[1].num_cubie = -1;
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
int research_num( int side, int type, int side2 ){
    // pour une arrete
    if (type == EDGE){
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
    //pour un coin, besoin de 2 faces pour définir le num
    if(type == CORNER){
        switch (side) {
            //cas du top
            case 0 :
                if(side2 == 1){
                    return 2;
                }
                else{
                    return 0;
                }
            case 1 :
                if(side2 == 0){
                    return 2;
                }
                else{
                    return 8;
                }
            case 2 :
                if(side2 == 1){
                    return 8;
                }
                else{
                    return 6;
                }
            case 3 :
                if(side2 == 2){
                    return 6;
                }
                else{
                    return 0;
                }
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
            printf("num :%d, x : %d, y : %d, type : %d, color : %d, voisin1(side): %d, voisin1(num) : %d voisin2(side): %d, voisin2(num) : %d\n",
                   rubiks[face].cubie[cubie].num,
                   rubiks[face].cubie[cubie].x,
                   rubiks[face].cubie[cubie].y,
                   rubiks[face].cubie[cubie].type,
                   rubiks[face].cubie[cubie].color,
                   rubiks[face].cubie[cubie].neighbours[0].num_side,
                   rubiks[face].cubie[cubie].neighbours[0].num_cubie,
                   rubiks[face].cubie[cubie].neighbours[1].num_side,
                   rubiks[face].cubie[cubie].neighbours[1].num_cubie
                   );

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