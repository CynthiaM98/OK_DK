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
		Perso(float x,float y,float z,float taille);
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
		void tete(float size, unsigned int *texID);
		void corps(float size, unsigned int *texID);
		void myCube(float size, unsigned int *texID);
		void membre(float size, unsigned int *texID);
		void printPerso(bool sautEnCours, bool lanceTonneau, unsigned int *texID);

	private : 
		float x, y, z; //coordonn�e
		bool surEchelle;
		float taille;
		Orientation orientation;
	
};


#endif
