/**
 * @file rubiks.c
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on gère toutes les propriétés du Rubik's Cube, depuis sa création, la gestion des faces
 * adjacentes, et les recherches associées (recherche par couleur, ou depuis la couleur).
 */

#include "rubiks.h"

/**
 * Initialisation du rubik's cube. Au départ, il est résolu.<br><br>
 * Dans cette fonction, et dans toutes celles qui en découlent, on considère que la face en cours de traitement est face
 * à nous. Puis on se réfère au fichier ./Doc/reference_rubiks_excel.png pour déterminer les adjacents.
 * <br>Si on prend la face blanche en exemple :
 * - La face au dessus est la face bleue
 * - La face à sa droite est la face rouge
 * - La face à sa gauche est la face orange
 * - La face sous-elle est la face verte
 * - La face opposée ne change jamais, dans le cas de la blanche, il s'agit de la face jaune.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void rubiks_creation(rubiks_side *rubiks) {
    int face, cubie;

    // On va former chacune des faces et à chaque fois définir ses voisins et son opposé
    for (face = WHITE; face <= YELLOW; face++) {
        rubiks[face].side = face;
        // On considère que la face en cours de création est face à nous.
        // Et à chaque fois on détermine les adjacents de la face en cours de traitement, ainsi que sa face opposée
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
                break;
        }

        // Initialisation des cubies de la face en cours de traitement. On parcourt donc le tableau de 0 à 8
        for (cubie = 0; cubie < 9; cubie++) {
            // donner a chaque cubie la couleur de sa face
            rubiks[face].cubie[cubie].color = rubiks[face].side;
            // donner à chaque cubie la couleur de sa face
            // On sauvegarde la face de rattachement du cubie en cours
            rubiks[face].cubie[cubie].cubie_side = rubiks[face].side;

            // On défini le type de cubie en cours de traitement, c'est soit un coin, soit un côté, soit un centre
            if (cubie == 0 || cubie == 2 || cubie == 6 || cubie == 8) {
                rubiks[face].cubie[cubie].type = CORNER;
            }
            if (cubie == 4) {
                rubiks[face].cubie[cubie].type = CENTER;
            }
            if (cubie == 1 || cubie == 3 || cubie == 5 || cubie == 7) {
                rubiks[face].cubie[cubie].type = EDGE;
            }
            // On sauvegarde le numéro de cubie
            rubiks[face].cubie[cubie].num = cubie;
            // Et enfin, on défini ses coordonnées car elles nous servirons aux rendus à l'écran
            rubiks[face].cubie[cubie].x = rubiks[face].cubie[cubie].num % 3;
            rubiks[face].cubie[cubie].y = (rubiks[face].cubie[cubie].num - rubiks[face].cubie[cubie].x) / 3;

        }
    }

    // Et enfin on défini les faces adjacentes
    rubiks_neighbour(rubiks);
}

/**
 * Cette fonction permet d'attribuer à chaque cubie ses voisin.
 * num_side indique sur quelle face il se trouve
 * num_cubie correspond au numéro du cubie voisin sur sa face
 * les voisins ne changent pas avec la réalisation de mouvements ils sont donc attribués définitivement.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void rubiks_neighbour(rubiks_side *rubiks) {
    // initialiser les voisins
    int face, cubie;
    // side relative : UP, DOWN, RIGHT, LEFT
    // side absolu : ORANGE, GREEN, BLUE...
    int side_relative, side_abs;
    for (face = WHITE; face <= YELLOW; face++) {
        for (cubie = 0; cubie < 9; cubie++) {
            // si le cubie est de type edge, un seul voisin
            if (rubiks[face].cubie[cubie].type == EDGE){
                //position relative de la face voisine, position absolu
                // trouver à côté de quelle face (relative) le cubie est en fonction de ses coordonnées
                // soit il a y = 0 (en haut)
                if (rubiks[face].cubie[cubie].y == 0){
                    side_relative = 0;
                }
                // en bas
                else if(rubiks[face].cubie[cubie].y == 2){
                    side_relative = 2;

                }
                    // au milieu : 2 possibilités
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
                // mise a -1 du 2nd voisin, se chiffre indique qu'il n'y a pas de second voisuin (type edge)
                rubiks[face].cubie[cubie].neighbours[1].num_side = -1;
                rubiks[face].cubie[cubie].neighbours[1].num_cubie = -1;
                // position initiale

            }
            if (rubiks[face].cubie[cubie].type == CORNER){
                // 2 voisins pour un corner
                int side_relative2, side_abs2;
                // trouver à côté de quelles faces (relative) le cubie est en fonction de ses coordonnées
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
                // enregistrer le numéro absolu de ces faces
                side_abs = rubiks[face].neighbour_side[side_relative];
                side_abs2 = rubiks[face].neighbour_side[side_relative2];
                // On peut maintenant attribuer num_side (2 fois)
                rubiks[face].cubie[cubie].neighbours[0].num_side = side_abs;
                rubiks[face].cubie[cubie].neighbours[1].num_side = side_abs2;
                //On peut maintenant retrouver num_cubie grâce à research_side() et research_num()
                rubiks[face].cubie[cubie].neighbours[0].num_cubie = research_num(research_side(rubiks,face, side_abs), CORNER,research_side(rubiks,side_abs2, side_abs));
                rubiks[face].cubie[cubie].neighbours[1].num_cubie = research_num(research_side(rubiks,face, side_abs2), CORNER,research_side(rubiks,side_abs, side_abs2));

            }
            // dans le cas du centre on considère que son cubie voisin est le cubie opposé sur le rubiks cube
            // il est donc facile à définir et il n'y a pas de deuxième voisin
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

/**
 * Cette fonction permet de trouver à partir de la position absolu d'une face (neighbour_side)
 * la position relative quelle occupe.
 * exemple : si je souhaite retrouver la position de GREEN par rapport à ORANGE la fonction renvoie LEFT.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param side La face principale qui nous sert de référence pour la recherche
 * @param neighbour_face todo : expliquer
 * @return Renvoi l'indice de la face trouvée ou 0 en cas d'échec de la recherche
 */
int research_side(rubiks_side *rubiks, int side, int neighbour_face){
    // neighbour_face (position absolue de la face voisine)
    // side : face principale
    // face : variable locale pour parcourir la liste de voisin de neighbour side
    for(int face = 0 ; face < 4 ; face++){

        if (rubiks[neighbour_face].neighbour_side[face] == side) {
            return face ;
        }
    }
    return 0;
}

/**
 * Cette fonction retourne le numéro du cubie selon la position relative de la face de son ou de ses voisins.
 *
 * @param side position relative de la face voisine au cubie dont on cherche le numéro.
 * @param type Le type recherché permet d'orienter la recherche
 * @param side2 Dans le cas où l'on cherche la position du'un coin alors il est nécessaire de connaitre la position de la face de son deuxième voisin
 * @return Renvoi l'indice de lu cubie trouvé, -1 en cas d'erreur, ou 0 en cas d'échec de la recherche
 */
int research_num( int side, int type, int side2 ){
    // pour une arrete
    if (type == EDGE){
        // retourne le bon numéro en fonction de la position de la face voisine au cubie
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
    //pour un coin, il est nécessaire d'avoir la position de 2 faces pour définir le numéro d'un cubie
    if(type == CORNER){
        // En fonction de la première face voisine, il reste 2 possibilités
        switch (side) {
            //cas du top
            case 0 :
                // le numéro de la seconde face voisine permet de choisir entre les 2 possibilités restante
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
    return 0;
}
