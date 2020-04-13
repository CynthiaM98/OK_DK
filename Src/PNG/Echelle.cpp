#include "Echelle.h"
#include "Coordonnee2D.h"


const int nbEchelle = 6;
const int nbEchelleCassee = 5;

float hauteurE = 25.0;
float largeurE = 8.0;

Echelle::Echelle(Coordonnee2D coinSupG, Coordonnee2D coinSupD, Coordonnee2D coinInfG, Coordonnee2D coinInfD) {
	this->coinSupG = coinSupG;
	this->coinSupD = coinSupD;
	this->coinInfG = coinInfG;
	this->coinInfD = coinInfD;
}

Echelle::Echelle() {}


Coordonnee2D Echelle::getCoinSupG() {
	return this->coinSupG;
}

Coordonnee2D Echelle::getCoinSupD() {
	return this->coinSupD;
}
Coordonnee2D Echelle::getCoinInfG() {
	return this->coinInfG;
}
Coordonnee2D Echelle::getCoinInfD() {
	return this->coinInfD;
}

Echelle* Echelle::getListEchelles(Perso mario) {
	Coordonnee2D e1_c1(1.0F - (largeurE/2.0F), 110.0F + (hauteurE/2.0F) + mario.getTaille() * 0.125F);
	Coordonnee2D e1_c2(1.0F + (largeurE / 2.0F), 110.0F + (hauteurE / 2.0F) + mario.getTaille() * 0.125F);
	Coordonnee2D e1_c3(1.0F - (largeurE / 2.0F), 110.0F - (hauteurE / 2.0F));
	Coordonnee2D e1_c4(1.0F + (largeurE / 2.0F), 110.0F - (hauteurE / 2.0F));

	Echelle e1(e1_c1, e1_c2, e1_c3, e1_c4);

	Coordonnee2D e2_c1(-25.0F - (largeurE / 2.0F), 90.0F + (hauteurE / 2.0F));
	Coordonnee2D e2_c2(-25.0F + (largeurE / 2.0F), 90.0F + (hauteurE / 2.0F));
	Coordonnee2D e2_c3(-25.0F - (largeurE / 2.0F), 90.0F - (hauteurE / 2.0F));
	Coordonnee2D e2_c4(-25.0F + (largeurE / 2.0F), 90.0F - (hauteurE / 2.0F));

	Echelle e2(e2_c1, e2_c2, e2_c3, e2_c4);

	Coordonnee2D e3_c1(15.0F - (largeurE / 2.0F), 70.0F + (hauteurE / 2.0F));
	Coordonnee2D e3_c2(15.0F + (largeurE / 2.0F), 70.0F + (hauteurE / 2.0F));
	Coordonnee2D e3_c3(15.0F - (largeurE / 2.0F), 70.0F - (hauteurE / 2.0F));
	Coordonnee2D e3_c4(15.0F + (largeurE / 2.0F), 70.0F - (hauteurE / 2.0F));

	Echelle e3(e3_c1, e3_c2, e3_c3, e3_c4);

	Coordonnee2D e4_c1(-28.0F - (largeurE / 2.0F), 50.0F + (hauteurE / 2.0F));
	Coordonnee2D e4_c2(-28.0F + (largeurE / 2.0F), 50.0F + (hauteurE / 2.0F));
	Coordonnee2D e4_c3(-28.0F - (largeurE / 2.0F), 50.0F - (hauteurE / 2.0F));
	Coordonnee2D e4_c4(-28.0F + (largeurE / 2.0F), 50.0F - (hauteurE / 2.0F));

	Echelle e4(e4_c1, e4_c2, e4_c3, e4_c4);

	Coordonnee2D e5_c1(10.0F - (largeurE / 2.0F), 30.0F + (hauteurE / 2.0F));
	Coordonnee2D e5_c2(10.0F + (largeurE / 2.0F), 30.0F + (hauteurE / 2.0F));
	Coordonnee2D e5_c3(10.0F - (largeurE / 2.0F), 30.0F - (hauteurE / 2.0F));
	Coordonnee2D e5_c4(10.0F + (largeurE / 2.0F), 30.0F - (hauteurE / 2.0F));

	Echelle e5(e5_c1, e5_c2, e5_c3, e5_c4);

	Coordonnee2D e6_c1(-27.0F - (largeurE / 2.0F), 10.0F + (hauteurE / 2.0F));
	Coordonnee2D e6_c2(-27.0F + (largeurE / 2.0F), 10.0F + (hauteurE / 2.0F));
	Coordonnee2D e6_c3(-27.0F - (largeurE / 2.0F), 10.0F - (hauteurE / 2.0F));
	Coordonnee2D e6_c4(-27.0F + (largeurE / 2.0F), 10.0F - (hauteurE / 2.0F));

	Echelle e6(e6_c1, e6_c2, e6_c3, e6_c4);

	Echelle *listEchelle = new Echelle[nbEchelle];
	listEchelle[0] = e1;
	listEchelle[1] = e2;
	listEchelle[2] = e3;
	listEchelle[3] = e4;
	listEchelle[4] = e5;
	listEchelle[5] = e6;

	return listEchelle;
}


Echelle * Echelle::getListEchellesCassee(Perso mario) {

	Coordonnee2D ec1_c1(10.0F - (largeurE / 2.0F), 90.0F + (hauteurE / 2.0F));
	Coordonnee2D ec1_c2(10.0F + (largeurE / 2.0F), 90.0F + (hauteurE / 2.0F));
	Coordonnee2D ec1_c3(10.0F - (largeurE / 2.0F), 90.0F - (hauteurE / 2.0F));
	Coordonnee2D ec1_c4(10.0F + (largeurE / 2.0F), 90.0F - (hauteurE / 2.0F));

	Echelle ec1(ec1_c1, ec1_c2, ec1_c3, ec1_c4);

	Coordonnee2D ec2_c1(35.0F - (largeurE / 2.0F), 70.0F + (hauteurE / 2.0F));
	Coordonnee2D ec2_c2(35.0F + (largeurE / 2.0F), 70.0F + (hauteurE / 2.0F));
	Coordonnee2D ec2_c3(35.0F - (largeurE / 2.0F), 70.0F - (hauteurE / 2.0F));
	Coordonnee2D ec2_c4(35.0F + (largeurE / 2.0F), 70.0F - (hauteurE / 2.0F));

	Echelle ec2(ec2_c1, ec2_c2, ec2_c3, ec2_c4);

	Coordonnee2D ec3_c1(0.0F - (largeurE / 2.0F), 50.0F + (hauteurE / 2.0F));
	Coordonnee2D ec3_c2(0.0F + (largeurE / 2.0F), 50.0F + (hauteurE / 2.0F));
	Coordonnee2D ec3_c3(0.0F - (largeurE / 2.0F), 50.0F - (hauteurE / 2.0F));
	Coordonnee2D ec3_c4(0.0F + (largeurE / 2.0F), 50.0F - (hauteurE / 2.0F));

	Echelle ec3(ec3_c1, ec3_c2, ec3_c3, ec3_c4);

	Coordonnee2D ec4_c1(-17.0F - (largeurE / 2.0F), 30.0F + (hauteurE / 2.0F));
	Coordonnee2D ec4_c2(-17.0F + (largeurE / 2.0F), 30.0F + (hauteurE / 2.0F));
	Coordonnee2D ec4_c3(-17.0F - (largeurE / 2.0F), 30.0F - (hauteurE / 2.0F));
	Coordonnee2D ec4_c4(-17.0F + (largeurE / 2.0F), 30.0F - (hauteurE / 2.0F));

	Echelle ec4(ec4_c1, ec4_c2, ec4_c3, ec4_c4);

	Coordonnee2D ec5_c1(30.0F - (largeurE / 2.0F), 10.0F + (hauteurE / 2.0F));
	Coordonnee2D ec5_c2(30.0F + (largeurE / 2.0F), 10.0F + (hauteurE / 2.0F));
	Coordonnee2D ec5_c3(30.0F - (largeurE / 2.0F), 10.0F - (hauteurE / 2.0F));
	Coordonnee2D ec5_c4(30.0F + (largeurE / 2.0F), 10.0F - (hauteurE / 2.0F));

	Echelle ec5(ec5_c1, ec5_c2, ec5_c3, ec5_c4);

	Echelle *listEchelleC = new Echelle[nbEchelleCassee];
	listEchelleC[0] = ec1;
	listEchelleC[1] = ec2;
	listEchelleC[2] = ec3;
	listEchelleC[3] = ec4;
	listEchelleC[4] = ec5;

	return listEchelleC;
}

void Echelle::printEchelle() {
	float largeur = largeurE / 2.0F;
	float x = 1.0F;
	//montant droit

	glPushMatrix();
	glColor4f(0.8F, 0.8F, 0.2F, 1.0F);
	glTranslatef(-largeur, 0.0, 0.0);
	glRotatef(90, 0.0F, 0.0F, 1.0F);
	glScalef(hauteurE, x, x);
	glutSolidCube(1.0);
	glPopMatrix();

	//montant gauche
	glPushMatrix();
	glTranslatef(largeur - 1, 0.0, 0.0);
	glRotatef(90, 0.0F, 0.0F, 1.0F);
	glScalef(hauteurE, x, x);
	glutSolidCube(x);
	glPopMatrix();

	//barreaux
	for (int i = 0;i < 3;++i) {
		glPushMatrix();
		glTranslatef(-x / 2, i * (-x + (hauteurE / 4)), 0.0);
		glScalef(2 * (largeur - x), 1.0F, 1.0F);
		glutSolidCube(x);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-x / 2, -i * (-x + (hauteurE / 4)), 0.0);
		glScalef(2 * (largeur - x), 1.0F, 1.0F);
		glutSolidCube(x);
		glPopMatrix();
	}
}

void Echelle::printEchelleCassee() {
	float largeur = largeurE / 2.0F;
	float x = 1.0F;
	//montant droit
	glPushMatrix();
	glTranslatef(-largeur, 0.0, 0.0);
	glRotatef(90, 0.0F, 0.0F, 1.0F);
	glScalef(hauteurE, x, x);
	glutSolidCube(1.0);
	glPopMatrix();

	//montant gauche
	glPushMatrix();
	glTranslatef(largeur - 1, 0.0, 0.0);
	glRotatef(90, 0.0F, 0.0F, 1.0F);
	glScalef(hauteurE, x, x);
	glutSolidCube(x);
	glPopMatrix();

	//barreaux
	for (int i = 1;i < 3;++i) {
		glPushMatrix();
		glTranslatef(-x / 2, i * (-x + (hauteurE / 4)), 0.0);
		glScalef(2 * (largeur - x), 1.0F, 1.0F);
		glutSolidCube(x);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-3 * x / 2, -i * (-x + (hauteurE / 4)), 0.0);
		glScalef(2 * (largeur - 1.5 * x), 1.0F, 1.0F);
		glutSolidCube(x);
		glPopMatrix();

	}
}


void Echelle::placementEchelles(float largeurPoutre) {
	

	glPushMatrix(); //echelle  3 -> 4
	glTranslatef(1.0, 110.0, -largeurPoutre / 2);
	Echelle::printEchelle();
	glPopMatrix();

	glPushMatrix(); //echelle  2 -> 3
	glTranslatef(-25.0, 90.0, -largeurPoutre / 2); //on recule pour que les échelles soit derrière les poutres
	Echelle::printEchelle();
	glPopMatrix();

	glPushMatrix(); //echelle cassee 2 -> 3
	glTranslatef(10.0, 90.0, -largeurPoutre / 2);
	Echelle::printEchelleCassee();
	glPopMatrix();

	glPushMatrix(); //echelle  cassee 1 -> 2
	glTranslatef(35.0, 70.0, -largeurPoutre / 2);
	Echelle::printEchelleCassee();
	glPopMatrix();

	glPushMatrix(); //echelle  1 -> 2
	glTranslatef(15.0, 70.0, -largeurPoutre / 2);
	Echelle::printEchelle();
	glPopMatrix();

	glPushMatrix(); //echelle  cassee 0 -> 1
	glTranslatef(0.0, 50.0, -largeurPoutre / 2);
	Echelle::printEchelleCassee();
	glPopMatrix();

	glPushMatrix(); //echelle 0 -> 1
	glTranslatef(-28.0, 50.0, -largeurPoutre / 2);
	Echelle::printEchelle();
	glPopMatrix();

	glPushMatrix(); //echelle  cassee -1 -> 0
	glTranslatef(-17.0, 30.0, -largeurPoutre / 2);
	Echelle::printEchelleCassee();
	glPopMatrix();

	glPushMatrix(); //echelle -1 -> 0
	glTranslatef(10.0, 30.0, -largeurPoutre / 2);
	Echelle::printEchelle();
	glPopMatrix();

	glPushMatrix(); //echelle  cassee -2 -> -1
	glTranslatef(30.0, 10.0, -largeurPoutre / 2);
	Echelle::printEchelleCassee();
	glPopMatrix();

	glPushMatrix(); //echelle -2 -> -1
	glTranslatef(-27.0, 10.0, -largeurPoutre / 2);
	Echelle::printEchelle();
	glPopMatrix();
	glPopAttrib();
	
}