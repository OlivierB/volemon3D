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

using namespace std;

int main()
{
    // Create the main window
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL");

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    // Création des joueurs
    Joueur j1 = Joueur(20, - 30, 0, 12, 100, 0, 0, -100);
    j1.setTouche(sf::Key::Up, sf::Key::Down, sf::Key::Left, sf::Key::Right, sf::Key::RControl);
    Joueur j2 = Joueur(70, 30, 0, 12, 100, 0, 100, 0);
    j2.setTouche(sf::Key::Z, sf::Key::S, sf::Key::Q, sf::Key::D, sf::Key::Space);

    // la balle
    Balle balle = Balle();

    // variable de camera
    int posX = 200;
    int posY = -40;
    int posZ = 60;

    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(255, 255, 255, 0);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)800/600, 1.f, 500.f);

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

            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }

    // traitements des actions des joueurs
        j1.mouvement(App.GetInput());
        j2.mouvement(App.GetInput());
        balle.deplacement(j1, j2);


        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Chargement de la matrice
        // initialisation de la matrice identité
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // camera
        gluLookAt(posX, posY, posZ, 50, 0, 0, 0, 0, 1);

        // les élements à dessiner
        plateau();
        filet();
    // JOUEUR 1
        //pour que les transformations soient réversibles
        glPushMatrix();
        // placement de la sphere
        glTranslated(j1.getPosX(), j1.getPosY(), j1.getPosZ());
        //cout << j1.getPosX() << endl;
        sphere(j1.getRayon(), 0, 0, 255);
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

        // Affichage
        App.Display();
        sf::Sleep(0.02f);
    }

    return EXIT_SUCCESS;
}


