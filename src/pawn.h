#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#ifndef PAWN_h 
#define PAWN_h

#define R 0
#define G 1
#define B 2

typedef enum player_type_t {
	PLAYER_TYPE_BLACK,
	PLAYER_TYPE_WHITE,
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
	GLdouble x; /* placeable */
	GLdouble y;
    GLdouble z;

	PawnType type;
	GLdouble width;
	GLdouble height;
	GLdouble color[3];

	/* some vertices */
    GLdouble va[3];
	GLdouble vb[3];
	GLdouble vc[3];
	GLdouble vd[3];
	GLdouble ve[3];
} Pawn;

Pawn *create_pawn();
void destroy_pawn(Pawn *cboard);
void display_pawn(Pawn *cboard);

#endif
