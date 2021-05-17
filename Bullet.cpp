#include "Bullet.h"

Bullet::Bullet()
{
	if (!bullet.loadFromFile("bullet1.png", sf::IntRect(0, 0, 20, 20)))
		std::cout << "error loading bullet1.png";
	createBullet();
}

void Bullet::createBullet()
{
	setTexture(bullet);
	bullet.setRepeated(false);
	bullet.setSmooth(true);

	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	origin.setX(getPosition().x);
	origin.setY(getPosition().y);
	setScale(.5, .5);
}

void Bullet::advance(float dt)
{
	float rad = getRotation() * .0174532925199;
	float x = speed * dt * sin(rad);
	float y = speed * dt * (-cos(rad));
	move(x, y);
	collider.updatePoints(getPosition().x, getPosition().y);
}