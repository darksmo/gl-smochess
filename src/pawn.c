#include <stdio.h>
#include <stdlib.h>

#include "pawn.h"

char* _get_model_name(Pawn *pawn, PlayerType player) 
{
	char *model_name = NULL;
    switch (pawn->type) {
        case PAWN_TYPE_PAWN: 
			model_name = "objs/pawn.obj";
			pawn->height = 0.05;
		break;
        case PAWN_TYPE_ROOK: 
			model_name = "objs/rook.obj";
			pawn->height = 0.05;
		break;
        case PAWN_TYPE_KNIGHT: 
			model_name = "objs/knight.obj";
			pawn->height = 0.05;
		break;
        case PAWN_TYPE_BISHOP: 
			model_name = "objs/bishop.obj";
			pawn->height = 0.05;
		break;
        case PAWN_TYPE_QUEEN: 
			model_name = "objs/queen.obj";
			pawn->height = 0.05;
		break;
        case PAWN_TYPE_KING: 
			model_name = "objs/king.obj";
			pawn->height = 0.05;
		break;
    }
	return model_name;
}

Pawn* create_pawn(PawnType type, PlayerType player)
{
    Pawn *pawn = malloc(sizeof(Pawn));
	pawn->pos[0] = 0;
	pawn->pos[1] = 0;
	pawn->pos[2] = 0;
	pawn->width = 0.05f;

	/* pawn colors */
	if (player == PLAYER_TYPE_BLACK) {
		pawn->color[R] = 0.01f;
		pawn->color[G] = 0.01f;
		pawn->color[B] = 0.01f;
		pawn->color[A] = 1.0f;
	}
	else {
		pawn->color[R] = 0.09f;
		pawn->color[G] = 0.09f;
		pawn->color[B] = 0.09f;
		pawn->color[A] = 1.0f;
	}
	pawn->color_selected[R] = 0.05f;
	pawn->color_selected[G] = 0.05f;
	pawn->color_selected[B] = 0.08f;

	pawn->type = type;
	pawn->height = 0.1f + ((GLdouble)type/(GLdouble)PAWN_TYPE_COUNT);

    char *model_name = _get_model_name(pawn, player);

    /* load the model in case */
    if (model_name) {
        pawn->model = (GLMmodel*) malloc(sizeof(GLMmodel));
		pawn->model = glmReadOBJ(model_name);
    }
	return pawn;
}


void display_pawn(Pawn *pawn, PawnState state) {
    glPushMatrix();

    /* draw pawn*/
    glTranslated(pawn->pos[0], pawn->pos[1], pawn->pos[2]);
	glScalef(pawn->width, pawn->height, pawn->width);

    if (pawn->model) {
		/* material colour */
		if (state == PAWN_SELECTED) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pawn->color_selected);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pawn->color_selected);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pawn->color_selected);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 2.5f);
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pawn->color);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pawn->color);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pawn->color);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.5f);
		}
        glmDraw(pawn->model, GLM_SMOOTH);
    }
    glPopMatrix();
}

void destroy_pawn(Pawn *pawn)
{
    free(pawn->model);
	free(pawn);
	pawn = NULL;
}
