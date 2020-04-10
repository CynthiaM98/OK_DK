#include "Perso.h"




Perso::Perso(float x, float y, float z, float taille) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->orientation = Gauche;
	this->surEchelle = false;
	this->taille = taille;
}

float Perso::getX() {
	return this->x;
}

float Perso::getTaille() {
	return this->taille;
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
bool Perso::getSurEchelle() {
	return this->surEchelle;
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

void Perso::setSurEchelle(bool status) {
	this->surEchelle = status;
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

void Perso::printPerso(bool sautEnCours) {
	glPushMatrix();
	switch (orientation) {
	case Droite:
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		break;
	case Gauche:
		glRotatef(90.0, 0.0, 1.0, 0.0);
		break;
	case Dos:
		glRotatef(180.0, 0.0, 1.0, 0.0);
		break;
	}
	
	float temp = 0.0F; //variable pour simplifier la lecture dans l'appelle des fonctions
	glPushMatrix();

	glPushMatrix();
	temp = 5.0* this->taille / 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau tête
	tete(this->taille);
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = this->taille / 2.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau corp
	corp(this->taille);

	if (!sautEnCours) {
		glPushMatrix(); //bras droit

		temp = this->taille / 4.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		membre(this->taille);
		glPopMatrix(); //retour au niveau du corp

		glPushMatrix(); //bras gauche
		glTranslatef(temp, 0.0F, 0.0F);
		membre(this->taille);
		glPopMatrix(); //retour au niveau du corp
	}
	else {
		glPushMatrix(); //bras droit

		temp = this->taille / 4.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille);
		glPopMatrix(); //retour au niveau du corp

		glPushMatrix(); //bras gauche
		glTranslatef(temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille);
		glPopMatrix(); //retour au niveau du corp
	}
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = this->taille / 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau jambe
	if (!sautEnCours) {
		glPushMatrix(); //jambe droite
		temp = this->taille / 12.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		membre(this->taille);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.0F, 0.0F);
		membre(this->taille);
		glPopMatrix();
	}
	else {
		glPushMatrix(); //jambe droite
		temp = this->taille / 12.0;
		glTranslatef(-temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}