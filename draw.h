//
// Created by clestrat on 26/04/2021.
//

#ifndef RUBIKS_EFREI_DRAW_H
#define RUBIKS_EFREI_DRAW_H
#include <ncurses.h>

#define SQ_HEIGHT 4
#define SQ_WIDTH 8
#define SQUARES 30

extern WINDOW *BOARD[SQUARES];

extern const short BLACK_ON_GREEN;
extern const short BLACK_ON_BLUE;

bool check_term(void);

bool colors(void);

void create_board(void);

void destroy_board(void);

void detect_resize(int);

#endif //RUBIKS_EFREI_DRAW_H
