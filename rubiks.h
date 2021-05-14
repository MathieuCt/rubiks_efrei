/**
 * @file rubiks.h
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on trouve Headers et structures utilisées partout dans le code. Et notamment dans rubiks.c
 */
#ifndef RUBIKS_EFREI_RUBIKS_H
#define RUBIKS_EFREI_RUBIKS_H

typedef enum {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW} T_COLOR;
typedef enum {UP, RIGHT, DOWN, LEFT} T_SIDE;
typedef enum {CORNER, EDGE, CENTER} T_CUBIE_TYPE;

//todo : commenter toutes les structures et à quoi servent chacun des membres
/**
 * Définition des adjacents à un cubie
 * @param num_side Face de rattachement du voisin
 * @param num_cubie Numéro du cubie dans sa face de rattachement. De 0 à 8.
 */
typedef struct {
    T_COLOR num_side;
    int num_cubie;
} neighbour; //todo : probablement à renommer

/**
 * Définition des cubies, qui sont les petits cubes de couleur rattachés à une face
 * @param x coordonnée horizontale du cubie
 * @param y coordonnée verticale du cubie
 * @param num Numéro du cubie dans la face : de 0 à 8
 * @param type Type de cubie, CORNER, EDGE ou CENTER
 * @param color Couleur du cubie
 * @param cubie_side Face de rattachement du cubie
 * @param neighbours[2] Définition des faces adjacentes au cubie. Il peut y en avoir 2 pour un CORNER et 1 pour un EDGE
 */
typedef struct {
    int x;
    int y;
    int num;
    T_CUBIE_TYPE type;
    T_COLOR color;
    T_COLOR cubie_side;
    neighbour neighbours[2];
} cubies;

/**
 * Définition d'une face du Rubik's Cube
 * @param neighbour_side[4] Une face a 4 faces adjacentes, UP, DOWN, LEFT, et RIGHT.
 * @param opposite_side Définition de la face opposée.
 * @param side Définition du numéro et couleur de la face. Soir WHITE, ORANGE, GREEN, RED, BLUE, ou YELLOW
 * @param cubie[9] Liaison vers les 9 cubies composants une face
 */
typedef struct {
    T_COLOR neighbour_side[4];
    T_COLOR opposite_side;
    T_COLOR side;
    cubies cubie[9];
} rubiks_side;

void rubiks_creation(rubiks_side *rubiks);
int research_side(rubiks_side *,int, int);
int research_num(int, int, int);
void rubiks_neighbour(rubiks_side *);


#endif //RUBIKS_EFREI_RUBIKS_H
