#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "pointCollider.h"
#include "Bullet.h"

namespace sf {
	class Player : public sf::Sprite
	{
	private:
		float speed = 200;
		float rotationSpeed = 100;

	public:
		bool vMove = true;
		float coolDown = -1;
		std::list<Bullet*> bullets;
		
		Texture playerImage{};
		Point p1{ 0, -25 };
		Point p2{ 25, 25 };
		Point p3{ -25, 25 };
		Point origin = Point(0, 0);
		Point *points[3] = { &p1, &p2, &p3 };

		PointCollider collider = PointCollider(&origin, points, 3);


		Player();
		Player(Texture t);
		void update();
		void createPlayer();
		void normalMove(float dt);
		void vehicleMove(float dt);

		void setMyScale(float sX, float sY);

		Bullet shoot();
		void test()
		{
				std::cout << "RE: " << &(*bullets.back()) << std::endl;
		}

	};
}
#endif // !_H_PLAYER

