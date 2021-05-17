#ifndef ASTROID_H_
#define ASTROID_H_

#include <SFML/Graphics.hpp>
#include "pointCollider.h"

namespace sf
{
	class Astroid : public CircleShape
	{
	private:
	public:
		float xSpeed, ySpeed;
		Astroid(float radius, std::size_t points) : CircleShape(radius, points){}
		Astroid() { spawnAstroid(); }
		~Astroid() {};

		Point origin = Point(getOrigin().x, getOrigin().y);
		Point *points;

		PointCollider *collider;

		void spawnAstroid();
		bool advance(float dt);

	};
}
#endif