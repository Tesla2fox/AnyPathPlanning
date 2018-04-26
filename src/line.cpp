#include "line.h"

namespace geo {
	Line::Line()
	{

	}

	Line::Line(Point pt1, Point pt2)
	{
		this->A = pt1;
		this->B = pt2;
		if (pt2.x > pt1.x)
		{
			this->_m_dire = positive;
		}
		else {
			this->_m_dire = negative;
		}
		this->calcRota();
		this->calcAlpha();

	}

	void Line::init(Point pt1, Point pt2)
	{
		this->A = pt1;
		this->B = pt2;

		if (pt2.x > pt1.x)
		{
			this->_m_dire = positive;
		}
		else {
			this->_m_dire = negative;
		}

		this->calcRota();
		this->calcAlpha();

	}


	Point Line::Step(double s)
	{
		Point res;
		auto dis = A.distance(B);
		if (dis< s)
		{
			return B;
		}
		if (this->_m_dire == positive)
		{
			res.x = A.x + this->cosAlpha*s;
			res.y = A.y + this->sinAlpha*s;
		}
		else
		{
			res.x = A.x - this->cosAlpha*s;
			res.y = A.y - this->sinAlpha*s;
		}
		return res;
	}

	void Line::calcRota()
	{
		auto Y_bais = B.y - A.y;
		auto X_bais = B.x - A.x;
		//    try
		/*    {
				double tryK = Y_bais / X_bais;
			}
		 */   double K = Y_bais / X_bais;
		if (K == K)
		{
			this->rotate = K;

		}

	}


	void Line::calcAlpha()
	{
		double K = this->rotate;
		double denominator = sqrt(K*K + 1);
		this->sinAlpha = K / denominator;
		this->cosAlpha = 1 / denominator;

	}

	bool Line::Jintersect(Line LineB)
	{

		return false;
	}

	int Line::Line2VPoint(std::vector < geo::Point >  &Vpnt, double const pstep)
	{
		Point addPnt = this->A;
        std::size_t addPntNum = 0;
		Vpnt.push_back(addPnt);
		addPntNum++;
		while (!((addPnt.x==B.x)&&(addPnt.y==B.y)))
		{			
			addPnt=addPnt.Step(pstep, B);
			addPntNum++;
			Vpnt.push_back(addPnt);
		}
		return addPntNum;
		
	}
}
