#include "point.h"
//#include "line.h"
namespace areaCut {
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

	//Point Point::Step(double step, Point B)
	//{
	//    Point A(this->x, this->y);
	//    Line StepLine( A ,B );
	//    auto res=StepLine.Step(step);
	//    return res;
	//}


	RegionMM::RegionMM()
	{
	}

	RegionMM::~RegionMM()
	{
	}

	//
	RegionMM::RegionMM(double x1, double x2, double y1, double y2)
	{
		this->max_x = x1;
		this->min_x = x2;
		this->max_y = y1;
		this->min_y = y2;
	}



	std::vector<Point> RegionMM::Square2Point()
	{
		std::vector<Point> resReGPS;

		{
			Point ReGPSUnit(this->min_x, this->min_y);
			//顶点1
			//Local2GPS(this->min_x, this->min_y, 0, &ReGPSUnit.lat, &ReGPSUnit.lon, nullptr);
			resReGPS.push_back(ReGPSUnit);

		}
		{
			//顶点2
			Point ReGPSUnit(this->max_x, this->min_y);
			//Local2GPS(this->max_x, this->min_y, 0, &ReGPSUnit.lat, &ReGPSUnit.lon, nullptr);
			resReGPS.push_back(ReGPSUnit);
		}

		{
			//顶点3
			Point ReGPSUnit(this->max_x, this->max_y);
			//Local2GPS(this->max_x, this->min_y, 0, &ReGPSUnit.lat, &ReGPSUnit.lon, nullptr);
			resReGPS.push_back(ReGPSUnit);
		}

		{
			//顶点4
			Point ReGPSUnit(this->min_x, this->max_y);
			//Local2GPS(this->max_x, this->min_y, 0, &ReGPSUnit.lat, &ReGPSUnit.lon, nullptr);
			resReGPS.push_back(ReGPSUnit);
		}
		return resReGPS;

	}
}