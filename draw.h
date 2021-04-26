//
// Created by clestrat on 26/04/2021.
//

#ifndef RUBIKS_EFREI_DRAW_H
#define RUBIKS_EFREI_DRAW_H
#include <ncurses.h>

#define RUBIK_LINES 3
#define RUBIK_COLS 4

#define SQ_HEIGHT 4
#define SQ_WIDTH 8
#define SQUARES (RUBIK_LINES * 3) * (RUBIK_COLS * 3)

extern WINDOW *BOARD[SQUARES];

extern const short BLACK_ON_WHITE;
extern const short BLACK_ON_ORANGE;
extern const short BLACK_ON_GREEN;
extern const short BLACK_ON_RED;
extern const short BLACK_ON_BLUE;
extern const short BLACK_ON_YELLOW;

bool check_term(void);

bool colors(void);

void create_board(void);

void destroy_board(void);

void detect_resize(__attribute__((unused)) int);

#endif //RUBIKS_EFREI_DRAW_H
