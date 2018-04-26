#include "Point.h"
#include "line.h"
namespace geo {
	Point::Point()
	{

	}

	Point::Point(double Mx, double My)
	{
		this->x = Mx;
		this->y = My;
	}

	double Point::distance(Point B)
	{
		double x = B.x - this->x;
		double y = B.y - this->y;
		auto dis2 = x * x + y * y;
		double dis = sqrt(dis2);
		return dis;
	}

	Point Point::Step(double step, Point B)
	{
		Point A(this->x, this->y);
		Line StepLine(A, B);
		auto res = StepLine.Step(step);
		return res;
	}
	inline bool Point::operator==(const Point &B) const
	{
		if ((this->x==B.x)&&(this->y==B.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	inline bool Point::operator!=(const Point &B) const
	{
		if ((this->x == B.x) && (this->y == B.y))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
