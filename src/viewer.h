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
    GLfloat height;
    GLfloat width;
    GLfloat depth;
    /* 
     * the percentage across the object width at which the eye of the
     * object is located
     * eye_at[0] = 0.0f: left side; 0.5f: middle; 1.0f: right side;
     * eye_at[1] = 0.0f: feet; 0.5: belly (center); 1.0f: head;
     */
    GLfloat eye_at[2];
    GLMmodel *model;
} Viewer;

Viewer* create_viewer(Placeable *object);
void observe_from_viewer(Viewer *v);
void display_viewer(Viewer *v);
void destroy_viewer(Viewer *v);
void observe_object(Viewer *v, Placeable *object);

#endif
