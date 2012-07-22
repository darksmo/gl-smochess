#include "placer.h"
#include "common.h"

void place_on_model(GLdouble pos[], Placeable *object)
{
	pos[1] = 0.5;
	GLfloat model_dimensions[3];
	glmDimensions(object->model, model_dimensions);
	pos[1] = object->pos[1] + model_dimensions[1] + 0.001;
}
