#include <GLUT/glut.h>

#ifndef VIEWER_h
#define VIEWER_h

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;	
	GLdouble lookat_x;
	GLdouble lookat_y;
	GLdouble lookat_z;
} Viewer;

Viewer* create_viewer();
void observe_from_viewer(Viewer *v);
void display_viewer(Viewer *v);
void destroy_viewer(Viewer *v);

#endif
