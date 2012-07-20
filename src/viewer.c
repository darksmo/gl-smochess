#include <stdio.h>
#include <stdlib.h>

#include "viewer.h"

Viewer* create_viewer()
{
    Viewer *v = malloc(sizeof(Viewer));
	v->x=0;
	v->y=1.90;
	v->z=3;
	v->lookat_x = 0;
	v->lookat_y = 0;
	v->lookat_z = 0;

	return v;
}

void observe_from_viewer(Viewer *v) {
   gluLookAt( v->x,        v->y,        v->z,
              v->lookat_x, v->lookat_y, v->lookat_z,
              0.0f, 1.0f, 0.0f );
}

void display_viewer(Viewer *v) {
}

void destroy_viewer(Viewer *v)
{
	free(v);
	v = NULL;
}
