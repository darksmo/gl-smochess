#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#include "pawn.h"

Pawn * create_pawn(PawnType type, PlayerType player)
{
    Pawn *pawn = malloc(sizeof(Pawn));
	pawn->x = 0.0f;
	pawn->y = 0.0f;
	pawn->z = 0.0f;
	pawn->width = 0.05f;

	if (player == PLAYER_TYPE_BLACK) {
		pawn->color[R] = 0;
		pawn->color[G] = 0;
		pawn->color[B] = 0;
	}
	else {
		pawn->color[R] = 255;
		pawn->color[G] = 255;
		pawn->color[B] = 255;
	}

	pawn->type = type;
	pawn->height = 0.1f + ((GLdouble)type/(GLdouble)PAWN_TYPE_COUNT);

	pawn->va[0] = -1.0f; pawn->va[1] = 0.0f; pawn->va[2] =  1.0f; 
	pawn->vb[0] =  1.0f; pawn->vb[1] = 0.0f; pawn->vb[2] =  1.0f; 
	pawn->vc[0] =  1.0f; pawn->vc[1] = 0.0f; pawn->vc[2] = -1.0f; 
	pawn->vd[0] = -1.0f; pawn->vd[1] = 0.0f; pawn->vd[2] = -1.0f; 
	pawn->ve[0] =  0.0f; pawn->ve[1] = 1.0f; pawn->ve[2] =  0.0f; 
	return pawn;
}

void display_pawn(Pawn *pawn) {
    glPushMatrix();
    
    glColor3d(pawn->color[R], pawn->color[G], pawn->color[B]);

    /* draw pawn*/
    glTranslated(pawn->x, pawn->y, pawn->z);
	glScalef(pawn->width, pawn->height, pawn->width);

    glBegin(GL_TRIANGLES);
		glVertex3dv(pawn->va); glVertex3dv(pawn->vd); glVertex3dv(pawn->ve);
		glVertex3dv(pawn->vb); glVertex3dv(pawn->va); glVertex3dv(pawn->ve);
		glVertex3dv(pawn->vc); glVertex3dv(pawn->vb); glVertex3dv(pawn->ve);
		glVertex3dv(pawn->vd); glVertex3dv(pawn->vc); glVertex3dv(pawn->ve);
    glEnd();

    glPopMatrix();
}

void destroy_pawn(Pawn *cboard)
{
	free(cboard);
	cboard = NULL;
}
