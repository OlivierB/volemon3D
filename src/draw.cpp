#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define PAS (M_PI/12)
#define DEBUT (M_PI/6)
#define FIN (2*M_PI - DEBUT)


// Fichier des méthodes pour dessiner les objets
#include <SFML/Window.hpp>
#include "math.h"
#include "../inc/draw.hpp"

// le plateau
void plateau() {
        glBegin(GL_QUADS);
        glColor3ub(255,0,0);
            glVertex3f(0, 100, 0);
            glVertex3f(100,  100, 0);
            glVertex3f(100,  -100, 0);
            glVertex3f(0, -100, 0);
        glEnd();
}

// le filet
void filet() {
    int decalY = 1;
        glBegin(GL_QUADS);
        glColor3ub(0,0,0);
            glVertex3f(0, -decalY, 0);
            glVertex3f(0,  -decalY, 20);
            glVertex3f(100,  -decalY, 20);
            glVertex3f(100, -decalY, 0);

            glVertex3f(0, decalY, 0);
            glVertex3f(0,  decalY, 20);
            glVertex3f(100,  decalY, 20);
            glVertex3f(100, decalY, 0);

            glVertex3f(0, -decalY, 20);
            glVertex3f(0,  decalY, 20);
            glVertex3f(100,  decalY, 20);
            glVertex3f(100, -decalY, 20);

            glVertex3f(0, -decalY, 0);
            glVertex3f(0, -decalY, 20);
            glVertex3f(0, decalY, 20);
            glVertex3f(0, decalY, 0);

            glVertex3f(100, -decalY, 0);
            glVertex3f(100, -decalY, 20);
            glVertex3f(100, decalY, 20);
            glVertex3f(100, decalY, 0);

        glEnd();
}

void demiSphere(int x, int y, int z, int r) {
    for (double a = 0; a < M_PI; a+=PAS)
    {
        double b1;
        double a1 = a + PAS;
        glBegin(GL_QUADS);
        // Intérieur de la bouche 1ere partie
        coord(a, DEBUT);
        coord(a1, DEBUT);
        glVertex3d(0, cos(a1), 50);
        glVertex3d(0, cos(a), 50);
        // Arc qui va du haut de la bouche au bas de la bouche
        for (double b = DEBUT; b < FIN; b+=PAS) {
            b1 = b + PAS;
            if (b1 > FIN) b1 = FIN;
            coord(a,b);
            coord(a1, b);
            coord(a1, b1);
            coord(a, b1);
        }
        // Intérieur de la bouche 2eme partie
        coord(a, FIN);
        coord(a1,FIN);
        glVertex3d(0, cos(a1), 50);
        glVertex3d(0, cos(a), 50);
        glEnd();
    }

}

void coord(double a, double b) {
    glVertex3d(sin(a)*cos(b), cos(a), sin(a)*sin(b) +50);
}

void sphere (int rayon, int r, int g, int b) {
    //pour que les transformations soient réversibles
    glPushMatrix();
    glColor3ub(r, g, b);
    // Declaration et initialisation
    GLUquadric* params;
    params = gluNewQuadric();
    // Definition du style
    gluQuadricDrawStyle( params, GLU_FILL);
    // Création de la sphere
    gluSphere(params, rayon, 15, 15);

    //supprime le quadrique pour libérer la memoire
    gluDeleteQuadric(params);
    //on revient a la matrice pricipale
    glPopMatrix();

}

void disque (int rayon, int r, int g, int b) {
    //pour que les transformations soient réversibles
    glPushMatrix();
    glColor3ub(r, g, b);
    // Declaration et initialisation
    GLUquadric* params;
    params = gluNewQuadric();
    // Definition du style
    gluQuadricDrawStyle( params, GLU_FILL);
    // Création de la sphere
    gluDisk(params, 0, (double)rayon - 0.2, 15, 1);

    //supprime le quadrique pour libérer la memoire
    gluDeleteQuadric(params);
    //on revient a la matrice pricipale
    glPopMatrix();
}

void dessinFennetre(int x, int y, int z, Joueur& j1, Joueur& j2, Balle& balle) {

        // Chargement de la matrice
        // initialisation de la matrice identité
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // camera
        gluLookAt(x, y, z, 50, 0, 0, 0, 0, 1);

        // les élements à dessiner
        plateau();
        filet();
    // JOUEUR 1
        //pour que les transformations soient réversibles
        glPushMatrix();
        // placement de la sphere
        glTranslated(j1.getPosX(), j1.getPosY(), j1.getPosZ());
        //cout << j1.getPosX() << endl;
        sphere(j1.getRayon(), 0, 255, 0);
        //on revient a la matrice pricipale
        glPopMatrix();
    // JOUEUR 2
        //pour que les transformations soient réversibles
        glPushMatrix();
        // placement de la sphere
        glTranslated(j2.getPosX(), j2.getPosY(), j2.getPosZ());
        //cout << j1.getPosX() << endl;
        sphere(j2.getRayon(), 0, 0, 255);
        //on revient a la matrice pricipale
        glPopMatrix();
    // LA BALLE
        //pour que les transformations soient réversibles
        glPushMatrix();
        // placement de la sphere
        glTranslated(balle.GetposX(), balle.GetposY(), balle.GetposZ());
        //cout << j1.getPosX() << endl;
        sphere(balle.Getrayon(), 255, 0, 255);
        //on revient a la matrice pricipale
        glPopMatrix();
        // OMBRE de la balle
        glPushMatrix();
        // placement de la sphere
        glTranslated(balle.GetposX(), balle.GetposY(), 1);
        //cout << j1.getPosX() << endl;
        disque(balle.Getrayon(), 0, 0, 0);
        //on revient a la matrice pricipale
        glPopMatrix();
}
