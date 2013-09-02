#include <stdio.h>
#include <stdlib.h>

#include "viewer.h"

Viewer* create_viewer(Placeable *object)
{
    Viewer *v = malloc(sizeof(Viewer));
	if (object) {
		v->pos[0] = object->pos[0];
		v->pos[1] = object->pos[1];
		v->pos[2] = object->pos[2];
        observe_object(v, object);
	}
	else {
		v->pos[0] = 0;
		v->pos[1] = 0.1;
		v->pos[2] = 1;
		v->lookat[0] = 0;
		v->lookat[1] = 0;
		v->lookat[2] = 0;
	}
	
    v->model = (GLMmodel*) malloc(sizeof(GLMmodel));
	v->model = glmReadOBJ("objs/girl/girl.obj");

    // dimensions
    GLfloat dimensions[3];
    glmDimensions(v->model, dimensions);
    v->height = dimensions[1];
    v->width = dimensions[0];
    v->depth = dimensions[2];

    // look at 90% of the height of the model from its center.
    v->eye_at[0] = 0.5; // w
    v->eye_at[1] = 0.9; // h

	return v;
}

void observe_object(Viewer *v, Placeable *object) 
{
    v->lookat[0] = object->pos[0];
    v->lookat[1] = object->pos[1];
    v->lookat[2] = object->pos[2];
}

void observe_from_viewer(Viewer *v) 
{
   gluLookAt(
       // eye position
       v->pos[0], 
       v->pos[1] + (
          (v->height/2) * v->eye_at[1]
       ),
       v->pos[2],
       // center of the object to look at
       v->lookat[0], v->lookat[1], v->lookat[2],
       0.0f, 1.0f, 0.0f );
}

void display_viewer(Viewer *v) {
    glPushMatrix();	
    glTranslated(v->pos[0], v->pos[1], v->pos[2]);
	glmDraw(v->model, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

void destroy_viewer(Viewer *v)
{
	free(v);
	v = NULL;
}
