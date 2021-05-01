#include "astroid.h"
#include <iostream>
using namespace sf;

//spawns astroids; sets random speed, position, size, points, 
void Astroid::spawnAstroid()
{
	//TODO use less rand()
	float rRadius = rand() % 100 + 25;
	int rPoints = rand() % 15 + 4;
	int xpos = rand() % 1601;
	int ypos = rand() % 901;
	float speed = (rand() % 201 + 20);

	//std::cout << "Astroid Spawned at: " << xpos << ", " << speed << std::endl;
	setRadius(rRadius);
	setPointCount(rPoints);
	setOrigin(rRadius, rRadius);
	setOutlineColor(sf::Color::Red);
	setOutlineThickness(2);


	if (xpos <= 400) //topScreen
	{
		setPosition(xpos,0);
		float ratio = speed / sqrtf(pow((800 - xpos),2) + 202500);
		xSpeed = (800 - xpos) * ratio;
		ySpeed = 450 * ratio;
	}
	else if (xpos <= 800) // left
	{
		setPosition(0, ypos);
		float ratio = speed / sqrtf(pow((450 - ypos), 2) + 640000);
		xSpeed = 800 * ratio;
		ySpeed = (450 - ypos) * ratio;
	}
	else if (xpos <= 1200) //bottom
	{
		setPosition(xpos, 900);
		float ratio = speed / sqrtf(pow((800 - xpos), 2) + 202500);
		xSpeed = (800 - xpos) * ratio;
		ySpeed = -450 * ratio;
	}
	else //right
	{
		setPosition(1600, ypos);
		float ratio = speed / sqrtf(pow((450 - ypos), 2) + 640000);
		xSpeed = -800 * ratio;
		ySpeed = (450 - ypos) * ratio;
	}

	//sets points
	points = new Point[rPoints];
	for (int i = 0; i < rPoints; i++)
	{
		float rad = i * 6.283185 / rPoints;
		points[i].baseX = sin(rad)*rRadius;
		points[i].baseY = -cos(rad)*rRadius;
	}
	points[0].left = &points[(rPoints - 1)];
	points[0].right = &points[1];
	for (int i = 1; i < rPoints - 1; i++)
	{
		points[i].left = &points[i-1];
		points[i].right = &points[i+1];
	}
	points[(rPoints-1)].left = &points[(rPoints - 2)];
	points[(rPoints-1)].right = &points[0];
	collider = new PointCollider(&origin, points, rPoints);
	std::cout << "Spawned Astroid" << std::endl;
}

//advances astroid by its speed*deltaTime; return false if it moves out of screen
bool Astroid::advance(float dt)
{
	move(xSpeed * dt, ySpeed * dt);
	collider->updatePoints(getPosition().x, getPosition().y);
	if (getPosition().x > 1600 || getPosition().x < 0 || getPosition().y < 0 || getPosition().y > 900)
		return false;
	return true;
}

