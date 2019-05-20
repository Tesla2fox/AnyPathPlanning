#ifndef SPLAN_H
#define SPLAN_H


#include <vector>
#include <tuple>

#include "bgeometry.h"
#include "obmap.h"
#include "Aplan.h"
#include "stree.h"


namespace pl
{
//enum SAnchorIndex { aiBottomLeft, aiBottom, aiBottomRight, aiLeft, aicentre, aiRight, aiTopLeft, aiTop, aiTopRight };

enum GraphType {localGraph, totalGraph};
typedef std::pair<int, double> Anchor2Dis;

class Splan
{
public:
    Splan();
    ~Splan();

    Splan(std::vector<bgeo::DPoint> vPoint);

    bool setRange(bgeo::DRing const &range);

    bool setRange(std::vector<double> & vx, std::vector<double> &vy);

	bool setExternRange(std::vector<std::vector<double>> & vx, std::vector<std::vector<double>> &vy);

    bool setPosition(double const &x ,double const &y);

    bool getPath(std::vector<double> &vx,std::vector<double> &vy);

    bool Inside(bgeo::DPoint const & pnt);

    bgeo::DRing m_Range;

	bgeo::DRing m_ExternRange;
	
	bool externRangeEmpty = true;

    bool loadMap(ob::Obmap & map);




    std::vector<ob::gridIndex> m_pathIndex;

    //////////////////////////////////////////////////////////////////////////
    //draw function
    //////////////////////////////////////////////////////////////////////////
//    QCustomPlot *qplot = nullptr;

//    QDraw planDraw;

//    void drawPath();
//    void drawGraph(const int &type);
//    void drawGraphEdges(const int & type);
//    //void drawPath();
//    void drawvPath();
//    void drawvPPath();
//    void drawSpanningTree();

    //
    ///////////////////////////
    //draw function end
    //////////////////////////


    /// total map to the local map  which is in the range
    bool Tmap2Localmap();

    //total graph 2 the local graph which is in the range
    bool TGraph2LocalGraph();

    /// plan funtion
    void GreedPlan();
    //
    void GreedPlan(const int &initvd);




    //void

    void LawnPlan(const int &initvd);
    void Plan();
    /// find the searchplan the  init point;


	double distancePath(std::vector<bgeo::DPoint> const & _path);
	
    int failIndex = 1;

	std::vector<int> _vFailIndex;


private:

    bgeo::DLineString m_path;

    std::vector<bgeo::DPoint> vPPath;
	std::vector<std::vector<bgeo::DPoint>> _vvPPath;
    bool initDisMap();
    std::map<int, double> m_disMap;
    ob::Obmap m_map;
    std::set<ob::gridIndex> loalGridIndex;
    bgeo::Graph localGraph;

    bgeo::STree m_Stree;


    std::vector<bool> STreeBranchMap;

    std::map<size_t,size_t> mT2local;
    std::map<size_t,size_t> mlocal2T;

    size_t localGraphNum = 0;

    //std::vector<bgeo::DPoint> m_Path;

    bgeo::DPoint m_startPnt;
    Aplan apl;

    size_t getDir(const bgeo::VertexDescriptor & cvd,const bgeo::VertexDescriptor & tvd);
    //plan function
    int findInitVert();



    int findGreedInitVert(int const &i_md);
    int findLawnInitVert();
    ///
    /// \brief getNeighbour find the neighbour vertex of the centre vertex
    /// \param vd  centre vertex
    /// \return
    ///
    std::vector<std::pair<bgeo::VertexDescriptor,size_t>> getNeighbour(bgeo::VertexDescriptor const & vd);

    std::vector<bgeo::VertexDescriptor> getNeighbourNoDir(bgeo::VertexDescriptor const &vd);
    std::vector<size_t> localGraphPathIndex;
    bool backFindVert();



    std::vector<std::vector<size_t>> vGraphPathIndex;

    std::vector<std::vector<bgeo::DPoint>> vPath;

    // the vector of every branch distance
    std::vector<double> vPathDis;


    // span  a tree
    int spanTreePlan(const int &initvd);

    //
    int treeFindVert(const size_t  & vPathIndex);

    //
    int recursionPlan(const int &initvd);

    void vPath2STree();

    int addSTreeBranch(const int &vPathIndex,bgeo::STreeVertexDescriptor const &StreeIndex);

    void STree2Path();

    double calVertDis(const bgeo::STreeVertexDescriptor &index );
    void findSTreePath( bgeo::STreeVertexDescriptor const &index );

    std::vector<bgeo::STreeVertexDescriptor> findChildern(bgeo::STreeVertexDescriptor
                                                          const & index);
    std::map<size_t,std::vector<size_t>> MapTree;
    std::vector<std::vector<size_t>> vvTreeList;
    //std::vector<std::pair<size_t,bool>> vTreeBoolean;
    std::vector<bool> vTreeBoolean;

    void clearBeforeData();

    int tree2Path();
    int branch2Path(const size_t & vPathIndex);
};
}

#endif // SPLAN_H
