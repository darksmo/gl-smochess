#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "pawn.h"

#ifndef CHESSBOARD_h
#define CHESSBOARD_h


#define NUM_CELLS 8
#define TOTAL_CELLS (NUM_CELLS*NUM_CELLS)
#define CELL(x,y) (x+(NUM_CELLS*(y)))
#define R 0
#define G 1
#define B 2
#define A 3

typedef struct {
	GLdouble pos[3]; /* placeable, x, y, z */

	GLdouble cell_width;
	GLdouble cell_height;

	GLfloat color_dark[4];
	GLfloat color_clear[4];
	GLfloat color_specular[4];

    int cell_selected;
    GLfloat color_selected[4];

	Pawn **board;
} Chessboard;

Chessboard *create_chessboard();
void destroy_chessboard(Chessboard *cboard);
void display_chessboard(Chessboard *cboard);

void select_cell(Chessboard *cboard, int x, int y);
void select_cell_up(Chessboard *cboard);
void select_cell_down(Chessboard *cboard);
void select_cell_left(Chessboard *cboard);
void select_cell_right(Chessboard *cboard);

void chessboard_place_pawn(Chessboard *cboard, Pawn *pawn, int x, int y);

#endif
