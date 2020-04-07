#include "Perso.h"

float taille = 10.0;


Perso::Perso(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->orientation = Gauche;

}

float Perso::getX() {
	return this->x;
}

float Perso::getY() {
	return this->y;
}
float Perso::getZ() {
	return this->z;
}
Perso::Orientation Perso::getOrientation() {
	return this->orientation;
}

void Perso::setX(float newX) {
	this->x = newX;
}
void Perso::setY(float newY) {
	this->y = newY;
}

void Perso::setOrientation(Perso::Orientation newOr) {
	this->orientation = newOr;
}

void Perso::tete(float size) {
	double tailleTete = size / 3.0;
	glScalef(tailleTete, tailleTete, tailleTete);
	glutSolidCube(1.0);
}

void Perso::corp(float size) {
	double tailleCorp = size / 3.0;
	glutSolidCube(tailleCorp);
}

void Perso::membre(float size) {
	float LargeurMembre = size / 6.0;
	float hauteurMembre = size / 3.0;
	glScalef(LargeurMembre, hauteurMembre, LargeurMembre*0.75);
	glutSolidCube(1.0);
}

void Perso::printPerso() {
	
	switch (orientation) {
	case Droite:
		glPushMatrix();
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		break;
	case Gauche:
		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		break;
	case Dos:
		glRotatef(180.0, 0.0, 1.0, 0.0);
		break;
	}

	float temp = 0.0F; //variable pour simplifier la lecture dans l'appelle des fonctions
	glPushMatrix();

	glPushMatrix();
	temp = 5.0*taille/ 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau tête
	tete(taille);
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = taille / 2.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau corp
	corp(taille);

	glPushMatrix(); //bras droit
	temp = taille / 4.0;
	glTranslatef(-temp, 0.0F, 0.0F);
	membre(taille);
	glPopMatrix(); //retour au niveau du corp

	glPushMatrix(); //bras gauche
	glTranslatef(temp, 0.0F, 0.0F);
	membre(taille);
	glPopMatrix(); //retour au niveau du corp

	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = taille / 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau jambe

	glPushMatrix(); //jambe droite
	temp = taille / 12.0;
	glTranslatef(-temp, 0.0F, 0.0F);
	membre(taille);
	glPopMatrix();

	glPushMatrix();//jambe gauche
	glTranslatef(temp, 0.0F, 0.0F);
	membre(taille);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}