#ifndef POINT_H
#define POINT_H

//#include "PointArray.h"
//#include "gps2local.h"

#include <vector>
#include "math.h"
namespace areaCut {
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
		//Point (double y);
	};




	class RegionMM
	{
	public:
		RegionMM();
		~RegionMM();

		//x1 代表最大的X
		//x2 代表最小的X
		//y1 代表最大的Y
		//y2 代表最小的Y
		RegionMM(double x1, double x2, double y1, double y2);

		double max_x;
		double min_x;
		double max_y;
		double min_y;
		size_t _m_AgentNum = 0;
		std::vector<Point> Square2Point();

	private:

	};

	struct Region4
	{
		std::vector<Point> _m_Vregion;
		//智能体的编号
		size_t _m_AgIndex;
		//曾经属于哪一个区域
		size_t _m_AreaIndex;
	};
}
#endif // POINT_H
