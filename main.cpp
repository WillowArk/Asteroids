#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "player.h"
#include "astroid.h"
#include "pointCollider.h"


const int screenWidth = 1600;
const int screenHeight = 900;
const int blockAmount = 10;
sf::Astroid *astroids[20];
float speed = 100;
sf::Clock deltaClock;
float deltaTime = 0;
float runTime = 0;

int main()
{

    sf::Texture ship;
    if (!ship.loadFromFile("ship.png", sf::IntRect(0, 0, 50, 50))) {
        std::cout << "error";
    }
    ship.setRepeated(false);
    ship.setSmooth(true);
    sf::Player playerSprite(ship);
    playerSprite.setPosition(screenWidth / 2, screenHeight / 2);
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");


    sf::Astroid testAstroid;



    testAstroid.test();
    playerSprite.collider.printPoints();
    std::cout << playerSprite.collider.closestPoint(600, 600) << std::endl;
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        deltaTime = deltaClock.restart().asSeconds();
        runTime += deltaTime;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       if (sf::Keyboard::isKeyPressed) {
           if (playerSprite.vMove)
           {
               playerSprite.vehicleMove(deltaTime);
           }
           else
           {
               playerSprite.normalMove(deltaTime);
           }
       }
       window.draw(playerSprite);



       window.draw(testAstroid);

       playerSprite.collider.showPoints(window, testAstroid.origin);
       testAstroid.collider->showPoints(window, playerSprite.origin);


       //astroids
       /*for (int i = 0; i + 1 < (runTime / 5) && i < 20; i++)
       {
           if (astroids[i] == nullptr)
           {
               astroids[i] = new sf::Astroid();
           }
           window.draw(*astroids[i]);
           if (!(astroids[i]->advance(deltaTime)))
           {
               delete astroids[i];
               astroids[i] = nullptr;
           }
       }*/
       if(playerSprite.collider.collides(*(testAstroid.collider)))
           std::cout << "IT WORKS!" << std::endl;
       if (runTime > 5)
       {
           runTime -= 5;
           playerSprite.collider.printPoints();
           testAstroid.collider->printPoints();
       }
       window.display();
    }
    return 0;
}

