// STL
#include <iostream>
#include <string>

// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Perso
#include "inc/Joueur.hpp"
#include "inc/draw.hpp"
#include "inc/balle.hpp"

#define LARGEUR 1300
#define HAUTEUR 600

using namespace std;

// prototype
void init (Joueur&, Joueur&, Balle&);

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(LARGEUR, HAUTEUR, 32), "SFML OpenGL");

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    // Création des joueurs
    Joueur j1 = Joueur(20, - 30, 0, 15, 100, 0, 0, -100);
    j1.setTouche(sf::Key::Z, sf::Key::S, sf::Key::Q, sf::Key::D, sf::Key::Space);
    Joueur j2 = Joueur(70, 30, 0, 15, 100, 0, 100, 0);
    j2.setTouche(sf::Key::Down, sf::Key::Up, sf::Key::Right, sf::Key::Left, sf::Key::RControl);

    // la balle
    Balle balle = Balle();

    // variable de camera
    int posX = 90;
    int posY = -140;
    int posZ = 80;

    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(255, 255, 255, 0);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // decoupage ecran
    glEnable(GL_SCISSOR_TEST);


    // Start game loop
    while (App.IsOpened())
    {
        // Declaration des variables pour les touches du clavier
        const sf::Input& Input = App.GetInput();
        // Reglage de la camera
        if(Input.IsKeyDown(sf::Key::Numpad7))
            posX++;
        if(Input.IsKeyDown(sf::Key::Numpad4))
            posX--;
        if(Input.IsKeyDown(sf::Key::Numpad8))
            posY++;
        if(Input.IsKeyDown(sf::Key::Numpad5))
            posY--;
        if(Input.IsKeyDown(sf::Key::Numpad9))
            posZ++;
        if(Input.IsKeyDown(sf::Key::Numpad6))
            posZ--;

        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();
            // reinitialisation
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return)) {
                init (j1, j2, balle);
            }

            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }


    // traitements des actions des joueurs
        j1.mouvement(App.GetInput());
        j2.mouvement(App.GetInput());
        balle.deplacement(j1, j2);


        // Clear color and depth buffer réinitialisation du scissor
        glDisable (GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable (GL_SCISSOR_TEST);



    // JOUEUR 1
    glScissor(0,0,LARGEUR/2, HAUTEUR);
    glViewport(0,0,LARGEUR/2, HAUTEUR);
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, (double)(LARGEUR/HAUTEUR/2), 1.f, 500.f);

        // dessin
        dessinFennetre(100, -150, 80, j1, j2, balle);


    // JOUEUR 2
    glScissor(LARGEUR/2,0,LARGEUR, HAUTEUR);
    glViewport(LARGEUR/2,0,LARGEUR/2, HAUTEUR);
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70, (double)(LARGEUR/HAUTEUR/2), 1.f, 500.f);

        // dessin
        dessinFennetre(25, 150, 80, j1, j2, balle);


sf::Shape Rect   = sf::Shape::Rectangle(LARGEUR/2 - 5, 0, LARGEUR/2 + 5, HAUTEUR, sf::Color(0,0,0));

        // Affichage
        App.Draw(Rect);
        App.Display();
        sf::Sleep(0.025f);
    }

    return EXIT_SUCCESS;
}

void init (Joueur& j1, Joueur& j2, Balle& balle) {
    j1.setPosX(70);
    j1.setPosY(-70);
    j1.setPosZ(0);

    j2.setPosX(30);
    j2.setPosY(70);
    j2.setPosZ(0);
    // la balle
    balle.SetposX(70);
    balle.SetposY(-70);
    balle.SetposZ(30);
    balle.setVitesseX(0);
    balle.setVitesseY(0);
    balle.setVitesseZ(0);
}
