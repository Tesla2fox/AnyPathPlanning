#ifndef POLYGONOB_H
#define POLYGONOB_H
#include "vector"
//#include "gps2local.h"
//#include "qcustomplot.h"
//#include "qvector.h"
#include "line.h"
#include "Point.h"

namespace ob {

	enum { GPSPolygonOb, LocalPolygonOb };
	enum {
		obWood, obHuge, obLittle, obYang, obPigHole};
class PolygonOb
{
public:    
    PolygonOb();
    PolygonOb(std::vector<double> ,std::vector<double>,int,int);

    //local
    std::vector<double> m_vecx;
    std::vector<double> m_vecy;
    //GPS
    std::vector<double> m_vlat;
    std::vector<double> m_vlon;


	//std::vector<m_vecx> 
	void m_local2GPS();
	void m_GPS2local();

	std::vector<geo::Line> m_Vline;
	
	int ob2VPoint(std::vector<geo::Point> & pnt);
//	bool DrawPolyOb(QCustomPlot  *Qgraph);
	//
    std::size_t m_type;

private:
    std::size_t m_pntNum;
	std::vector<geo::Point> m_Vpnt;
};

}
#endif // POLYGONOB_H
