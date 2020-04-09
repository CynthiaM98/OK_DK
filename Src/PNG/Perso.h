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
		bool getSurEchelle();
		Orientation getOrientation();
		void setX(float newX);
		void setY(float newY);
		void setOrientation(Orientation newOr);
		void setSurEchelle(bool status);
		void tete(float size);
		void corp(float size);
		void membre(float size);
		void printPerso(bool sautEnCours);

	private : 
		float x, y, z; //coordonnée
		bool surEchelle;
		Orientation orientation;
	
};


#endif
