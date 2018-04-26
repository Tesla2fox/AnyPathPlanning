
#ifndef APLAN_H
#define APLAN_H

#include "bgeometry.h"
#include "obmap.h"
//#include "Draw.h"
#include <iostream>

//#include "qdebug.h"

#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <stack>
namespace pl {
	enum AnchorIndex { aiBottomLeft, aiBottom, aiBottomRight, aiLeft,aicentre,aiRight, aiTopLeft, aiTop , aiTopRight };

	typedef std::pair<int, double> Anchor2Dis;


	class ANode
	{
	public:
		ANode();
		~ANode();
		ANode(bgeo::PointVert vert, bgeo::DPoint tar, double disg, int dir);

		ANode(bgeo::PointVert vert, bgeo::DPoint tar, double disg, int dir,ob::gridIndex par);

		bgeo::PointVert vertPnt;
		bgeo::DPoint targetPnt;
		double disH = 0;
		double disG = 0;
		double disF = 0;
		int direction;
		double getdisF() const { return this->disF; }
		void caldisF();
		void setdisG(double const &);
		ob::gridIndex parent;
	private:
	};

	bool ANodeFunction(ANode a, ANode b);
	typedef std::pair<ob::gridIndex, ANode> mNode;


	class Aplan
	{
	public:
		Aplan();
		~Aplan();
		bool init();
		bool init(double s_x, double s_y, double t_x, double t_y);
		bool loadMap(ob::Obmap & map);

        int failIndex = 1;

		bool getStartPnt(double const & x, double const & y);
		bool getTargetPnt(double const & x, double const & y);
		
		bool target2Grid();
		bool start2Grid();

        //
        void setMaxSearchTimes(const size_t & st) {this->maxSearhTimes =st;}

		//
		bool AstarPlan();

		bool AstarPlan(bool const &grpMode);

		bool setGroupMode(bool const &grpMode);

		ob::Obmap m_map;
		ob::gridIndex m_Tindex;
		ob::gridIndex m_Sindex;

		bgeo::DLineString m_path;
		std::vector<ob::gridIndex> m_pathIndex;

        bool getPath(std::vector<double> & vx,std::vector<double> &vy);
	
		//////////////////////////////////////////////////////////////////////////
		//draw function 
		//////////////////////////////////////////////////////////////////////////
//		QCustomPlot *qplot = nullptr;

//		QDraw planDraw;

//		void drawPath();
		
//		void slowDraw();


//		void drawS2T();


//        void drawCloseList();
        ////

	private:
		bool groupMode = false;

		bgeo::DPoint m_startPnt;
		bgeo::DPoint m_targetPnt;
		std::map<int, double> m_disMap;
		bool initDisMap();

		bool AstarSearch();
		bool AstarPathFinder();

		bool AstarShorten();

		std::list<ANode> m_openList;
		// std::set<ob::gridIndex> m_openSet;
		std::list<ob::gridIndex> m_openSet;
		std::map<ob::gridIndex, ANode> m_closeList;

		std::set<ob::gridIndex> m_closeSet;
		std::vector<ANode> m_closeVect;

		void SortedAddToOpenList(ANode const & mNode);
		std::vector<ob::gridIndex> getNeighbor(ob::gridIndex const &mindex);
		std::vector<ob::gridIndex> getNeighbor(ob::gridIndex const &mindex,std::vector<int> &vdirIndex);

		//return ID
		int shortenList(std::list<bgeo::DPoint> & ldpoint,int const & ID);
		
		int shortenList(std::list<bgeo::DPoint> & ldpoint, std::list<bgeo::DPoint>::const_iterator );

        // max search time
        size_t maxSearhTimes = 20000;

	};

}

#endif
