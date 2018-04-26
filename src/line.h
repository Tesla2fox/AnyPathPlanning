#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "math.h"
#include <vector>
namespace geo {
	enum Direction { positive, negative };
	class Line
	{
	public:

		Line();
		Point A;
		Point B;
		Line(Point pt1, Point pt2);
		void init(Point pt1, Point pt2);

		Point Step(double s);
		double rotate;
		double length;
		//double t;
		double sinAlpha;
		double cosAlpha;
		double alpha;
		Direction _m_dire;
		//protected:
		void calcRota();
		void calcAlpha();
		///
		/// \brief Jintersect 判断两条直线是否相交
		/// \param LineB
		/// \return
		///
		bool Jintersect(Line LineB);
		///
		/// \brief Jintersect
		/// \param LineB
		/// \param interPoint 若相交，返回相交的点。
		/// \return
		///
		bool Jintersect(Line LineB, Point &interPoint);

		int Line2VPoint(std::vector<geo::Point> &Vpnt,double const pstep);
	};


	class StLine
	{
	public:
		StLine() {}
	};
}
#endif // LINE_H
