#ifndef COORDONNEE2D_H
#define COORDONNEE2D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Coordonnee2D {

public:
	Coordonnee2D(float x, float y);
	Coordonnee2D();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

private:
	float x, y;


};

#endif