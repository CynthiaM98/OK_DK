#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <string>

#include "PNG/ChargePngFile.h"
#include "PNG/Perso.h"
#include "PNG/Poutre.h"




static unsigned int textureID[1] = { 0 };


static float px = 0.0;
static float py = 60.0;
static float pz = 10.0;

static float initCamX = px;
static float initCamY = py;
static float initCamZ = pz;

static float rxs = 0.0;
static float rys = 0.0;
static float rzs = 0.0;

static int n = 100;
static int n1 = 72;
static int n2 = 360;

static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };
static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };

static int animation = 0;
static int culling = 0;
static int texture = 1;
static int filDeFer = 1;
static int lumiere = 0;

int windowWidth = 1000;
int windowHeight = 1000;
int WindowDK;

//POUTRES
float largeurPoutre = 8.0F;
float hauteurPoutre = 0.5F;
float longueurPoutre = 100.0F;
float compensationPoutre = 1.5 * hauteurPoutre;

//ECHELLES
float hauteurEchelle = 25.0;
float largeurEchelle = 8.0;
float demieHauteurEchelle = hauteurEchelle / 2.0;
float demieLargeurEchelle = largeurEchelle / 2.0;

const int nombreEchelle = 6;
const int nombreEchelleCassee = 5;
const int nombrePoutre = 8;

//MARIO
float initXMario = 5.0;
float initYMario = 120+ compensationPoutre;
//float initYMario = (-0.06 * initXMario) + compensationPoutre;
float initZMario = -1.0;
float longueurPas = 0.5F;
bool chute = false;

Perso mario(initXMario, initYMario, initZMario);

Perso::Orientation initOrientationMario = mario.getOrientation();

//PEACH
float xPrincesse = -30.0;
float yPrincesse = 120.0;
float zPrincesse = 0.0;

Perso princess(xPrincesse, yPrincesse, zPrincesse);


//DK
float xDonkeyKong = 40.0;
float yDonkeyKong = (99.69 + 0.06 * xDonkeyKong) + compensationPoutre;
float zDonkeyKong = 0.0;

//TONNEAU
float xTonneauBegin = 30;
float yTonneauBegin = 102 + 2 * compensationPoutre;
float zTonneauBegin = -largeurPoutre / 3;
int nbTonneau = 0;
float tabTonneau[100][3];
float largeurTonneau = 3.0;

bool gameover = false;
bool pause = false;
bool victoire = false;
bool saut = false;
bool sautEnCours = false;
bool godMod = false;
bool cameraFPS = false;
float initYsaut = 0.0f;
//FCT ECHELLES

float listeDesEchelles[nombreEchelle][4][2] = { //{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}


    {
        {1.0F - demieLargeurEchelle,110.0F + demieHauteurEchelle + mario.getTaille() * 0.125F},
        {1.0F + demieLargeurEchelle,110.0F + demieHauteurEchelle + mario.getTaille() * 0.125F},
        {1.0F - demieLargeurEchelle,110.0F - demieHauteurEchelle},
        {1.0F + demieLargeurEchelle,110.0F - demieHauteurEchelle}  //echelle 3 -> 4
    },
    {
        {-25.0F - demieLargeurEchelle,90.0F + demieHauteurEchelle},
        {-25.0F + demieLargeurEchelle,90.0F + demieHauteurEchelle},
        {-25.0F - demieLargeurEchelle,90.0F - demieHauteurEchelle},
        {-25.0F + demieLargeurEchelle,90.0F - demieHauteurEchelle}  //echelle 2 -> 3
    },
    {
        {15.0F - demieLargeurEchelle,70.0F + demieHauteurEchelle},
        {15.0F + demieLargeurEchelle,70.0F + demieHauteurEchelle},
        {15.0F - demieLargeurEchelle,70.0F - demieHauteurEchelle},
        {15.0F + demieLargeurEchelle,70.0F - demieHauteurEchelle}  //echelle 1 -> 2
    },
    {
        {-28.0F - demieLargeurEchelle,50.0F + demieHauteurEchelle},
        {-28.0F + demieLargeurEchelle,50.0F + demieHauteurEchelle},
        {-28.0F - demieLargeurEchelle,50.0F - demieHauteurEchelle},
        {-28.0F + demieLargeurEchelle,50.0F - demieHauteurEchelle}  //echelle 0 -> 1
    },
    {
        {10.0F - demieLargeurEchelle,30.0F + demieHauteurEchelle},
        {10.0F + demieLargeurEchelle,30.0F + demieHauteurEchelle},
        {10.0F - demieLargeurEchelle,30.0F - demieHauteurEchelle},
        {10.0F + demieLargeurEchelle,30.0F - demieHauteurEchelle}  //echelle -1 -> 0
    },
    {
        {-27.0F - demieLargeurEchelle,10.0F + demieHauteurEchelle},
        {-27.0F + demieLargeurEchelle,10.0F + demieHauteurEchelle},
        {-27.0F - demieLargeurEchelle,10.0F - demieHauteurEchelle},
        {-27.0F + demieLargeurEchelle,10.0F - demieHauteurEchelle}  //echelle -2 -> -1
    }
};


float listeDesEchellesCassees[nombreEchelleCassee][4][2] = { //{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}


    {
        {10.0F - demieLargeurEchelle,90.0F + demieHauteurEchelle},
        {10.0F + demieLargeurEchelle,90.0F + demieHauteurEchelle},
        {10.0F - demieLargeurEchelle,90.0F - demieHauteurEchelle},
        {10.0F + demieLargeurEchelle,90.0F - demieHauteurEchelle}  //echelle cassee 2 -> 3
    },
    {
        {35.0F - demieLargeurEchelle,70.0F + demieHauteurEchelle},
        {35.0F + demieLargeurEchelle,70.0F + demieHauteurEchelle},
        {35.0F - demieLargeurEchelle,70.0F - demieHauteurEchelle},
        {35.0F + demieLargeurEchelle,70.0F - demieHauteurEchelle}  //echelle cassee 1 -> 2
    },
    {
        {0.0F - demieLargeurEchelle,50.0F + demieHauteurEchelle},
        {0.0F + demieLargeurEchelle,50.0F + demieHauteurEchelle},
        {0.0F - demieLargeurEchelle,50.0F - demieHauteurEchelle},
        {0.0F + demieLargeurEchelle,50.0F - demieHauteurEchelle}  //echelle cassee 0 -> 1 
    },
    {
        {-17.0F - demieLargeurEchelle,30.0F + demieHauteurEchelle},
        {-17.0F + demieLargeurEchelle,30.0F + demieHauteurEchelle},
        {-17.0F - demieLargeurEchelle,30.0F - demieHauteurEchelle},
        {-17.0F + demieLargeurEchelle,30.0F - demieHauteurEchelle}//echelle cassee -1 -> -0 
    },
    {
        {30.0F - demieLargeurEchelle,10.0F + demieHauteurEchelle},
        {30.0F + demieLargeurEchelle,10.0F + demieHauteurEchelle},
        {30.0F - demieLargeurEchelle,10.0F - demieHauteurEchelle},
        {30.0F + demieLargeurEchelle,10.0F - demieHauteurEchelle}  //echelle cassee -2 -> -1
    }

};

//FCT POUTRES
//numeroPoutre,yCentre,xCentre,xGauche,xDroit,ordoOrigine,coefDir,angle
Poutre p0(-2.0F, 0.0F, -5.0F, -55.0F, 45.0F, 0.0F, -0.06F, 3.2F);
Poutre p1(-1.0F, 20.0F, 5.0F, -45.0F, 55.0F, 19.69F, 0.06F, -3.5F);
Poutre p2(0.0F, 40.0F, -5.0F, -55.0F, 45.0F, 39.72F, -0.06F, 3.2F);
Poutre p3(1.0F, 60.0F, 5.0F, -45.0F, 55.0F, 59.69F, 0.06F, -3.5F);
Poutre p4(2.0F, 80.0F, -5.0F, -55.0F, 45.0F, 79.72F, -0.06F, 3.2F);
Poutre p5(3.0F, 100.0F, 5.0F, -45.0F, 55.0F, 99.69F, 0.06F, -3.5F);
Poutre p6(4.0F, 120.0F, -10.0, -35.0F, 15.0F, 120.0F, 0.0F, 0.0F);
Poutre p7(42.0F, 103.0F, 64.0, 54.0F, 74.0F, 103.0F, 0.0F, 0.0F);

Poutre listePoutre[nombrePoutre] = { p0, p1, p2, p3, p4, p5, p6,p7 };


//TEXTURES
GLfloat no_mat[] = { 0.0F,0.0F,0.0F,1.0F };
GLfloat mat_ambient[] = { 0.7F,0.7F,0.7F,1.0F };
GLfloat mat_ambient_color[] = { 0.8F,0.8F,0.2F,1.0F };

GLfloat mat_specular[] = { 1.0F,1.0F,1.0F,1.0F };
GLfloat no_shininess[] = { 0.0F };
GLfloat low_shininess[] = { 5.0F };
GLfloat high_shininess[] = { 100.0F };
GLfloat mat_emission[] = { 0.3F,0.2F,0.2F,0.0F };

GLfloat couleur_echelles[] = { 0.1F,0.5F,0.8F,1.0F };
GLfloat couleur_tonneaux[] = { 0.1F,0.5F,0.8F,1.0F };
GLfloat couleur_princesse[] = { 5.5F,0.5F,5.5F,1.0F };
GLfloat couleur_dk[] = { 0.5F,41.0F,0.0F,1.0F };

static void chargementTexture(char* filename, unsigned int textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    {
        int rx;
        int ry;

        unsigned char *img = chargeImagePng(filename, &rx, &ry);
        if (img) {
            glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            free(img);
            printf("Texture chargée %d : %s\n", textureID, filename);
        }
        else {
            printf("Texture non charge\n");
        }
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

static void init(void) {
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, blanc);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glGenTextures(1, textureID);
    chargementTexture("Emojis.jpg", textureID[0]);
}

void idle(void) {
    printf("A\n");
}

static void rectangle(float largeur, float hauteur) {
    largeur /= 2.0F;
    hauteur /= 2.0F;
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0F, 0.0F, 1.0F);
    glTexCoord2f(0.0F, 0.0F);
    glVertex3f(-largeur, -hauteur, 0.0F);
    glTexCoord2f(1.0F, 0.0F);
    glVertex3f(largeur, -hauteur, 0.0F);
    glTexCoord2f(1.0F, 1.0F);
    glVertex3f(largeur, hauteur, 0.0F);
    glTexCoord2f(0.0F, 1.0F);
    glVertex3f(-largeur, hauteur, 0.0F);
    glEnd();
    glPopMatrix();
}


static void echelle(float hauteur, float largeur) {
    largeur /= 2.0F;
    float x = 1.0F;
    //montant droit

    glPushMatrix();
    glColor4f(0.8F, 0.8F, 0.2F, 1.0F);
    glTranslatef(-largeur, 0.0, 0.0);
    glRotatef(90, 0.0F, 0.0F, 1.0F);
    glScalef(hauteur, x, x);
    glutSolidCube(1.0);
    glPopMatrix();

    //montant gauche
    glPushMatrix();
    glTranslatef(largeur - 1, 0.0, 0.0);
    glRotatef(90, 0.0F, 0.0F, 1.0F);
    glScalef(hauteur, x, x);
    glutSolidCube(x);
    glPopMatrix();

    //barreaux
    for (int i = 0;i < 3;++i) {
        glPushMatrix();
        glTranslatef(-x / 2, i * (-x + (hauteur / 4)), 0.0);
        glScalef(2 * (largeur - x), 1.0F, 1.0F);
        glutSolidCube(x);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-x / 2, -i * (-x + (hauteur / 4)), 0.0);
        glScalef(2 * (largeur - x), 1.0F, 1.0F);
        glutSolidCube(x);
        glPopMatrix();
    }

}




static void echelleCassee(float hauteur, float largeur) {
    largeur /= 2.0F;
    float x = 1.0F;
    //montant droit
    glPushMatrix();
    glTranslatef(-largeur, 0.0, 0.0);
    glRotatef(90, 0.0F, 0.0F, 1.0F);
    glScalef(hauteur, x, x);
    glutSolidCube(1.0);
    glPopMatrix();

    //montant gauche
    glPushMatrix();
    glTranslatef(largeur - 1, 0.0, 0.0);
    glRotatef(90, 0.0F, 0.0F, 1.0F);
    glScalef(hauteur, x, x);
    glutSolidCube(x);
    glPopMatrix();

    //barreaux
    for (int i = 1;i < 3;++i) {
        glPushMatrix();
        glTranslatef(-x / 2, i * (-x + (hauteur / 4)), 0.0);
        glScalef(2 * (largeur - x), 1.0F, 1.0F);
        glutSolidCube(x);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-3 * x / 2, -i * (-x + (hauteur / 4)), 0.0);
        glScalef(2 * (largeur - 1.5 * x), 1.0F, 1.0F);
        glutSolidCube(x);
        glPopMatrix();

    }

}



static void tonneau(float xTonneau, float yTonneau, float zTonneau, bool echelle) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_tonneaux);
    float n;
    glPushMatrix();
	glTranslatef(xTonneau, yTonneau + 4 * compensationPoutre, zTonneau); //face arrière
	if (echelle) {
		glRotatef(90.0, 0.0, 1.0, 0.0);
	}
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        n = i * 3.14 / 180;
        glVertex2f(largeurTonneau * cos(n), largeurTonneau * sin(n));
    }
    glEnd();
    glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.0, largeurPoutre * 0.75);//face avant
    glRotatef(180.0, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        n = i * 3.14 / 180;
        glVertex2f(largeurTonneau * cos(n), largeurTonneau * sin(n));
    }
    glEnd();
    glPopMatrix();
	GLUquadric *glNewQuad = gluNewQuadric();
	gluCylinder(glNewQuad, largeurTonneau, largeurTonneau, largeurPoutre * 0.75, 30.0, 30.0);
    glPopMatrix();
    tabTonneau[nbTonneau][0] = xTonneau;
    tabTonneau[nbTonneau][1] = yTonneau;
    tabTonneau[nbTonneau][2] = 0.0F;
}

static void donkeyKong(float size) {
    //mario(size,false);
}



static void placementEchelles() {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_echelles);

    glPushMatrix(); //echelle  3 -> 4
    glTranslatef(1.0, 110.0, -largeurPoutre / 2);
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  2 -> 3
    glTranslatef(-25.0, 90.0, -largeurPoutre / 2); //on recule pour que les échelles soit derrière les poutres
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle cassee 2 -> 3
    glTranslatef(10.0, 90.0, -largeurPoutre / 2);
    echelleCassee(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  cassee 1 -> 2
    glTranslatef(35.0, 70.0, -largeurPoutre / 2);
    echelleCassee(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  1 -> 2
    glTranslatef(15.0, 70.0, -largeurPoutre / 2);
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  cassee 0 -> 1
    glTranslatef(0.0, 50.0, -largeurPoutre / 2);
    echelleCassee(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle 0 -> 1
    glTranslatef(-28.0, 50.0, -largeurPoutre / 2);
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  cassee -1 -> 0
    glTranslatef(-17.0, 30.0, -largeurPoutre / 2);
    echelleCassee(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle -1 -> 0
    glTranslatef(10.0, 30.0, -largeurPoutre / 2);
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle  cassee -2 -> -1
    glTranslatef(30.0, 10.0, -largeurPoutre / 2);
    echelleCassee(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPushMatrix(); //echelle -2 -> -1
    glTranslatef(-27.0, 10.0, -largeurPoutre / 2);
    echelle(hauteurEchelle, largeurEchelle);
    glPopMatrix();

    glPopMatrix();

}


static void placementMario() {
    glPushMatrix();
    glTranslatef(mario.getX(), mario.getY(), mario.getZ());
    mario.printPerso(sautEnCours);
    glPopMatrix();
}


static void placementPrincesse() {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_princesse); // TODO : REMPLACER LE MATERIAU PAR UNE TEXTURE
    glPushMatrix();
    glTranslatef(princess.getX(), princess.getY(), princess.getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    princess.printPerso(false);
    glPopMatrix();
    glPopMatrix();
}
/*
static void placementDK() {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_dk); // TODO : REMPLACER LE MATERIAU PAR UNE TEXTURE
    glPushMatrix();
    glTranslatef(xDonkeyKong, yDonkeyKong, zDonkeyKong);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    princesse(tailleMario*1.7);
    glPopMatrix();
    glPopMatrix();
}
*/

void placementPoutres() {
    glPushMatrix();
    
    p7.dessinerPoutre(1);

    p6.dessinerPoutre(2);

    p5.dessinerPoutre(0);

    p4.dessinerPoutre(0);

    p3.dessinerPoutre(0);

    p2.dessinerPoutre(0);

    p1.dessinerPoutre(0);

    p0.dessinerPoutre(0);

    glPopMatrix();

}

void placementTasTonneaux() {
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    tonneau(56,-3.0 ,-110.0, false);
    tonneau(62,-3.0 ,-110.0, false);
    tonneau(68,-3.0 ,-110.0, false);
    tonneau(60, -3.0, -110-(largeurTonneau*2), false);
    tonneau(66, -3.0, -110 - (largeurTonneau * 2), false);
    tonneau(63, -3.0, -110 - (largeurTonneau * 4), false);
    glPopMatrix();

}

static void sceneJeu() {
    glEnable(GL_DEPTH_TEST);
    glTranslated(0.0, 0.0, -90.0);
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    placementPoutres();
    placementEchelles();
    glTranslatef(-3.75F, 3.0F, 0.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    glPopMatrix();
    glPushMatrix();
    placementMario();
    placementPrincesse();
    for (int i = 0; i < nbTonneau; ++i) {
		if (tabTonneau[i][2] == 0) {
			tonneau(tabTonneau[i][0], tabTonneau[i][1], zTonneauBegin,false);
		}
		else {
			tonneau(tabTonneau[i][0], tabTonneau[i][1], zTonneauBegin,true);
		}
    }
    //placementDK();
    placementTasTonneaux();
    glPopMatrix();
}

static void sceneGameOver() {
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0, 1.0, 1.0);
    std::string textGO = "GAME OVER !!";
    std::string pointilleGO = "------------";
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth / 2, 0, windowHeight / 2);

    glRasterPos2f(windowWidth * 0.20, windowHeight / 4);
    for (int i = 0;i < textGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.27);
    for (int i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.23);
    for (int i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}


static void sceneVictory() {
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0, 1.0, 1.0);
    std::string textGO = "C'EST GAGNE !!";
    std::string pointilleGO = "------------";
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth / 2, 0, windowHeight / 2);

    glRasterPos2f(windowWidth * 0.20, windowHeight / 4);
    for (int i = 0;i < textGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.27);
    for (int i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.23);
    for (int i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}


static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,10.0,1.0 };
    glPolygonMode(GL_FRONT_AND_BACK, (filDeFer) ? GL_FILL : GL_LINE);
    if (texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    if (!cameraFPS) {
        switch (lumiere) {
        case 0:
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            gluLookAt(px, py, pz, 0.0, 60.0, -50.0, 0.0, 1.0, 0.0);
            break;
        case 1:
            gluLookAt(px, py, pz, 0.0, 60.0, -50.0, 0.0, 1.0, 0.0);
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            break;
        }
    }
    else {
        switch (lumiere) {
        case 0:
            switch(mario.getOrientation()){
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            case Perso::Gauche:
                if (mario.getX() <0) {
                    gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY()+1.5 +  mario.getTaille(), -90.0 - mario.getZ(),  mario.getX() - mario.getTaille() / 3.0-0.1, mario.getY() +mario.getTaille()+1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
                else {
                    if(mario.getX() > 0){
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0 , mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(),- mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                    }
                    else {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), -1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);

                    }
                }
            break;
            case Perso::Droite:
                if (mario.getX() < 0) {
                     gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(),- mario.getX() - mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
                else {
                    if (mario.getX() > 0) {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);

                    }
                    else {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), 1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ()- mario.getTaille() / 3.0-1.0, 0.0, 1.0, 0.0);

                    
                    }
                }
            break;
            
            case Perso::Dos:
                gluLookAt(mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(),  mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                break;
            
            
            }
            break;
        case 1:
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            switch (mario.getOrientation()) {
                glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            case Perso::Gauche:
                if (mario.getX() < 0) {
                    gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), mario.getX() - mario.getTaille() / 3.0 - 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
                else {
                    if (mario.getX() > 0) {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), -mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                    }
                    else {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), -1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);

                    }
                }
                break;
            case Perso::Droite:
                if (mario.getX() < 0) {
                    gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), -mario.getX() - mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
                else {
                    if (mario.getX() > 0) {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);

                    }
                    else {
                        gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), 1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ() - mario.getTaille() / 3.0 - 1.0, 0.0, 1.0, 0.0);


                    }
                }
                break;

            case Perso::Dos:
                gluLookAt(mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(), mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                break;
            }
            break;
        }
    }
    sceneJeu();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);
}





static void displayWGO(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sceneGameOver();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);

}

static void displayWVictoire(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sceneVictory();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);

}






static void reshape(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double)tx / ty;
    if (ratio >= 1.0)
        gluPerspective(80, ratio, 10.0, 2000.0);
    else
        gluPerspective(80 / ratio, ratio, 10.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void reshapeWGO(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutReshapeWindow(windowWidth / 2, windowHeight / 2);
    gluOrtho2D(-windowWidth / 4, windowWidth / 4, -windowHeight / 4, windowHeight / 4);
}



static void reshapeWVictoire(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutReshapeWindow(windowWidth / 2, windowHeight / 2);
    gluOrtho2D(-windowWidth / 4, windowWidth / 4, -windowHeight / 4, windowHeight / 4);
}


static void special(int key, int x, int y) {
    //printf("K  x=%d y=%d z=%d\n", px, py, pz);
    switch (key) {
    case GLUT_KEY_UP: //page down pour avancer
        pz -= 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN: //page down pour reculer
        pz += 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:  //page down pour aller a gauche
        px -= 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:  //page down pour aller a droite
        px += 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP: //page down pour monter
        py += 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN: //page down pour descendre
        py -= 0.5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_END: //retour à la position de base de la caméra via la touche "fin"
        px = initCamX;
        py = initCamY;
        pz = initCamZ;
        glutPostRedisplay();
        break;
    }
}

static void tomber(int value) {
	mario.setY(mario.getY() - 0.2);
	if (mario.getY() <= value) {
		if (chute) {
			gameover = true;
            return;
		}
		sautEnCours = false;
		return;
	}
	glutPostRedisplay();
	glutTimerFunc(1, tomber, value);
}


static void gaucheMario(int poutre) {
	mario.setSurEchelle(false);
    mario.setOrientation(Perso::Orientation::Gauche);
    mario.setX(mario.getX() - longueurPas);
    switch (poutre) {
    case -2: case 0: case 2:
        if (mario.getX() >= 45 || mario.getX() <= -55) {
			chute = true;
			sautEnCours = true;
			tomber(-20);
        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        break;
    case -1: case 1: case 3:
        if (mario.getX() >= 55 || mario.getX() <= -45) {
            int indice = poutre + 1;
			sautEnCours = true;
			tomber((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        break;
    case 4: 
        if (mario.getX() <= -25) {
            victoire = true;
            glutDestroyWindow(WindowDK);
            glutInitWindowSize(windowWidth / 2, windowHeight / 2);
            glutInitWindowPosition(50, 50);
            glutCreateWindow("DonkeyKong - VICTOIRE !"); //creer la fenetre de gameOver
            glutReshapeFunc(reshapeWVictoire);
            glutDisplayFunc(displayWVictoire);
        }
        break;
    default:
        break;
    }
}


static void droiteMario(int poutre) {
	mario.setSurEchelle(false);
    mario.setOrientation(Perso::Orientation::Droite);
    mario.setX(mario.getX() + longueurPas);
    switch (poutre) {
    case -1: case 1: 
        if (mario.getX() >= 55 || mario.getX() <= -45) {
			chute = true;
			sautEnCours = true;
			tomber(-20);
        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);

        }
        break;
    case 3:
        if (mario.getX() >= 55 || mario.getX() <= -45) {
			chute = true;
			sautEnCours = true;
            tomber(-20.0);
        }
        else {
            if (mario.getX() >= 40) { //gameover quand mario "marche" sur donkeyKong
                gameover = true;
                return;
            }
            else {
                int indice = poutre + 2;
                mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
            }

        }
        break;

    case -2:
        if (mario.getX() >= 45 || mario.getX() <= -55) {
            chute = true;
			sautEnCours = true;
			tomber(-20.0);
        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        break;
    case 0: case 2:

        if (mario.getX() >= 45 || mario.getX() <= -55) {
            int indice = poutre + 1;
			sautEnCours = true;
			tomber(listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX() + compensationPoutre);
            //mario.setX(45.0);
            //mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        break;
    case 4:
        int indice = poutre + 1;
        if (mario.getX() >= 15) {
			sautEnCours = true;
			tomber(listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX() + compensationPoutre);
            //mario.setX(15.0);
            //mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + compensationPoutre);
        }
        break;
    } 
}

static void sautMario(int value) {
    if (saut) {
       
        if (mario.getY() - initYsaut < 10.0) {
            mario.setY(mario.getY() + 0.05);
        }
        else {
            saut = false;
        }
        
    }
    if (!saut) {
        if (mario.getY() > initYsaut) {
            mario.setY(mario.getY() - 0.05);
        }
        else {
            sautEnCours = false;
        }
    }
    if(sautEnCours){
        glutTimerFunc(2, sautMario, 0);
    }
}

static void keyboard(unsigned char key, int x, int y) {
	int index1 = 0;
	bool trouveHaut = false;
	int index2 = 0;
	bool trouveBas = false;

	//printf(" Touche: %c = %d \n", key, key);
	switch (key) {

	case 109: case 77: //mode fil de fer en appuyant sur la touche m
		filDeFer = (filDeFer + 1) % 2;
		glutPostRedisplay();
		break;

	case 0x0D: //eclairage en appuyant sur entrée
		lumiere = (lumiere + 1) % 2;
		glutPostRedisplay();
		break;

	case 0x1B: //quitter en appuyant sur échap
		exit(0);
		break;
	case 0x20: //saut de mario avec la barre espace
		if (!sautEnCours && !mario.getSurEchelle()) {

			sautEnCours = true;
			saut = true;
			initYsaut = mario.getY();
			sautMario(0);
		}


		break;

	case 122: case 90://faire monter Mario avec Z ou z
		if (!gameover && !pause && !victoire) {
			do {
				//on récupère les coordonnées des 4 coins de la zone échelle
				float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
				float tempSupDroit[2] = { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
				float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
				float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };
				bool tempB = mario.getX() < tempSupDroit[0] && mario.getX() > tempSupGauche[0];
				bool tempB2 = mario.getY() + mario.getTaille() * 0.25 >= tempInfDroit[1] && mario.getY() + mario.getTaille() * 0.25 <= tempSupGauche[1];
				if (tempB && tempB2) {
					trouveHaut = true;
					sautEnCours = false;
					mario.setSurEchelle(true);
				}
				index1++;

			} while (index1 < nombreEchelle && !trouveHaut);

			if (trouveHaut) {
				mario.setY(mario.getY() + 0.5);
				index1 = 0;
				trouveHaut = false;
				mario.setOrientation(Perso::Orientation::Dos);
				glutPostRedisplay();
			}
		}
		break;

	case 115: case 83://faire descendre Mario avec S ou s
		if (!gameover && !pause && !victoire) {
			do {
				//on récupère les coordonnées des 4 coins de la zone échelle
				float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
				float tempSupDroit[2] = { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
				float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
				float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };
				bool tempB = mario.getX() < tempSupDroit[0] && mario.getX() > tempSupGauche[0];
				bool tempB2 = mario.getY() - mario.getTaille() * 0.25 >= tempInfDroit[1] && mario.getY() - mario.getTaille() * 0.25 <= tempSupDroit[1];
				if (tempB && tempB2) {
					trouveHaut = true;
					sautEnCours = false;
					mario.setSurEchelle(true);
				}
				index1++;

			} while (index1 < nombreEchelle && !trouveHaut);

			if (trouveHaut) {
				mario.setY(mario.getY() - longueurPas);
				index1 = 0;
				trouveHaut = false;
				mario.setOrientation(Perso::Orientation::Dos);
				glutPostRedisplay();
			}
		}
		break;

	case 113: case 81: //faire aller Mario à gauche avec Q ou q
		if (!gameover && !pause && !victoire && !sautEnCours) {
			if (mario.getY() >= -2.8 + compensationPoutre && mario.getY() <= 5.0 + compensationPoutre) { //Si Mario sur poutre -2 - OK
				if (mario.getX() < 45 && mario.getX() > -55) {
					gaucheMario(-2);
				}
			}
			else {
				if (mario.getY() >= 16.94 + compensationPoutre && mario.getY() <= 26.0 + compensationPoutre) { //Si Mario sur poutre -1 - OK
					if (mario.getX() < 55 && mario.getX() > -45) {
						gaucheMario(-1);
					}
				}
				else {
					if (mario.getY() >= 37.2 + compensationPoutre && mario.getY() <= 45.0 + compensationPoutre) { //Si Mario sur poutre 0 - OK
						if (mario.getX() < 45 && mario.getX() > -55) {
							gaucheMario(0);
						}
					}
					else {
						if (mario.getY() >= 56.94 + compensationPoutre && mario.getY() <= 66.0 + compensationPoutre) { //Si Mario sur poutre +1 - OK
							if (mario.getX() < 55 && mario.getX() > -45) {
								gaucheMario(1);
							}
						}
						else {
							if (mario.getY() >= 77.2 + compensationPoutre && mario.getY() <= 85.0 + compensationPoutre) { //Si Mario sur poutre +2 - OK
								if (mario.getX() < 45 && mario.getX() > -55) {
									gaucheMario(2);
								}
							}
							else {
								if (mario.getY() >= 96.94 + compensationPoutre && mario.getY() <= 103.6 + compensationPoutre) { //Si Mario sur poutre +3 - OK
									if (mario.getX() < 55 && mario.getX() > -45) {
										gaucheMario(3);
									}
								}
								else {
									if (mario.getY() >= 119.0 + compensationPoutre && mario.getY() <= 122.0 + compensationPoutre) { //Si Mario sur poutre victoire - OK
										if (mario.getX() < 15 && mario.getX() > -35) {
											gaucheMario(4);
										}
									}
								}
							}
						}
					}
				}
			}
			glutPostRedisplay();
		}
		break;

	case 100: case 68: //faire aller Mario à droite avec D ou d
		if (!gameover && !pause && !victoire && !sautEnCours) {
			if (mario.getY() >= -2.8 + compensationPoutre && mario.getY() <= 5.0 + compensationPoutre) { //Si Mario sur poutre -2 - OK
				if (mario.getX() < 45 && mario.getX() > -55) {
					droiteMario(-2);
				}
			}
			else {
				if (mario.getY() >= 16.94 + compensationPoutre && mario.getY() <= 26.0 + compensationPoutre) { //Si Mario sur poutre -1 - OK
					if (mario.getX() < 55 && mario.getX() > -45) {
						droiteMario(-1);
					}
				}
				else {
					if (mario.getY() >= 35.0 + compensationPoutre && mario.getY() <= 45.0 + compensationPoutre) { //Si Mario sur poutre 0 - OK
						if (mario.getX() <= 45 && mario.getX() > -55) {
							droiteMario(0);

						}
					}
					else {
						if (mario.getY() >= 54.0 + compensationPoutre && mario.getY() <= 66.0 + compensationPoutre) { //Si Mario sur poutre +1 - OK
							if (mario.getX() < 55 && mario.getX() > -45) {
								droiteMario(1);

							}
						}
						else {
							if (mario.getY() >= 75.0 + compensationPoutre && mario.getY() <= 85.0 + compensationPoutre) { //Si Mario sur poutre +2 - OK
								if (mario.getX() < 45 && mario.getX() > -55) {
									droiteMario(2);

								}
							}
							else {
								if (mario.getY() >= 94.0 + compensationPoutre && mario.getY() <= 106.0 + compensationPoutre) { //Si Mario sur poutre +3 - OK
									if (mario.getX() < 55 && mario.getX() > -45) {
										droiteMario(3);

									}
								}
								else {
									if (mario.getY() >= 119.0 + compensationPoutre && mario.getY() <= 125.0 + compensationPoutre) { //Si Mario sur poutre victoire - OK
										if (mario.getX() < 15 && mario.getX() > -35) {
											droiteMario(4);

										}
									}
								}
							}
						}
					}
				}
			}
			glutPostRedisplay();
		}
		break;
	case 112: case 80: //Mettre le jeu en pause avec p ou P
        pause = !pause;
		glutPostRedisplay();
		break;

	case 103: case 71: //Passez en god mod avec g ou G
		godMod = !godMod;
		glutPostRedisplay();
        break;
	
    case 86: case 118:
        printf("%f\n", mario.getZ());
        printf("%f\n", mario.getZ());
        printf("%f\n", mario.getZ());
        cameraFPS = !cameraFPS;
        glutPostRedisplay();
        break;
    }
}

static void clean(void) {
    for (int i = 0; i < 1; i++) {
        if (textureID[i] != 0) {
            glDeleteTextures(1, &textureID[i]);
        }
    }
}

static void decalerTableauTonneau(float indice) {
    if (nbTonneau == 1) {// Cas 1 seul élément
        nbTonneau = 0;
        return;
    }
    else if (nbTonneau == indice + 1) {//Cas dernière case enlevé
        nbTonneau--;
        return;
    }
    for (int i = indice; i < nbTonneau - 1; ++i) {//Cas classique
        tabTonneau[i][0] = tabTonneau[i + 1][0];
        tabTonneau[i][1] = tabTonneau[i + 1][1];
    }
    nbTonneau--;
}

static void mouvementTonneau(float ordoOrigine, float coefDir, float distance, int i) {
    tabTonneau[i][0] += distance;
    tabTonneau[i][1] = (ordoOrigine + coefDir * tabTonneau[i][0]) + 2 * compensationPoutre;
}

void updateTonneau(int value) {
    if(!gameover && !pause && !victoire){
    float hauteurMario = mario.getTaille();
    float posXMario = mario.getX();
    float posYMario = mario.getY();
    float largeurMario = hauteurMario / 6 * 0.75;
    float supprimerTonneau = -1;
    float vitesseTonneau = longueurPas *0.75;

	//Descendre échelles
	for (int i = 0; i < nbTonneau; ++i) {
		bool descendreEchelle = false;
		bool descendreEchelleCassees = false;
		for (int j = 0; j < nombreEchelle; ++j) {
			float tempSupGauche[2] = { listeDesEchelles[j][0][0],listeDesEchelles[j][0][1] };
			float tempSupDroit[2] = { listeDesEchelles[j][1][0],listeDesEchelles[j][1][1] };
			float tempInfGauche[2] = { listeDesEchelles[j][2][0],listeDesEchelles[j][2][1] };
			float tempInfDroit[2] = { listeDesEchelles[j][3][0],listeDesEchelles[j][3][1] };
			bool tempX = tabTonneau[i][0] > tempSupGauche[0] + demieLargeurEchelle/3 - vitesseTonneau && tabTonneau[i][0] < tempSupDroit[0] - demieLargeurEchelle - demieLargeurEchelle*2/3 + vitesseTonneau;
			bool tempY = tabTonneau[i][1] <= tempSupGauche[1] + largeurTonneau && tabTonneau[i][1] >= tempInfGauche[1] + largeurTonneau * 2;
			if (tempX && tempY) {
				if (tabTonneau[i][2] == 0) {
					int descendreAleatoire = rand() % 2;
					tabTonneau[i][2] = (float)descendreAleatoire;
				}
				if (tabTonneau[i][2] == 1) {
					tabTonneau[i][1] -= longueurPas;
					descendreEchelle = true;
					break;
				}
			}
		}
		//Descendre échelles cassees
		if (!descendreEchelle) {
			for (int j = 0; j < nombreEchelleCassee; ++j) {
				float tempSupGauche[2] = { listeDesEchellesCassees[j][0][0],listeDesEchellesCassees[j][0][1] };
				float tempSupDroit[2] = { listeDesEchellesCassees[j][1][0],listeDesEchellesCassees[j][1][1] };
				float tempInfGauche[2] = { listeDesEchellesCassees[j][2][0],listeDesEchellesCassees[j][2][1] };
				float tempInfDroit[2] = { listeDesEchellesCassees[j][3][0],listeDesEchellesCassees[j][3][1] };
				bool tempX = tabTonneau[i][0] >= tempSupGauche[0]  && tabTonneau[i][0] <= tempSupDroit[0] - largeurEchelle;
				bool tempY = tabTonneau[i][1] <= tempSupGauche[1] + largeurTonneau && tabTonneau[i][1] >= tempInfGauche[1] + largeurTonneau * 2;
				if (tempX && tempY) {
					if (tabTonneau[i][2] == 0) {
						int descendreAleatoire = rand() % 2;
						tabTonneau[i][2] = (float)descendreAleatoire;
					}
					if (tabTonneau[i][2] == 1) {
						tabTonneau[i][1] -= longueurPas;
						descendreEchelleCassees = true;
						break;
					}
				}
			}
		}
		if (!descendreEchelle && !descendreEchelleCassees) {
			tabTonneau[i][2] = 0;
			if (tabTonneau[i][1] >= -3.0 + 2 * compensationPoutre && tabTonneau[i][1] <= 2.8 + 2 * compensationPoutre) {
				if (tabTonneau[i][0] - longueurPas < 55 && tabTonneau[i][0] + longueurPas>-55) {
					mouvementTonneau(0, -0.06, vitesseTonneau, i);
				}
			}
			else {
				if (tabTonneau[i][1] >= 16.2 + 2 * compensationPoutre && tabTonneau[i][1] <= 23.0 + 2 * compensationPoutre) {
					if (tabTonneau[i][0] - longueurPas < 56 && tabTonneau[i][0] + longueurPas> -50) {
						mouvementTonneau(19.69, 0.06, -vitesseTonneau, i);
					}
				}
				else {
					if (tabTonneau[i][1] >= 36.0 + 2 * compensationPoutre && tabTonneau[i][1] <= 42.8 + 2 * compensationPoutre) {
						if (tabTonneau[i][0] - longueurPas < 50 && tabTonneau[i][0] + longueurPas > -55) {
							mouvementTonneau(39.72, -0.06, vitesseTonneau, i);
						}
					}
					else {
						if (tabTonneau[i][1] >= 55 + 2 * compensationPoutre && tabTonneau[i][1] <= 63.06 + 2 * compensationPoutre) {
							if (tabTonneau[i][0] - longueurPas < 56 && tabTonneau[i][0] + longueurPas > -50) {
								mouvementTonneau(59.69, 0.06, -vitesseTonneau, i);
							}
						}
						else {
							if (tabTonneau[i][1] >= 75 + 2 * compensationPoutre && tabTonneau[i][1] <= 82.8 + 2 * compensationPoutre) {
								if (tabTonneau[i][0] - longueurPas < 50 && tabTonneau[i][0] + longueurPas > -55) {
									mouvementTonneau(79.72, -0.06, vitesseTonneau, i);
								}
							}
							else {
								if (tabTonneau[i][1] >= 95.00 + 2 * compensationPoutre && tabTonneau[i][1] <= 103.6 + 2 * compensationPoutre) {
									if (tabTonneau[i][0] - longueurPas < 55 && tabTonneau[i][0] + longueurPas > -50) {
										mouvementTonneau(99.69, 0.06, -vitesseTonneau, i);
									}
								}
								else {
									if (tabTonneau[i][1] >= 120.0 + 2 * compensationPoutre && tabTonneau[i][1] <= 122.0 + 2 * compensationPoutre) {
										if (tabTonneau[i][0] - longueurPas < 15 && tabTonneau[i][0] + longueurPas > -35) {
											//printf("X Tonneau :%f\n", tabTonneau[i][0]);
											//printf("Y Tonneau :%f\n", tabTonneau[i][1]);
										}
									}
								}
							}
						}
					}
				}
			}

			//Deplacement vertical
            if (tabTonneau[i][1] <= 97.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 83.06 + 2 * compensationPoutre) {
                tabTonneau[i][1] -= longueurPas;
            }
			if (tabTonneau[i][1] <= 77.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 63.06 + 2 * compensationPoutre) {
				tabTonneau[i][1] -= longueurPas;
			}
			else if (tabTonneau[i][1] <= 57.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 43.0 + 2 * compensationPoutre) {
				tabTonneau[i][1] -= longueurPas;
			}
			else if (tabTonneau[i][1] <= 38.2 + 2 * compensationPoutre && tabTonneau[i][1] >= 23.0 + 2 * compensationPoutre) {
				tabTonneau[i][1] -= longueurPas;
			}
			else if (tabTonneau[i][1] <= 17.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 2.7 + 2 * compensationPoutre) {
				tabTonneau[i][1] -= longueurPas;
			}
			else if (tabTonneau[i][1] <= -2.9 + 2 * compensationPoutre && tabTonneau[i][1] >= -30 + 2 * compensationPoutre) {
				tabTonneau[i][1] -= longueurPas;
			}
			else if (tabTonneau[i][1] <= -30 + 2 * compensationPoutre) {
				supprimerTonneau = i;
			}
		}

		//Collisions tonneaux
        if (tabTonneau[i][0] + 3.0 >= posXMario - largeurMario && tabTonneau[i][0] - 3.0 <= posXMario + largeurMario) {
			if (tabTonneau[i][1] + largeurTonneau >= posYMario && tabTonneau[i][1] <= posYMario + hauteurMario) {
				if (!godMod) {
					printf("Aie partout\n");
					gameover = true;
                    return;
				}

			}
        }
    }

    if (supprimerTonneau >= 0) {
        decalerTableauTonneau(supprimerTonneau);
        supprimerTonneau = -1;
    }
    glutPostRedisplay();
    
    }
    glutTimerFunc(25, updateTonneau, 0);
}

static void ajoutTonneau(int value) {
	if (!gameover && !pause && !victoire) {
		tonneau(xTonneauBegin, yTonneauBegin, zTonneauBegin, false);
		nbTonneau++;
		glutTimerFunc(5000, ajoutTonneau, 0);
	}
    else if(pause){
		glutTimerFunc(5000, ajoutTonneau, 0);
	}
}


static void printWVictoire(int value) {
    if (victoire) {
        victoire = false;
        glutDestroyWindow(WindowDK);
        glutInitWindowSize(windowWidth / 2, windowHeight / 2);
        glutInitWindowPosition(50, 50);
        glutCreateWindow("DonkeyKong - VICTOIRE !"); //creer la fenetre de gameOver
        glutReshapeFunc(reshapeWVictoire);
        glutDisplayFunc(displayWVictoire);   // Register display callback

    }

    glutTimerFunc(2, printWVictoire, value);
}

static void printWGameOver(int value) {
    if (gameover) {
        gameover = false;
        glutDestroyWindow(WindowDK);
        glutInitWindowSize(windowWidth / 2, windowHeight / 2);
        glutInitWindowPosition(50, 50);
        glutCreateWindow("DonkeyKong - GAME OVER !"); //creer la fenetre de gameOver
        glutReshapeFunc(reshapeWGO);
        glutDisplayFunc(displayWGO);   // Register display callback

    }

    glutTimerFunc(2, printWGameOver, value);
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(50, 50);
    WindowDK=glutCreateWindow("DonkeyKong");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(5, ajoutTonneau, 0);
    glutTimerFunc(100, updateTonneau, 0);
    glutTimerFunc(5, printWGameOver, 0);
    glutTimerFunc(5, printWVictoire, 0);
    glutMainLoop();
    return(0);
}

