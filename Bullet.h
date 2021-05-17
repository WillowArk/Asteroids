#pragma once
#include <SFML/Graphics.hpp>
#include "pointCollider.h";
class Bullet : public sf::Sprite
{
	sf::Texture bullet;
	float speed = 200;

public:
	Point origin = Point(0, 0);
	PointCollider collider = PointCollider(&origin, &origin, 1);

	Bullet();

	void createBullet();
	void advance(float dt);
};

