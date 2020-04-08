#include "Poutre.h"

float largeur = 8.0F;
float hauteur = 0.5F;
float longueur = 100.0F;

GLfloat couleur_poutres[] = { 2.50,2.4,1.45F,1.0F };

Poutre::Poutre(float id, float yCentre, float xG, float xD, float ordoOrigine, float coefDir) {
	this->id = id;
	this->yCentre = yCentre;
	this->xG = xG;
	this->xD = xD;
	this->ordoOrigine = ordoOrigine;
	this->coefDir = coefDir;
}

float Poutre::getId() {
	return this->id;
}

float Poutre::getYCentre() {
	return this->yCentre;
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


void Poutre::planchePoutre(float largeur, float longueur, float hauteur) {
	largeur /= 2.0;
	longueur /= 2.0;
	hauteur /= 2.0;
	glBegin(GL_QUADS);
	glPushMatrix();
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

											 //face supérieure
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

											 //face inférieure
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

											   //face arrière
	glNormal3f(0.0F, 0.0F, -1.0F);
	glVertex3d(-largeur, hauteur, -longueur); // 6
	glVertex3d(largeur, hauteur, -longueur); // 5
	glVertex3d(largeur, -hauteur, -longueur); // 7
	glVertex3d(-largeur, -hauteur, -longueur); // 8
	glPopMatrix();
	glEnd();

}

void Poutre::poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme) {
	double largeurSurDix = largeurPlateforme / 10.0;

	glPushMatrix();

	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glPushMatrix();

	//plateforme supérieure
	glTranslatef(0.0F, 0.0F, 2 * hauteurPlateforme);
	planchePoutre(largeurPlateforme, hauteurPlateforme, longueurPlateforme);
	glPopMatrix();

	//plateforme inférieure
	glTranslatef(0.0F, 0.0F, -2 * hauteurPlateforme);
	planchePoutre(largeurPlateforme, hauteurPlateforme, longueurPlateforme);
	glPopMatrix();


	//barre de soutien de la poutre
	planchePoutre(largeurPlateforme / 2, longueurPlateforme, hauteurPlateforme * 4);

}

void Poutre::placementPoutres() {
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_poutres);
	glPushMatrix(); //poutre victoire
	glTranslatef(-10.0, 6 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur / 2, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre etage +3
	glTranslatef(5.0, 5 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-3.5, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre etage +2
	glTranslatef(-5.0, 4 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(3.2, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre etage +1
	glTranslatef(5.0, 3 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-3.5, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre centrale
	glTranslatef(-5.0, 2 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(3.2, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre etage -1
	glTranslatef(5.0, 1 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-3.5, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPushMatrix(); //poutre etage -2
	glTranslatef(-5.0, 0 * 20.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(3.2, 1.0, 0.0, 0.0);
	poutreDK(largeur, longueur, hauteur);
	glPopMatrix();

	glPopMatrix();

}