#ifndef PAWN_h 
#define PAWN_h

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "glm.h"

#define R 0
#define G 1
#define B 2
#define A 3

typedef enum player_type_t {
	PLAYER_TYPE_WHITE,
	PLAYER_TYPE_BLACK,
	PLAYER_TYPE_COUNT,
} PlayerType;

typedef enum pawn_type_t {
	PAWN_TYPE_PAWN,
	PAWN_TYPE_KNIGHT,
	PAWN_TYPE_BISHOP,
	PAWN_TYPE_ROOK,
	PAWN_TYPE_QUEEN,
	PAWN_TYPE_KING,
	PAWN_TYPE_COUNT,
} PawnType;

typedef struct {
	/* An object always starts with these fields */
	GLdouble pos[3];
    GLMmodel *model;

	PawnType type;
	GLdouble width;
	GLdouble height;

	GLfloat color[4];
	GLfloat color_specular[4];
	GLfloat shininess;
} Pawn;

Pawn * create_pawn(PawnType type, PlayerType player);
void destroy_pawn(Pawn *pawn);
void display_pawn(Pawn *pawn);

#endif
