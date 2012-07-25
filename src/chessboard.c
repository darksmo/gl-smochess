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
    cboard->cell_highlighted = CELL_NONE;
    cboard->cell_selected =  CELL_NONE;

	/* logical cells for the pawn */
	cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);
	memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

	return cboard;
}

void chessboard_place_pawn(Chessboard *cboard, Pawn *p, int cell) {
	/* invert the position of the pieces along the y-axis */

	p->pos[0] = ((GLdouble)CELLX(cell)/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = 0;
	p->pos[2] = ((GLdouble)CELLY(cell)/NUM_CELLS) - 0.5f + cboard->cell_height/2;

	cboard->board[CELL(CELLX(cell),NUM_CELLS - CELLY(cell) - 1)] = p;
}

void highlight_cell(Chessboard* c, int x, int y) {
    c->cell_highlighted = CELL(x,y);
}

Pawn *get_pawn(Chessboard* c, int cell) {
	return c->board[cell];
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
            if (cboard->cell_highlighted == CELL(xcell, ycell)) {
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
			Pawn *pawn = get_pawn(cboard, CELL(xcell, ycell));
			if (pawn) {
				display_pawn(pawn, 
					CELL(xcell, ycell) == cboard->cell_selected ? PAWN_SELECTED 
																: PAWN_NORMAL
				);
			}
    	}
   }
   glPopMatrix();
}

void highlight_cell_up(Chessboard *cboard)
{
	int celly = CELLY(cboard->cell_highlighted);
	celly += celly == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
    cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly);
}
void highlight_cell_down(Chessboard *cboard)
{
	int celly = CELLY(cboard->cell_highlighted);
	celly -= celly == 0 ? -NUM_CELLS + 1 : 1; 
    cboard->cell_highlighted = CELL(CELLX(cboard->cell_highlighted), celly);
}
void highlight_cell_left(Chessboard *cboard)
{
	int cellx = CELLX(cboard->cell_highlighted);
	cellx += cellx == 0 ? NUM_CELLS-1 : -1; 
    cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted));
}
void highlight_cell_right(Chessboard *cboard)
{
	int cellx = CELLX(cboard->cell_highlighted);
	cellx += cellx == NUM_CELLS-1 ? -NUM_CELLS+1 : 1; 
    cboard->cell_highlighted = CELL(cellx, CELLY(cboard->cell_highlighted));
}
void select_cell(Chessboard *cboard, int cell)
{
	int cell_wish = cell == CELL_CURRENT ? cboard->cell_highlighted : cell;
	if (get_pawn(cboard, cell_wish)) {
		cboard->cell_selected = cell_wish;
	}
}

