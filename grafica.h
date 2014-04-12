#ifndef GRAFICA_H
#define GRAFICA_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern const int SCREEN_FPS;

int initGL();
void render();
void change_size();
void draw();
#endif
