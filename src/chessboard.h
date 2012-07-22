#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "pawn.h"

#ifndef CHESSBOARD_h
#define CHESSBOARD_h

#define NUM_CELLS 8

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

	Pawn **board;
} Chessboard;

Chessboard *create_chessboard();
void destroy_chessboard(Chessboard *cboard);
void display_chessboard(Chessboard *cboard);

void chessboard_place_pawn(Chessboard *cboard, Pawn *pawn, int x, int y);

#endif
