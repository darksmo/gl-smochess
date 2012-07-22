#include "table.h"

Table * create_table()
{
	Table *table = malloc(sizeof(Table));
	table->pos[0] = 0;
	table->pos[1] = 0;
	table->pos[2] = 0;

	table->model = (GLMmodel*) malloc(sizeof(GLMmodel));
	table->model = glmReadOBJ("objs/table/minotti.obj");

	return table;
}

void destroy_table(Table *table)
{
	free(table);
}

void display_table(Table *table)
{
    glPushMatrix();	
    glTranslated(table->pos[0], table->pos[1], table->pos[2]);
	glmDraw(table->model, GLM_SMOOTH | GLM_MATERIAL );
	glPopMatrix();
}
