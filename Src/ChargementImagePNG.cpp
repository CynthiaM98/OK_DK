#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#include "PNG/ChargePngFile.h"


static unsigned int textureID[1] = { 0 };

static double px = 0.0;
static double py = 60.0;
static double pz = 10.0;

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

float largeurPoutre = 8.0F;
float hauteurPoutre = 0.5F;
float longueurPoutre = 100.0F;
float compensationPoutre = 1.5 * hauteurPoutre;
float tailleMario = 10.0;
enum Orientation{ Droite, Gauche, Dos };
Orientation orientationMario=Gauche;
float xMario = 5.0;
float yMario = (-0.06 * xMario) + compensationPoutre;
float zMario = -1.0;

float initXMario = xMario;
float initYMario = yMario;
float initZMario = zMario;
Orientation initOrientationMario = orientationMario;
const int nombreEchelle = 4;

float listeDesEchelles[nombreEchelle][4][2]= { //{{x,y}coinSupGauche,{x,y}coinSupDroit,{x,y}coinInfGauche,{x,y}coinInfDroit}
    {
        {-4.0,75.0},{4.0,75.0},{-4.0,25.0},{4.0,25.0}  //echelle 1 -> 2
    },
    {
        {11.0,95.0},{19.0,95.0},{11.0,45.0},{19.0,45.0}  //echelle 0 -> 1
    },
    {
        {-21.0,55.0},{-13.0,55.0},{-21.0,5.0},{-21.0,5.0}  //echelle -1 -> 0
    },
    {
        {-31.0,35.0},{-23.0,35.0},{-31.0,-15.0},{-23.0,-15.0}  //echelle -1 -> -2
    }
};

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
    hauteur /= 2.0F;
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
    hauteur /= 2.0F;
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


    /* code a reprendre si tu veux une poutre comme dans le vrai jeu avec les triangles et tout car j'y arrive pas
    //triangle coté 1
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0F, 0.0F, -1.0F);
    glVertex3d(-4 * largeurSurDix, 4*hauteurPlateforme , -longueurPlateforme / 2.0);
    glVertex3d(-3 * largeurSurDix, 4 * hauteurPlateforme , -longueurPlateforme / 2.0);
    glVertex3d(0, 4 * hauteurPlateforme / 2.0, longueurPlateforme / 2);
    glVertex3d(-1 * largeurSurDix, 4 * hauteurPlateforme / 2.0, longueurPlateforme / 2);
    glNormal3f(0.0F, 0.0F, 1.0F);
    glVertex3d(4 * largeurSurDix, 4 * hauteurPlateforme , -longueurPlateforme / 2.0);
    glVertex3d(3 * largeurSurDix, 4 * hauteurPlateforme , -longueurPlateforme / 2.0);
    glVertex3d(0, 4 * hauteurPlateforme , longueurPlateforme / 2);
    glVertex3d(1 * largeurSurDix, 4 * hauteurPlateforme , longueurPlateforme / 2);
    glEnd();

    glPopMatrix();
    //triangle coté 2


    //triangle coté 3
    //triangle coté 4

    */
}

static void tonneau(float largeur, float longueur, unsigned int* textureID) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_tonneaux);
    float n;
    glPushMatrix();
    glTranslatef(-50.0, 84.0, -longueur /2); //face arrière
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
    glTranslatef(0.0, 0.0, longueur); //face avant
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
    gluCylinder(glNewQuad, largeur, largeur, longueur, 30.0, 30.0);
    glEnd();

    glPopMatrix();
}

static void teteMario(float size) {
    double tailleTete = size / 3.0;
    glScalef(tailleTete, tailleTete, tailleTete);
    glutSolidCube(1.0);
}


static void corpMario(float size) {
    double tailleCorp = size / 3.0;
    glutSolidCube(tailleCorp);
}

static void membreMario(float size) {
    float LargeurMembre = size / 6.0;
    float hauteurMembre = size / 3.0;
    glScalef(LargeurMembre, hauteurMembre, LargeurMembre*0.75);
    glutSolidCube(1.0);
}

static void mario(float size) {
    //TODO GERER L ORIENTATION DE MARIO SI IL EST SUR UNE POUTRE MONTANTE A GAUCHE, A DROITE OU SUR UNE ECHELLE
    switch (orientationMario) {
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
    temp = 5.0*size/6.0;
    glTranslatef(0.0F, temp, 0.0F); //niveau tête
    teteMario(size);
    glPopMatrix(); //retour origine

    glPushMatrix();
    temp = size / 2.0;
    glTranslatef(0.0F, temp, 0.0F); //niveau corp
    corpMario(size);

    glPushMatrix(); //bras droit
    temp = size/4.0;
    glTranslatef(-temp, 0.0F, 0.0F);
    membreMario(size);
    glPopMatrix(); //retour au niveau du corp

    glPushMatrix(); //bras gauche
    glTranslatef(temp, 0.0F, 0.0F);
    membreMario(size);
    glPopMatrix(); //retour au niveau du corp

    glPopMatrix(); //retour origine

    glPushMatrix();
    temp = size / 6.0;
    glTranslatef(0.0F, temp, 0.0F); //niveau jambe

    glPushMatrix(); //jambe droite
    temp = size/12.0;
    glTranslatef(-temp, 0.0F, 0.0F);
    membreMario(size);
    glPopMatrix();

    glPushMatrix();//jambe gauche
    glTranslatef(temp, 0.0F, 0.0F);
    membreMario(size);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
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
    glTranslatef(0.0, 50.0, -largeurPoutre / 2); //on recule pour que les échelles soit derrière les poutres
    echelle(50.0F, 8.0F);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15.0, 70.0, -largeurPoutre/2);
    echelle(50.0F, 8.0F);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(35.0, 70.0, -largeurPoutre / 2);
    echelleCassee(50.0F, 8.0F);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-17.0, 30.0, -largeurPoutre / 2);
    echelle(50.0F, 8.0F); 
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30.0, 10.0, -largeurPoutre / 2);
    echelleCassee(50.0F, 8.0F);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-27.0, 10.0, -largeurPoutre / 2);
    echelle(50.0F, 8.0F);
    glPopMatrix();

}


static void placementMario() {
    glPushMatrix();
    glTranslatef(xMario, yMario, zMario);
    mario(tailleMario);
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
    glTranslatef(-3.75F,3.0F,0.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    tonneau(3.0, largeurPoutre, textureID);
    glPopMatrix();
    glPushMatrix();
    placementMario();
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
          px = 0.0;
          py = 40.0;
          pz = 10.0;
          glutPostRedisplay();
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

    case 122: //faire monter Mario avec Z
        printf("MARIO HAUT\n");
        printf("X MARIO :%f\n", xMario);
        printf("Y MARIO :%f\n", yMario);
        do{
                //on récupère les coordonnées des 4 coins de la zone échelle
                float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
                float tempSupDroit[2]= { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
                float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
                float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };
                
                printf("-------------------------------------------\n");
                printf("ON CHECK SI MARIO A UN X ENTRE %f ET %f \n", tempSupGauche[0], tempSupDroit[0]);
                bool tempB=xMario<tempSupDroit[0] && xMario>tempSupGauche[0];
                printf("%s\n", tempB ? "OUI" : "NON");
                printf("ON CHECK SI MARIO A UN Y ENTRE %f ET %f \n", tempInfGauche[1], tempSupGauche[1]);
                bool tempB2 = yMario >= tempInfDroit[1] && yMario <= tempSupGauche[1];
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
            yMario += 0.5;
            index1 = 0;
            trouveHaut = false;
            orientationMario = Dos;
            glutPostRedisplay();
        }
        break;

    case 115: //faire descendre Mario avec S
        printf("MARIO BAS\n");
        printf("X MARIO :%f\n", xMario);
        printf("Y MARIO :%f\n", yMario);
        do {
            //on récupère les coordonnées des 4 coins de la zone échelle
            float tempSupGauche[2] = { listeDesEchelles[index1][0][0],listeDesEchelles[index1][0][1] };
            float tempSupDroit[2] = { listeDesEchelles[index1][1][0],listeDesEchelles[index1][1][1] };
            float tempInfGauche[2] = { listeDesEchelles[index1][2][0],listeDesEchelles[index1][2][1] };
            float tempInfDroit[2] = { listeDesEchelles[index1][3][0],listeDesEchelles[index1][3][1] };

            printf("-------------------------------------------\n");
            printf("ON CHECK SI MARIO A UN X ENTRE %f ET %f \n", tempSupGauche[0], tempSupDroit[0]);
            bool tempB = xMario<tempSupDroit[0] && xMario>tempSupGauche[0];
            printf("%s\n", tempB ? "OUI" : "NON");
            printf("ON CHECK SI MARIO A UN Y ENTRE %f ET %f \n", tempInfGauche[1], tempSupGauche[1]);
            bool tempB2 = yMario >= tempInfDroit[1] && yMario <= tempSupGauche[1];
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
            yMario -= 0.5;
            index1 = 0;
            trouveHaut = false;
            orientationMario = Dos;
            glutPostRedisplay();
        }
        break;

    case 113: //faire aller Mario à gauche avec Q ou q
       // printf("MARIO GAUCHE\n");

        if (yMario >= -2.8 + compensationPoutre && yMario <= 2.8 + compensationPoutre) { //Si Mario sur poutre -2 - OK
            if(xMario<45 && x>-55){
               // printf("X MARIO :%f\n", xMario);
                //printf("Y MARIO :%f\n", yMario);
                orientationMario = Gauche;
                xMario -= 0.5;
                yMario = (-0.06 * xMario) + compensationPoutre;
            }
        }
        else {
            if (yMario >= 16.94 + compensationPoutre && yMario <= 23.06 + compensationPoutre) { //Si Mario sur poutre -1 - OK
                if (xMario < 55 && x > -45) {
                    orientationMario = Gauche;
                    xMario -= 0.5;
                    yMario = (19.69 + 0.06 * xMario) + compensationPoutre;
                }
            }
            else {
                if (yMario >= 37.2 + compensationPoutre && yMario <= 42.8 + compensationPoutre) { //Si Mario sur poutre 0 - OK
                    if (xMario < 45 && x > -55) {
                        orientationMario = Gauche;
                        xMario -= 0.5;
                        yMario = (39.72 - 0.06 * xMario) + compensationPoutre;
                    }
                }
                else {
                    if (yMario >= 56.94 + compensationPoutre && yMario <= 63.06 + compensationPoutre) { //Si Mario sur poutre +1 - OK
                        if (xMario < 55 && x > -45) {
                            orientationMario = Gauche;
                            xMario -= 0.5;
                            yMario = (59.69 + 0.06 * xMario) + compensationPoutre;
                        }
                    }
                    else {
                        if (yMario >= 77.2 + compensationPoutre && yMario <= 82.8 + compensationPoutre) { //Si Mario sur poutre +2 - OK
                            if (xMario < 45 && x > -55) {
                                orientationMario = Gauche;
                                xMario -= 0.5;
                                yMario = (79.72 - 0.06 * xMario) + compensationPoutre;
                            }
                        }
                    }
                }
            }
        }
        glutPostRedisplay();
        break;

    case 100: //faire aller Mario à droite avec D ou d
       // printf("MARIO DROITE\n");

        if (yMario >= -2.8 + compensationPoutre && yMario <= 2.8 + compensationPoutre) { //Si Mario sur poutre -2 - OK
            if (xMario < 45 && x > -55) {
              //  printf("X MARIO :%f\n",xMario);
               // printf("Y MARIO :%f\n", yMario);
                orientationMario = Droite;
                xMario += 0.5;
                yMario = (-0.06 * xMario) + compensationPoutre;
            }
        }
        else {
            if (yMario >= 16.94 + compensationPoutre && yMario <= 23.06 + compensationPoutre) { //Si Mario sur poutre -1 - OK
                if (xMario < 55 && x > -45) {
                    orientationMario = Droite;
                    xMario += 0.5;
                    yMario = (19.69 + 0.06 * xMario) + compensationPoutre;
                }
            }
            else {
                if (yMario >= 37.2 + compensationPoutre && yMario <= 42.8 + compensationPoutre) { //Si Mario sur poutre 0 - OK
                    if (xMario < 45 && x > -55) {
                        orientationMario = Droite;
                        xMario += 0.5;
                        yMario = (39.72 - 0.06 * xMario) + compensationPoutre;
                    }
                }
                else {
                    if (yMario >= 56.94 + compensationPoutre && yMario <= 63.06+ compensationPoutre) { //Si Mario sur poutre +1 - OK
                        if (xMario < 55 && x > -45) {
                            orientationMario = Droite;
                            xMario += 0.5;
                            yMario = (59.69 + 0.06 * xMario) + compensationPoutre;
                        }
                    }
                    else {
                        if (yMario >= 77.2+ compensationPoutre && yMario <= 82.8 + compensationPoutre) { //Si Mario sur poutre +2 - OK
                            if (xMario < 45 && x > -55) {
                                orientationMario = Droite;
                                xMario += 0.5;
                                yMario = (79.72 - 0.06 * xMario) + compensationPoutre;
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

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DonkeyKong");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}

