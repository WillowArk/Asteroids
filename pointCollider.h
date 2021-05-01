#ifndef POINTCOLLIDER_H_
#define POINTCOLLIDER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
class Point
{

public:
	float baseX, baseY;
	float currX, currY;

	Point* left = nullptr;
	Point* right = nullptr;

	Point() : baseX(0), baseY(0), currX(0), currY(0) {}
	Point(float x, float y)
	{
		baseX = x;
		currX = x;
		baseY = y;
		currY = y;
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

	PointCollider(Point *org, Point* arr, int n)
	{
		origin = org;
		pointList = arr;
		numP = n;
	}
	PointCollider(Point *org, Point **arr, int n)
	{
		origin = org;
		pointList = *arr;
		numP = n;
	}

	void updatePoints(float objX, float objY);
	void printPoints();
	void showPoints(sf::RenderWindow& window, Point orgn);

	Point getOrigin() { return *origin; }
	Point* closestPoint(float x, float y);

	bool collides(PointCollider obj);
	Point lineIntersection(Point a, Point b, Point c, Point d);
	bool validPoint(Point p, Point a, Point b);

};


#endif