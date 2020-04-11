#include "Perso.h"
int Perso::idCounter = 0;

Perso::Perso(float x, float y, float z, float taille) {
	this->id = this->id++;
	this->x = x;
	this->y = y;
	this->z = z;
	this->orientation = Gauche;
	this->surEchelle = false;
	this->taille = taille;
	id = idCounter++;
}

float Perso::getX() {
	return this->x;
}

int Perso::getId() {
	return this->id;
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


void Perso::myCube(float size, unsigned int* texID){
	float c = (float)size / 2.0F;
	GLboolean nm = glIsEnabled(GL_NORMALIZE);
	if (!nm)
		glEnable(GL_NORMALIZE);
	float normale[4];
	glGetFloatv(GL_CURRENT_NORMAL, normale);
	glPushMatrix();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[8]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(0.0F, 0.0F, -1.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(c, c, -c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(c, -c, -c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(-c, -c, -c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(-c, c, -c); }
	glEnd();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[0]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(0.0F, 0.0F, 1.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(c, c, c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(-c, c, c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(-c, -c, c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(c, -c, c); }
	glEnd();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[0]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(-1.0F, 0.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(-c, c, -c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(-c, -c, -c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(-c, -c, c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(-c, c, c); }
	glEnd();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[0]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(1.0F, 0.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(c, c, c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(c, -c, c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(c, -c, -c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(c, c, -c); }
	glEnd();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[0]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(0.0F, -1.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(-c, -c, c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(-c, -c, -c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(c, -c, -c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(c, -c, c); }
	glEnd();
	switch (this->id) {
	case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 1: glBindTexture(GL_TEXTURE_2D, texID[0]);
		break;
	case 2: glBindTexture(GL_TEXTURE_2D, texID[0]);
	}
	glBegin(GL_QUADS);
	{ glNormal3f(0.0F, 1.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(c, c, c);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(c, c, -c);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(-c, c, -c);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(-c, c, c); }
	glEnd();
	glPopMatrix();
	glNormal3f(normale[0], normale[1], normale[2]);
	if (!nm)
		glDisable(GL_NORMALIZE);
}

void Perso::membre(float size, unsigned int *texID) {
	float LargeurMembre = size / 6.0;
	float hauteurMembre = size / 3.0;
	glScalef(LargeurMembre, hauteurMembre, LargeurMembre*0.75);
	myCube(1.0,texID);
}

void Perso::tete(float size, unsigned int *texID) {
	double tailleTete = size / 3.0;
	glScalef(tailleTete, tailleTete, tailleTete);
	myCube(1.0,texID);
}

void Perso::corps(float size, unsigned int *texID) {
	double tailleCorps = size / 3.0;
	myCube(tailleCorps,texID);
}

void Perso::printPerso(bool sautEnCours,bool lanceTonneau, unsigned int *texID) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texID[0]);
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
	if (lanceTonneau) {
		glRotatef(90.0, 0.0, 1.0, 0.0);
	}
	float temp = 0.0F; //variable pour simplifier la lecture dans l'appelle des fonctions
	glPushMatrix();

	glPushMatrix();
	temp = 5.0* this->taille / 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau tête
	tete(this->taille, texID);
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = this->taille / 2.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau corps
	corps(this->taille,texID);

	if (!sautEnCours) {
		glPushMatrix(); //bras droit

		temp = this->taille / 4.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		membre(this->taille,texID);
		glPopMatrix(); //retour au niveau du corps
		if (lanceTonneau) {
			glPushMatrix(); //bras gauche
			glTranslatef(temp, 0.0F, temp);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			membre(this->taille,texID);
			glPopMatrix(); //retour au niveau du corps
		}
		else {
			glPushMatrix(); //bras gauche
			glTranslatef(temp, 0.0F, 0.0F);
			membre(this->taille, texID);
			glPopMatrix(); //retour au niveau du corps
		}
		
	}
	else {
		glPushMatrix(); //bras droit
		temp = this->taille / 4.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille, texID);
		glPopMatrix(); //retour au niveau du corps

		glPushMatrix(); //bras gauche
		glTranslatef(temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille, texID);
		glPopMatrix(); //retour au niveau du corps
	}
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = this->taille / 6.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau jambe
	if (!sautEnCours) {
		glPushMatrix(); //jambe droite
		temp = this->taille / 12.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		membre(this->taille, texID);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.0F, 0.0F);
		membre(this->taille, texID);
		glPopMatrix();
	}
	else {
		glPushMatrix(); //jambe droite
		temp = this->taille / 12.0;
		glTranslatef(-temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille, texID);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille, texID);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}