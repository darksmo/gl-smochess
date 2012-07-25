#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chessboard.h"

void destroy_chessboard(Chessboard *cboard)
{
    free(cboard->board); cboard->board = NULL;
	free(cboard);        cboard = NULL;
}

Chessboard * create_chessboard()
{
    Chessboard *cboard = malloc(sizeof(Chessboard));
	cboard->pos[0] = 0;
	cboard->pos[1] = 0;
	cboard->pos[2] = 0;

	cboard->cell_height = 1.0f / NUM_CELLS;
	cboard->cell_width  = 1.0f / NUM_CELLS;
	
	/* colors */
	cboard->color_dark[R] = 0.3f; cboard->color_dark[G] = 0.3f;
	cboard->color_dark[B] = 0.4f; cboard->color_dark[A] = 1.0f;

	cboard->color_clear[R] = 1.0f; cboard->color_clear[G] = 1.0f;
	cboard->color_clear[B] = 1.0f; cboard->color_clear[A] = 1.0f;

	cboard->color_selected[R] = 0.0f; cboard->color_selected[G] = 0.0f;
	cboard->color_selected[B] = 1.0f; cboard->color_selected[A] = 0.2f;
	
	cboard->color_specular[R] = 1.0f; cboard->color_specular[G] = 1.0f;
	cboard->color_specular[B] = 1.0f; cboard->color_specular[A] = 1.0f;

    /* select no cell */
    cboard->cell_selected = CELL(0,1);

	/* logical cells for the pawn */
	cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);
	memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}

void chessboard_place_pawn(Chessboard *cboard, Pawn *p, int x, int y) {
	/* invert the position of the pieces along the y-axis */

	p->pos[0] = ((GLdouble)x/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = 0;
	p->pos[2] = ((GLdouble)y/NUM_CELLS) - 0.5f + cboard->cell_height/2;

	cboard->board[CELL(x, y)] = p;
}

void select_cell(Chessboard* c, int x, int y) {
    c->cell_selected = CELL(x,y);
}

Pawn *get_pawn(Chessboard* c, int x, int y) {
	/* invert the position of the pieces along the y-axis */
	return NULL;
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
		ycell = NUM_CELLS;

    	color = 1 - color;
    	for (y=-0.5f; y<0.5f; y+=step){
			ycell--;

    		/* flip color */
    		color = 1 - color;
    
    		/* choose material color */
            if (cboard->cell_selected == CELL(xcell, ycell)) {
                glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_selected);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_selected);
                glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
            }
            else {
                if (color) { 
                    glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_dark);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_dark);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                    glMaterialf(GL_FRONT, GL_SHININESS, 60.0f);
                }
                else {
                    glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_clear);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_clear);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
                }
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
			Pawn *pawn = cboard->board[CELL(xcell, ycell)];
			if (pawn) display_pawn(pawn);
    	}
   }
   glPopMatrix();
}

void select_cell_up(Chessboard *cboard)
{
    if (cboard->cell_selected <= TOTAL_CELLS - NUM_CELLS)
        cboard->cell_selected+=NUM_CELLS;
}
void select_cell_down(Chessboard *cboard)
{
    if (cboard->cell_selected >= NUM_CELLS)
        cboard->cell_selected-=NUM_CELLS;
}
void select_cell_left(Chessboard *cboard)
{
    cboard->cell_selected--;
}
void select_cell_right(Chessboard *cboard)
{
    cboard->cell_selected++;
}

