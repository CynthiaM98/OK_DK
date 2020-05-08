/********************************************************************************************/
/********************************************************************************************/
/* MAILLARD Cynthia - AUBRY Cl�ment - THIEBAUD J�r�my*/
/********************************************************************************************/
/********************************************************************************************/


#include "Poutre.h"

float largeur = 8.0F;
float hauteur = 0.5F;
float longueur = 100.0F;
const int nbPoutre = 8;

GLfloat couleur_poutres[] = { 2.50,2.4,1.45F,1.0F };


Poutre::Poutre(float id, float yCentre, float xCentre, float xG, float xD, float ordoOrigine, float coefDir,float angle) {
	this->id = id;
	this->yCentre = yCentre;
	this->xCentre = xCentre;
	this->xG = xG;
	this->xD = xD;
	this->ordoOrigine = ordoOrigine;
	this->coefDir = coefDir;
	this->angle = angle;
}

Poutre::Poutre() {}

float Poutre::getId() {
	return this->id;
}

float Poutre::getYCentre() {
	return this->yCentre;
}


float Poutre::getXCentre() {
	return this->xCentre;
}

float Poutre::getXG() {
	return this->xG;
}

float Poutre::getXD() {
	return this->xD;
}

float Poutre::getOrdoOrigine() {
	return this->ordoOrigine;
}

float Poutre::getCoefDir() {
	return this->coefDir;
}

float Poutre::getAngle() {
	return this->angle;
}

Poutre * Poutre::getListPoutre() {

	//numeroPoutre,yCentre,xCentre,xGauche,xDroit,ordoOrigine,coefDir,angle
	Poutre p0(-2.0F, 0.0F, -5.0F, -55.0F, 45.0F, 0.0F, -0.06F, 3.2F);
	Poutre p1(-1.0F, 20.0F, 5.0F, -45.0F, 55.0F, 19.69F, 0.06F, -3.5F);
	Poutre p2(0.0F, 40.0F, -5.0F, -55.0F, 45.0F, 39.72F, -0.06F, 3.2F);
	Poutre p3(1.0F, 60.0F, 5.0F, -45.0F, 55.0F, 59.69F, 0.06F, -3.5F);
	Poutre p4(2.0F, 80.0F, -5.0F, -55.0F, 45.0F, 79.72F, -0.06F, 3.2F);
	Poutre p5(3.0F, 100.0F, 5.0F, -45.0F, 55.0F, 99.69F, 0.06F, -3.5F);
	Poutre p6(4.0F, 120.0F, -10.0, -35.0F, 15.0F, 120.0F, 0.0F, 0.0F);
	Poutre p7(42.0F, 103.0F, 64.0, 54.0F, 74.0F, 103.0F, 0.0F, 0.0F);

	Poutre *listPoutre = new Poutre[nbPoutre];
	listPoutre[0] = p0;
	listPoutre[1] = p1;
	listPoutre[2] = p2;
	listPoutre[3] = p3;
	listPoutre[4] = p4;
	listPoutre[5] = p5;
	listPoutre[6] = p6;
	listPoutre[7] = p7;

	return listPoutre;

}


void Poutre::planchePoutre(float largeur, float longueur, float hauteur) {
	largeur /= 2.0;
	longueur /= 2.0;
	hauteur /= 2.0;
	glPushMatrix();
	glBegin(GL_QUADS);
	float couleur[4] = { (2.50,2.4,1.45F,1.0F) };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red);
									  //face avant
	glNormal3f(0.0F, 0.0F, 1.0F);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
	glVertex3d(largeur, hauteur, longueur); // 1
	glVertex3d(-largeur, hauteur, longueur); // 2
	glVertex3d(-largeur, -hauteur, longueur); // 3
	glVertex3d(largeur, -hauteur, longueur); // 4

											 //face sup�rieure
	glNormal3f(0.0F, 1.0F, 0.0F);
	glVertex3d(largeur, hauteur, longueur); // 1
	glVertex3d(largeur, hauteur, -longueur); // 5
	glVertex3d(-largeur, hauteur, -longueur); // 6
	glVertex3d(-largeur, hauteur, longueur); // 2

											 //face droite
	glNormal3f(1.0F, 0.0F, 0.0F);
	glVertex3d(largeur, hauteur, longueur); // 1
	glVertex3d(largeur, -hauteur, longueur); // 4
	glVertex3d(largeur, -hauteur, -longueur); // 7
	glVertex3d(largeur, hauteur, -longueur); // 5

											 //face inf�rieure
	glNormal3f(0.0F, -1.0F, 0.0F);
	glVertex3d(largeur, -hauteur, longueur); // 4
	glVertex3d(-largeur, -hauteur, longueur); // 3
	glVertex3d(-largeur, -hauteur, -longueur); // 8
	glVertex3d(largeur, -hauteur, -longueur); // 7

											  //face gauche
	glNormal3f(-1.0F, 0.0F, 0.0F);
	glVertex3d(-largeur, -hauteur, longueur); // 3
	glVertex3d(-largeur, hauteur, longueur); // 2
	glVertex3d(-largeur, hauteur, -longueur); // 6
	glVertex3d(-largeur, -hauteur, -longueur); // 8

											   //face arri�re
	glNormal3f(0.0F, 0.0F, -1.0F);
	glVertex3d(-largeur, hauteur, -longueur); // 6
	glVertex3d(largeur, hauteur, -longueur); // 5
	glVertex3d(largeur, -hauteur, -longueur); // 7
	glVertex3d(-largeur, -hauteur, -longueur); // 8
	glEnd();
	glPopMatrix();
}

void Poutre::poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme) {
	double largeurSurDix = largeurPlateforme / 10.0;

	glPushMatrix();

	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glPushMatrix();

	//plateforme sup�rieure
	glTranslatef(0.0F, 0.0F, 2 * hauteurPlateforme);
	planchePoutre(largeurPlateforme, hauteurPlateforme, longueurPlateforme);
	glPopMatrix();

	//plateforme inf�rieure
	glTranslatef(0.0F, 0.0F, -2 * hauteurPlateforme);
	planchePoutre(largeurPlateforme, hauteurPlateforme, longueurPlateforme);
	glPopMatrix();


	//barre de soutien de la poutre
	planchePoutre(largeurPlateforme / 2, longueurPlateforme, hauteurPlateforme * 4);

}

void Poutre::dessinerPoutre(int isASpecialPoutre) {
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_poutres);
	glTranslatef(this->xCentre, this->yCentre, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(this->angle, 1.0, 0.0, 0.0);
	
	switch(isASpecialPoutre){
	case 2:
		poutreDK(largeur, longueur/2, hauteur); //poutre Peach
		break;
	case 1 :
		poutreDK(largeur, longueur / 5, hauteur); //poutre Tas tonneau
		break;
	case 0: 
		poutreDK(largeur, longueur, hauteur); //poutre normale
		break;
	default:
		break;
	}
	glPopMatrix();
}

