#include "player.h"

using namespace sf;

void Player::update()
{
	if (Keyboard::isKeyPressed)
	{
		
	}
}

void Player::defaultPlayer()
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height /2);
	p1.left = &p2;
	p1.right = &p3;
	p2.left = &p3;
	p2.right = &p1;
	p3.left = &p1;
	p3.right = &p2;
	collider.updatePoints(getPosition().x, getPosition().y);
}

void Player::normalMove(float dt)
{
	float movement = speed * dt;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		move(0, -movement);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		move(-movement, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		move(0, movement);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		move(movement, 0);
	}
	collider.updatePoints(getPosition().x, getPosition().y);
}
void Player::vehicleMove(float dt)
{
	float rotated = getRotation() * .0174532;
	float movement = dt * speed;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		move(movement * sin(rotated), -movement * cos(rotated));
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		rotate(-rotationSpeed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		move(movement * sin(rotated), movement * cos(rotated));
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		rotate(rotationSpeed*dt);
	}
}
