#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "player.h"
#include "astroid.h"
#include "pointCollider.h"
#include "bullet.h";
#include "gameMenu.h"


const int screenWidth = 1600;
const int screenHeight = 900;
const int blockAmount = 10;
sf::Astroid *astroids[20];
float speed = 100;
sf::Clock deltaClock;
float deltaTime = 0;
float runTime = 0;
bool test = true;
int main()
{

    sf::Player playerSprite;
    playerSprite.setPosition(screenWidth / 2, screenHeight / 2);
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");


    GameMenu menu = GameMenu(window);
    bool playerDied = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear(sf::Color::Black);
        deltaTime = deltaClock.restart().asSeconds();
        runTime += deltaTime;

       if (sf::Keyboard::isKeyPressed) {
           if (playerSprite.vMove)
           {
               playerSprite.vehicleMove(deltaTime);
           }
           else
           {
               playerSprite.normalMove(deltaTime);
           }

           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
           {
               if (playerSprite.coolDown + 1 < runTime)
               {
                   playerSprite.coolDown = runTime;
                   playerSprite.shoot();
               }
           }
       }


       //astroids
       for (int i = 0; i + 1 < (runTime / 5) && i < 20; i++)
       {
           if (astroids[i] == nullptr)
           {
               astroids[i] = new sf::Astroid();
           }
           //playerCollision
           if (playerSprite.getGlobalBounds().intersects(astroids[i]->getGlobalBounds()))
           {
               playerSprite.collider.showPoints(window, astroids[i]->origin);
               astroids[i]->collider->showPoints(window, playerSprite.origin);
               if (playerSprite.collider.collides(*astroids[i]->collider))
               {
                   playerDied = true;
               }
           }
           window.draw(*astroids[i]);
           //bullets
           Bullet* remove = nullptr;
           for (Bullet* b : playerSprite.bullets)
           {
               (*b).advance(deltaTime);

               if (b->collider.withinRadius(5, *astroids[i]->collider))
               {
                   remove = b;
                   delete b;
                   delete astroids[i];
                   astroids[i] = nullptr;
               }
               else
                window.draw(*b);
           }
           playerSprite.bullets.remove(remove);
           //returns true if astroid moves outside screen
           if (astroids[i] != nullptr)
           {
               if (!(astroids[i]->advance(deltaTime)))
               {
                   delete astroids[i];
                   astroids[i] = nullptr;
               }
           }
       }
       if (playerDied)
           break;
       playerSprite.collider.showPoints(window);
       window.draw(playerSprite);
       window.display();
    }
    return 0;
}

