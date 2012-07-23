#ifndef VIEWER_h
#define VIEWER_h

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "common.h"

typedef struct {
	GLdouble pos[3];
	GLdouble lookat[3];
} Viewer;

Viewer* create_viewer(Placeable *object);
void observe_from_viewer(Viewer *v);
void display_viewer(Viewer *v);
void destroy_viewer(Viewer *v);
void observe_object(Viewer *v, Placeable *object);

#endif
