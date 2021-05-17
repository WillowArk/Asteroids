#include "player.h"

using namespace sf;


Player::Player()
{
	if (!playerImage.loadFromFile("ship.png", sf::IntRect(0, 0, 50, 50))) {
		std::cout << "Error: Failed to load playerImage";
	}
	createPlayer();
}

Player::Player(Texture t)
{
	playerImage = t;
	createPlayer();
}

void Player::update()
{
	if (Keyboard::isKeyPressed)
	{
		
	}
}

void Player::createPlayer()
{
	setTexture(playerImage);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height /2);
	setMyScale(.75, .75);
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
		collider.rotatePoints(-rotationSpeed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		move(movement * sin(rotated), movement * cos(rotated));
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		rotate(rotationSpeed*dt);
		collider.rotatePoints(rotationSpeed * dt);
	}
	collider.updatePoints(getPosition().x, getPosition().y);
}

//sets scale of image and points
void Player::setMyScale(float sX, float sY)
{
	setScale(sX, sY);
	p1.baseX = p1.baseX * sX;
	p1.baseY = p1.baseY * sY; 
}

//creates a new bullet from the player
Bullet Player::shoot()
{	
	bullets.push_back(new Bullet());
	bullets.back()->setPosition(getPosition());
	bullets.back()->setRotation(getRotation());
	std::cout << "Shoot: " << &(bullets.back()->origin) << std::endl;
	return *bullets.back();
}