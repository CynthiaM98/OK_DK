#ifndef ECHELLE_H
#define ECHELLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Coordonnee2D.h"
#include "Perso.h"

class Echelle {
	//{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}

	public :
		Echelle();
		Echelle(Coordonnee2D coinSupG, Coordonnee2D coinSupD, Coordonnee2D coinInfG, Coordonnee2D coinInfD);
		Coordonnee2D getCoinSupG();
		Coordonnee2D getCoinSupD();
		Coordonnee2D getCoinInfG();
		Coordonnee2D getCoinInfD();
		static Echelle * getListEchelles(Perso mario);
		static Echelle * getListEchellesCassee(Perso mario);
		static void printEchelle();
		static void printEchelleCassee();
		static void placementEchelles(float largeurPoutre);

	private :
		Coordonnee2D coinSupG;
		Coordonnee2D coinSupD;
		Coordonnee2D coinInfG;
		Coordonnee2D coinInfD;


};

#endif