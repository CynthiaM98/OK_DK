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
		void tete(float size);
		void corp(float size);
		void membre(float size);
		void printPerso(bool sautEnCours, bool lanceTonneau);

	private : 
		float x, y, z; //coordonn�e
		bool surEchelle;
		float taille;
		Orientation orientation;
	
};


#endif
