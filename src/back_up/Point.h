#ifndef POINT_H
#define POINT_H
#include "math.h"

namespace geo
{
	///
	/// \brief The Point class
	/// 2D的点
	class Line;
	class Point
	{
	public:
		Point();
		double x;
		double y;
		Point(double x, double y);
		double distance(Point B);
		Point Step(double step, Point A);
		inline bool operator== (const Point &B) const;
		inline bool operator!= (const Point &B) const;

		//Point (double y);
	};
}
#endif // POINT_H
