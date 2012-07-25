#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "pawn.h"
#include "placer.h"
#include "table.h"
#include "viewer.h"
#include "glm.h"

#define HEIGHT 800
#define WIDTH 800

Chessboard *chessboard;
Pawn *pawn[2][16];
Table *table;

/* some lighting */
GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightPositionA[4] = { -100.0f, 100.0f, -100.0f, 1.0f };
GLfloat lightPositionB[4] = {  100.0f, 100.0f,  100.0f, 1.0f };

/* the viewer */
Viewer *viewer;

void init() {
    /* the chessboard and the table and the player (viewer)*/
	chessboard = create_chessboard();
	table      = create_table();

	/* place the chessboard on the table */
	place_on_model(chessboard->pos, (Placeable *) table);

	viewer = create_viewer((Placeable *)chessboard);

	/* the chess set */
	int player, i;
	for (player = 0; player < PLAYER_TYPE_COUNT; player++) {
		for (i=0;  i<8;  i++) pawn[player][i] = create_pawn(PAWN_TYPE_PAWN, player);
		for (i=8;  i<10; i++) pawn[player][i] = create_pawn(PAWN_TYPE_ROOK, player);
		for (i=10; i<12; i++) pawn[player][i] = create_pawn(PAWN_TYPE_KNIGHT, player);
		for (i=12; i<14; i++) pawn[player][i] = create_pawn(PAWN_TYPE_BISHOP, player);
		pawn[player][14] = create_pawn(PAWN_TYPE_QUEEN, player);
		pawn[player][15] = create_pawn(PAWN_TYPE_KING, player);
	}
	
	/* place all the pieces */
	int x, y;
	/* -- white -- */
	y=7; chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][8],  CELL(0, y)); /* rooks */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][9],  CELL(7, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][10], CELL(1, y)); /* knight */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][11], CELL(6, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][12], CELL(2, y)); /* bishop */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][13], CELL(5, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][14], CELL(3, y)); /* queen */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][15], CELL(4, y)); /* king */
	y=6; for (x=0; x<8; x++) chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][x], CELL(x, y));
	
	/* -- black -- */
	y=0; chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][8],  CELL(0, y)); /* rooks */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][9],  CELL(7, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][10], CELL(1, y)); /* knight */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][11], CELL(6, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][12], CELL(2, y)); /* bishop */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][13], CELL(5, y));
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][14], CELL(3, y)); /* queen */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][15], CELL(4, y)); /* king */
	y=1; for (x=0; x<8; x++) chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][x], CELL(x, y));
	
    /* opengl initialisations */
	glClearColor (0.8, 0.8, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	// glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
}

void end() {
	destroy_chessboard(chessboard);
	destroy_viewer(viewer);
}

void display() {
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffers
   glLoadIdentity();
	
   /* lighting */
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightA);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightA);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightA);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPositionA);

   glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLightB);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightB);
   glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightB);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPositionB);
   
   observe_from_viewer(viewer);

   display_table(table);
   display_chessboard(chessboard);

   glFlush();
   glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void timer(int extra) {
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

void keypressed(unsigned char key, int x, int y) {
	if (key == 's') { viewer->pos[2]+=0.05; }
	if (key == 'w') { viewer->pos[2]-=0.05; }
	if (key == 'a') { viewer->pos[0]-=0.05; }
	if (key == 'd') { viewer->pos[0]+=0.05; }
	if (key == 'f') { highlight_cell_left(chessboard); }
	if (key == 'g') { highlight_cell_down(chessboard); }
	if (key == 'h') { highlight_cell_right(chessboard); }
	if (key == 't') { highlight_cell_up(chessboard); }
	if (key == 'p') { select_cell(chessboard, CELL_CURRENT); }
    if (key == 'x') { exit(0); }
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("gl-smochess");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keypressed);

	glutTimerFunc(0,timer,0);
	
    init();
	glutMainLoop();

	end();

	return 0;
}


