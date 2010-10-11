#ifndef BALLE_H
#define BALLE_H

#include "Joueur.hpp"

class Balle
{
    public:
        Balle();
        virtual ~Balle();
         int GetposX() { return b_posX; }
        void SetposX( int val) { b_posX = val; }
         int GetposY() { return b_posY; }
        void SetposY( int val) { b_posY = val; }
         int GetposZ() { return b_posZ; }
        void SetposZ( int val) { b_posZ = val; }
         double Getpoids() { return b_poids; }
        void Setpoids( double val) { b_poids = val; }
         double getVitesseX() { return b_vitesseX; }
        void setVitesseX( double val) { b_vitesseX = val; }
         double getVitesseY() { return b_vitesseY; }
        void setVitesseY( double val) { b_vitesseY = val; }
         double getVitesseZ() { return b_vitesseZ; }
        void setVitesseZ( double val) { b_vitesseZ = val; }
         int Getrayon() { return b_rayon; }
        void Setrayon( int val) { b_rayon = val; }

        void deplacement(Joueur&, Joueur&);
        void collisionBord();
        void collisionFilet();
        void collisionJoueur(Joueur&);
        double distance(int, int, int, int, int, int);

    protected:

    private:
         int b_posX;
         int b_posY;
         int b_posZ;
         double b_poids;
         int b_rayon;
         double b_vitesseX;
         double b_vitesseY;
         double b_vitesseZ;
};

#endif // BALLE_H
