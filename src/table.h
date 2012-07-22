#ifndef TABLE_h 
#define TABLE_h

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "glm.h"

#define R 0
#define G 1
#define B 2
#define A 3

typedef struct {
	GLdouble pos[3];
    GLMmodel *model;

	GLdouble width;
	GLdouble height;

	GLfloat color[4];
	GLfloat color_specular[4];
	GLfloat shininess;
} Table;

Table * create_table();
void destroy_table(Table *table);
void display_table(Table *table);

#endif
