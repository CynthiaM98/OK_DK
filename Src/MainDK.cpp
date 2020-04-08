#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "PNG/ChargePngFile.h"
#include "PNG/Perso.h"



static unsigned int textureID[1] = { 0 };


static double px = 0.0;
static double py = 60.0;
static double pz = 10.0;

static double initCamX = px;
static double initCamY = py;
static double initCamZ = pz;

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
const int nombrePoutre = 7;

//MARIO
float initXMario = 5.0;
float initYMario = (-0.06 * initXMario) + compensationPoutre;
float initZMario = -1.0;
float longueurPas = 0.5F;

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
float xTonneauBegin = -45.0;
float yTonneauBegin = 82.0+ 2 *compensationPoutre;
float zTonneauBegin = -largeurPoutre/2;
int nbTonneau = 0;
float tabTonneau[100][100];

bool gameover = false;

//FCT ECHELLES

float listeDesEchelles[nombreEchelle][4][2] = { //{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}
    
    
    {
        {1.0 - demieLargeurEchelle,110.0 + demieHauteurEchelle},
        {1.0 + demieLargeurEchelle,110.0 + demieHauteurEchelle},
        {1.0 - demieLargeurEchelle,110.0 - demieHauteurEchelle},
        {1.0 + demieLargeurEchelle,110.0 - demieHauteurEchelle}  //echelle 3 -> -4
    },
    {  
        {-25.0 - demieLargeurEchelle,90.0 + demieHauteurEchelle},
        {-25.0 + demieLargeurEchelle,90.0 + demieHauteurEchelle},
        {-25.0 - demieLargeurEchelle,90.0 - demieHauteurEchelle},
        {-25.0 + demieLargeurEchelle,90.0 - demieHauteurEchelle}  //echelle 2 -> 3
    },
    {
        {15.0 - demieLargeurEchelle,70.0 + demieHauteurEchelle},
        {15.0 + demieLargeurEchelle,70.0 + demieHauteurEchelle},
        {15.0 - demieLargeurEchelle,70.0 - demieHauteurEchelle},
        {15.0 + demieLargeurEchelle,70.0 - demieHauteurEchelle}  //echelle 1 -> 2
    },
    {
        {-28.0 - demieLargeurEchelle,50.0 + demieHauteurEchelle},
        {-28.0 + demieLargeurEchelle,50.0 + demieHauteurEchelle},
        {-28.0 - demieLargeurEchelle,50.0 - demieHauteurEchelle},
        {-28.0 + demieLargeurEchelle,50.0 - demieHauteurEchelle}  //echelle 0 -> 1
    },
    {
        {10.0 - demieLargeurEchelle,30.0 + demieHauteurEchelle},
        {10.0 + demieLargeurEchelle,30.0 + demieHauteurEchelle},
        {10.0 - demieLargeurEchelle,30.0 - demieHauteurEchelle},
        {10.0 + demieLargeurEchelle,30.0 - demieHauteurEchelle}  //echelle -1 -> 0
    },
    {
        {-27.0 - demieLargeurEchelle,10.0 + demieHauteurEchelle},
        {-27.0 + demieLargeurEchelle,10.0 + demieHauteurEchelle},
        {-27.0 - demieLargeurEchelle,10.0 - demieHauteurEchelle},
        {-27.0 + demieLargeurEchelle,10.0 - demieHauteurEchelle}  //echelle -2 -> -1
    }
};


float listeDesEchellesCassees[nombreEchelleCassee][4][2] = { //{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}
  
   
    {
        {10.0 - demieLargeurEchelle,90.0 + demieHauteurEchelle},
        {10.0 + demieLargeurEchelle,90.0 + demieHauteurEchelle},
        {10.0 - demieLargeurEchelle,90.0 - demieHauteurEchelle},
        {10.0 + demieLargeurEchelle,90.0 - demieHauteurEchelle}  //echelle cassee 2 -> 3
    },
    {
        {35.0 - demieLargeurEchelle,70.0 + demieHauteurEchelle},
        {35.0 + demieLargeurEchelle,70.0 + demieHauteurEchelle},
        {35.0 - demieLargeurEchelle,70.0 - demieHauteurEchelle},
        {35.0 + demieLargeurEchelle,70.0 - demieHauteurEchelle}  //echelle cassee 1 -> 2
    },
    {
        {0.0 - demieLargeurEchelle,50.0 + demieHauteurEchelle},
        {0.0 + demieLargeurEchelle,50.0 + demieHauteurEchelle},
        {0.0 - demieLargeurEchelle,50.0 - demieHauteurEchelle},
        {0.0 + demieLargeurEchelle,50.0 - demieHauteurEchelle}  //echelle cassee 0 -> 1 
    },
    {
        {-17.0 - demieLargeurEchelle,30.0 + demieHauteurEchelle},
        {-17.0 + demieLargeurEchelle,30.0 + demieHauteurEchelle},
        {-17.0 - demieLargeurEchelle,30.0 - demieHauteurEchelle},
        {-17.0 + demieLargeurEchelle,30.0 - demieHauteurEchelle}//echelle cassee -1 -> -0 
    },
    {
        {30.0 - demieLargeurEchelle,10.0 + demieHauteurEchelle},
        {30.0 + demieLargeurEchelle,10.0 + demieHauteurEchelle},
        {30.0 - demieLargeurEchelle,10.0 - demieHauteurEchelle},
        {30.0 + demieLargeurEchelle,10.0 - demieHauteurEchelle}  //echelle cassee -2 -> -1
    }

};

//FCT POUTRES
float listePoutre[nombrePoutre][6] = { //{numeroPoutre,yCentre,xGauche,xDroit,ordoOrigine,coefDir}
    {-2,0,-55,45,0,-0.06},
    {-1,20,-45,55,19.69,0.06},
    {0,40,-55,45,39.72,-0.06},
    {1,60,-45,55,59.69,0.06},
    {2,80,-55,45,79.72,-0.06},
    {3,100,-45,55,99.69,0.06},
    {4,120,-35,15,120.0,0.0}
};



//TEXTURES
GLfloat no_mat[] = { 0.0F,0.0F,0.0F,1.0F };
GLfloat mat_ambient[] = { 0.7F,0.7F,0.7F,1.0F };
GLfloat mat_ambient_color[] = { 0.8F,0.8F,0.2F,1.0F };

GLfloat mat_specular[] = { 1.0F,1.0F,1.0F,1.0F };
GLfloat no_shininess[] = { 0.0F };
GLfloat low_shininess[] = { 5.0F };
GLfloat high_shininess[] = { 100.0F };
GLfloat mat_emission[] = { 0.3F,0.2F,0.2F,0.0F };
GLfloat couleur_poutres[] = { 2.50,2.4,1.45F,1.0F };
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
		
        /*unsigned char *img = chargeImagePng(filename, &rx, &ry);
        if (img) {
            glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            free(img);
            printf("Texture chargée %d : %s\n", textureID, filename);
        }
        else {
            printf("Texture non charge\n");
        }*/
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
    chargementTexture("Wood.jpg", textureID[0]);
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
            glTranslatef(-3*x / 2, -i * (-x + (hauteur / 4)), 0.0);
            glScalef(2 * (largeur - 1.5*x), 1.0F, 1.0F);
            glutSolidCube(x);
            glPopMatrix();
        
    }

}

static void planchePoutre(float largeur, float longueur, float hauteur) {
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

static void poutreDK(float largeurPlateforme, float longueurPlateforme, float hauteurPlateforme) {
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

static void tonneau(float xTonneau, float yTonneau, float zTonneau) {
	float largeur = 3.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_tonneaux);
    float n;
    glPushMatrix();
    glTranslatef(xTonneau, yTonneau, zTonneau); //face arrière
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glPushMatrix();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        n = i * 3.14 / 180;
        glVertex2f(largeur * cos(n), largeur * sin(n));
    }
    glEnd();
    glPopMatrix();
    glTranslatef(0.0, 0.0, largeurPoutre); //face avant
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        n = i * 3.14 / 180;
        glVertex2f(largeur * cos(n), largeur * sin(n));
    }
    glEnd();
    glPopMatrix();
    glBegin(GL_POLYGON);
    GLUquadric* glNewQuad = gluNewQuadric();
    gluCylinder(glNewQuad, largeur, largeur, largeurPoutre, 30.0, 30.0);
    glEnd();

    glPopMatrix();
	tabTonneau[nbTonneau][0] = xTonneau;
	tabTonneau[nbTonneau][1] = yTonneau;
}




static void donkeyKong(float size) {
    //mario(size,false);
}

static void placementPoutres() {
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_poutres);
    glPushMatrix(); //poutre victoire
    glTranslatef(-10.0, 6 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre/2, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre etage +3
    glTranslatef(5.0, 5 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef (-3.5, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre etage +2
    glTranslatef(-5.0, 4 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(3.2, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre etage +1
    glTranslatef(5.0, 3 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(-3.5, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre centrale
    glTranslatef(-5.0, 2 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef( 3.2, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre etage -1
    glTranslatef(5.0, 1 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(-3.5, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPushMatrix(); //poutre etage -2
    glTranslatef(-5.0, 0 * 20.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(3.2, 1.0, 0.0, 0.0);
    poutreDK(largeurPoutre, longueurPoutre, hauteurPoutre);
    glPopMatrix();

    glPopMatrix();

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
    glTranslatef(15.0, 70.0, -largeurPoutre/2);
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
    mario.printPerso();
    glPopMatrix();
}


static void placementPrincesse() {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur_princesse); // TODO : REMPLACER LE MATERIAU PAR UNE TEXTURE
    glPushMatrix();
    glTranslatef(princess.getX(), princess.getY(), princess.getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    princess.printPerso();
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
    glTranslatef(-3.75F,3.0F,0.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    glPopMatrix();
    glPushMatrix();
    placementMario();
    placementPrincesse();
	for (int i = 0; i < nbTonneau; ++i) {
		tonneau(tabTonneau[i][0], tabTonneau[i][1], zTonneauBegin);
	}
    //placementDK();
    glPopMatrix();
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
    sceneJeu();
    
    glPopMatrix();
    glPopAttrib();
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
        gluPerspective(80,ratio, 10.0, 2000.0);
    else
        gluPerspective(80 / ratio, ratio, 10.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
  static void special(int key, int x, int y) {
      printf("K  x=%d y=%d z=%d\n", px, py, pz);
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


  static void gaucheMario(float ordoOrigine, float coefDir, int poutre) {

      mario.setOrientation(Perso::Orientation::Gauche);
      mario.setX(mario.getX() - longueurPas);
      switch (poutre) {
      case -2: case 0: case 2:
          if (mario.getX() >= 45 || mario.getX() <= -55) {
              mario.setY(-20.0);
              gameover = true;
          }
          else {
              mario.setY((ordoOrigine + coefDir * mario.getX()) + compensationPoutre);
          }
          break;
      case -1: case 1: case 3:
          if (mario.getX() >= 55 || mario.getX() <= -45) {
              int indice = poutre + 1;
              mario.setX(-45.0);
              mario.setY((listePoutre[indice][4] + listePoutre[indice][5] * mario.getX()) + compensationPoutre);
          }
          else {
              mario.setY((ordoOrigine + coefDir * mario.getX()) + compensationPoutre);
          }
          break;
      case 4:
          break;
      default:
          break;
      }
  }


  static void droiteMario(float ordoOrigine, float coefDir, int poutre) {
      mario.setOrientation(Perso::Orientation::Droite);
      mario.setX(mario.getX() + longueurPas);
      switch (poutre) {
      case -1: case 1: case 3:
          if (mario.getX() >= 55 || mario.getX() <= -45) {
              mario.setY(-20.0);
              gameover = true;
          }
          else {
              mario.setY((ordoOrigine + coefDir * mario.getX()) + compensationPoutre);
          }
          break;
      case -2:
          if (mario.getX() >= 45 || mario.getX() <= -55) {
              mario.setY(-20.0);
              gameover = true;
          }
          else {
              mario.setY((ordoOrigine + coefDir * mario.getX()) + compensationPoutre);
          }
          break;
      case 0: case 2:

          if (mario.getX() >= 45 || mario.getX() <= -55) {
              int indice = poutre + 1;
              mario.setX(45.0);
              mario.setY((listePoutre[indice][4] + listePoutre[indice][5] * mario.getX()) + compensationPoutre);
          }
          else {
              mario.setY((ordoOrigine + coefDir * mario.getX()) + compensationPoutre);
          }
          break;
      case 4:
          break;
      default:
          break;
      }
  }

  static void keyboard(unsigned char key, int x, int y) {
      int index1 = 0;
      bool trouveHaut = false;
      int index2 = 0;
      bool trouveBas = false;

      printf(" Touche: %c = %d \n", key, key);
      switch (key) {

      case 0x20: //mode fil de fer en appuyant sur la barre espace
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

      case 122: case 90://faire monter Mario avec Z ou z
          printf("MARIO HAUT\n");
          printf("X MARIO :%f\n", mario.getX());
          printf("Y MARIO :%f\n", mario.getY());
          do {
              //on récupère les coordonnées des 4 coins de la zone échelle
              float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
              float tempSupDroit[2] = { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
              float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
              float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };

              printf("-------------------------------------------\n");
              printf("ON CHECK SI MARIO A UN X ENTRE %f ET %f \n", tempSupGauche[0], tempSupDroit[0]);
              bool tempB = mario.getX() < tempSupDroit[0] && mario.getX() > tempSupGauche[0];
              printf("%s\n", tempB ? "OUI" : "NON");
              printf("ON CHECK SI MARIO A UN Y ENTRE %f ET %f \n", tempInfGauche[1], tempSupGauche[1]);
              bool tempB2 = mario.getY() + mario.getTaille() * 0.25 >= tempInfDroit[1] && mario.getY() + mario.getTaille() * 0.25 <= tempSupGauche[1];
              printf("%s\n", tempB2 ? "OUI" : "NON");
              printf("-------------------------------------------\n");
              //on check si Mario est dans cette zone
              if (tempB && tempB2) {
                  printf("OUI\n");
                  trouveHaut = true;
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
          break;

      case 115: case 83://faire descendre Mario avec S ou s
          printf("MARIO BAS\n");
          printf("X MARIO :%f\n", mario.getX());
          printf("Y MARIO :%f\n", mario.getY());
          do {
              //on récupère les coordonnées des 4 coins de la zone échelle
              float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
              float tempSupDroit[2] = { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
              float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
              float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };

              printf("-------------------------------------------\n");
              printf("ON CHECK SI MARIO A UN X ENTRE %f ET %f \n", tempSupGauche[0], tempSupDroit[0]);
              bool tempB = mario.getX() < tempSupDroit[0] && mario.getX() > tempSupGauche[0];
              printf("%s\n", tempB ? "OUI" : "NON");
              printf("ON CHECK SI MARIO A UN Y ENTRE %f ET %f \n", tempInfGauche[1], tempSupGauche[1]);
              bool tempB2 = mario.getY() + mario.getTaille() * 0.25 >= tempInfDroit[1] && mario.getY() + mario.getTaille() * 0.25 <= tempSupGauche[1];
              printf("%s\n", tempB2 ? "OUI" : "NON");
              printf("-------------------------------------------\n");
              //on check si Mario est dans cette zone
              if (tempB && tempB2) {
                  printf("OUI\n");
                  trouveHaut = true;
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
          break;

      case 113: case 81: //faire aller Mario à gauche avec Q ou q
         // printf("MARIO GAUCHE\n");

          if (mario.getY() >= -2.8 + compensationPoutre && mario.getY() <= 5.0 + compensationPoutre) { //Si Mario sur poutre -2 - OK
              if (mario.getX() < 45 && mario.getX() > -55) {
                  printf("X MARIO :%f\n", mario.getX());
                  printf("Y MARIO :%f\n", mario.getY());
                  gaucheMario(0, -0.06, -2);
              }
          }
          else {
              if (mario.getY() >= 16.94 + compensationPoutre && mario.getY() <= 26.0 + compensationPoutre) { //Si Mario sur poutre -1 - OK
                  if (mario.getX() < 55 && mario.getX() > -45) {
                      gaucheMario(19.69, 0.06, -1);
                  }
              }
              else {
                  if (mario.getY() >= 37.2 + compensationPoutre && mario.getY() <= 45.0 + compensationPoutre) { //Si Mario sur poutre 0 - OK
                      if (mario.getX() < 45 && mario.getX() > -55) {
                          gaucheMario(39.72, -0.06, 0);

                      }
                  }
                  else {
                      if (mario.getY() >= 56.94 + compensationPoutre && mario.getY() <= 66.0 + compensationPoutre) { //Si Mario sur poutre +1 - OK
                          if (mario.getX() < 55 && mario.getX() > -45) {
                              gaucheMario(59.69, 0.06, 1);


                          }
                      }
                      else {
                          if (mario.getY() >= 77.2 + compensationPoutre && mario.getY() <= 85.0 + compensationPoutre) { //Si Mario sur poutre +2 - OK
                              if (mario.getX() < 45 && mario.getX() > -55) {
                                  gaucheMario(79.72, -0.06, 2);

                              }
                          }
                          else {
                              if (mario.getY() >= 96.94 + compensationPoutre && mario.getY() <= 103.6 + compensationPoutre) { //Si Mario sur poutre +3 - OK
                                  if (mario.getX() < 55 && mario.getX() > -45) {
                                      gaucheMario(99.69, 0.06, 3);

                                  }
                              }
                              else {
                                  if (mario.getY() >= 120.0 + compensationPoutre && mario.getY() <= 122.0 + compensationPoutre) { //Si Mario sur poutre victoire - OK
                                      if (mario.getX() < 15 && mario.getX() > -35) {
                                          gaucheMario(120.0, 1.00, 4);

                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
          glutPostRedisplay();
          break;

      case 100: case 68: //faire aller Mario à droite avec D ou d
         // printf("MARIO DROITE\n");

          if (mario.getY() >= -2.8 + compensationPoutre && mario.getY() <= 5.0 + compensationPoutre) { //Si Mario sur poutre -2 - OK
              if (mario.getX() < 45 && mario.getX() > -55) {
                  printf("X MARIO :%f\n", mario.getX());
                  printf("Y MARIO :%f\n", mario.getY());
                  droiteMario(0.0, -0.06, -2);
              }
          }
          else {
              if (mario.getY() >= 16.94 + compensationPoutre && mario.getY() <= 26.0 + compensationPoutre) { //Si Mario sur poutre -1 - OK
                  if (mario.getX() < 55 && mario.getX() > -45) {
                      droiteMario(19.69, 0.06, -1);
                  }
              }
              else {
                  if (mario.getY() >= 35.0 + compensationPoutre && mario.getY() <= 45.0 + compensationPoutre) { //Si Mario sur poutre 0 - OK
                      if (mario.getX() <= 45 && mario.getX() > -55) {
                          droiteMario(39.72, -0.06, 0);

                      }
                  }
                  else {
                      if (mario.getY() >= 54.0 + compensationPoutre && mario.getY() <= 66.0 + compensationPoutre) { //Si Mario sur poutre +1 - OK
                          if (mario.getX() < 55 && mario.getX() > -45) {
                              droiteMario(59.69, 0.06, 1);

                          }
                      }
                      else {
                          if (mario.getY() >= 75.0 + compensationPoutre && mario.getY() <= 85.0 + compensationPoutre) { //Si Mario sur poutre +2 - OK
                              if (mario.getX() < 45 && mario.getX() > -55) {
                                  droiteMario(79.72, -0.06, 2);

                              }
                          }
                          else {
                              if (mario.getY() >= 94.0 + compensationPoutre && mario.getY() <= 106.0 + compensationPoutre) { //Si Mario sur poutre +3 - OK
                                  if (mario.getX() < 55 && mario.getX() > -45) {
                                      droiteMario(99.69, 0.06, 3);

                                  }
                              }
                              else {
                                  if (mario.getY() >= 120.0 + compensationPoutre && mario.getY() <= 125.0 + compensationPoutre) { //Si Mario sur poutre victoire - OK
                                      if (mario.getX() < 15 && mario.getX() > -35) {
                                          droiteMario(120, 0.00, 4);

                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
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

static void mouvementTonneau(float ordoOrigine, float coefDir, float distance, int i) {
	tabTonneau[i][0] += distance;
	tabTonneau[i][1] = (ordoOrigine + coefDir * tabTonneau[i][0]) + 2*compensationPoutre;
}

void updateTonneau(int value) {
	for (int i = 0; i < nbTonneau; ++i) {
		//printf("X Tonneau debut :%f\n", xTonneau);
		//printf("Y Tonneau debut :%f\n", yTonneau);
		if (tabTonneau[i][1] >= -2.8 + 2 * compensationPoutre && tabTonneau[i][1] <= 2.8 + 2 * compensationPoutre) { //Si Mario sur poutre -2 - OK
			printf("Oui1");
			if (tabTonneau[i][0] - longueurPas < 45 && tabTonneau[i][0] + longueurPas>-55) {
				printf("X Tonneau :%f\n", tabTonneau[i][0]);
				printf("Y Tonneau :%f\n", tabTonneau[i][1]);
				mouvementTonneau(0, -0.06, longueurPas,i);
			}
		}
		else {
			if (tabTonneau[i][1] >= 16.94 + 2 * compensationPoutre && tabTonneau[i][1] <= 23.0 + 2 * compensationPoutre) { //Si Mario sur poutre -1 - OK
				printf("Oui2");
				if (tabTonneau[i][0] - longueurPas < 56 && tabTonneau[i][0] + longueurPas> -45) {
					printf("X Tonneau :%f\n", tabTonneau[i][0]);
					printf("Y Tonneau :%f\n", tabTonneau[i][1]);
					mouvementTonneau(19.69, 0.06, -longueurPas, i);
				}
			}
			else {
				if (tabTonneau[i][1] >= 35.2 + 2 * compensationPoutre && tabTonneau[i][1] <= 42.8 + 2 * compensationPoutre) { //Si Mario sur poutre 0 - OK
					printf("Oui3");
					printf("Y Tonneau :%f\n", tabTonneau[i][1]);
					if (tabTonneau[i][0] - longueurPas < 55 && tabTonneau[i][0] + longueurPas > -55) {
						printf("X Tonneau :%f\n", tabTonneau[i][0]);
						printf("Y Tonneau :%f\n", tabTonneau[i][1]);
						mouvementTonneau(39.72, -0.06, longueurPas, i);
					}
				}
				else {
					if (tabTonneau[i][1] >= 55 + 2 * compensationPoutre && tabTonneau[i][1] <= 63.06 + 2 * compensationPoutre) { //Si Mario sur poutre +1 - OK
						printf("Oui4");
						if (tabTonneau[i][0] - longueurPas < 56 && tabTonneau[i][0] + longueurPas > -50) {
							printf("X Tonneau :%f\n", tabTonneau[i][0]);
							printf("Y Tonneau :%f\n", tabTonneau[i][1]);
							mouvementTonneau(59.69, 0.06, -longueurPas, i);
						}
					}
					else {
						if (tabTonneau[i][1] >= 75 + 2 * compensationPoutre && tabTonneau[i][1] <= 82.8 + 2 * compensationPoutre) { //Si Mario sur poutre +2 - OK
							printf("Oui5");
							if (tabTonneau[i][0] - longueurPas < 55 && tabTonneau[i][0] + longueurPas > -55) {
								printf("X Tonneau :%f\n", tabTonneau[i][0]);
								printf("Y Tonneau :%f\n", tabTonneau[i][1]);
								mouvementTonneau(79.72, -0.06, longueurPas, i);
							}
						}
						else {
							if (tabTonneau[i][1] >= 96.94 + 2 * compensationPoutre && tabTonneau[i][1] <= 103.6 + 2 * compensationPoutre) { //Si Mario sur poutre +3 - OK
								printf("Oui6");
								if (tabTonneau[i][0] - longueurPas < 55 && tabTonneau[i][0] + longueurPas > -45) {
									printf("X Tonneau :%f\n", tabTonneau[i][0]);
									printf("Y Tonneau :%f\n", tabTonneau[i][1]);
									mouvementTonneau(99.69, 0.06, -longueurPas, i);
								}
							}
							else {
								if (tabTonneau[i][1] >= 120.0 + 2 * compensationPoutre && tabTonneau[i][1] <= 122.0 + 2 * compensationPoutre) { //Si Mario sur poutre victoire - OK
									if (tabTonneau[i][0] - longueurPas < 15 && tabTonneau[i][0] + longueurPas > -35) {
										printf("X Tonneau :%f\n", tabTonneau[i][0]);
										printf("Y Tonneau :%f\n", tabTonneau[i][1]);
									}
								}
							}
						}
					}
				}
			}
		}

		//Deplacement vertical
		if (tabTonneau[i][1] <= 77.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 63.06 + 2 * compensationPoutre) {
			tabTonneau[i][1] -= longueurPas;
		}
		else if (tabTonneau[i][1] <= 58.20 + 2 * compensationPoutre && tabTonneau[i][1] >= 43.0 + 2 * compensationPoutre) {
			tabTonneau[i][1] -= longueurPas;
		}
		else if (tabTonneau[i][1] <= 37.9 + 2 * compensationPoutre && tabTonneau[i][1] >= 23.0 + 2 * compensationPoutre) {
			tabTonneau[i][1] -= longueurPas;
		}
		else if (tabTonneau[i][1] <= 17.0 + 2 * compensationPoutre && tabTonneau[i][1] >= 2.7 + 2 * compensationPoutre) {
			tabTonneau[i][1] -= longueurPas;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(25,updateTonneau, 0);
}

static void ajoutTonneau(int value) {
	tonneau(xTonneauBegin, yTonneauBegin, zTonneauBegin);
	nbTonneau++;
	glutTimerFunc(5000, ajoutTonneau, 0);
}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DonkeyKong");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
	glutTimerFunc(5, ajoutTonneau, 0);
	glutTimerFunc(100, updateTonneau, 0);
	
    glutMainLoop();
    return(0);
}

