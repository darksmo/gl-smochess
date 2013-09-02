#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "pawn.h"
#include "bitboard.h"
#include "engine.h"

#ifndef CHESSBOARD_h
#define CHESSBOARD_h


#define NUM_CELLS 8
#define TOTAL_CELLS (NUM_CELLS*NUM_CELLS)
#define CELLY(cell) ((int)((float)cell/(float)NUM_CELLS))
#define CELLX(cell) (cell - (NUM_CELLS * CELLY(cell)))
#define CELL_CURRENT -2
#define CELL_NONE -1
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
    GLfloat color_highlighted[4];

    int cell_highlighted;
    int cell_selected;
    GLfloat color_selected[4];
    int cells_highlighted[64];

	PlayerType player_turn;

    /* the bitboard representation of the chessboard */
    Bitboard *bitboard;


	Pawn **board;
} Chessboard;

Chessboard *create_chessboard();
void destroy_chessboard(Chessboard *cboard);
void display_chessboard(Chessboard *cboard);

void highlight_cell(Chessboard *cboard, int x, int y);
void highlight_cell_up(Chessboard *cboard);
void highlight_cell_down(Chessboard *cboard);
void highlight_cell_left(Chessboard *cboard);
void highlight_cell_right(Chessboard *cboard);
void select_cell(Chessboard *cboard, int cell, char key);

void chessboard_place_pawn(Chessboard *cboard, Pawn *pawn, int cell);
void chessboard_clear_cell(Chessboard *cboard, int cell);

/* 
 * chessboard_ready: to be called after the pawns have been placed on the
 * initial chessboard. This procedure initializes the internal bitboard based
 * on the pawn placed on the 3d chessboard.
 */
void chessboard_ready(Chessboard *cboard);

#endif
