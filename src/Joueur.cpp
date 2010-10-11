// Implémentation du joueur

// inclusion des bibliothèque

// inclusion du header
#include "../inc/Joueur.hpp"

Joueur::Joueur() {
    Joueur(0, 0, 0, 1);
}

Joueur::Joueur(int x, int y, int z, int rayon) {
    setPosX(x);
    setPosY(y);
    setPosZ(z);
    setScore(0);
    setRayon(rayon);
    setPoids(1);
    setPas(1);
    j_force = 0;
    j_monter = sf::Key::A;
    j_descendre = sf::Key::A;
    j_droite = sf::Key::A;
    j_gauche = sf::Key::A;
    j_sauter = sf::Key::A;
}

Joueur::Joueur(int x, int y, int z, int rayon, int xMax, int xMin, int yMax, int yMin) {
    setPosX(x);
    setPosY(y);
    setPosZ(z);
    setScore(0);
    setRayon(rayon);
    setPoids(1);
    setPas(2);
    j_force = 0;
    j_monter = sf::Key::A;
    j_descendre = sf::Key::A;
    j_droite = sf::Key::A;
    j_gauche = sf::Key::A;
    j_sauter = sf::Key::A;
    setXMax(xMax);
    setXMin(xMin);
    setYMax(yMax);
    setYMin(yMin);
}

Joueur::~Joueur() {
}

// Getter et Setter
void Joueur::setPosX(int x) {
    j_posX = x;
}
int Joueur::getPosX() {
    return j_posX;
}
void Joueur::setPosY(int y) {
    j_posY = y;
}
int Joueur::getPosY() {
    return j_posY;
}
void Joueur::setPosZ(int z) {
    j_posZ = z;
}
int Joueur::getPosZ() {
    return j_posZ;
}
void Joueur::setScore(int sc) {
    j_score = sc;
}
int Joueur::getScore() {
    return j_score;
}
void Joueur::setRayon(int r) {
    j_rayon = r;
}
int Joueur::getRayon() {
    return j_rayon;
}
void Joueur::setXMax(int x) {
    j_xMax = x;
}
int Joueur::getXMax(){
    return j_xMax;
}
void Joueur::setXMin(int x) {
    j_xMin = x;
}
int Joueur::getXMin(){
    return j_xMin;
}
void Joueur::setYMax(int y) {
    j_yMax = y;
}
int Joueur::getYMax(){
    return j_yMax;
}
void Joueur::setYMin(int y) {
    j_yMin = y;
}
int Joueur::getYMin(){
    return j_yMin;
}

void Joueur::setTouche(sf::Key::Code mt, sf::Key::Code dc, sf::Key::Code dt, sf::Key::Code gc, sf::Key::Code st) {
    j_monter = mt;
    j_descendre = dc;
    j_droite = gc;
    j_gauche = dt;
    j_sauter = st;
}

// Methodes de traitements
void Joueur::deplacement(int deltaX,int deltaY,int deltaZ){
    setPosX(getPosX() + deltaX);
    setPosY(getPosY() + deltaY);
    setPosZ(getPosZ() + deltaZ);
}

void Joueur::mouvement(const sf::Input& Input) {
    // la gravité et le saut
    setPosZ(getPosZ() - getPoids() + j_force);
    if(getPosZ() > 0)
        j_force -= getPoids();
    else
        j_force = 0;
    if(getPosZ() < 0)
        setPosZ(0);

    if(Input.IsKeyDown(getMonter())) {
        setPosY(getPosY() + getPas());
        if(getPosY() > (getYMax() - getRayon()))
           setPosY(getYMax() - getRayon());
    }
    if(Input.IsKeyDown(getDescendre())){
        setPosY(getPosY() - getPas());
        if(getPosY() < (getYMin() + getRayon()))
           setPosY(getYMin() + getRayon());
    }
    if(Input.IsKeyDown(getDroite())) {
        setPosX(getPosX() + getPas());
        if(getPosX() > (getXMax() - getRayon()))
            setPosX(getXMax() - getRayon());
    }
    if(Input.IsKeyDown(getGauche())) {
        setPosX(getPosX() - getPas());
        if(getPosX() < (getXMin() + getRayon()))
            setPosX(getXMin() + getRayon());
    }
    if(Input.IsKeyDown(getSauter())) {
        if(getPosZ() <= 0)
            j_force = 9;
    }

}


