#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chessboard.h"


/* - - - - - - - engine related - - - - - - - */

PieceType bitboard_type_mapper(void *el)
{   
    Pawn **x = (Pawn**) el;
    if (*x) {
        if ((*x)->player == PLAYER_TYPE_BLACK) {
            switch ((*x)->type) { 
                case PAWN_TYPE_KNIGHT: return BLACK_KNIGHT;
                case PAWN_TYPE_BISHOP: return BLACK_BISHOP;
                case PAWN_TYPE_QUEEN:  return BLACK_QUEEN;
                case PAWN_TYPE_PAWN:   return BLACK_PAWN;
                case PAWN_TYPE_ROOK:   return BLACK_ROOK;
                case PAWN_TYPE_KING:   return BLACK_KING;
            }
        }
        else {
            switch ((*x)->type) { 
                case PAWN_TYPE_KNIGHT: return WHITE_KNIGHT;
                case PAWN_TYPE_BISHOP: return WHITE_BISHOP;
                case PAWN_TYPE_QUEEN:  return WHITE_QUEEN;
                case PAWN_TYPE_PAWN:   return WHITE_PAWN;
                case PAWN_TYPE_ROOK:   return WHITE_ROOK;
                case PAWN_TYPE_KING:   return WHITE_KING;
            }
        }
    }
    return PIECE_NONE;
}
void chessboard_ready(Chessboard *cboard) {
    cboard->bitboard = create_bitboard((void *)cboard->board, sizeof(Pawn*), &bitboard_type_mapper, 1);
    print_chessboard(cboard->bitboard);
}

/* - - - - -  chessboard view related - - - - - - */

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
	
    cboard->color_highlighted[R] = 1.0f; cboard->color_highlighted[G] = 0.0f;
	cboard->color_highlighted[B] = 0.0f; cboard->color_highlighted[A] = 0.5f;
	
	cboard->color_specular[R] = 1.0f; cboard->color_specular[G] = 1.0f;
	cboard->color_specular[B] = 1.0f; cboard->color_specular[A] = 1.0f;

	cboard->player_turn = PLAYER_TYPE_WHITE;

    /* select no cell */
    cboard->cell_highlighted = CELL_NONE;
    cboard->cell_selected =  CELL_NONE;
    memset(cboard->cells_highlighted, CELL_NONE, sizeof(int)*64);

	/* logical cells for the pawn */
	cboard->board = malloc(sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);
	memset(cboard->board, 0, sizeof(Pawn*) * NUM_CELLS * NUM_CELLS);

    /* the bitboard */
    cboard->bitboard = NULL;

	return cboard;
}


void chessboard_set_piece_at_cell(Chessboard *cboard, Pawn *p, int cell)
{
	/* invert the position of the pieces along the y-axis */
	p->pos[0] = ((GLdouble)CELLX(cell)/NUM_CELLS) - 0.5f + cboard->cell_width/2;
	p->pos[1] = 0;
	p->pos[2] = ((GLdouble)(NUM_CELLS-CELLY(cell)-1)/NUM_CELLS) - 0.5f + cboard->cell_height/2;
}

void chessboard_place_pawn(Chessboard *cboard, Pawn *p, int cell)
{
    chessboard_set_piece_at_cell(cboard, p, cell);
	cboard->board[cell] = p;
}

void highlight_cell(Chessboard* c, int x, int y)
{
    c->cell_highlighted = CELL(x,y);
}

Pawn *get_pawn(Chessboard* c, int cell)
{
    void *p = get_piece_addr(c->bitboard, _FILE(cell), _RANK(cell));
    if (p) {
        return *((Pawn **) p);
    }
}

void display_chessboard(Chessboard *cboard)
{
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
            if (CELL_NONE != cboard->cells_highlighted[CELL(xcell, ycell)]) {
                glMaterialfv(GL_FRONT, GL_AMBIENT, cboard->color_highlighted);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, cboard->color_highlighted);
                glMaterialfv(GL_FRONT, GL_SPECULAR, cboard->color_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
            }
            else {
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
            void *p = get_piece_addr(cboard->bitboard, xcell, ycell);
			if (p != NULL) {
                Pawn *pawn = *((Pawn **) p);
                chessboard_set_piece_at_cell(cboard, pawn, CELL(xcell, ycell));
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

void set_turn(Chessboard *cboard, PlayerType player) {
	cboard->player_turn = player;
}
void flip_turn(Chessboard *cboard) {
	cboard->player_turn = 
		cboard->player_turn == PLAYER_TYPE_WHITE ? PLAYER_TYPE_BLACK
												 : PLAYER_TYPE_WHITE;
}

void select_cell(Chessboard *cboard, int cell)
{
    Move m;
    m.promote_to = PIECE_NONE;
    int i;
	int cell_wish = cell == CELL_CURRENT ? cboard->cell_highlighted : cell;
	Pawn *p = get_pawn(cboard, cell_wish);
	if (p) {
		if (p->player == cboard->player_turn) {
			/* own pawn selected -- clear selection / select pawn */
			cboard->cell_selected = cell_wish == cboard->cell_selected ? CELL_NONE : cell_wish;
            for (i=0; i<64; i++) { cboard->cells_highlighted[i] = CELL_NONE; }

            /* show legal moves */
            if (cboard->cell_selected != CELL_NONE) {
                m.from_rank = CELLY(cboard->cell_highlighted);
                m.from_file = CELLX(cboard->cell_highlighted);
                while (get_next_legal_move(cboard->bitboard, &m)) {
                    cboard->cells_highlighted[CELL(m.to_file, m.to_rank)] = 1;
                }
            }
		}
		else {
			if(CELL_NONE != cboard->cell_selected) {
				/* opponent pawn selected -- take */
                m.from_rank = CELLY(cboard->cell_selected);
                m.from_file = CELLX(cboard->cell_selected);
                m.to_rank = CELLY(cell_wish);
                m.to_file = CELLX(cell_wish);
                if (is_legal_move(cboard->bitboard, &m)) {
                    /* bitboard */
                    bitboard_do_move(cboard->bitboard, &m);                

                    flip_turn(cboard);
                }
			}
            for (i=0; i<64; i++) { cboard->cells_highlighted[i] = CELL_NONE; }
		}
	}
	else {
		/* empty cell selected */
		if(CELL_NONE != cboard->cell_selected) {
			/* move in empty cell */
            m.from_rank = CELLY(cboard->cell_selected);
            m.from_file = CELLX(cboard->cell_selected);
            m.to_rank = CELLY(cell_wish);
            m.to_file = CELLX(cell_wish);
            if (is_legal_move(cboard->bitboard, &m)) {
                /* bitboard */
                bitboard_do_move(cboard->bitboard, &m);                

                flip_turn(cboard);
            }
		}
		cboard->cell_selected = CELL_NONE;
        for (i=0; i<64; i++) { cboard->cells_highlighted[i] = CELL_NONE; }
	}

}

void chessboard_clear_cell(Chessboard *cboard, int cell)
{
	cboard->board[cell] = NULL;
}
