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

public:
	Poutre(float id, float yCentre, float xCentre, float xG, float xD, float ordoOrigine, float coefDir, float angle);
	float getId();
	float getYCentre();
	float getXCentre();
	float getXG();
	float getXD();
	float getOrdoOrigine();
	float getCoefDir();
	float getAngle();
	static void planchePoutre(float largeur, float longueur, float hauteur);
	static void poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme);
	void dessinerPoutre(bool isTheLastPoutre);
private:
	float id, yCentre, xCentre, xG, xD, ordoOrigine, coefDir, angle;

};


#endif