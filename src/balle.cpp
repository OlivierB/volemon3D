#include "../inc/balle.hpp"

#include "math.h"
#define FORCE 6

#include <iostream>
using namespace std;

Balle::Balle()
{
    SetposX( 20);
    SetposY( -30);
    SetposZ( 25);
    Setpoids(0.2);
    setVitesseX( 0);
    setVitesseY( 0);
    setVitesseZ( 0);
    Setrayon(2);
}

Balle::~Balle()
{
    //dtor
}

void Balle::deplacement(Joueur& j1, Joueur& j2) {
    // LES COLISIONS
        // on teste d'abord les collisions l'environnement
        collisionBord();
        // collision avec les joueurs
        collisionJoueur(j1);
        collisionJoueur(j2);
        // collision avec le filet a la priorité
        collisionFilet();

    // LE MOUVEMENT
        // la gravité
        if(GetposZ() > 0 + Getrayon())
            setVitesseZ(getVitesseZ() - Getpoids());

        // calcul de l'ajout
        SetposX(round((double)GetposX() + getVitesseX()));
        SetposY(round((double)GetposY() + getVitesseY()));
        SetposZ(round((double)GetposZ() + getVitesseZ()));

}

void Balle::collisionBord() {
    if(((GetposX() < 0 + Getrayon()) && getVitesseX() < 0) || ((GetposX() > 100 - Getrayon()) && getVitesseX() > 0)) {
        setVitesseX(- getVitesseX());
    }
    if(((GetposY() < -100 + Getrayon()) && getVitesseY() < 0)  || ((GetposY() > 100 - Getrayon()) && getVitesseY() > 0)) {
        setVitesseY(- getVitesseY());
    }
    if(GetposZ() < Getrayon() && getVitesseZ() < 0) {
        if(fabs(getVitesseZ()) <= 1) {
            SetposZ(0 + Getrayon()-1);
            setVitesseZ(0);
            // arret total de la balle (frottement)
            if(getVitesseX() <= 1 && getVitesseY() <= 1 ) {
                setVitesseX(0);
                setVitesseY(0);
            }
            else {
                setVitesseX(getVitesseX()/1.5);
                setVitesseY(getVitesseY()/1.5);
            }

        }
        else {
            setVitesseZ(fabs(getVitesseZ())/1.5);
        }

    }
}

void Balle::collisionFilet() {
    int correction = 4;
    if(GetposZ() <= 20) {
        if((GetposY() < Getrayon()+correction) && (GetposY() >  - Getrayon()-correction)) {
            if(GetposY() > 0  &&  getVitesseY() < 0) {
                setVitesseY(- getVitesseY());
            }
            else if (GetposY() < 0  &&  getVitesseY() > 0) {
                setVitesseY(- getVitesseY());
            }
        }
    }
    else {
        // cas ou la balle frole le filet c a dire getposX() > 20 et < 20 + getrayon()
    }
}

void Balle::collisionJoueur(Joueur& j) {
    double distanceJB = distance(j.getPosX(), j.getPosY(), j.getPosZ(), GetposX(), GetposY(), GetposZ());
    if((double)(j.getRayon() + Getrayon()) >= distanceJB) {
        setVitesseX((GetposX() - j.getPosX()) / distanceJB * FORCE);
        setVitesseY((GetposY() - j.getPosY()) / distanceJB * FORCE);
        setVitesseZ((GetposZ() - j.getPosZ()) / distanceJB * FORCE);
    }
}

double Balle::distance(int a1 , int b1, int c1, int a2, int b2, int c2) {
    double a3 = a1 - a2;
    double b3 = b1 - b2;
    double c3 = c1 - c2;
    return sqrt( a3*a3 +  b3*b3 + c3*c3 );
}
