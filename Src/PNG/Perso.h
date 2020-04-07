#ifndef PERSO_H
#define PERSO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Perso {

	

	public:
		enum Orientation { Droite, Gauche, Dos };
		Perso(float x,float y,float z);
		float getX();
		float getY();
		float getZ();
		Orientation getOrientation();
		void setX(float newX);
		void setY(float newY);
		void setOrientation(Orientation newOr);
		void teteMario(float size);
		void corpMario(float size);
		void membreMario(float size);
		void printMario(bool isMario);

	private : 
		float x, y, z; //coordonnée
		Orientation orientation;
	
};


#endif
