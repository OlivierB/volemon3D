#ifndef JOUEURINFO
#define JOUEURINFO

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Joueur {
    // ---------------------
    // METHODES
    // ---------------------
    public:
    // Constructeurs / destructeur
        Joueur(int, int, int, int);
        Joueur(int, int, int, int, int, int, int, int);
        Joueur();
        ~Joueur();

    // Getter et Setter
        void setPosX(int);
        void setPosY(int);
        void setPosZ(int);
        void setScore(int);
        void setRayon(int);
        void setXMax(int);
        void setXMin(int);
        void setYMax(int);
        void setYMin(int);
         int getPoids() { return j_poids; }
        void setPoids(int val) { j_poids = val; }
         int getPas() { return j_pas; }
        void setPas(int val) { j_pas = val; }

        int getPosX();
        int getPosY();
        int getPosZ();
        int getScore();
        int getRayon();
        int getXMax();
        int getXMin();
        int getYMax();
        int getYMin();
        int getForce() { return j_force; };
        sf::Key::Code getMonter() { return j_monter; }
        sf::Key::Code getDescendre() { return j_descendre; }
        sf::Key::Code getDroite() { return j_droite; }
        sf::Key::Code getGauche() { return j_gauche; }
        sf::Key::Code getSauter() { return j_sauter; }

    // autres methodes
        void setTouche(sf::Key::Code, sf::Key::Code, sf::Key::Code, sf::Key::Code, sf::Key::Code);
        void deplacement(int,int,int);
        void mouvement(const sf::Input& Input);

    // ---------------------
    // ATTRIBUTS
    // ---------------------
    private:
        int j_posX;
        int j_posY;
        int j_posZ;
        int j_score;
        int j_rayon;
        int j_xMax;
        int j_xMin;
        int j_yMax;
        int j_yMin;
        int j_poids;
        int j_pas;
        sf::Key::Code j_monter;
        sf::Key::Code j_descendre;
        sf::Key::Code j_droite;
        sf::Key::Code j_gauche;
        sf::Key::Code j_sauter;
        int j_force;
};

#endif // CONSTANTS_HPP_INCLUDED
