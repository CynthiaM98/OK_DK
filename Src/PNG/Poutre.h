#ifndef POUTRE_H
#define POUTRE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Poutre {
	//numeroPoutre,yCentre,xGauche,xDroit,ordoOrigine,coefDir

	public : 
		Poutre(float id, float yCentre, float xG, float xD, float ordoOrigine, float coefDir);
		float getId();
		float getYCentre();
		float getXG();
		float getXD();
		float getOrdoOrigine();
		float getCoefDir();
		static void planchePoutre(float largeur, float longueur, float hauteur);
		static void poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme);
		static void placementPoutres();
	private :
		float id, yCentre, xG, xD, ordoOrigine, coefDir;
		
};


#endif