#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "pointCollider.h"

namespace sf {
	class Player : public sf::Sprite
	{
	private:
		float speed = 100;
		float rotationSpeed = 100;
	public:
		float xLocation;
		float yLocation;
		float a = 10;
		float b = 5;
		bool vMove = false;

		Point p1{ -3, -25 };
		Point p2{ 25, 25 };
		Point p3{ -30, 25 };
		Point origin = Point(getOrigin().x, getOrigin().y);
		Point *points[3] = { &p1, &p2, &p3 };

		PointCollider collider = PointCollider(&origin, points, 3);


		Player() : Sprite() { //Does not work
			Texture ship;
			if (!ship.loadFromFile("ship.png", sf::IntRect(0, 0, 50, 50))) {
				std::cout << "error";
			}
			setTexture(ship);
			defaultPlayer();
		}
		Player(Texture& t) : Sprite(t) {
			defaultPlayer();
		}
		void update();
		void defaultPlayer();
		void normalMove(float dt);
		void vehicleMove(float dt);

	};
}
#endif // !_H_PLAYER

