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


void Perso::myCube(float size, unsigned int* texID, int partieCorps){
	float c = (float)size / 2.0F;
	GLboolean nm = glIsEnabled(GL_NORMALIZE);
	if (!nm)
		glEnable(GL_NORMALIZE);
	float normale[4];
	glGetFloatv(GL_CURRENT_NORMAL, normale);
	glPushMatrix(); //face avant
	switch (this->id) {
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[0]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[5]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[11]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[17]);
		}
		break;
	case 1:
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[23]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[28]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[34]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[40]);
		}
		break;
	case 2:
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[46]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[51]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[57]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[63]);
		}
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
	switch (this->id) {//face arrière
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[1]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[6]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[12]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[18]);
		}
		break;
	case 1: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[24]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[29]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[35]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[41]);
		}
		break;
	case 2: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[47]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[52]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[58]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[64]);
		}
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
	switch (this->id) {//face gauche
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[2]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[7]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[13]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[19]);
		}
		break;
	case 1: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[25]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[30]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[36]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[42]);
		}
		break;
	case 2: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[48]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[53]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[59]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[65]);
		}
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
	switch (this->id) {//face droite
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[3]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[8]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[14]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[20]);
		}
		break;
	case 1: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[26]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[31]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[37]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[43]);
		}
		break;
	case 2:
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[49]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[54]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[60]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[66]);
		}
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
	switch (this->id) {//face dessous
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[4]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[9]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[15]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[21]);
		}
		break;
	case 1: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[27]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[32]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[38]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[44]);
		}
		break;
	case 2:
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[50]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[55]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[61]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[67]);
		}
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
	switch (this->id) {//face dessus
	case 0: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[4]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[10]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[16]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[22]);
		}
		break;
	case 1: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[27]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[33]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[39]);
			break;
		case 3:	glBindTexture(GL_TEXTURE_2D, texID[45]);
		}
		break;
	case 2: 
		switch (partieCorps) {
		case 0: glBindTexture(GL_TEXTURE_2D, texID[50]);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, texID[56]);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, texID[62]);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, texID[68]);
		}
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

void Perso::membre(float size, unsigned int *texID, int partieCorps) {
	float LargeurMembre = size / 6.0;
	float hauteurMembre = size / 3.0;
	glScalef(LargeurMembre, hauteurMembre, LargeurMembre*0.75);
	myCube(1.0,texID, partieCorps);
}

void Perso::tete(float size, unsigned int *texID) {
	double tailleTete = (size / 3.0)*0.85;
	glScalef(tailleTete, tailleTete, tailleTete);
	myCube(1.0,texID, 0);
}

void Perso::corps(float size, unsigned int *texID) {
	double tailleCorps = size / 3.0;
	myCube(tailleCorps,texID,1);
}

void Perso::printPerso(bool sautEnCours,bool lanceTonneau,bool auSecours, int direction , unsigned int *texID) {
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
		glRotatef(-90.0, 0.0, 1.0, 0.0);
	}
	if (auSecours) {
		glTranslatef(0.0, 1.5, 0.0);
	}
	float temp = 0.0F; //variable pour simplifier la lecture dans l'appelle des fonctions
	glPushMatrix();

	glPushMatrix();
	temp =( 5.0* this->taille / 6.0);
	glTranslatef(0.0F, temp, 0.0F); //niveau tête
	
	tete(this->taille, texID);
	glPopMatrix(); //retour origine

	glPushMatrix();
	temp = this->taille / 2.0;
	glTranslatef(0.0F, temp, 0.0F); //niveau corps
	corps(this->taille,texID);

	if (!sautEnCours) {
		glPushMatrix(); //bras droit
		if (lanceTonneau) {
			temp = this->taille / 4.0;
			glTranslatef(-temp, 0.0F, 0.0F);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			membre(this->taille, texID,2);
		}
		else {
			if (auSecours) {
				temp = this->taille / 4.0;
				glTranslatef(-temp, 0.0F, 0.0F);
				glRotatef(100.0, 1.0, 0.0, 0.0);
				glRotatef(60.0, 0.0, 1.0, 0.0);
				membre(this->taille, texID, 2);
			}
			else {
				temp = this->taille / 4.0;
				glTranslatef(-temp, 0.0F, 0.0F);
				switch (direction) {
				case 0: //Immobile
					break;
				case 1: //Gauche
					glRotatef(-45.0, 1.0, 0.0, 0.0);
					break;
				case 2: //Droite
					glRotatef(45.0, 1.0, 0.0, 0.0);
					break;
				}
				membre(this->taille, texID, 2);
			}
		}
		glPopMatrix(); //retour au niveau du corps

		glPushMatrix(); //bras gauche
		if (auSecours) {
			temp = this->taille / 4.0;
			glTranslatef(temp, 0.0F, 0.0F);
			glRotatef(100.0, 1.0, 0.0, 0.0);
			glRotatef(60.0, 0.0, 1.0, 0.0);
			membre(this->taille, texID, 2);
		}
		else {
			glTranslatef(temp, 0.0F, 0.0F);
			switch (direction) {
			case 0: //Immobile
				break;
			case 1: //Gauche
				glRotatef(45.0, 1.0, 0.0, 0.0);
				break;
			case 2: //Droite
				glRotatef(-45.0, 1.0, 0.0, 0.0);
				break;
			}
			membre(this->taille, texID, 2);
			
		}
		glPopMatrix(); //retour au niveau du corps
	}
	else {
		glPushMatrix(); //bras droit
		temp = this->taille / 4.0;
		glTranslatef(-temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille, texID,2);
		glPopMatrix(); //retour au niveau du corps

		glPushMatrix(); //bras gauche
		glTranslatef(temp, 0.0F, 0.0F);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		membre(this->taille, texID,2);
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
		switch (direction) {
			case 0: //Immobile
				break;
			case 1: //Gauche
				glRotatef(45.0, 1.0, 0.0, 0.0);
				break;
			case 2: //Droite
				glRotatef(-45.0, 1.0, 0.0, 0.0);
				break;
		}
		membre(this->taille, texID,3);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.0F, 0.0F);
		switch (direction) {
		case 0: //Immobile
			break;
		case 1: //Gauche
			glRotatef(-45.0, 1.0, 0.0, 0.0);
			break;
		case 2: //Droite
			glRotatef(45.0, 1.0, 0.0, 0.0);
			break;
		}
		membre(this->taille, texID,3);
		glPopMatrix();
	}
	else {
		glPushMatrix(); //jambe droite
		temp = this->taille / 12.0;
		glTranslatef(-temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille, texID,3);
		glPopMatrix();

		glPushMatrix();//jambe gauche
		glTranslatef(temp, 0.5F, 0.0F);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		membre(this->taille, texID,3);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}