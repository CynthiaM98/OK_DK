/********************************************************************************************/
/********************************************************************************************/
/* MAILLARD Cynthia - AUBRY Clément - THIEBAUD Jérémy*/
/********************************************************************************************/
/********************************************************************************************/


#ifndef POUTRE_H
#define POUTRE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Poutre {
	//numeroPoutre,yCentre,xCentre,xGauche,xDroit,ordoOrigine,coefDir,angle

public:
	Poutre(float id, float yCentre, float xCentre, float xG, float xD, float ordoOrigine, float coefDir, float angle);
	Poutre();
	float getId();
	float getYCentre();
	float getXCentre();
	float getXG();
	float getXD();
	float getOrdoOrigine();
	float getCoefDir();
	float getAngle();
	static Poutre * getListPoutre();
	static void planchePoutre(float largeur, float longueur, float hauteur);
	static void poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme);
	void dessinerPoutre(int isASpecialPoutre);
private:
	float id, yCentre, xCentre, xG, xD, ordoOrigine, coefDir, angle;

};


#endif