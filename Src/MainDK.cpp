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
#include "PNG/Coordonnee2D.h"
#include "PNG/Echelle.h"

/*ID
Mario : 0
Peach : 1
Donkey Kong : 2 
*/

/********************************************************************************************/
/********************************************************************************************/
/* DECLARATION DES VARIABLES ET DES CONSTANTES*/
/********************************************************************************************/
/********************************************************************************************/
static unsigned int textureID[72] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

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
static bool lumiere = false;

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

float tailleHumaine = 7.0F;

//MARIO
float initXMario = 5.0;
//float initYMario = 120+ compensationPoutre;
float initYMario = (-0.06 * initXMario) + 1.75*compensationPoutre;
float initZMario = -1.0;
float longueurPas = 0.5F;
bool chute = false;

Perso mario(initXMario, initYMario, initZMario, tailleHumaine);

Perso::Orientation initOrientationMario = mario.getOrientation();

int directionMario = 0;
int changerPiedsMario = 0;
int directionAvantMario = 0;

//PEACH
float xPrincesse = -30.0;
float yPrincesse = 120.0+ 1.75 * compensationPoutre;
float zPrincesse = 0.0;

Perso princess(xPrincesse, yPrincesse, zPrincesse, tailleHumaine);

//DK
float xDonkeyKong = 40.0;
float yDonkeyKong = (99.69 + 0.06 * xDonkeyKong) + 1.75 * compensationPoutre;
float zDonkeyKong = -2.0;

Perso donkeyKong(xDonkeyKong, yDonkeyKong, zDonkeyKong, 17.0F);
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
bool lanceTonneaux = false;
bool auSecours = false;
bool sautEnCours = false;
bool godMod = false;
bool cameraFPS = false;
float initYsaut = 0.0f;


//Echelle normale

Echelle * listeDesEchelles = Echelle::getListEchelles(mario);

//Echelles cassée

Echelle * listeDesEchellesCassees = Echelle::getListEchellesCassee(mario);

//Poutres
Poutre * listePoutre = Poutre::getListPoutre();



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
GLfloat couleur_tonneaux[] = { 0.9F, 0.7F, 0.3F,1.0F };

const GLfloat light0_position[] = { 0.0,0.0,10.0,1.0 };
const GLfloat light2_position[] = { -45.0,50.0,10.0,1.0 };
GLfloat amb1[] = { 0.9,0.9,0.9,1.0 };
GLfloat dif1[] = { 0.8,0.8,0.8,1.0 };
GLfloat spe1[] = { 0.1,0.1,0.1,1.0 };

static float diffuse0[4] = { 0.6F,0.6F,0.6F,1.0F };
static float ambiant0[4] = { 0.2F,0.2F,0.2F,1.0F };
static float specular0[4] = { 0.8F,0.8F,0.8F,1.0F };
static float position0[4] = { 0.0,0.0,0.0,1.0 };
static float spotCutOff0[1] = { 15.0F };
static float spotDir0[3] = { 0.0F,0.0F,-1.0F };

/********************************************************************************************/
/********************************************************************************************/
/* FONCTIONS UTILITAIRES*/
/********************************************************************************************/
/********************************************************************************************/

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
            //printf("Texture chargee %d : %s\n", textureID, filename);
        }
        else {
           // printf("Texture non charge\n");
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
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glGenTextures(72, textureID);


	//Mario
	chargementTexture("textureMario/marioAvantTete.png", textureID[0]);
	chargementTexture("textureMario/marioArriereTete.png", textureID[1]);
	chargementTexture("textureMario/marioGaucheTete.png", textureID[2]);
	chargementTexture("textureMario/marioDroiteTete.png", textureID[3]);
	chargementTexture("textureMario/marioDessusTete.png", textureID[4]);
	chargementTexture("textureMario/marioAvantTorse.png", textureID[5]);
	chargementTexture("textureMario/marioArriereTorse.png", textureID[6]);
	chargementTexture("textureMario/marioGaucheTorse.png", textureID[7]);
	chargementTexture("textureMario/marioDroiteTorse.png", textureID[8]);
	chargementTexture("textureMario/marioDessousTorse.png", textureID[9]);
	chargementTexture("textureMario/marioDessusTorse.png", textureID[10]);
	chargementTexture("textureMario/marioAvantBras.png", textureID[11]);
	chargementTexture("textureMario/marioArriereBras.png", textureID[12]);
	chargementTexture("textureMario/marioGaucheBras.png", textureID[13]);
	chargementTexture("textureMario/marioDroiteBras.png", textureID[14]);
	chargementTexture("textureMario/marioDessousBras.png", textureID[15]);
	chargementTexture("textureMario/marioDessusBras.png", textureID[16]);
	chargementTexture("textureMario/marioAvantJambe.png", textureID[17]);
	chargementTexture("textureMario/marioArriereJambe.png", textureID[18]);
	chargementTexture("textureMario/marioGaucheJambe.png", textureID[19]);
	chargementTexture("textureMario/marioDroiteJambe.png", textureID[20]);
	chargementTexture("textureMario/marioDessousJambe.png", textureID[21]);
	chargementTexture("textureMario/marioDessusJambe.png", textureID[22]);
	//Peach
	chargementTexture("texturePeach/peachAvantTete.png", textureID[23]);
	chargementTexture("texturePeach/peachArriereTete.png", textureID[24]);
	chargementTexture("texturePeach/peachGaucheTete.png", textureID[26]);
	chargementTexture("texturePeach/peachDroiteTete.png", textureID[25]);
	chargementTexture("texturePeach/peachDessusTete.png", textureID[27]);
	chargementTexture("texturePeach/peachAvantTorse.png", textureID[28]);
	chargementTexture("texturePeach/peachArriereTorse.png", textureID[29]);
	chargementTexture("texturePeach/peachGaucheTorse.png", textureID[30]);
	chargementTexture("texturePeach/peachDroiteTorse.png", textureID[31]);
	chargementTexture("texturePeach/peachDessousTorse.png", textureID[32]);
	chargementTexture("texturePeach/peachDessusTorse.png", textureID[33]);
	chargementTexture("texturePeach/peachAvantBras.png", textureID[34]);
	chargementTexture("texturePeach/peachArriereBras.png", textureID[35]);
	chargementTexture("texturePeach/peachGaucheBras.png", textureID[36]);
	chargementTexture("texturePeach/peachDroiteBras.png", textureID[37]);
	chargementTexture("texturePeach/peachDessousBras.png", textureID[38]);
	chargementTexture("texturePeach/peachDessusBras.png", textureID[39]);
	chargementTexture("texturePeach/peachAvantJambe.png", textureID[40]);
	chargementTexture("texturePeach/peachArriereJambe.png", textureID[41]);
	chargementTexture("texturePeach/peachGaucheJambe.png", textureID[42]);
	chargementTexture("texturePeach/peachDroiteJambe.png", textureID[43]);
	chargementTexture("texturePeach/peachDessousJambe.png", textureID[44]);
	chargementTexture("texturePeach/peachDessusJambe.png", textureID[45]);
	//Dk
	chargementTexture("textureDK/dkAvantTete.png", textureID[46]);
	chargementTexture("textureDK/dkArriereTete.png", textureID[47]);
	chargementTexture("textureDK/dkGaucheTete.png", textureID[49]);
	chargementTexture("textureDK/dkDroiteTete.png", textureID[48]);
	chargementTexture("textureDK/dkDessusTete.png", textureID[50]);
	chargementTexture("textureDK/dkAvantTorse.png", textureID[51]);
	chargementTexture("textureDK/dkArriereTorse.png", textureID[52]);
	chargementTexture("textureDK/dkGaucheTorse.png", textureID[53]);
	chargementTexture("textureDK/dkDroiteTorse.png", textureID[54]);
	chargementTexture("textureDK/dkDessousTorse.png", textureID[55]);
	chargementTexture("textureDK/dkDessusTorse.png", textureID[56]);
	chargementTexture("textureDK/dkAvantBras.png", textureID[57]);
	chargementTexture("textureDK/dkArriereBras.png", textureID[58]);
	chargementTexture("textureDK/dkGaucheBras.png", textureID[59]);
	chargementTexture("textureDK/dkDroiteBras.png", textureID[60]);
	chargementTexture("textureDK/dkDessousBras.png", textureID[61]);
	chargementTexture("textureDK/dkDessusBras.png", textureID[62]);
	chargementTexture("textureDK/dkAvantJambe.png", textureID[63]);
	chargementTexture("textureDK/dkArriereJambe.png", textureID[64]);
	chargementTexture("textureDK/dkGaucheJambe.png", textureID[65]);
	chargementTexture("textureDK/dkDroiteJambe.png", textureID[66]);
	chargementTexture("textureDK/dkDessousJambe.png", textureID[67]);
	chargementTexture("textureDK/dkDessusJambe.png", textureID[68]);
    
}

void idle(void) {
    printf("A\n");
}

static void clean(void) {
    for (int i = 0; i < 1; i++) {
        if (textureID[i] != 0) {
            glDeleteTextures(1, &textureID[i]);
        }
    }
}

/********************************************************************************************/
/********************************************************************************************/
/* MODELISATION DES TONNEAUX */
/********************************************************************************************/
/********************************************************************************************/

static void tonneau(float xTonneau, float yTonneau, float zTonneau, bool echelle, unsigned int *texID) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_tonneaux);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
 
    float n;
    glPushMatrix();
	glTranslatef(xTonneau, yTonneau + 4 * compensationPoutre, zTonneau); //face arrière
	if (echelle) {
		glRotatef(90.0, 0.0, 1.0, 0.0);
	}
	
	glPushMatrix();

	glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        n = i * 3.14 / 180;
       glVertex2f(largeurTonneau * cos(n), largeurTonneau * sin(n));
    }
    glEnd();
    glPopMatrix();
	glPushMatrix();
    glTranslatef(0.0, 0.0, largeurPoutre * 0.75);//face avant
    

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
    glPopAttrib();
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
    if (!gameover && !pause && !victoire) {
        float hauteurMario = mario.getTaille();
        float posXMario = mario.getX();
        float posYMario = mario.getY();
        float largeurMario = hauteurMario / 6 * 0.75;
        float supprimerTonneau = -1;
        float vitesseTonneau = longueurPas * 0.75;

        //Descendre échelles
        for (int i = 0; i < nbTonneau; ++i) {
            bool descendreEchelle = false;
            bool descendreEchelleCassees = false;
            for (int j = 0; j < nombreEchelle; ++j) {
                Coordonnee2D tempSupGauche = listeDesEchelles[j].getCoinSupG();
                Coordonnee2D tempSupDroit = listeDesEchelles[j].getCoinSupD();
                Coordonnee2D tempInfGauche = listeDesEchelles[j].getCoinInfG();
                Coordonnee2D tempInfDroit = listeDesEchelles[j].getCoinInfD();

                bool tempX = tabTonneau[i][0] > tempSupGauche.getX() + demieLargeurEchelle / 3 - vitesseTonneau && tabTonneau[i][0] < tempSupDroit.getX() - demieLargeurEchelle - demieLargeurEchelle * 2 / 3 + vitesseTonneau;
                bool tempY = tabTonneau[i][1] <= tempSupGauche.getY() + largeurTonneau && tabTonneau[i][1] >= tempInfGauche.getY() + largeurTonneau * 2;
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
                    Coordonnee2D tempSupGauche = listeDesEchellesCassees[j].getCoinSupG();
                    Coordonnee2D tempSupDroit = listeDesEchellesCassees[j].getCoinSupD();
                    Coordonnee2D tempInfGauche = listeDesEchellesCassees[j].getCoinInfG();
                    Coordonnee2D tempInfDroit = listeDesEchellesCassees[j].getCoinInfD();

                    bool tempX = tabTonneau[i][0] >= tempSupGauche.getX() && tabTonneau[i][0] <= tempSupDroit.getX() - largeurEchelle;
                    bool tempY = tabTonneau[i][1] <= tempSupGauche.getY() + largeurTonneau && tabTonneau[i][1] >= tempInfGauche.getY() + largeurTonneau * 2;
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

static void animationDK(int value) {
    if (value == 0) {
        lanceTonneaux = true;
        glutTimerFunc(500, animationDK, 1);
    }
    else {
        lanceTonneaux = false;
    }
}

static void animationPrincesse(int value) {
    if (value == 0) {
        auSecours = true;
        glutTimerFunc(500, animationPrincesse, 1);
    }
    else {
        auSecours = false;
        int randTiming = rand() % (10000-4000);
        glutTimerFunc(randTiming, animationPrincesse, 0);
    }
}

static void ajoutTonneau(int value) {
    if (!gameover && !pause && !victoire) {
        glutTimerFunc(0, animationDK, 0);
        tonneau(xTonneauBegin, yTonneauBegin, zTonneauBegin, false, textureID);
        nbTonneau++;
        glutTimerFunc(5000, ajoutTonneau, 0);
    }
    else if (pause) {
        glutTimerFunc(5000, ajoutTonneau, 0);
    }
}
/********************************************************************************************/
/********************************************************************************************/
/* PLACEMENT DES PERSONNAGES */
/********************************************************************************************/
/********************************************************************************************/



static void placementMario() {
    glPushMatrix();
    glTranslatef(mario.getX(), mario.getY(), mario.getZ());
    mario.printPerso(sautEnCours, false,false,directionMario, textureID);
    glPopMatrix();
}




static void placementPrincesse() {

    glPushMatrix();
    glPushMatrix();
    glTranslatef(princess.getX(), princess.getY(), princess.getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    princess.printPerso(false, false,auSecours, 0, textureID);
    glPopMatrix();
    glPopMatrix();
    
}



static void placementDK() {

    glPushMatrix();
    glPushMatrix();
    glTranslatef(donkeyKong.getX(), donkeyKong.getY(), donkeyKong.getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
	donkeyKong.printPerso(false, lanceTonneaux,false, 0, textureID);
	glPopMatrix();
    glPopMatrix();
}



/********************************************************************************************/
/********************************************************************************************/
/* DECLARATION DES OBJETS DE LA SCENE DE JEU */
/********************************************************************************************/
/********************************************************************************************/

void placementPoutres() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	listePoutre[7].dessinerPoutre(1);
	listePoutre[6].dessinerPoutre(2);
	listePoutre[5].dessinerPoutre(0);
	listePoutre[4].dessinerPoutre(0);
	listePoutre[3].dessinerPoutre(0);
	listePoutre[2].dessinerPoutre(0);
	listePoutre[1].dessinerPoutre(0);
	listePoutre[0].dessinerPoutre(0);
    glPopAttrib();
    glPopMatrix();

}

void placementTasTonneaux() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    tonneau(56,-3.0 ,-110.0, false, textureID);
    tonneau(62,-3.0 ,-110.0, false, textureID);
    tonneau(68,-3.0 ,-110.0, false, textureID);
    tonneau(60, -3.0, -110-(largeurTonneau*2), false, textureID);
    tonneau(66, -3.0, -110 - (largeurTonneau * 2), false, textureID);
    tonneau(63, -3.0, -110 - (largeurTonneau * 4), false, textureID);
    glPopMatrix();

}

/********************************************************************************************/
/********************************************************************************************/
/* SCENE UTILISEE POUR LE JEU EN COURS DE PARTIE */
/********************************************************************************************/
/********************************************************************************************/
static void sceneJeu() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
    glTranslated(0.0, 0.0, -90.0);
    glPushMatrix();
    placementPoutres();

	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_echelles);
    Echelle::placementEchelles(largeurPoutre);
	glPopMatrix();

    glTranslatef(-3.75F, 3.0F, 0.0F);
    glPopMatrix();
    glPushMatrix();
    placementMario();
    placementPrincesse();
    placementDK();
    for (int i = 0; i < nbTonneau; ++i) {
		if (tabTonneau[i][2] == 0) {
			tonneau(tabTonneau[i][0], tabTonneau[i][1], zTonneauBegin,false, textureID);
		}
		else {
			tonneau(tabTonneau[i][0], tabTonneau[i][1], zTonneauBegin,true, textureID);
		}
    }
    
    placementTasTonneaux();
    glPopMatrix();
}

static void selectionLight0() {
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_POSITION, light2_position);
    gluLookAt(px, py, pz, 0.0, 60.0, -90.0, 0.0, 1.0, 0.0);

}

static void selectionLight1() {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT2);
    GLfloat light1_position[] = { mario.getX(),mario.getY()-60.0,1.0,1.0 };
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiant0);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir0);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutOff0);
    gluLookAt(px, py, pz, 0.0, 60.0, -90.0, 0.0, 1.0, 0.0);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glPolygonMode(GL_FRONT_AND_BACK, (filDeFer) ? GL_FILL : GL_LINE);
    if (texture) {
        glEnable(GL_TEXTURE_2D);

    }
    else
        glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    if (!cameraFPS) {
        if (!lumiere) {
            selectionLight0();
        }
        else{
            selectionLight1();
        }
    }
    else {
        switch (mario.getOrientation()) {
            if (!lumiere) {
                selectionLight0();
            }
            else{
                selectionLight1();
            }
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
                gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), -mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
            }
            else {
                if (mario.getX() > 0) {
                    gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
                else {
                    gluLookAt(mario.getX() + mario.getTaille() / 3.0, mario.getY() + 1.5 + mario.getTaille(), -90.0 - mario.getZ(), mario.getX() + mario.getTaille() / 3.0 + 0.1, mario.getY() + mario.getTaille() + 1.5, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
                }
            }
            break;

        case Perso::Dos:
            gluLookAt(mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(), mario.getX() - mario.getTaille() / 3.0, mario.getY() + 5.0 * mario.getTaille() / 6.0, -90.0 - mario.getZ(), 0.0, 1.0, 0.0);
            break;
        }
    }
    if (lumiere == 1) {
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    }
    sceneJeu();

    glPopMatrix();
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

/********************************************************************************************/
/********************************************************************************************/
/* SCENE UTILISEE POUR LE GAMEOVER */
/********************************************************************************************/
/********************************************************************************************/
static void reshapeWGO(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutReshapeWindow(windowWidth / 2, windowHeight / 2);
    gluOrtho2D(-windowWidth / 4, windowWidth / 4, -windowHeight / 4, windowHeight / 4);
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
    for (size_t i = 0;i < textGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.27);
    for (size_t i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.23);
    for (size_t i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
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







/********************************************************************************************/
/********************************************************************************************/
/* SCENE UTILISEE POUR LA VICTOIRE */
/********************************************************************************************/
/********************************************************************************************/
static void reshapeWVictoire(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutReshapeWindow(windowWidth / 2, windowHeight / 2);
    gluOrtho2D(-windowWidth / 4, windowWidth / 4, -windowHeight / 4, windowHeight / 4);
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
    for (size_t i = 0;i < textGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.27);
    for (size_t i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glRasterPos2f(windowWidth * 0.20, windowHeight * 0.23);
    for (size_t i = 0;i < pointilleGO.length();i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pointilleGO[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
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




/********************************************************************************************/
/********************************************************************************************/
/* FONCTIONS CLAVIER ET DEPLACEMENT */
/********************************************************************************************/
/********************************************************************************************/

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
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);
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
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);
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
        else {
            mario.setY(120.0 + 1.75 * compensationPoutre);
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
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);

        }
        break;
    case 3:
        if (mario.getX() >= 55 || mario.getX() <= -45) {
            chute = true;
            sautEnCours = true;
            tomber(-20.0);
        }
        else {
            if (mario.getX() >= xDonkeyKong - 5.0) { //gameover quand mario "marche" sur donkeyKong
                gameover = true;
                return;
            }
            else {
                int indice = poutre + 2;
                mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);
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
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);
        }
        break;
    case 0: case 2:

        if (mario.getX() >= 45 || mario.getX() <= -55) {
            int indice = poutre + 1;
            sautEnCours = true;
            tomber(listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX() + compensationPoutre);

        }
        else {
            int indice = poutre + 2;
            mario.setY((listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX()) + 1.75 * compensationPoutre);
        }
        break;
    case 4:
        int indice = poutre + 1;
        if (mario.getX() >= 15) {
            sautEnCours = true;
            tomber(listePoutre[indice].getOrdoOrigine() + listePoutre[indice].getCoefDir() * mario.getX() + compensationPoutre);

        }
        else {
            mario.setY(120.0 + 1.75 * compensationPoutre);

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
    if (sautEnCours) {
        glutTimerFunc(2, sautMario, 0);
    }
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

	case 0x0D: //eclairage spot/normal en appuyant sur entrée
        lumiere = !lumiere;
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
				directionMario = 0;
				//on récupère les coordonnées des 4 coins de la zone échelle
				Coordonnee2D tempSupGauche = listeDesEchelles[index1].getCoinSupG();
				Coordonnee2D tempSupDroit = listeDesEchelles[index1].getCoinSupD();
				Coordonnee2D tempInfGauche = listeDesEchelles[index1].getCoinInfG();
				Coordonnee2D tempInfDroit = listeDesEchelles[index1].getCoinInfD();

				bool tempB = mario.getX() < tempSupDroit.getX() && mario.getX() > tempSupGauche.getX();
				bool tempB2 = mario.getY() + mario.getTaille() * 0.25 >= tempInfDroit.getY() && mario.getY() + mario.getTaille() * 0.25 <= tempSupGauche.getY();
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
			directionMario = 0;
			do {
				//on récupère les coordonnées des 4 coins de la zone échelle
				Coordonnee2D tempSupGauche = listeDesEchelles[index1].getCoinSupG();
				Coordonnee2D tempSupDroit = listeDesEchelles[index1].getCoinSupD();
				Coordonnee2D tempInfGauche = listeDesEchelles[index1].getCoinInfG();
				Coordonnee2D tempInfDroit = listeDesEchelles[index1].getCoinInfD();
				bool tempB = mario.getX() < tempSupDroit.getX() && mario.getX() > tempSupGauche.getX();
				bool tempB2 = mario.getY() - mario.getTaille() * 0.25 >= tempInfDroit.getY() && mario.getY() - mario.getTaille() * 0.25 <= tempSupDroit.getY();
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
			if (directionMario != 1 && directionAvantMario != 1) {
				changerPiedsMario = 0;
				directionMario = 1;
				directionAvantMario = 1;
			}
			changerPiedsMario++;
			if (changerPiedsMario == 10) {
				directionMario = 2;
			}
			else if (changerPiedsMario == 20){
				directionMario = 1;
				changerPiedsMario = 0;
			}
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
			if (directionMario != 2 && directionAvantMario != 2) {
				changerPiedsMario = 0;
				directionMario = 2;
				directionAvantMario = 2;
			}
			changerPiedsMario++;
			if (changerPiedsMario == 10) {
				directionMario = 1;
			}
			else if (changerPiedsMario == 20) {
				directionMario = 2;
				changerPiedsMario = 0;
			}
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




/********************************************************************************************/
/********************************************************************************************/
/* MAIN */
/********************************************************************************************/
/********************************************************************************************/

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
    glutTimerFunc(1000, animationPrincesse, 0);
    glutMainLoop();
    return(0);
}

