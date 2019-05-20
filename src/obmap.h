#ifndef OBMAP_H
#define OBMAP_H

#include "bgeometry.h"
//#include "Draw.h"
//#include "polygonob.h"
//#include "Point.h"
//#include "gps2local.h"
#include "simple_svg.hpp"
#include <functional>
#include <vector>
#include <queue>
#include <math.h>
#include <map>

namespace ob {

	enum MapType { SearchMap, AggregationMap };
	typedef std::map <std::pair<int, int>, bgeo::PointVert> gridMap;
//    typedef std::map<std::pair>
	typedef std::pair<int, int> gridIndex;
class Obmap
{
public:
    Obmap();

    ///add  obstacles

    void addObRing(bgeo::DRing const & obring) {m_vDRing.push_back(obring);}
	void addObRing(std::vector<double> const &vx, std::vector<double> const &vy);

	void setGridRange(double const &min_x, double const min_y, double const &max_x, double const &max_y);

	void setGridSize(double const & aSize, double const &sSize) { this->AgridStep = aSize; this->gridStep = sSize; }


	void ReadRange(bgeo::DRing const & range) { m_Range = range; }

	void addDynamicObRing(bgeo::DRing  const& obring);
	//void addOb(ob::PolygonOb Ob);


	//draw function 
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//

////	QCustomPlot *qplot = nullptr;
//	QDraw mapDraw;

//	void drawObRing();
//	void drawgrid(const int & SorA);

//	void drawShoulder();
//	void drawRange();

//    void drawEdge();

	//
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	bool Map2grid();

	bool Map2Agrid();
	
	bool empty(int const & t);
	
	
	gridMap Tgrid;

	//图形式的栅格化地图
    bgeo::Graph Tgraph;
    //add the egdes to the graph
    bool graphAdddge();

	gridMap ATgrid;

	gridMap GTgrid;

	bool writeMapGrid();
	
	bool loadMapGrid(const char *pFilename);

	gridIndex pnt2Index(bgeo::DPoint const & pnt,int const &type);


	bool intersects(bgeo::DLineString  &line);
	
	void Ring2Vline();
	
	void addShoulder(std::vector<double> vpx, std::vector<double> vpy, std::vector<double> vqx,std::vector<double> vqy);

    bool setOb(double const &ob_x, double const &ob_y);


	bool savePic();

private:

	//初始化搜索地图的边
	void initSearchGridEdge();

	//获取搜索
	std::vector<ob::gridIndex> getSearchNeighbor(ob::gridIndex const &mindex);
	
	//std::vector<ob::PolygonOb>  m_vPolyOb;


	//路肩的集合
	std::vector<bgeo::DSegment> vSegment;

    bool MapIntersection(bgeo::DSegment const &sg);
	
	size_t m_ObNum;
	//每一个搜索栅格的距离
	double gridStep = 2;

	//每一个集结栅格的距离

	double AgridStep = 0.5;
	
	//障碍物的信息
    std::vector<bgeo::DRing> m_vDRing;

	//工作环境的信息
	bgeo::DRing m_Range;

	bgeo::DPoint mWsPoint1;
	bgeo::DPoint mWsPoint3;



    std::map<std::pair<int,int>,int> map2graph;
    std::map<int,std::pair<int,int>> graph2map;
	///搜索
	//最大行
	size_t m_MaxRow;
	//最大列
	size_t m_MaxCol;

	//集结
	//最大行
	size_t m_AMaxRow;
	//最大列
	size_t m_AMaxCol;


	std::vector<bgeo::DLineString> vline;
};

extern Obmap MainMap;

}
#endif // OBMAP_H
