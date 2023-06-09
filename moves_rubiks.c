/**
 * @file moves_rubiks.c
 * @author Mathieu CHANTOT et Clément LE STRAT
 * @date 7 Mai 2021
 * @brief Dans ce fichier, on gère les déplacements possible du Rubik's Cube, ainsi que le mélange automatique et la résolution d'un cube.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "draw.h"
#include "moves_rubiks.h"
#include "rubiks.h"

solutions_steps * history = NULL;

/**
 * Cette fonction permet de déplacer un coin du cube sur la face "side", depuis "from" vers "to".
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param side La face du rubiks à traiter
 * @param from Déplacer depuis ce cubie
 * @param to Déplacer vers ce cubie
 */
void move_corner(rubiks_side *rubiks, int side, int from, int to) {
    // On commence par faire tourner le coin.
    rubiks[side].cubie[to].color = rubiks[side].cubie[from].color;
    // Et on fait tourner les coins voisins.
    rubiks[rubiks[side].cubie[to].neighbours[0].num_side].cubie[rubiks[side].cubie[to].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[0].num_side].cubie[rubiks[side].cubie[from].neighbours[0].num_cubie].color ;
    rubiks[rubiks[side].cubie[to].neighbours[1].num_side].cubie[rubiks[side].cubie[to].neighbours[1].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[1].num_side].cubie[rubiks[side].cubie[from].neighbours[1].num_cubie].color ;
}

/**
 * Cette fonction permet de déplacer une arête sur la face "side" depuis "from" vers "to".
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param side La face du rubiks à traiter
 * @param from Déplacer depuis ce cubie
 * @param to Déplacer vers ce cubie
 */
void move_edge(rubiks_side *rubiks, int side, int from, int to) {
    rubiks[side].cubie[to].color = rubiks[side].cubie[from].color;
    rubiks[rubiks[side].cubie[to].neighbours[0].num_side].cubie[rubiks[side].cubie[to].neighbours[0].num_cubie].color =
            rubiks[rubiks[side].cubie[from].neighbours[0].num_side].cubie[rubiks[side].cubie[from].neighbours[0].num_cubie].color;
}

/**
 * cette fonction permet de faire tourner la face side du cube dans le sens horaire
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param side La face à faire tourner dans le sens horaire
 * @param add_to_history Si true, on ajoute le mouvement à l'historique des étapes de la résolution du cube.
 */
void move_side_clockwise(rubiks_side *rubiks, int side, int add_to_history) {
    char tab_face[][10] = {"BLANC", "ORANGE", "VERT", "ROUGE", "BLEU", "JAUNE"};

    int tmp1, tmp2, tmp3;
    // On sauvegarde les données du coin 0 pour pouvoir les utiliser à la fin de l'algorithme, pour écraser le coin 2
    tmp1 = rubiks[side].cubie[0].color;
    tmp2 = rubiks[rubiks[side].cubie[0].neighbours[0].num_side].cubie[rubiks[side].cubie[0].neighbours[0].num_cubie].color;
    tmp3 = rubiks[rubiks[side].cubie[0].neighbours[1].num_side].cubie[rubiks[side].cubie[0].neighbours[1].num_cubie].color;
    // On commence par faire tourner les coins.
    move_corner(rubiks, side, 6, 0);
    move_corner(rubiks, side, 8, 6);
    move_corner(rubiks, side, 2, 8);

    // Et on finit par récupérer les données sauvegardées pour faire "tourner" le cubie[2]
    rubiks[side].cubie[2].color = tmp1;
    rubiks[rubiks[side].cubie[2].neighbours[0].num_side].cubie[rubiks[side].cubie[2].neighbours[0].num_cubie].color = tmp2 ;
    rubiks[rubiks[side].cubie[2].neighbours[1].num_side].cubie[rubiks[side].cubie[2].neighbours[1].num_cubie].color = tmp3 ;

    // Maintenant, on fait tourner les arêtes
    // On sauvegarde les données de l'arête 1 pour pouvoir les utiliser à la fin de l'algorithme, pour écraser l'arête 5
    tmp1 = rubiks[side].cubie[1].color;
    tmp2 = rubiks[rubiks[side].cubie[1].neighbours[0].num_side].cubie[rubiks[side].cubie[1].neighbours[0].num_cubie].color;

    move_edge(rubiks, side, 3, 1);
    move_edge(rubiks, side, 7, 3);
    move_edge(rubiks, side, 5, 7);

    // Et enfin l'arête restante 5, deviens 0.
    rubiks[rubiks[side].cubie[5].neighbours[0].num_side].cubie[rubiks[side].cubie[5].neighbours[0].num_cubie].color = tmp2;
    rubiks[side].cubie[5].color = tmp1;

    // Et on ajoute le mouvement réalisé à l'historique des étapes, uniquement si ça nous a été demandé
    if (add_to_history) {
        if (history == NULL) {
            history = init_solution(tab_face[side]);
        }
        else {
            add_step_to_solution(history, tab_face[side]);
        }
    }
}

/**
 * Cette fonction fait tourner la face side dans le sens anti-horaire. En réalité, cela revient à tourner trois
 * fois dans le sens horaire.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param side La face à faire tourner dans le sens horaire
 * @param add_to_history Si true, on ajoute le mouvement à l'historique des étapes de la résolution du cube.
 */
void move_side_anticlockwise(rubiks_side *rubiks, int side, int add_to_history) {
    char tab_face[][10] = {"BLANC", "ORANGE", "VERT", "ROUGE", "BLEU", "JAUNE"};
    // On appelle trois fois la fonction move_side_clockwise, plutôt que de faire une fonction inverse.
    for (int i = 0; i < 3; i++)
    {
        move_side_clockwise(rubiks, side, false);
    }

    // Et on ajoute le mouvement réalisé à l'historique des étapes, uniquement si ça nous a été demandé
    if (add_to_history) {
        if (history == NULL) {
            history = init_solution(strcat(tab_face[side], " '"));
        }
        else {
            add_step_to_solution(history, strcat(tab_face[side], " '"));
        }
    }
}

/**
 * Cette fonction permet de mélanger le cube de manière aléatoire. Elle choisit entre 20 et 30 mouvements à réaliser
 * tout en choisissant une face à déplacer, au hasard.
 *
 * @param rubiks un pointeur vers une structure rubiks_side
 */
void mix_rubiks(rubiks_side *rubiks){
    // On initialise le système de hasard en fonction de l'heure
    srand(time(NULL));

    // On choisit un nombre de mouvements entre 20 et 30
    int nbr_moves = 20 + rand() % (30 + 1 - 20);
    for (int i = 0 ; i < nbr_moves; i++){
        // Réalise "nbr_moves" nombre de mouvements aléatoires
        move_side_clockwise(rubiks, rand() % (5 + 1), false);
    }
}

/**
 *  Cette fonction permet de créer un damier de couleurs
 *
 * @param rubiks un pointeur vers une structure rubiks_side
 */
void alternate_color(rubiks_side * rubiks){
    move_side_clockwise(rubiks, 0, false);
    move_side_clockwise(rubiks, 0, false);
    move_side_clockwise(rubiks, 5, false);
    move_side_clockwise(rubiks, 5, false);
    move_side_clockwise(rubiks, 1, false);
    move_side_clockwise(rubiks, 1, false);
    move_side_clockwise(rubiks, 3, false);
    move_side_clockwise(rubiks, 3, false);
    move_side_clockwise(rubiks, 2, false);
    move_side_clockwise(rubiks, 2, false);
    move_side_clockwise(rubiks, 4, false);
    move_side_clockwise(rubiks, 4, false);
}

/**
 * Cette fonction permet de résoudre le cube.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void solve_rubiks(rubiks_side *rubiks){
    // On commence par la résolution de la face blanche
    solve_white_side(rubiks);
    // Puis la résolution de la 2eme couronne
    solve_middle_row(rubiks);
    // résolution de la croix blanche
    solve_yellow_cross(rubiks);
    // résolution des coins jaunes
    solve_yellow_corner(rubiks);
    print_solution(history);
    free_solution(history);
}

/**
 * Cette fonction permet de résoudre les coins jaunes
 *
 * @param rubiks Un pointeur vers une structure rubiks
 */
void solve_yellow_corner(rubiks_side * rubiks){
    // cubie permet d'enregistrer les informations d'un cubie (position, voisin, couleur...) après l'avoir cherché
    cubies cubie;
    // ON recherche la position du coin de référence, l'objectif est de correctement le placer
    cubie = search_cubie(rubiks,YELLOW,ORANGE,CORNER);
    int i = 0;
    // 3 possibilités pour que le coin de de référence (orange/vert/jaune) soit bien placé
    while((cubie.cubie_side != YELLOW || cubie.num != 0 ) &&
        (cubie.cubie_side != GREEN || cubie.num != 6 ) &&
        (cubie.cubie_side != ORANGE || cubie.num != 8 )){
        // si le coin de référence se trouve sur le coin qui ne bouge pas ( <=> à 2 mouvements sans résultats), on le change
        if( i == 2){
            turn_three_corner(rubiks);
            i = 0;
        }
        else {
            // tourner 3 côtés
            i++;
            // mouvement de la face jaune obligatoire pour tourner le coin de référence
            move_side_clockwise(rubiks, YELLOW, true);
            turn_three_corner(rubiks);
            move_side_anticlockwise(rubiks, YELLOW, true);
        }
        cubie = search_cubie(rubiks, YELLOW, ORANGE, CORNER);
    }
    while((cubie.cubie_side != YELLOW || cubie.num != 2 ) &&
          (cubie.cubie_side != GREEN || cubie.num != 8 ) &&
          (cubie.cubie_side != RED || cubie.num != 6 )) {
        turn_three_corner(rubiks);
        cubie = search_cubie(rubiks, YELLOW, GREEN, CORNER);
    }
    // La doc du sujet est indigeste, surtout à programmer, donc: on utilise la technique détaillée dans cet articele:
    //https://ruwix.com/the-rubiks-cube/how-to-solve-the-rubiks-cube-beginners-method/orient-yellow-corners-how-to-solve-last-layer-corner/
    // on parcours tous les coins
    for(int j = 0 ; j <= 3 ; j++){
        while(rubiks[YELLOW].cubie[0].color != YELLOW){
            move_side_anticlockwise(rubiks, ORANGE, true);
            move_side_anticlockwise(rubiks, WHITE, true);
            move_side_clockwise(rubiks, ORANGE, true);
            move_side_clockwise(rubiks, WHITE, true);
        }
        move_side_clockwise(rubiks, YELLOW, true);
    }


}

/**
 * Cette fonction permet de faire tourner trois côtés d'une même face sans bouger le 4em
 * et le reste du cube.
 *
 * @param Rubiks est un pointeur vers une strucure rubiks_sid
 */
 void turn_three_corner(rubiks_side *rubiks){
    move_side_anticlockwise(rubiks, RED, true);
    move_side_clockwise(rubiks, YELLOW, true);
    move_side_clockwise(rubiks, ORANGE, true);
    move_side_anticlockwise(rubiks, YELLOW, true);
    move_side_clockwise(rubiks, RED, true);
    move_side_clockwise(rubiks, YELLOW, true);
    move_side_anticlockwise(rubiks, ORANGE, true);
    move_side_anticlockwise(rubiks, YELLOW, true);
 }

/**
 * Cette fonction résoud la croix jaune.
 *
 * @param rubiks Un pointeur vers une structure rubiks
 */
void solve_yellow_cross(rubiks_side *rubiks) {
    // un tableau pour savoir quelles arètes jaunes sont sur la face jaunes
    int yellow_edge[9] = {0};
    int j = 0;
    // si la croix est déjà résolue.
    int cross = 0;
    // on cherche d'abord à résoudre la croix sans se soucier des arêtes
    // parcourir les cubies de la face jaune
    do {
        move_side_clockwise(rubiks, YELLOW, true);
        for (int i = 0; i <= 8; i++) {
            // si le cubie est une arète et qu'il est jaune
            if (rubiks[YELLOW].cubie[i].type == EDGE) {
                if (rubiks[YELLOW].cubie[i].color == YELLOW) {
                    // si le cubie jaune est sur le dessus on note un dans le tableau dédié
                    yellow_edge[i] = 1;
                } else {
                    yellow_edge[i] = 0;
                }
                // on compte le nombre d'arètes parcourues
            }
        }
        j++;
        // si la croix jaune est déjà résolu
        if (yellow_edge[1] == 1 && yellow_edge[3] == 1 && yellow_edge[5] == 1 && yellow_edge[7] == 1) cross = 1;
        if (yellow_edge[1] == 0 && yellow_edge[3] == 0 && yellow_edge[5] == 0 && yellow_edge[7] == 0) cross = -1;
    } while (yellow_edge[5] != 1 && cross == 0);

    // si aucune des arètes est bien placée alors les algorithmes doivent être exécuté
    // si 2 cotés adjacents sont jaune: 2 possibilités
    if ((yellow_edge[5] == 1 && (yellow_edge[1] == 1 || yellow_edge[7] == 1) && cross == 0) || cross == -1) {
        // dans le cas du l il peut être néssessaire de refaire tourner la face jaune
        if (yellow_edge[1] == 1) move_side_clockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, GREEN, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_clockwise(rubiks, GREEN, true);
        move_side_clockwise(rubiks, ORANGE, true);
    }
    // si deux cotés opposés sont jaunes et que les autres ne sont pas jaunes
    if ((yellow_edge[3] == 1 && yellow_edge[5] == 1 && yellow_edge[1] == 0 && yellow_edge[7] == 0 && cross == 0) ||
        cross == -1) {
        move_side_clockwise(rubiks, GREEN, true);
        move_side_clockwise(rubiks, ORANGE, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, GREEN, true);
    }

    // On cherche maintenant à positionner les bon voisins des arêtes
    // on initialise à nouveau cross pour savoir quelle combinaison effectuée
    // elle sont déja bien placées si aucune n'est mal placée
    cross = 0;
    // Tourner la face jaune jusqu'à ce qu'une des combinaison apparaisse
    for (int k =0; k < 4; k++){
        int edge_placed = 1;
        for (int i = ORANGE; i <= BLUE; i++) {
            if (rubiks[i].cubie[7].color != rubiks[i].side) {
                edge_placed = 0;
            }
        }
        if (edge_placed == 1) cross = 1;
    }
    while(cross == 0) {
        move_side_clockwise(rubiks, YELLOW, true);
        // si 2 faces opposées sont bien placés
        if (rubiks[BLUE].cubie[7].color == BLUE && rubiks[GREEN].cubie[7].color == GREEN)
            cross = 2;
        // 2 faces opposées correctement positionnées mais mal placées pour le prochain algo
        if (rubiks[ORANGE].cubie[7].color == ORANGE && rubiks[RED].cubie[7].color == RED) {
            cross = 2;
            move_side_clockwise(rubiks, YELLOW, true);
        }
        // savoir si une arête et sa voisine de droite sont bien placées
        for (int i = ORANGE; i <= BLUE; i++) {
            if (rubiks[i].side == rubiks[i].cubie[7].color &&
                rubiks[rubiks[i].neighbour_side[3]].side == rubiks[rubiks[i].neighbour_side[3]].cubie[7].color) {
                cross = 3;

            }
        }
    }
    // On sait maintenant quel algo exécuter,

    if(cross == 2){
        move_side_clockwise(rubiks, ORANGE, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_clockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);


        cross = 3;

    }
    if(cross == 3){
        // faire tourner la face jaune jusqu'à ce que les 2 arêtes biens placées soient en bonne position pour l'algo
        while (rubiks[BLUE].cubie[7].color != rubiks[rubiks[RED].cubie[7].color].neighbour_side[RIGHT]) {
            move_side_clockwise(rubiks, YELLOW, true);
        }
        move_side_clockwise(rubiks, ORANGE, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_clockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_clockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
        move_side_anticlockwise(rubiks, ORANGE, true);
        move_side_anticlockwise(rubiks, YELLOW, true);
    }

    // faire tourner la face jaune jusqu'à ce que au moins une arête ( <=> toutes les arêtes) retrouve la bonne position
    while(rubiks[GREEN].side != rubiks[GREEN].cubie[7].color){
        move_side_clockwise(rubiks, YELLOW, true);

    }
}


/**
 * Cette fonction cherche à résoudre la 2ème couronne du rubik's cube
 * Le choix est fait de ne pas "retourner" le rubiks cube et d'adapter les algorithmes en conséquence.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side*/
void solve_middle_row(rubiks_side *rubiks){
    // cubie permet d'enregistrer les informations d'un cubie (position, voisin, couleur...) après l'avoir cherché
    cubies cubie;
    //Pour chaque face regarder si l'arrète milieu, gauche est la bonne
    for(int i = ORANGE ; i <= BLUE ; i++){
        // chercher où se trouve le cubie
        cubie = search_cubie(rubiks,i , rubiks[i].neighbour_side[LEFT],EDGE);
        // si le cubie est sur la 2ème couronne, il faut le ramener sur la 3ème
        if(cubie.y == 1 && cubie.cubie_side != YELLOW){
            //prendre l'arrète qui se trouve sur la même face mais sur la 3ème couronne pour le remplacer
            if(cubie.num == 5) {
                right_move(rubiks, rubiks[YELLOW].cubie[rubiks[cubie.cubie_side].cubie[7].neighbours[0].num_cubie]);
            }
            else{
                left_move(rubiks, rubiks[YELLOW].cubie[rubiks[cubie.cubie_side].cubie[7].neighbours[0].num_cubie]);
            }
            cubie = search_cubie(rubiks,i , rubiks[i].neighbour_side[LEFT],EDGE);
        }
        // si le cubie est sur  la face jaune, on cherche à le positionner selon son voisin
        if(cubie.cubie_side == YELLOW){
            while( cubie.neighbours[0].num_side != rubiks[i].neighbour_side[LEFT]){
                move_side_clockwise(rubiks, YELLOW, true);
                cubie = search_cubie(rubiks,i , rubiks[i].neighbour_side[LEFT],EDGE);
            }
            // Déplacer l'arrète de la 3ème couronne à sa position finale
            right_move(rubiks, cubie);
        }
        if(cubie.num == 7){
            while( cubie.cubie_side != i){
                move_side_clockwise(rubiks, YELLOW, true);
                cubie = search_cubie(rubiks,i , rubiks[i].neighbour_side[LEFT],EDGE);
            }
            left_move(rubiks, rubiks[YELLOW].cubie[cubie.neighbours[0].num_cubie]);
        }
    }
}

 /**
  * Cette fonction permet de déplacer une arête correctement positionné de la 3ème couronne à la 2ème couronne
  * Déplacement vers le côté droit.
  * Utilisée lors de la résolution de la 2ème couronne.
  *
  * @param rubiks Un pointeur vers une structure rubiks_side
  * @param cubie cubie situé au dessus de l'arrète à déplacer
  */
void right_move(rubiks_side *rubiks, cubies cubie){
    // algorithme retranscrit pour être réaliser sans retournement du cube
     move_side_anticlockwise(rubiks, YELLOW, true);
     move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[0].num_side].neighbour_side[RIGHT], true);
     move_side_clockwise(rubiks, YELLOW, true);
     move_side_clockwise(rubiks, rubiks[cubie.neighbours[0].num_side].neighbour_side[RIGHT], true);
     move_side_clockwise(rubiks, YELLOW, true);
     move_side_clockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
     move_side_anticlockwise(rubiks, YELLOW, true);
     move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
}

/**
 * Cette fonction permet de déplacer une arête correctement positionné de la 3ème couronne à la 2ème couronne
 * Déplacement vers le côté gauche.
 * Utilisée lors de la résolution de la 2ème couronne.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param cubie cubie situé au dessus de l'arrète à déplacer
 */
void left_move(rubiks_side *rubiks, cubies cubie){
    // algorithme retranscrit pour être réaliser sans retournement du cube
    move_side_clockwise(rubiks, YELLOW, true);
    move_side_clockwise(rubiks, rubiks[cubie.neighbours[0].num_side].neighbour_side[LEFT], true);
    move_side_anticlockwise(rubiks, YELLOW, true);
    move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[0].num_side].neighbour_side[LEFT], true);
    move_side_anticlockwise(rubiks, YELLOW, true);
    move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
    move_side_clockwise(rubiks, YELLOW, true);
    move_side_clockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
}

/**
 * Cette fonction cherche à résoudre la face blanche du Rubik's Cube.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 */
void solve_white_side(rubiks_side * rubiks){
    // On commence par la croix blanche
    // l'idée est de déplacer une arête blanche sur la face jaune, l'aligner avec sa couleur et la mettre sur la face blanche
    // cubie permet d'enregistrer les informations d'un cubie (position, voisin, couleur...) après l'avoir cherché
    cubies cubie;
    // boucle sur les arêtes blanches, on les identifie par la couleur de leur voisin
    for (T_COLOR i = ORANGE ; i < YELLOW ; i++ ){
        // On cherche la position de la combinaison couleur, couleur du voisin, type)
        cubie = search_cubie(rubiks, WHITE, i, EDGE);

        // le mettre sur la face jaune
        //si le cubie se trouve sur la  3ème couronne
        if ((cubie.num == 7 ) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            // le déplacer sur la face jaune
            move_side_clockwise(rubiks, cubie.cubie_side, true);
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT], true);
            //tourner la face jaune pour pouvoir annuler le 2nd mouvement sans revenir en arrière
            move_side_anticlockwise(rubiks, YELLOW, true);
            // annuler le 2nd mouvement
            move_side_anticlockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[LEFT], true);
            // annuler le premier mouvement
            move_side_anticlockwise(rubiks, cubie.cubie_side, true);
            // rechercher la nouvelle position du cubie après déplacement
            cubie = search_cubie(rubiks, WHITE, i, EDGE);
        }
        //si le cubie est sur la 1ère couronne
        else if ((cubie.num == 1) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            // le déplacer sur la face jaune
            move_side_clockwise(rubiks, cubie.cubie_side, true);
            move_side_anticlockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT], true);
            //tourner la face jaune pour pouvoir annuler le 2nd mouvement sans revenir en arrière
            move_side_clockwise(rubiks, YELLOW, true);
            // annuler le 2nd mouvement
            move_side_clockwise(rubiks, rubiks[cubie.cubie_side].neighbour_side[RIGHT], true);
            // je crois qu'annuler le premier mouvement ne sert à rien dans ce cas (aucun bon cubie ne peut occuper cette place)
            //move_side_anticlockwise(rubiks, cubie.cubie_side);
            // rechercher la nouvelle position du cubie après déplacement
            cubie = search_cubie(rubiks, WHITE, i, EDGE);
        }
        // si le cubie se trouve sur une arête de la 2nd couronne
        else if ((cubie.num == 3 || cubie.num == 5) && (cubie.cubie_side > WHITE && cubie.cubie_side < YELLOW)){
            // un mouvement pour arriver sur le jaune
            if( cubie.num == 5) {
                // aller sur le jaune
                move_side_anticlockwise(rubiks, cubie.neighbours[0].num_side, true);
                // tourner le jaune
                move_side_clockwise(rubiks, YELLOW, true);
                // annuler le premier mouvement
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
            }
            else {
                // aller sur le jaune
                move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
                //tourner le jaune
                move_side_clockwise(rubiks, YELLOW, true);
                // annuler le premier mouvement
                move_side_anticlockwise(rubiks, cubie.neighbours[0].num_side, true);
            }
            // rechercher la nouvelle position du cubie après déplacement
            cubie = search_cubie(rubiks, WHITE, i, EDGE);
        }
        // si le cubie est déjà sur la face blanche il n'est peut-être pas à la bonne place
        else if (cubie.cubie_side == WHITE) {
            // aller sur la face jaune
            move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
            move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
            // trouver sa nouvelle position
            cubie = search_cubie(rubiks, WHITE, i, EDGE);
        }
        // tant que le voisin n'est pas sur la bonne face
       while(cubie.neighbours[0].num_side != i ){
           //tourner la face jaune jusqu'à ce que le cubie à placer soit aligné avec la bonne couleur
           move_side_clockwise(rubiks, YELLOW, true);
           //rechercher sa nouvelle position
           cubie = search_cubie(rubiks, WHITE, i,EDGE);
        }
       // placer le cubie une fois aligné sur la face jaune, sur la face blanche
        move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
        move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
    }
    // Ensuite, les coins blancs Coins blancs
    // parcourir les coins blanc en fonction de leur premier voisin (suffisant pour les identifier)
    for(T_COLOR i = ORANGE ; i < YELLOW ; i++ ){
        // chercher la position du premier coin
        cubie = search_cubie(rubiks, WHITE, i,CORNER);
        // si le cubie est sur la 1ère couronne
        if(cubie.y == 0 && cubie.cubie_side != WHITE && cubie.cubie_side != YELLOW) {
            // cas de la position 0
            if (cubie.num == 0) {
                // le mettre sur la 3ème couronne
                move_side_anticlockwise(rubiks, cubie.cubie_side, true);
                //tourner la face jaune !le sens est important!
                move_side_anticlockwise(rubiks, YELLOW, true);
                // annuler le premier mouvement
                move_side_clockwise(rubiks, cubie.cubie_side, true);
                cubie = search_cubie(rubiks, WHITE, i, CORNER);
            }
                // cas de la position 0, seul les sens des mouvements changent
            else {
                // le mettre sur la 3ème couronne
                move_side_clockwise(rubiks, cubie.cubie_side, true);
                //tourner la face jaune !le sens est important!
                move_side_clockwise(rubiks, YELLOW, true);
                // annuler le premier mouvement
                move_side_anticlockwise(rubiks, cubie.cubie_side, true);
                cubie = search_cubie(rubiks, WHITE, i, CORNER);
            }
        }
        // si le cubie est sur la face blanche
        else if (cubie.cubie_side == WHITE){
            // on tourne la face de l'un de ses voisin
            move_side_anticlockwise(rubiks, cubie.neighbours[0].num_side, true);
            //On éloigne le cubie en tournant 2 fois la face jaune
            move_side_clockwise(rubiks, YELLOW, true);
            move_side_clockwise(rubiks, YELLOW, true);
            //annuler le 1er mouvement
            move_side_clockwise(rubiks, cubie.neighbours[0].num_side, true);
            cubie = search_cubie(rubiks, WHITE, i, CORNER);
        }
        // aligner le coins avec le bon angle le bon cubie
        // cas où le cubie est sur la face jaune
        if(cubie.cubie_side == YELLOW){
            //ses voisins doivent être de couleurs inversées
            while(rubiks[cubie.neighbours[0].num_side].cubie[cubie.neighbours[0].num_cubie].color != rubiks[cubie.neighbours[1].num_side].side) {
                move_side_clockwise(rubiks, YELLOW, true);
                cubie = search_cubie(rubiks, WHITE, i, CORNER);
            }
            cubie = search_cubie(rubiks, WHITE, i, CORNER);
            //tourner 1 fois la face de son voisin 2
            move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[1].num_side].side, true);
            // tourner 2 fois la face jaune
            move_side_anticlockwise(rubiks, YELLOW, true);
            move_side_anticlockwise(rubiks, YELLOW, true);
            //remonter une fois la fasse du voisin 1
            move_side_clockwise(rubiks, rubiks[cubie.neighbours[1].num_side].side, true);
            move_side_clockwise(rubiks, YELLOW, true);
            // le cubie n'est maintenant plus sur la face jaune mais toujours sur le boin coin
            cubie = search_cubie(rubiks, WHITE, i, CORNER);

        }
        else{
            //un de ses voisin doit être sur la bonne couleur
            while(rubiks[cubie.neighbours[0].num_side].cubie[cubie.neighbours[0].num_cubie].color != rubiks[cubie.neighbours[0].num_side].side && rubiks[cubie.neighbours[1].num_side].cubie[cubie.neighbours[1].num_cubie].color != rubiks[cubie.neighbours[1].num_side].side){
                move_side_clockwise(rubiks, YELLOW, true);
                cubie = search_cubie(rubiks, WHITE, i, CORNER);

            }
        }
        // positionner correctement le coin, 2 algo selon le voisin bien placé
        if(rubiks[cubie.neighbours[0].num_side].cubie[cubie.neighbours[0].num_cubie].color == rubiks[cubie.neighbours[0].num_side].side) {
            move_side_anticlockwise(rubiks, YELLOW, true);
            move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
            move_side_clockwise(rubiks, YELLOW, true);
            move_side_clockwise(rubiks, rubiks[cubie.neighbours[0].num_side].side, true);
        }
        else{
            move_side_clockwise(rubiks, YELLOW, true);
            move_side_clockwise(rubiks, rubiks[cubie.neighbours[1].num_side].side, true);
            move_side_anticlockwise(rubiks, YELLOW, true);
            move_side_anticlockwise(rubiks, rubiks[cubie.neighbours[1].num_side].side, true);
        }
    }
}

/**
 * Cette fonction permet de trouver un cubie en fonction de sa couleur et celle de ses voisins.
 *
 * @param rubiks Un pointeur vers une structure rubiks_side
 * @param cubie_color couleur du cubie que l'on cherche
 * @param neighbour1 couleur du premier voisin du cubie recherché
 * @param cubie_type type du cubie recherché
 * @return toutes les information sur un cubie une fois qu'il a été trouvé
 */
cubies search_cubie(rubiks_side * rubiks, T_COLOR cubie_color, T_COLOR neighbour1, T_CUBIE_TYPE cubie_type){
    // parcours tous les cubies du rubiks jusqu'à identifier le bon
    for(int face = WHITE; face <= YELLOW; face++){
        for (int cubie = 0; cubie < 9; cubie++) {
            // si la couleur du cubie recherché correspond et si celle de son premier voisin correspondent et si le type correspond
            if(cubie_color == rubiks[face].cubie[cubie].color && neighbour1 == rubiks[rubiks[face].cubie[cubie].neighbours[0].num_side].cubie[rubiks[face].cubie[cubie].neighbours[0].num_cubie].color && cubie_type == rubiks[face].cubie[cubie].type){
                //même pour un corner qui a 2 voisins, le contrôle du premier voisin est suffisant
                return rubiks[face].cubie[cubie] ;
            }
        }
    }
    return rubiks[0].cubie[0];
}

/**
 * Cette fonction initialise une liste chaînée avec le premier mouvement de la solution. Elle renvoie un pointeur
 * vers le premier élément (rubiks_solution.solution) de la liste chaînée (solution_steps).
 *
 * @param new_step Description du premier mouvement, au format texte
 * @return Pointeur vers le premier élément de la liste chaînée de l'historique des étapes de résolution.
 */
solutions_steps * init_solution(char new_step[SIZE_MOVE])
{
    // On initialise le premier élément de la solution, soit le premier élément de la liste chaînée.
    solutions_steps *step = malloc(sizeof(solutions_steps));

    // Gestion des erreurs d'allocation. Moindre problème, on quitte le programme.
    if (step == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Et on initialise la nouvelle liste chaînée avec son premier élément, sans élément suivant
    strcpy(step->solution_step, new_step);
    step->next_step = NULL;
    // Et enfin, on retourne un pointeur vers vers le premier élément de la liste chaînée.
    // Ce pointeur devra être conservé non modifié tout au long de la vie de la liste. Il ne doit pas varier !
    return step;
}

/**
 * Cette fonction ajoute une nouvelle étape de résolution à un historique déjà existant.
 *
 * @param first_step Pointeur vers le premier élément de la liste chaînée de l'historique des étapes de résolution
 * @param new_step Texte à stocker pour cette nouvelle étape
 */
void add_step_to_solution(solutions_steps *first_step, char new_step[SIZE_MOVE])
{
    // On alloue la mémoire pour une nouvelle étape de la solution
    solutions_steps *step_tmp = malloc(sizeof(solutions_steps));
    solutions_steps *tmp;

    // Gestion des erreurs, si l'un des pointeurs est NULL, on quitte.
    if (first_step == NULL || step_tmp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // On sauvegarde le pointeur de tête de liste chaînée, car il ne faut jamais modifier "first_step".
    tmp = first_step;
    // Et on se déplace jusqu'à la fin de la liste chaînée, dans ce cas next_step == NULL
    while (tmp->next_step != NULL) {
        tmp = tmp->next_step;
    }

    // Et enfin, on ajoute le nouvel élément à la fin.
    tmp->next_step = step_tmp;
    strcpy(tmp->next_step->solution_step, new_step);
    // Le suivant est donc NULL
    tmp->next_step->next_step = NULL;
}

/**
 * Cette fonction imprime à l'écran, toutes les étapes d'une solution
 *
 * @param first_step Pointeur vers le premier élément de la liste chaînée de l'historique des étapes de résolution à imprimer.
 */
void print_solution(solutions_steps *first_step)
{
    int i = 0;
    solutions_steps *tmp = NULL;

    // Si first_step n'est pas initialisé, on ne peut rien faire, on sort.
    if (first_step == NULL) {
        return;
    }

    printf("La couleur indiquée donne la face à faire tourner et un \"'\" indique que la rotation se fait dans un sens antihoraire.\n");
    // On sauvegarde la position du premier pointeur pour ne pas le modifier
    tmp = first_step;
    do {
        // On affiche les différents mouvements, en sautant de ligne toutes les 6 "mouvements"
        printf("%s | ", tmp->solution_step);
        tmp = tmp->next_step;
        if( i % 6 == 0 && i != 0) printf("\n");
        i++;
    } while (tmp != NULL);
    printf("\nLe cube a été résolu en %d mouvements\n", --i);
}

/**
 * Cette fonction libère totalement la mémoire allouée par la liste chainée des étapes d'une solution.
 *
 * @param first_step Pointeur vers le premier élément de la liste chaînée de l'historique des étapes de résolution à supprimer.
 */
void free_solution(solutions_steps *first_step)
{
    solutions_steps *next_move;
    solutions_steps * tmp;

    next_move = first_step;
    while (next_move != NULL) {
        // On parcourt la liste chaînée en libérant à chaque fois l'étape en cours, et on se position sur le suivant
        tmp = next_move->next_step;
        free(next_move);
        next_move = tmp;
    }
    first_step = NULL;
}
