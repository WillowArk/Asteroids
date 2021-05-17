#ifndef POINTCOLLIDER_H_
#define POINTCOLLIDER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
struct Point
{

public:
	float baseX, baseY;
	float currX, currY;
	float rotation; //angle from origin in radians
	float magnitude;
	Point* left = nullptr;
	Point* right = nullptr;

	Point() : baseX(0), baseY(0), currX(0), currY(0) {}
	Point(float x, float y)
	{
		baseX = x;
		currX = x;
		baseY = y;
		currY = y;
		magnitude = sqrt(pow(baseX, 2) + pow(baseY, 2));
		rotation = (atan2f(baseY, baseX));
	}


	void setX(float f) {  currX = baseX + f; }
	void setY(float f) { currY = baseY + f; }
};

class PointCollider
{
private:
	Point *origin;
	Point *pointList;
	int numP;
public:

	PointCollider(Point* org, Point* arr, int n);
	PointCollider(Point* org, Point** arr, int n);

	void updatePoints(float objX, float objY);
	void rotatePoints(float deg);

	void printPoints();
	void showPoints(sf::RenderWindow& window);
	void showPoints(sf::RenderWindow& window, Point orgn);

	Point getOrigin() { return *origin; }
	Point* closestPoint(float x, float y);

	bool withinRadius(float r, PointCollider obj);
	bool intersectsRadius(Point p1, Point p2, Point org, float r);

	bool collides(PointCollider obj);
	Point lineIntersection(Point a, Point b, Point c, Point d);
	bool validPoint(Point p, Point a, Point b);

};


#endif