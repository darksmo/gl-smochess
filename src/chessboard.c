#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chessboard.h"

Chessboard * create_chessboard()
{
    Chessboard *cboard = malloc(sizeof(Chessboard));
	cboard->pos[0] = 0;
	cboard->pos[1] = 0;
	cboard->pos[2] = 0;

	cboard->cell_height = 1.0f / NUM_CELLS;
	cboard->cell_width  = 1.0f / NUM_CELLS;
	
	/* colors */
	cboard->color_dark[R] = 0.4f; cboard->color_dark[G] = 0.4f;
	cboard->color_dark[B] = 0.4f; cboard->color_dark[A] = 1.0f;

	cboard->color_clear[R] = 1.0f; cboard->color_clear[G] = 1.0f;
	cboard->color_clear[B] = 1.0f; cboard->color_clear[A] = 1.0f;
	
	cboard->color_specular[R] = 1.0f; cboard->color_specular[G] = 1.0f;
	cboard->color_specular[B] = 1.0f; cboard->color_specular[A] = 1.0f;

	/* logical cells for the pawn */
	cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);
	memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}

void chessboard_place_pawn(Chessboard *cboard, Pawn *p, int x, int y) {
	/* invert the position of the pieces along the y-axis */
	y = NUM_CELLS - y - 1;

	p->pos[0] = ((GLdouble)x/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = 0;
	p->pos[2] = ((GLdouble)y/NUM_CELLS) - 0.5f + cboard->cell_height/2;
	cboard->board[x + (NUM_CELLS * y)] = p;
}

Pawn *get_pawn(Chessboard* c, int x, int y) {
	/* invert the position of the pieces along the y-axis */
	y = NUM_CELLS - y - 1;

	return c->board[x + (NUM_CELLS * y)];
}

void display_chessboard(Chessboard *cboard) {
    glPushMatrix();
    glTranslatef(cboard->pos[0], cboard->pos[1], cboard->pos[2]);
    GLdouble x, y;
    int color = 0;
    
	int xcell = -1;
	int ycell;
	GLdouble step = cboard->cell_width;
    for (x=-0.5f; x<0.5f; x+=step){
		xcell++;
		ycell = -1;

    	color = 1 - color;
    	for (y=-0.5f; y<0.5f; y+=step){
			ycell++;

    		/* flip color */
    		color = 1 - color;
    
    		/* choose material color */
    		if (color) { 
				glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_dark);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_dark);
				glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
    		}
    		else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_clear);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_clear);
				glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
    		}

    		/* draw cell */
    		glBegin(GL_QUADS);
				glNormal3f(0.0,0.0,1.0);
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
   glPopMatrix();
}

void destroy_chessboard(Chessboard *cboard)
{
	free(cboard);
	cboard = NULL;
}
