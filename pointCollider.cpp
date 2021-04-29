#include "pointCollider.h"
#include <stdlib.h>
#include <iostream>

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

void PointCollider::printPoints()
{
	for (int i = 0; i < numP; i++)
	{
		std::cout << "Point " << i << ": " << &pointList[i] << " : {" << pointList[i].currX << ", " << pointList[i].currY << "}" << std::endl;
	}
}

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

bool PointCollider::collides(PointCollider obj)
{
	Point itsClosest = *(obj.closestPoint(origin->currX, origin->currY));
	Point myClosest = *closestPoint(obj.getOrigin().currX, obj.getOrigin().currY);

	std::cout << myClosest.currX << ", " << myClosest.currY << std::endl;
	
	if (intersects(myClosest, *myClosest.left, itsClosest, *itsClosest.left))
		return true;
	if (intersects(myClosest, *myClosest.left, itsClosest, *itsClosest.right))
		return true;
	if (intersects(myClosest, *myClosest.right, itsClosest, *itsClosest.left))
		return true;
	if (intersects(myClosest, *myClosest.right, itsClosest, *itsClosest.right))
		return true;

	return false;
}

//helper function for collides method
bool PointCollider::intersects(Point p1, Point q1, Point p2, Point q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false;
}

bool PointCollider::onSegment(Point p, Point q, Point r)
{
	float max1 = (p.currX > r.currX) ? p.currX : r.currX;
	float max2 = (p.currY > r.currY) ? p.currY : r.currY;
	float min1 = (p.currX < r.currX) ? p.currX : r.currX;
	float min2 = (p.currY < r.currY) ? p.currY : r.currY;
	if (q.currX <= max1 && q.currX >= min1 && q.currY <= max2 && q.currY >= min2)
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int PointCollider::orientation(Point p, Point q, Point r)
{

	int val = (q.currY - p.currY) * (r.currX - q.currX) -
		(q.currX - p.currY) * (r.currX - q.currY);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}