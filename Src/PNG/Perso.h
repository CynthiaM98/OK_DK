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
		float getTaille();
		Orientation getOrientation();
		void setX(float newX);
		void setY(float newY);
		void setOrientation(Orientation newOr);
		void tete(float size);
		void corp(float size);
		void membre(float size);
		void printPerso();

	private : 
		float x, y, z; //coordonnée
		Orientation orientation;
	
};


#endif
