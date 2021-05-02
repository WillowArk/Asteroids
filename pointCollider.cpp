#include "pointCollider.h"
#include <stdlib.h>
#include <iostream>


//constructors
PointCollider::PointCollider(Point* org, Point* arr, int n)
{
	origin = org;
	pointList = arr;
	numP = n;

}

PointCollider::PointCollider(Point* org, Point** arr, int n)
{
	origin = org;
	pointList = *arr;
	numP = n;
}


//Updates points based on origin given
void PointCollider::updatePoints(float objX, float objY)
{
	for (int i = 0; i < numP; i++)
	{
		pointList[i].setX(objX);
		pointList[i].setY(objY);
	}

	origin->setX(objX);
	origin->setY(objY);
}


//rotates points around origin by given degrees * deltaTime;
void PointCollider::rotatePoints(float deg)
{
	float rad = deg * .0174532925199;
	float getRad;
	for (int i = 0; i < numP; i++)
	{
		getRad = pointList[i].rotation += rad;
		pointList[i].baseX = cos(getRad) * pointList[i].magnitude;
		pointList[i].baseY = sin(getRad) * pointList[i].magnitude;
	}
}


//print location of points to console
void PointCollider::printPoints()
{
	for (int i = 0; i < numP; i++)
	{
		std::cout << "Point " << i << ": " << &pointList[i] << " : {" << pointList[i].currX << ", " << pointList[i].currY << "}" << std::endl;
	}
}


//Shows points to given screen highlighting point closest to given point
void PointCollider::showPoints(sf::RenderWindow& window, Point orgn)
{
	for (int i = 0; i < numP; i++)
	{
		sf::CircleShape circle(5, 8);
		circle.setOrigin(2.5, 2.5);
		circle.setPosition(pointList[i].currX, pointList[i].currY);
		if (closestPoint(orgn.currX, orgn.currY) == &pointList[i])
		{
			circle.setFillColor(sf::Color::Green);
		}
		window.draw(circle);
	}
}


void PointCollider::showPoints(sf::RenderWindow& window)
{
	for (int i = 0; i < numP; i++)
	{
		sf::CircleShape circle(5, 8);
		circle.setOrigin(2.5, 2.5);
		circle.setPosition(pointList[i].currX, pointList[i].currY);
		window.draw(circle);
	}
}
//gets closest point in collider to given point
Point* PointCollider::closestPoint(float x, float y)
{
	Point* closest = &pointList[0];
	float a = pow((x - closest->currX), 2) + pow((y - closest->currY), 2);
	for (int i = 1; i < numP; i++)
	{
		float b = pow((x - pointList[i].currX), 2) + pow((y - pointList[i].currY), 2);
		a = (a < 0) ? a * -1 : a;
		b = (b < 0) ? b * -1 : b;
		if (b < a)
		{
			a = b;
			closest = &pointList[i];
		}
	}
	return closest;
}

//returns true if this object collides with given object
bool PointCollider::collides(PointCollider obj)
{
	Point myClosest = *closestPoint(obj.getOrigin().currX, obj.getOrigin().currY);
	Point myLeft = *myClosest.left;
	Point myRight = *myClosest.right;
	Point itsClosest = *(obj.closestPoint(origin->currX, origin->currY));
	Point itsLeft = *itsClosest.left;
	Point itsRight = *itsClosest.right;

	Point junction = lineIntersection(myClosest, myLeft, itsClosest, itsLeft);
	if (validPoint(junction, myClosest, myLeft) && validPoint(junction, itsClosest, itsLeft))
		return true;
	junction = lineIntersection(myClosest, myRight, itsClosest, itsLeft);
	if (validPoint(junction, myClosest, myRight) && validPoint(junction, itsClosest, itsLeft))
		return true;
	junction = lineIntersection(myClosest, myLeft, itsClosest, itsRight);
	if (validPoint(junction, myClosest, myLeft) && validPoint(junction, itsClosest, itsRight))
		return true;
	junction = lineIntersection(myClosest, myRight, itsClosest, itsRight);
	if (validPoint(junction, myClosest, myRight) && validPoint(junction, itsClosest, itsRight))
		return true;
	return false;
}

//helper method for collider; checks if two given lines intersect
Point PointCollider::lineIntersection(Point a, Point b, Point c, Point d)
{
	//get mx+b
	float slope1 = (b.currY - a.currY) / (b.currX - a.currX);
	float b1 = a.currY - slope1 * a.currX;
	float slope2 = (d.currY - c.currY) / (d.currX - c.currX);
	float b2 = c.currY - slope2 * c.currX;
	

	if (slope1 == slope2)
	{
		//a and c will always be the closest points
		float x = ((a.currX - d.currX) / 2) + d.currX;
		float y = ((a.currY - d.currY) / 2) + d.currY;
		return Point{ x, y };
	}
	else
	{
		float x = (b2 - b1) / (slope1 - slope2);
		float y = slope1 * x + b1;
		return Point{x, y};
	}
}
//helper method to check if given point of intersection is in between two points
bool PointCollider::validPoint(Point p, Point a, Point b)
{
	float minX;
	float maxX;
	float minY;
	float maxY;
	if (a.currX < b.currX)
	{
		minX = a.currX;
		maxX = b.currX;
	}
	else
	{
		minX = b.currX;
		maxX = a.currX;
	}

	if (a.currY < b.currY)
	{
		minY = a.currY;
		maxY = b.currY;
	}
	else
	{
		minY = b.currY;
		maxY = a.currY;
	}

	if (p.currX >= minX && p.currX <= maxX && p.currY >= minY && p.currY <= maxY)
		return true;

	return false;
}