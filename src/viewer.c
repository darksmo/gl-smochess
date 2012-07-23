#include <stdio.h>
#include <stdlib.h>

#include "viewer.h"

Viewer* create_viewer(Placeable *object)
{
    Viewer *v = malloc(sizeof(Viewer));
	if (object) {
		v->pos[0] = object->pos[0];
		v->pos[1] = object->pos[1] + 0.55f;
		v->pos[2] = object->pos[2] + 0.85f;
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
   gluLookAt( v->pos[0]  , v->pos[1]  , v->pos[2],
              v->lookat[0], v->lookat[1], v->lookat[2],
              0.0f, 1.0f, 0.0f );
}

void display_viewer(Viewer *v) {
}

void destroy_viewer(Viewer *v)
{
	free(v);
	v = NULL;
}
