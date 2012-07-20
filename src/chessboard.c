#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>

#include "chessboard.h"

#define XXX cboard->cell_height

Chessboard * create_chessboard()
{
    Chessboard *cboard = malloc(sizeof(Chessboard));
	cboard->x = 0;
	cboard->y = 0;
	cboard->z = 0;
	cboard->ncells = NUM_CELLS;
	cboard->border = 0;
	cboard->cell_height = 1.0f / NUM_CELLS;
	cboard->cell_width  = 1.0f / NUM_CELLS;
	cboard->color_dark[R] = 139;
	cboard->color_dark[G] = 69;
	cboard->color_dark[B] = 19;
	cboard->color_clear[R] = 255;
	cboard->color_clear[G] = 215;
	cboard->color_clear[B] = 0;

	cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}

void chessboard_place_pawn(Chessboard *cboard, Pawn *p, int x, int y) {
	/* invert the position of the pieces along the y-axis */
	y = NUM_CELLS - y - 1;

	p->x = ((GLdouble)x/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->y = 0;
	p->z = ((GLdouble)y/NUM_CELLS) - 0.5f + cboard->cell_height/2;
	cboard->board[x + (NUM_CELLS * y)] = p;
}

Pawn *get_pawn(Chessboard* c, int x, int y) {
	/* invert the position of the pieces along the y-axis */
	y = NUM_CELLS - y - 1;

	return c->board[x + (NUM_CELLS * y)];
}

void display_chessboard(Chessboard *cboard) {
    glPushMatrix();
    GLdouble x, y;
    int color = 0;
    
	int xcell = -1;
	int ycell;
    glColor3f(cboard->color_dark[R], cboard->color_dark[G], cboard->color_dark[B]);
	GLdouble step = cboard->cell_width;
    for (x=-0.5f; x<0.5f; x+=step){
		xcell++;
		ycell = -1;

    	color = 1 - color;
    	for (y=-0.5f; y<0.5f; y+=step){
			ycell++;

    		/* flip color */
    		color = 1 - color;
    
    		/* choose color */
    		if (color) { 
    			glColor3ub(cboard->color_dark[R], cboard->color_dark[G],
    				cboard->color_dark[B]);
    		}
    		else {
    			glColor3ub(cboard->color_clear[R], cboard->color_clear[G],
    				cboard->color_clear[B]);
    		}
    		/* draw cell */
    		glBegin(GL_QUADS);
    			glVertex3d(x, 0, y);
    			glVertex3d(x+step, 0, y);
    			glVertex3d(x+step, 0, y+step);
    			glVertex3d(x, 0, y+step);
    		glEnd();

			/* draw pawn at cell */
			Pawn *pawn = get_pawn(cboard, xcell, ycell);
			if (pawn) display_pawn(pawn);
    	}
   }
   glTranslatef(cboard->x, cboard->y, cboard->z);
   glPopMatrix();
}

void destroy_chessboard(Chessboard *cboard)
{
	free(cboard);
	cboard = NULL;
}
