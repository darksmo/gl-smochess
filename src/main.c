#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "pawn.h"
#include "viewer.h"
#include "glm.h"

#define HEIGHT 800
#define WIDTH 800

Chessboard *chessboard;
Pawn *pawn[2][16];

/* some lighting */
GLfloat ambientLight[4] = { 0.4f, 0.4f, 0.5f, 1.0f };
GLfloat diffuseLight[4] = { 0.6f, 0.6f, 0.5f, 1.0f };
GLfloat specularLight[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat position[4] = { 1.0f, 1.0f, 1.0f, 0.3f };

/* the viewer */
Viewer *viewer;

void init() {
	viewer = create_viewer();

    /* the chessboard */
	chessboard = create_chessboard();

	/* create chess set */
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
	y=0; chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][8], 0, y); /* rooks */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][9], 7, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][10], 1, y); /* knight */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][11], 6, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][12], 2, y); /* bishop */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][13], 5, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][14], 3, y); /* queen */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][15], 4, y); /* king */
	y=1; for (x=0; x<8; x++) chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_WHITE][x], x, y);
	
	/* -- black -- */
	y=7; chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][8], 0, y); /* rooks */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][9], 7, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][10], 1, y); /* knight */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][11], 6, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][12], 2, y); /* bishop */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][13], 5, y);
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][14], 3, y); /* queen */
	     chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][15], 4, y); /* king */
	y=6; for (x=0; x<8; x++) chessboard_place_pawn(chessboard, pawn[PLAYER_TYPE_BLACK][x], x, y);
	
    /* opengl initialisations */
	glClearColor (0.8, 0.8, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	/* lighting */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void end() {
	destroy_chessboard(chessboard);
	destroy_viewer(viewer);
}

void display() {
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffers
   glLoadIdentity();
   
   observe_from_viewer(viewer);

   display_chessboard(chessboard);

   // glFlush();
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
	if (key == 's') { viewer->z+=0.05; }
	if (key == 'w') { viewer->z-=0.05; }
	if (key == 'a') { viewer->x-=0.05; }
	if (key == 'd') { viewer->x+=0.05; }
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


