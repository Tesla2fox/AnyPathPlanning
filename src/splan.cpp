#include "splan.h"
#include <queue>
#include <math.h>
#include <time.h>
#include <functional>
#include <random>
#include <iostream>
#include "stadfxEx.h"

namespace pl {

Splan::Splan()
{
    this->initDisMap();
}

Splan::~Splan()
{
}
Splan::Splan(std::vector<bgeo::DPoint> vPoint)
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//draw function
//////////////////////////////////////////////////////////////////////////



//void Splan::drawPath()
//{
//    this->planDraw.qplot = this->qplot;

//    //    planDraw.LineString(this->m_path);
//    planDraw.slowLine(this->m_path);
//}


//void Splan::drawGraph(const int &type)
//{
//    this->planDraw.qplot = this->qplot;
//    auto  QTgraph =  this->m_map.Tgraph;
//    qDebug()<<"the num of the Tgraph"<<boost::num_vertices(QTgraph);

//    if (type == GraphType::localGraph)
//    {
//        QTgraph = this->localGraph;
//        qDebug()<<"the num of the localGraph"<<boost::num_vertices(QTgraph);
//    }
//    double halfStep = 1;
//    std::pair<bgeo::VertexIterator, bgeo::VertexIterator> _b2e_vi = boost::vertices(QTgraph);

//    for (bgeo::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
//    {
//        bgeo::VertexDescriptor vd = *vit;
//        bgeo::VertexProperty &vp = QTgraph[vd];


//        QCPItemEllipse *circle = new QCPItemEllipse(this->qplot);
//        circle->topLeft->setCoords(vp.pnt.x() - halfStep, vp.pnt.y() + halfStep);
//        circle->bottomRight->setCoords(vp.pnt.x() + halfStep, vp.pnt.y() - halfStep);
//        QPen pen;

//        switch (vp.Type)
//        {
//        case bgeo::vertType::WayVert:
//        {
//            pen.setColor(Qt::GlobalColor::darkMagenta);
//            break;
//        }
//        case bgeo::vertType::ObVert:
//        {
//            pen.setColor(Qt::GlobalColor::darkGreen);
//            QBrush brush;
//            brush.setColor(Qt::GlobalColor::cyan);
//            brush.setStyle(Qt::Dense1Pattern);
//            circle->setBrush(brush);
//            break;
//        }
//        case bgeo::vertType::EdgeObVert:
//        {
//            pen.setColor(Qt::GlobalColor::darkGreen);
//            QBrush brush;
//            brush.setColor(Qt::GlobalColor::green);
//            brush.setStyle(Qt::Dense1Pattern);
//            circle->setBrush(brush);
//            break;
//        }
//        case bgeo::vertType::NearVert:
//        {
//            pen.setColor(Qt::GlobalColor::darkRed);
//            QBrush brush;
//            brush.setColor(Qt::GlobalColor::darkRed);
//            brush.setStyle(Qt::Dense1Pattern);
//            circle->setBrush(brush);
//            break;
//        }
//        case bgeo::vertType::ShoulderVert:
//        {
//            pen.setColor(Qt::GlobalColor::green);
//            QBrush brush;
//            brush.setColor(Qt::GlobalColor::gray);
//            brush.setStyle(Qt::Dense1Pattern);
//            circle->setBrush(brush);
//            break;
//        }
//        default:
//            break;
//        }
//        circle->setPen(pen);
//    }
//    qplot->replot();
//}

//void Splan::drawGraphEdges(const int &type)
//{
//    this->planDraw.qplot = this->qplot;
//    auto  QTgraph =  this->m_map.Tgraph;
//    qDebug()<<"the num of the Tgraph"<<boost::num_edges(QTgraph);

//    if (type == GraphType::localGraph)
//    {
//        QTgraph = this->localGraph;
//        qDebug()<<"the num of the localGraph"<<boost::num_edges(QTgraph);
//    }

//    std::pair<bgeo::EdgeIterator,bgeo::EdgeIterator> _b2e_ei = boost::edges(QTgraph);

//    for (auto eit = _b2e_ei.first; eit != _b2e_ei.second ; eit ++)
//    {
//        bgeo::EdgeDescriptor ed = *eit;
//        bgeo::VertexDescriptor sVertd = boost::source(ed, QTgraph);
//        bgeo::VertexDescriptor tVertd = boost::target(ed, QTgraph);

//        bgeo::VertexProperty &sVert = QTgraph[sVertd];
//        bgeo::VertexProperty &tVert = QTgraph[tVertd];

//        QCPItemLine *Line = new QCPItemLine(this->qplot);
//        Line->start->setType(QCPItemPosition::ptPlotCoords);
//        Line->end->setType(QCPItemPosition::ptPlotCoords);
//        Line->start->setCoords(sVert.pnt.x(), sVert.pnt.y());
//        Line->end->setCoords(tVert.pnt.x(), tVert.pnt.y());

//        QPen pen;
//        pen.setStyle(Qt::SolidLine);
//        pen.setWidth(2);
//        pen.setColor(Qt::GlobalColor::darkBlue);
//        Line->setPen(pen);

//    }
//    qplot->replot();

//}

//void Splan::drawvPath()
//{
//    this->planDraw.qplot = this->qplot;
//    size_t BranchIndex  = 1;
//    for (auto &it : this->vPath)
//    {
//        QCPCurve *pathCurve = new QCPCurve(qplot->xAxis, qplot->yAxis);
//        QVector<QCPCurveData> pathCurveData;
//        for (size_t i = 0; i < it.size(); i++)
//        {
//            pathCurveData.push_back(QCPCurveData(i, it.at(i).x(), it.at(i).y()));
//        }
//        pathCurve->data()->set(pathCurveData, false);

//        qplot->xAxis->setScaleRatio(qplot->yAxis);
//        pathCurve->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
//        QPen pen;
//        // get a random color

//        auto getColorInt = [=](){return (rand()%255);};
//        pen.setColor(QColor(getColorInt(),getColorInt(),getColorInt()));
//        pen.setWidth(4);
//        pathCurve->setPen(pen);

//        //add the txt
//        //        QCPItemText *txt = new QCPItemText(this->qplot);
//        //        txt->position->setCoords(it.at(0).x() + 1, it.at(0).y() + 1);
//        //        QString QSt_index = QString("Branch -%1").arg(BranchIndex++);
//        //        txt->setText(QSt_index);
//        //        ///
//        qplot->replot();

//    }

//}

//void Splan::drawvPPath()
//{
//    this->planDraw.qplot = this->qplot;

//    QCPCurve *lineStringCurve = new QCPCurve(qplot->xAxis, qplot->yAxis);
//    QVector<QCPCurveData> lineStringCurveData;
//    qDebug()<<"vPPath Size =  "<<vPPath.size();
//    for(size_t i = 0;i <  this->vPPath.size(); i++)
//    {
//        lineStringCurveData.push_back(QCPCurveData(i, vPPath.at(i).x(), vPPath.at(i).y()));

//        lineStringCurve->data()->set(lineStringCurveData, false);

//        qplot->xAxis->setScaleRatio(qplot->yAxis);
//        lineStringCurve->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));

//        QPen pen;
//        if(i%2)
//        {
//            pen.setColor(Qt::GlobalColor::red);
//        }
//        else
//        {
//            pen.setColor(Qt::GlobalColor::blue);
//        }
//        pen.setWidth(4);
//        lineStringCurve->setPen(pen);
//        //unix;
//        //Sleep(100);
//        //lineStringCurve->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
//        qplot->replot();


//    }
//    //		return true;
//}

//void Splan::drawSpanningTree()
//{
//    auto vi =boost::vertices(this->m_Stree);

//    auto vertNums = boost::num_vertices(this->m_Stree);
//    qDebug()<<"vertNum = "<<vertNums;
//    this->planDraw.qplot = this->qplot;

//    size_t BranchIndex = 1;


//    for(bgeo::STreeVertexIterator vit = vi.first; vit != vi.second ; vit++)
//    {
//        qDebug()<<"BranchIndex"<<BranchIndex;
//        auto vd = *vit;
//        auto & StreeVert=this->m_Stree[vd];

//        QCPCurve *pathCurve = new QCPCurve(qplot->xAxis, qplot->yAxis);
//        QVector<QCPCurveData> pathCurveData;
//        auto &it = StreeVert.vPoint;
//        if(it.empty())
//        {
//            qDebug()<<"empty";
//            continue;
//        }
//        if(it.size()<=1)
//        {
//            qDebug()<<"wtf";
//        }
//        for (size_t i = 0; i < it.size(); i++)
//        {
//            pathCurveData.push_back(QCPCurveData(i, it.at(i).x(), it.at(i).y()));
//        }
//        pathCurve->data()->set(pathCurveData, false);

//        qplot->xAxis->setScaleRatio(qplot->yAxis);
//        pathCurve->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
//        QPen pen;
//        // get a random color

//        auto getColorInt = [=](){return (rand()%255);};
//        pen.setColor(QColor(getColorInt(),getColorInt(),getColorInt()));
//        pen.setWidth(4);
//        pathCurve->setPen(pen);

//        //add the txt
//        QCPItemText *txt = new QCPItemText(this->qplot);


//        std::default_random_engine engine(time(NULL));
//        std::uniform_real_distribution<double> distribution(-3.0,3.0);

//        if(BranchIndex%2)
//        {
//            txt->position->setCoords(it.at(0).x()+ 0.5/*+ distribution(engine)*/, it.at(0).y()+0.5 /*+ distribution(engine)*/);
//        }
//        else
//        {
//            txt->position->setCoords(it.at(0).x()-0.5 /*+ distribution(engine)*/, it.at(0).y()-0.5 /*+ distribution(engine)*/);
//        }
//        QString QSt_index = QString("B-%1 -%2").arg(BranchIndex++).arg(StreeVert.level);
//        txt->setText(QSt_index);

//        //        sleep(1);
//        //sleep()
//        qplot->replot();


//    }
//    qplot->replot();

//}

//////////////////////////////////////////////////////////////////////////

///end draw function

bool Splan::setRange(bgeo::DRing const &range)
{
    this->m_Range.clear();
    this->m_Range = range;
    return false;
}
bool Splan::setRange(std::vector<double> & vx, std::vector<double> &vy)
{
    this->m_Range.clear();
    for (size_t i = 0; i < vx.size(); i++)
    {
        bgeo::DPoint pntUnit(vx.at(i),vy.at(i));
//        qDebug()<<i<<" _x = "<<vx.at(i);
//        qDebug()<<i<<" _y = "<<vy.at(i);

        this->m_Range.push_back(pntUnit);
    }
    return false;
}

bool Splan::setPosition(const double &x, const double &y)
{
    this->m_startPnt.x(x);
    this->m_startPnt.y(y);
    apl.getStartPnt(this->m_startPnt.x(),this->m_startPnt.y());
    if(apl.start2Grid())
    {
        std::cout<<"setPos success"<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"setPos failed"<<std::endl;
        this->failIndex = -2;
    }
    return false;
}

bool Splan::getPath(std::vector<double> &vx, std::vector<double> &vy)
{

    if(this->vPPath.empty())
    {
        return false;
    }
    for (auto &it : this->vPPath)
    {
        vx.push_back(it.x());
        vy.push_back(it.y());
    }
    return true;
}
bool Splan::initDisMap()
{
    this->m_disMap.insert(Anchor2Dis(aiTop, 2));
    this->m_disMap.insert(Anchor2Dis(aiLeft, 2));
    this->m_disMap.insert(Anchor2Dis(aiRight, 2));
    this->m_disMap.insert(Anchor2Dis(aiBottom, 2));
    this->m_disMap.insert(Anchor2Dis(aiTopLeft, 2.828));
    this->m_disMap.insert(Anchor2Dis(aiTopRight, 2.828));
    this->m_disMap.insert(Anchor2Dis(aiBottomRight, 2.828));
    this->m_disMap.insert(Anchor2Dis(aiBottomLeft, 2.828));
    return false;
}

///
/// \brief Splan::getDir  get the direction of the  centre vertex  to the local vertex
/// \param cvd  centre vertex
/// \param tvd  local vertex
/// \return  direction
///
size_t Splan::getDir(const bgeo::VertexDescriptor &cvd, const bgeo::VertexDescriptor &tvd)
{
    // bgeo::VertexDescriptor lvd = *neighbourIt;
    // bgeo::VertexProperty &lvp = this->localGraph[lvd];
    //this->localGraph[]
    size_t dir = 100;
    auto cvp = this->localGraph[cvd];
    auto lvp = this->localGraph[tvd];

    auto c_x = cvp.pnt.x();
    auto c_y = cvp.pnt.y();
    auto l_x = lvp.pnt.x();
    auto l_y = lvp.pnt.y();


    const float EPSINON = 0.001;

    if(std::abs(c_y-l_y)<EPSINON)
    {
        //if()

        if(std::abs(c_x-l_x)<EPSINON)
        {
            dir =  pl::aicentre;
            return dir;
        }

        if(c_x>l_x)
        {
            dir =  pl::aiLeft;
            return dir;
        }
        if(c_x<l_x)
        {
            dir =  pl::aiRight ;
            return dir;
        }
    }


    if(c_y>l_y)
    {
        //if()

        if(std::abs(c_x-l_x)<EPSINON)
        {
            dir =  pl::aiBottom;
            return dir;
        }
        if(c_x>l_x)
        {
            dir =  pl::aiBottomLeft;
            return dir;
        }
        if(c_x<l_x)
        {
            dir =  pl::aiBottomRight ;
            return dir;
        }
    }

    if(c_y<l_y)
    {
        //if()

        if(std::abs(c_x-l_x)<EPSINON)
        {
            dir =  pl::aiTop;
            return dir;
        }

        if(c_x>l_x)
        {
            dir =  pl::aiTopLeft;
            return dir;
        }
        if(c_x<l_x)
        {
            dir =  pl::aiTopRight ;
            return dir;
        }
    }
}
bool Splan::Inside(bgeo::DPoint const & pnt)
{
    return bg::within(pnt, this->m_Range);
}
bool Splan::loadMap(ob::Obmap & map)
{
    if (map.empty(ob::MapType::SearchMap))
    {
        return false;
    }
    else
    {
        this->m_map = map;
        this->apl.loadMap(map);
        this->apl.setMaxSearchTimes(20000);
        return true;
    }
}
//
bool Splan::Tmap2Localmap()
{
    auto &gridMap = this->m_map.Tgrid;

    for (auto &it : gridMap)
    {
        if (this->Inside(it.second.pnt))
        {
            loalGridIndex.insert(it.first);
        }
    }
    return false;
}

bool Splan::TGraph2LocalGraph()
{

    //product the vertex of the graph
    {
        auto & Tgraph = this->m_map.Tgraph;
        auto num = boost::num_vertices(Tgraph);
//        qDebug()<<"numTotal Graph=="<<num;


        std::pair<bgeo::VertexIterator,bgeo::VertexIterator> _b2e_vi = boost::vertices(Tgraph);

        localGraph.clear();
        mT2local.clear();
        mlocal2T.clear();
        size_t VlocalInd = 0;

        for (auto vit = _b2e_vi.first ; vit != _b2e_vi.second ; vit++)
        {
            bgeo::VertexDescriptor  vd = *vit;
            bgeo::VertexProperty &vp = Tgraph[vd];

            if(Inside(vp.pnt))
            {
                vp.EdgeState = false;
                vp.QueueState = false;
                vp.NeighbourState = false;
                boost::add_vertex(vp,this->localGraph);
                this->mT2local.insert(std::pair<size_t,size_t> ( vd,VlocalInd));
                this->mlocal2T.insert(std::pair<size_t,size_t> (VlocalInd,vd) );
                VlocalInd++;
            }
        }
    }
    // add the edge 2 the localgraph
    {
        std::pair<bgeo::VertexIterator,bgeo::VertexIterator> _b2e_vi = boost::vertices(this->localGraph);

        for (auto vit = _b2e_vi.first ; vit != _b2e_vi.second ; vit++)
        {
            bgeo::VertexDescriptor vd = *vit;
            auto toVertDes  = this->mlocal2T[vd];
            auto neighbour = boost::adjacent_vertices(toVertDes,this->m_map.Tgraph);

            for (auto neighbourIt = neighbour.first;  neighbourIt != neighbour.second ; neighbourIt++)
            {
                bgeo::VertexDescriptor tvd = *neighbourIt;
                auto loVertDes  = this->mT2local[tvd];
                if(vd!= loVertDes)
                {
                    if(this->localGraph[loVertDes].NeighbourState==false)
                    {
                        boost::add_edge(loVertDes,vd,this->localGraph);
                    }
                }
            }
            this->localGraph[vd].NeighbourState = true;
//            qDebug()<<vd;
        }

    }
    this->localGraphNum = boost::num_vertices(this->localGraph);

    deg::conf_debug<<"the localGraphVertexNum = "<<this->localGraphNum <<std::endl;
    if(localGraphNum==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void Splan::clearBeforeData()
{
    this->localGraphPathIndex.clear();
    this->m_path.clear();
    this->vGraphPathIndex.clear();
    this->vPath.clear();
    this->MapTree.clear();
    this->vvTreeList.clear();
    this->vTreeBoolean.clear();
    this->vPathDis.clear();
    this->m_Stree.clear();
    this->STreeBranchMap.clear();
    this->vPPath.clear();
}


void Splan::Plan()
{
	_vFailIndex.clear();
	_vFailIndex.assign(10, 1);
	_vvPPath.clear();
	for (size_t i = 0; i < 10; i++)
	{
		if (this->TGraph2LocalGraph())
		{

		}
		else
		{
			this->failIndex = -8;
			//return;
			_vFailIndex.at(i) = this->failIndex;
			_vvPPath.push_back(vPPath);
			continue;
		}
		clearBeforeData();

		auto initvd = this->findGreedInitVert(i);

		if (initvd < 0)
		{
			deg::conf_debug << " can 't find the init vertex " << std::endl;
			this->failIndex = -7;
			_vFailIndex.at(i) = this->failIndex;
			_vvPPath.push_back(vPPath);
			continue;
		}

		bgeo::STreeVert StreeInitVert;

		for (auto &it : this->m_path)
		{
			StreeInitVert.vPoint.push_back(it);
		}
		StreeInitVert.level = 0;
		boost::add_vertex(StreeInitVert, this->m_Stree);

		this->recursionPlan(initvd);

		// make the path vector to the spanning tree
		this->vPath2STree();
		if (failIndex == -10)
		{
			//return;
			this->failIndex = -7;
			_vFailIndex.at(i) = this->failIndex;
			_vvPPath.push_back(vPPath);
			continue;
		}

		this->STree2Path();
		_vvPPath.push_back(vPPath);
	}
	int p_dis = 99999;

	deg::conf_debug << "get the path " << std::endl;
	deg::conf_debug << "FailIndex Size is " << _vFailIndex.size() << std::endl;

	std::vector<std::vector<bgeo::DPoint>> v_pathTemp;
	for (size_t i = 0; i < _vFailIndex.size(); i++)
	{
		if (_vFailIndex.at(i) < 0)
		{
		}
		else
		{
			if (_vvPPath.at(i).empty())
			{

			}
			else
			{
				v_pathTemp.push_back(_vvPPath.at(i));
				auto dis = this->distancePath(_vvPPath[i]);
				if ( dis < p_dis)
				{
					vPPath = _vvPPath.at(i);					
					p_dis = dis;
					failIndex = 1;
				}

			}
		}
	}
	//auto vPathTempSize = v_pathTemp.size();
	//if ( vPathTempSize> 3)
	//{
	//	vPPath = v_pathTemp.at(vPathTempSize - 1);
	//}
	//vPPath = v_pathTemp.at(0);

	deg::conf_debug << "path planning is success" << std::endl;
	//std::cout << "wtf" << std::endl;
}

double Splan::distancePath(std::vector<bgeo::DPoint> const & _path)
{
	double sum_dis = 0;
	for (size_t i = 0; i < (_path.size()-1); i++)
	{
		auto dis = bg::distance(_path[i], _path[i + 1]);
		sum_dis += dis;
	}
	return sum_dis;
}




void Splan::GreedPlan(const int &initvd)
{
    // std::vector<size_t> m_pathIndex;
    //this->m_pathIndex.push_back(initvd);
    //std::vector<bgeo::DPoint> PathTem;

    if (this->m_disMap.empty())
    {
        //
        // distance map init failed
        return;
    }
    this->localGraphPathIndex.push_back(initvd);
    bgeo::DLineString pathTem;
    //pathTem.
    pathTem.push_back(this->localGraph[initvd].pnt);
    this->m_path.push_back(this->localGraph[initvd].pnt);

    bgeo::VertexDescriptor centreVertDes;
    size_t centreDir = pl::aicentre;
    std::vector<size_t> VcentreDir;
    VcentreDir.push_back(centreDir);
    std::vector<double> vdis;
    vdis.push_back(0);

    //vdis.push_back();
    size_t findNum = 0 ;
    do {
        centreVertDes = localGraphPathIndex.back();
        centreDir = pl::aicentre;
        do
        {
            //
            this->localGraph[centreVertDes].EdgeState = true;

            //当前位置

            std::vector<std::pair<bgeo::VertexDescriptor, size_t>> vNverts = getNeighbour(centreVertDes);

            //std::vector<double> Vdis;
            double min_dis = 9999;
            bgeo::VertexDescriptor nextVertDes;
            size_t nextDir;

            if(vNverts.empty())
            {
                break;
            }
            for(auto &it :  vNverts)
            {
                //mGrid[]it.first
                double disg;
                if(centreDir==it.second)
                {
                    disg = this->m_disMap[it.second];
                }
                else
                {
                    disg = this->m_disMap[it.second];
                }
                if(disg<min_dis)
                {
                    min_dis = disg;
                    nextVertDes = it.first;
                    nextDir = it.second;
                }
            }
            this->m_path.push_back(this->localGraph[nextVertDes].pnt);
            this->localGraphPathIndex.push_back(nextVertDes);
            centreDir = nextDir;
            centreVertDes = nextVertDes;
        } while (true);

        findNum ++;
    //        qDebug()<<findNum;
        if(findNum>10)
        {
            break;
        }
    }
    while (this->backFindVert());

}

///
/// \brief Splan::spanTreePlan
/// \param initvd init  vertex
/// \return  the branch index
///  the vPath and the
int Splan::spanTreePlan(const int &initvd)
{

    bgeo::VertexDescriptor centreVertDes;
    size_t centreDir = pl::aicentre;


    centreVertDes = initvd;
    std::vector<bgeo::DPoint> PathUnit;
    decltype(localGraphPathIndex) GraphPathIndexUnit;
    double pathDis = 0;
    double addDis = 0;
    do
    {
        PathUnit.push_back(this->localGraph[centreVertDes].pnt);
        GraphPathIndexUnit.push_back(centreVertDes);
        pathDis += addDis;

        //
        this->localGraph[centreVertDes].EdgeState = true;
		

        std::vector<std::pair<bgeo::VertexDescriptor, size_t>> vNverts = getNeighbour(centreVertDes);


        double min_dis = 9999;
        bgeo::VertexDescriptor nextVertDes;


        size_t nextDir;

        if(vNverts.empty())
        {
            break;
            //
            //return -1;
        }
        for(auto &it :  vNverts)
        {
            double disg;
            disg = this->m_disMap[it.second];

            if(centreDir==it.second)
            {
                disg = this->m_disMap[it.second];
            }
            else
            {
                disg = this->m_disMap[it.second]  +0.6;
            }

            if(disg<min_dis)
            {
                min_dis = disg;
                nextVertDes = it.first;
                nextDir = it.second;
            }
        }

        /// debug code ///
        //        std::vector<decltype(centreVertDes)> vvdes;
        //        for (auto  & it : vNverts)
        //         {
        //             vvdes.push_back(it.first);
        //         }
        //        auto vvdesIter= std::find(vvdes.begin(),vvdes.end(),centreVertDes);
        //        if (vvdesIter != vvdes.end())
        //        {
        //            qDebug()<<"wtf!@";
        //        }

        ///debug code end//
        ///

        //PathUnit.push_back(this->localGraph[nextVertDes].pnt);
        //GraphPathIndexUnit.push_back(nextVertDes);
        centreVertDes = nextVertDes;
        centreDir  =   nextDir;
        addDis = min_dis;
    } while (true);
    if(PathUnit.size()<2)
    {
        return -1;
    }
    //branch path queue
    vPath.push_back(PathUnit);
    //branch path index queue
    vGraphPathIndex.push_back(GraphPathIndexUnit);
    //brach path distacne
    this->vPathDis.push_back(pathDis);

    return (vPath.size()-1);
}

int Splan::treeFindVert(const size_t &vPathIndex)
{
    auto &Branch = this->vGraphPathIndex[vPathIndex];

    //std::reverse(Branch.begin(),Branch.end());
    //size_t i = Branch.size() - 1;
    size_t i = 0;
    std::vector<size_t> vIndex;
    for (auto & it  :Branch)
    {
        std::vector<std::pair<bgeo::VertexDescriptor, size_t>> vNverts = getNeighbour(it);

        if(vNverts.empty())
        {

        }
        else
        {
            this->recursionPlan(it);
            vIndex.push_back(i);
        }
        //i--;
        i++;
    }
    this->MapTree.insert(std::pair<size_t,std::vector<size_t>>(vPathIndex,vIndex));
    return -1;
}

int Splan::recursionPlan(const int &initvd)
{
    auto spanTreeMark = this->spanTreePlan(initvd);

//    qDebug()<<"spanTreeMark=="<<spanTreeMark;

    if(spanTreeMark<0)
    {
        return -1;
    }
    else
    {
        auto treeFindMark =  this->treeFindVert(spanTreeMark);
        if(treeFindMark < 0)
        {
            return -1;
        }
		return -1;
    }

}

void Splan::vPath2STree()
{
	auto it = this->MapTree.begin();
	while (it != this->MapTree.end())
	{
		vvTreeList.push_back(it->second);
		this->vTreeBoolean.push_back(false);
		it++;
	}
	if (this->vvTreeList.empty())
	{
		//起始点没有邻居
		this->failIndex = -10;
		return;
	}
    addSTreeBranch(0,0);
}

int Splan::addSTreeBranch(const int &vPathIndex,
                          bgeo::STreeVertexDescriptor const &StreeIndex)
{

    if(this->vvTreeList.at(vPathIndex).empty())
    {
        bgeo::STreeVert vertUnit;
        for(auto &it : vGraphPathIndex[vPathIndex])
        {
            //this->m_path.push_back(this->localGraph[it].pnt);
            vertUnit.vPoint.push_back(this->localGraph[it].pnt);
        }
        vTreeBoolean.at(vPathIndex) = true;
        vertUnit.level = this->m_Stree[StreeIndex].level + 1;
        vertUnit.leaf = true;
//        qDebug()<<" add the level is"<< vertUnit.level;

        boost::add_vertex(vertUnit,this->m_Stree);

        auto vertDes = boost::num_vertices(this->m_Stree) - 1;

        boost::add_edge(vertDes,StreeIndex,this->m_Stree);
        ///
        /// if it is the leaf node
        return -1;
    }

    auto &vTreeList = this->vvTreeList.at(vPathIndex);
    auto &GraphPathIndex = this->vGraphPathIndex[vPathIndex];
    auto &BranchPath  = this->vPath[vPathIndex];
    vTreeBoolean.at(vPathIndex) = true;



    auto endTra =  vTreeList.back();
    size_t ptimes = 0;
    bgeo::STreeVertexDescriptor vertDesLast;
    bgeo::STreeVertexDescriptor vertDes , rootDes;

    vertDes = StreeIndex;
    vertDesLast = StreeIndex;
    size_t trajectoryLast = 0;
    do
    {
        //vvTreeList.at()
        auto  trajectorySize = vTreeList.front();
        if(trajectoryLast!=trajectorySize)
        {
            bgeo::STreeVert vertUnit;
            for(size_t i = trajectoryLast ; i< trajectorySize; i ++)
            {
                vertUnit.vPoint.push_back(BranchPath.at(i));
            }
            if(ptimes ==0)
            {
                rootDes = StreeIndex;
            }
            else
            {
                rootDes = vertDesLast;
            }
            vertUnit.level = this->m_Stree[rootDes].level + 1;

//            qDebug()<<" add the level is"<< vertUnit.level;
            //add the vertex and  add the edge
            boost::add_vertex(vertUnit,this->m_Stree);

            vertDes = boost::num_vertices(this->m_Stree) - 1;
            vertDesLast = vertDes;
            boost::add_edge(rootDes,vertDes,this->m_Stree);
            ptimes++;
            trajectoryLast = trajectorySize;
        }

        auto nextIndex =GraphPathIndex.at(trajectorySize);

        size_t nextvPathIndex = 0;
        for(size_t i = 0 ; i < this->vvTreeList.size(); i++)
        {

            if (this->vTreeBoolean.at(i)== false)
            {

                if(vGraphPathIndex.at(i).front()==nextIndex)
                {
                    nextvPathIndex = i;
                    break;
                }
            }
        }

        this->addSTreeBranch(nextvPathIndex,vertDes);
        vTreeList.erase(vTreeList.begin());
    }
    while (!vTreeList.empty());

    bgeo::STreeVert vertUnit;



    for(size_t i = endTra ; i< BranchPath.size(); i ++)
    {
        //this->m_path.push_back(BranchPath.at(i));
        vertUnit.vPoint.push_back(BranchPath.at(i));
    }
    vertUnit.level = this->m_Stree[vertDesLast].level +1;
    vertUnit.leaf = true;
    boost::add_vertex(vertUnit,this->m_Stree);

    vertDes = boost::num_vertices(this->m_Stree) - 1;

    //vertDesLast = vertDes;
    boost::add_edge(vertDesLast,vertDes,this->m_Stree);


    return -1;
}

void Splan::STree2Path()
{
    auto StreeNum = boost::num_vertices(this->m_Stree);
    for(size_t i = 0; i< StreeNum; i++)
    {
        this->STreeBranchMap.push_back(false);
    }

    auto mapempty = [=](decltype(STreeBranchMap) a){
        auto iter = std::find(a.begin(),a.end(),false);
        if(iter == a.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    {



    }
    auto  wtfff = mapempty(STreeBranchMap);
    std::vector<bgeo::DPoint> PathTemp;

    auto wtf = findChildern(1);

    calVertDis(0);

    findSTreePath(0);

	deg::conf_debug <<" the path size is " << this->vPPath.size();

    //this->m_path.clear();
    //this->m_path  = this->vPPath;
//    qDebug()<<"wtf";
}

double Splan::calVertDis(const bgeo::STreeVertexDescriptor &index)
{
    double res;
    if(this->m_Stree[index].leaf)
    {
        m_Stree[index].dis = m_Stree[index].vPoint.size();
    }
    else
    {
        auto childernIndexs = findChildern(index);
        for(auto &it : childernIndexs)
        {
            calVertDis(it);
            m_Stree[index].dis += m_Stree[it].dis;
        }
    }
    res = m_Stree[index].dis;
    return res;
}

void Splan::findSTreePath(const bgeo::STreeVertexDescriptor &index)
{
    if(this->m_Stree[index].leaf)
    {
        this->vPPath.insert(vPPath.end(),m_Stree[index].vPoint.begin(),
                            m_Stree[index].vPoint.end());

        auto vpnt = m_Stree[index].vPoint;
        std::reverse(vpnt.begin(),vpnt.end());
        this->vPPath.insert(vPPath.end(),vpnt.begin(),
                            vpnt.end());
    }
    else
    {
        auto childernIndexs = findChildern(index);

        std::tuple<bgeo::STreeVertexDescriptor,double> IndexTDis;
        typedef std::tuple<bgeo::STreeVertexDescriptor,double> tupleIndex;
        std::vector<decltype(IndexTDis)> vtuple;
        for(auto & it :childernIndexs)
        {
            vtuple.push_back(std::make_tuple(it,m_Stree[it].dis));
        }

        std::function<bool(tupleIndex,tupleIndex)> compfunc = [=](tupleIndex a,tupleIndex b)
        {if(std::get<1>(a)<std::get<1>(b))
            {return true;}
            else
            { return false;}
        };

        std::sort(vtuple.begin(),vtuple.end(),compfunc);
        childernIndexs.clear();
        for(auto &it : vtuple)
        {
            childernIndexs.push_back(std::get<0>(it));
        }
        auto vpnt = m_Stree[index].vPoint;
        this->vPPath.insert(vPPath.end(),vpnt.begin(),
                            vpnt.end());
        for(auto &it : childernIndexs)
        {
            findSTreePath(it);
        }
        std::reverse(vpnt.begin(),vpnt.end());

        this->vPPath.insert(vPPath.end(),vpnt.begin(),
                            vpnt.end());

    }

}

std::vector<bgeo::STreeVertexDescriptor> Splan::findChildern(const bgeo::STreeVertexDescriptor &index)
{
    std::vector<bgeo::STreeVertexDescriptor> res;
    //       std::pair<bgeo::AdjacencyIterator, bgeo::AdjacencyIterator> neighbors =
    auto neighbors = boost::adjacent_vertices(index,this->m_Stree);
    for (auto ni = neighbors.first; ni != neighbors.second; ++ni)
    {
        if(m_Stree[index].level < m_Stree[*ni].level)
        {
            res.push_back(*ni);
        }
    }
    return res;
}


int Splan::tree2Path()
{
    auto it = this->MapTree.begin();
    while ( it != this->MapTree.end())
    {
        vvTreeList.push_back(it->second);
        this->vTreeBoolean.push_back(false);
        it++;
    }
    branch2Path(0);

    return -1;
}

int Splan::branch2Path(const size_t &vPathIndex)
{

    if(this->vvTreeList.at(vPathIndex).empty())
    {
        for(auto &it : vGraphPathIndex[vPathIndex])
        {
            this->m_path.push_back(this->localGraph[it].pnt);
        }
        vTreeBoolean.at(vPathIndex) = true;
        return -1;
    }

    auto &vTreeList = this->vvTreeList.at(vPathIndex);
    auto &GraphPathIndex = this->vGraphPathIndex[vPathIndex];
    auto &BranchPath  = this->vPath[vPathIndex];
    vTreeBoolean.at(vPathIndex) = true;

    auto endTra =  vTreeList.back();
    do
    {
        //vvTreeList.at()
        auto  trajectorySize = vTreeList.front();
        for(size_t i = 0 ; i< trajectorySize; i ++)
        {
            this->m_path.push_back(BranchPath.at(i));
        }
        auto nextIndex =GraphPathIndex.at(trajectorySize);

        size_t nextvPathIndex = 0;
        for(size_t i = 0 ; i < this->vvTreeList.size(); i++)
        {

            if (this->vTreeBoolean.at(i)== false)
            {

                if(vGraphPathIndex.at(i).front()==nextIndex)
                {
                    nextvPathIndex = i;
                    break;
                }
            }
        }

        branch2Path(nextvPathIndex);
        vTreeList.erase(vTreeList.begin());
    }
    while (!vTreeList.empty());

    for(size_t i = endTra ; i< BranchPath.size(); i ++)
    {
        this->m_path.push_back(BranchPath.at(i));
    }

    return -1;
}



void Splan::LawnPlan(const int &initvd)
{

}


bool Splan::backFindVert()
{
    //std::vector<size_t>

    std::vector<bgeo::VertexDescriptor> RverVpro;
    auto pathSize = this->localGraphPathIndex.size();
    //auto tempath = this->m_path;
    std::vector<bgeo::DPoint> tempath;
    for (auto & it : this->m_path)
    {
        tempath.push_back(it);
    }



    for (size_t i = 0; i < pathSize; i++)
    {
        RverVpro.push_back(localGraphPathIndex.at(pathSize - 1 - i));
    }

    if (RverVpro.size()>this->localGraphNum)
    {
        return false;
    }

    std::pair<bgeo::VertexIterator,bgeo::VertexIterator> vi = boost::vertices(this->localGraph);

    for ( auto vit = vi.first ; vit != vi.second ; vit++ )
    {
        bgeo::VertexDescriptor vd = *vit;
        bgeo::VertexProperty &vp = this->localGraph[vd];
        vp.QueueState = false;
        //vp.EdgeState = false;
    }

    bgeo::VertexDescriptor nextIndex = 0;
    size_t nextSize = 0;
    bool nextBoolean = false;
    for (size_t i = 0; i < RverVpro.size(); i++)
    {
        std::pair<bgeo::AdjacencyIterator, bgeo::AdjacencyIterator> neighbors =
                boost::adjacent_vertices(RverVpro.at(i),this->localGraph);

        for (auto ni = neighbors.first; ni != neighbors.second; ++ni)
        {
            if(this->localGraph[*ni].EdgeState == false)
            {
                nextSize = i;
                nextIndex = *ni;
                nextBoolean = true;
                break;
            }
        }
        if (nextBoolean)
        {
            break;
        }
    }

    if (nextBoolean)
    {
        for (size_t i = 0; i < nextSize; i++)
        {
            //this->m_path.push_back(*(tempPath.end() - 1 - i));
            //this->m_pathIndex.push_back(RverVpro.at(i));
            this->m_path.push_back(*(tempath.end() - 1 - i));
            this->localGraphPathIndex.push_back(RverVpro.at(i));
        }
        this->m_path.push_back(this->localGraph[nextIndex].pnt);
        this->localGraphPathIndex.push_back(nextIndex);
    }
    //qDebug() << nextIndex << endl;


    return nextBoolean;
}





int Splan::findInitVert()
{

    std::pair<bgeo::VertexIterator,bgeo::VertexIterator> _b2e_vi = boost::vertices(this->localGraph);

    double initDis = 10000;
    bgeo::VertexDescriptor initVd;
    bgeo::VertexProperty initVp;
    std::vector<bgeo::VertexDescriptor> vvdx, vvdy;
    std::vector<double> vdis;
    std::vector<double> vsortDis;
    std::vector<bgeo::VertexDescriptor> vdes;

    for(size_t i = 0 ; i< 10 ; i++)
    {
        vdis.push_back(9999);
    }

    for (auto vit = _b2e_vi.first ; vit != _b2e_vi.second ; vit++)
    {
        //bgeo::Graph::adjacency_list neighbourIt;
        bgeo::VertexDescriptor vd = *vit;
        bgeo::VertexProperty vp = this->localGraph[vd];
        auto dis = bg::distance(vp.pnt,this->m_startPnt);
        vdis.push_back(dis);
        if (dis<initDis)
        {
            initDis = dis;
            initVd = vd;
            initVp = vp;
        }
        vvdx.push_back(vp.pnt.x());
        vvdy.push_back(vp.pnt.y());
    }

    apl.getStartPnt(this->m_startPnt.x(),this->m_startPnt.y());
    apl.getTargetPnt(initVp.pnt.x(),initVp.pnt.y());
    auto aplboolean = apl.AstarPlan();
    if(aplboolean==true)
    {
        this->m_path.clear();
        this->m_path=apl.m_path;
        return initVd;
    }

    // X min
    initVd = std::min_element(vvdx.begin(),vvdx.end()) - vvdx.begin();
    apl.getTargetPnt(this->localGraph[initVd].pnt.x(),this->localGraph[initVd].pnt.y());
    aplboolean = apl.AstarPlan();

    if(aplboolean==true)
    {
        this->m_path.clear();
        this->m_path=apl.m_path;
        return initVd;
    }

    // X max
    initVd = std::max_element(vvdx.begin(),vvdx.end()) - vvdx.begin();
    apl.getTargetPnt(this->localGraph[initVd].pnt.x(),this->localGraph[initVd].pnt.y());
    aplboolean = apl.AstarPlan();

    if(aplboolean==true)
    {
        this->m_path.clear();
        this->m_path=apl.m_path;
        return initVd;
    }

    // y min
    initVd = std::min_element(vvdy.begin(),vvdy.end()) - vvdy.begin();
    apl.getTargetPnt(this->localGraph[initVd].pnt.x(),this->localGraph[initVd].pnt.y());
    aplboolean = apl.AstarPlan();

    if(aplboolean==true)
    {
        this->m_path.clear();
        this->m_path=apl.m_path;
        return initVd;
    }

    // y max
    initVd = std::min_element(vvdy.begin(),vvdy.end()) - vvdy.begin();
    apl.getTargetPnt(this->localGraph[initVd].pnt.x(),this->localGraph[initVd].pnt.y());
    aplboolean = apl.AstarPlan();

    if(aplboolean==true)
    {
        this->m_path.clear();
        this->m_path=apl.m_path;
        return initVd;
    }

    return -1;
}

int Splan::findGreedInitVert(int const &i_md)
{
    std::pair<bgeo::VertexIterator,bgeo::VertexIterator> _b2e_vi = boost::vertices(this->localGraph);
    // double initDis = 10000;
    bgeo::VertexDescriptor initVd;
    bgeo::VertexProperty initVp;
    //std::vector<bgeo::VertexDescriptor> vvdx, vvdy;
    //std::vector<double> vdis;
    //std::vector<bgeo::VertexDescriptor> vvdes;
    std::vector<std::pair<bgeo::VertexDescriptor,double>> sortDesDis;
    typedef std::pair<bgeo::VertexDescriptor,double> DESDIS;
    std::vector<std::pair<bgeo::VertexDescriptor,double>> sortDesY, sortDesX;

    for (auto vit = _b2e_vi.first ; vit != _b2e_vi.second ; vit++)
    {
        //bgeo::Graph::adjacency_list neighbourIt;
        bgeo::VertexDescriptor vd = *vit;
        bgeo::VertexProperty vp = this->localGraph[vd];
        auto dis = bg::distance(vp.pnt,this->m_startPnt);
        //vdis.push_back(dis);
        //vvdes.push_back(vd);
        sortDesDis.push_back(std::pair<bgeo::VertexDescriptor,double>(vd,dis));
        sortDesY.push_back(std::pair<bgeo::VertexDescriptor,double>(vd,vp.pnt.y()));
		sortDesX.push_back(std::pair<bgeo::VertexDescriptor, double>(vd, vp.pnt.x()));
    }
    //std::sort(vdis.begin(),vdis.end)
	 
    //compare the value  greater or smaller
	if (i_md > 4)
	{
		  auto maxlocal = boost::num_vertices(this->localGraph);

		  std::random_device rd;
		  std::mt19937 gen(rd());
		  std::uniform_int_distribution<> dis(0, maxlocal-1);

		  do
		  {
			  initVd = dis(gen);			  
			  std::cout << "initvd" << initVd << std::endl;
			  deg::conf_debug << "initvd" << initVd << std::endl;
		  } while (this->localGraph[initVd].Type != bgeo::vertType::WayVert);
		  
		  initVp = this->localGraph[initVd];

		  apl.getStartPnt(this->m_startPnt.x(), this->m_startPnt.y());
		  apl.getTargetPnt(initVp.pnt.x(), initVp.pnt.y());
		  auto aplboolean = apl.AstarPlan();
		  if (aplboolean == true)
		  {
			  this->m_path.clear();
			  this->m_path = apl.m_path;
			  //initVd = sortDesY.at(i).first;
			  deg::conf_debug << "initvd" << initVd << std::endl;
		  }

		  return initVd;

//		  return initVd;
	}
	
	std::function<bool(DESDIS, DESDIS)> compfunc;

	if(i_md%2)
	{
		compfunc = [=](DESDIS a, DESDIS b) {if (a.second<b.second) { return true; }
		else { return false; }
		};
	}
	else
	{
		compfunc = [=](DESDIS a, DESDIS b) {if (a.second>b.second) { return true; }
		else { return false; }
		};
	}
    

    std::sort(sortDesY.begin(),sortDesY.end(),compfunc);
    std::sort(sortDesDis.begin(),sortDesDis.end(),compfunc);
	std::sort(sortDesX.begin(), sortDesX.end(), compfunc);

    //auto vsortDis = vdis;
    //std::sort(vsortDis.begin(),vsortDis.end());
	size_t step = 1;

	switch (i_md%3)
	{
	case 1:
		for (size_t i = 0; i < sortDesY.size(); i++)
		{
			if (i>4)
			{
				break;
			}

			initVp = this->localGraph[sortDesY.at(i).first];

			if (this->localGraph[sortDesY.at(i).first].Type != bgeo::vertType::WayVert)
			{
				continue;
			}
			//this->localGraph[initVp]
			apl.getStartPnt(this->m_startPnt.x(), this->m_startPnt.y());
			apl.getTargetPnt(initVp.pnt.x(), initVp.pnt.y());
			auto aplboolean = apl.AstarPlan();
			if (aplboolean == true)
			{
				this->m_path.clear();
				this->m_path = apl.m_path;
				initVd = sortDesY.at(i).first;
				deg::conf_debug << "initvd" << initVd << std::endl;
				return initVd;
			}
			deg::conf_debug << "alpan failed   " << i << std::endl;
		}
	case 0:
		for (size_t i = 0; i < sortDesDis.size(); i += step)
		{
			initVp = this->localGraph[sortDesDis.at(i).first];

			if (this->localGraph[sortDesDis.at(i).first].Type != bgeo::vertType::WayVert)
			{
				continue;
			}

			apl.getStartPnt(this->m_startPnt.x(), this->m_startPnt.y());
			apl.getTargetPnt(initVp.pnt.x(), initVp.pnt.y());
			auto aplboolean = apl.AstarPlan();
			if (aplboolean == true)
			{
				this->m_path.clear();
				this->m_path = apl.m_path;
				//this->m_pathIndex
				initVd = sortDesDis.at(i).first;
				std::cout << "initvd" << initVd << std::endl;
				return initVd;
			}
			if (i > 5)
			{
				break;
			}
		}
	case 2:
		//
		for (size_t i = 0; i < sortDesX.size(); i++)
		{
			if (i>4)
			{
				break;
			}

			initVp = this->localGraph[sortDesX.at(i).first];
			apl.getStartPnt(this->m_startPnt.x(), this->m_startPnt.y());
			apl.getTargetPnt(initVp.pnt.x(), initVp.pnt.y());
			auto aplboolean = apl.AstarPlan();
			if (aplboolean == true)
			{
				this->m_path.clear();
				this->m_path = apl.m_path;
				initVd = sortDesX.at(i).first;
				std::cout << "initvd" << initVd << std::endl;
				return initVd;
			}

		}
		break;
	default:
		break;
	}





    return -1;
}

int Splan::findLawnInitVert()
{

    return 0;
}

std::vector<std::pair<bgeo::VertexDescriptor, size_t> > Splan::getNeighbour(const bgeo::VertexDescriptor &vd)
{
    std::vector<std::pair<bgeo::VertexDescriptor,size_t>> vRes;
    bgeo::VertexProperty &cvp = this->localGraph[vd];

    std::set<bgeo::VertexDescriptor> Svds;
    Svds.insert(vd);
    auto neighbour = boost::adjacent_vertices(vd,this->localGraph);

    for (auto neighbourIt = neighbour.first;  neighbourIt != neighbour.second ; neighbourIt++)
    {
         bgeo::VertexDescriptor lvd = *neighbourIt;
        bgeo::VertexProperty &lvp = this->localGraph[lvd];
        //this->localGraph[]
        size_t dir ;

        //if (this->localGraph[])
        if (lvp.EdgeState ==true)
        {
            continue;
        }

        auto c_x = cvp.pnt.x();
        auto c_y = cvp.pnt.y();
        auto l_x = lvp.pnt.x();
        auto l_y = lvp.pnt.y();


        const float EPSINON = 0.001;

        if(std::abs(c_y-l_y)<EPSINON)
        {

            if(std::abs(c_x-l_x)<EPSINON)
            {
                dir =  pl::aicentre;
                goto bindingPair;
            }

            if(c_x>l_x)
            {
                dir =  pl::aiLeft;
                goto bindingPair;
            }
            if(c_x<l_x)
            {
                dir =  pl::aiRight ;
                goto bindingPair;
            }
        }


        if(c_y>l_y)
        {

            if(std::abs(c_x-l_x)<EPSINON)
            {
                dir =  pl::aiBottom;
                goto bindingPair;
            }
            if(c_x>l_x)
            {
                dir =  pl::aiBottomLeft;
                goto bindingPair;
            }
            if(c_x<l_x)
            {
                dir =  pl::aiBottomRight ;
                goto bindingPair;
            }
        }

        if(c_y<l_y)
        {

            if(std::abs(c_x-l_x)<EPSINON)
            {
                dir =  pl::aiTop;
                goto bindingPair;
            }

            if(c_x>l_x)
            {
                dir =  pl::aiTopLeft;
                goto bindingPair;
            }
            if(c_x<l_x)
            {
                dir =  pl::aiTopRight ;
                goto bindingPair;
            }
        }

bindingPair:
        if(Svds.count(lvd)==0)
        {
            std::pair<bgeo::VertexDescriptor,size_t> pairUnit(lvd,dir);
            vRes.push_back(pairUnit);
            Svds.insert(lvd);
        }
    }

    return vRes;

}

std::vector<bgeo::VertexDescriptor> Splan::getNeighbourNoDir(const bgeo::VertexDescriptor &vd)
{

    std::vector<bgeo::VertexDescriptor> vRes;
    std::set<bgeo::VertexDescriptor> Svds;
    Svds.insert(vd);
    auto neighbour = boost::adjacent_vertices(vd,this->localGraph);

    for (auto neighbourIt = neighbour.first;  neighbourIt != neighbour.second ; neighbourIt++)
    {
        bgeo::VertexDescriptor lvd = *neighbourIt;
        bgeo::VertexProperty &lvp = this->localGraph[lvd];
        if (lvp.EdgeState ==true)
        {
            continue;
        }
        if(Svds.count(lvd)==0)
        {
            vRes.push_back(lvd);
            Svds.insert(lvd);
        }
    }
    return vRes;

}


}
