#include "obmap.h"
#include <memory.h>
#include "xml/tinyxml.h"
#include "xml/tinystr.h"
#include "time.h"
#include <iostream>
//unix
#include <cstdlib>

namespace ob {
Obmap::Obmap()
{

    //设置栅格地图的工作范围
    mWsPoint1.x(-75);
    mWsPoint1.y(-80);
    mWsPoint3.x(95);
    mWsPoint3.y(15);

    auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
    auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

    //计算搜索栅格和集结栅格的最大行列数目

    //the max col and the max row
    this->m_MaxCol = ceil(bais_x / this->gridStep);
    this->m_MaxRow = ceil(bais_y / this->gridStep);

    //MapType::AggregationMap

    this->m_AMaxCol = ceil(bais_x / this->AgridStep);
    this->m_AMaxRow = ceil(bais_y / this->AgridStep);

}

void Obmap::addObRing(std::vector<double> const & vx, std::vector<double> const & vy)
{
	auto ringUnit = bgeo::v2Ring(vx, vy);
	m_vDRing.push_back(ringUnit);
}

void Obmap::setGridRange(double const & min_x, double const min_y, double const & max_x, double const & max_y)
{
	this->mWsPoint1.x(min_x);
	this->mWsPoint1.y(min_y);
	this->mWsPoint3.x(max_x);
	this->mWsPoint3.y(max_y);
}

/////////////////////////////////////////////////////////////////////////
///
///
///
///
///
///
///

/// 画图部分
//void Obmap::drawObRing()
//{
//    //this->mapDraw.qplot;
//    this->mapDraw.qplot = this->qplot;
//    for (size_t i = 0; i < this->m_vDRing.size(); i++)
//    {
//        mapDraw.Ring(m_vDRing.at(i));
//    }
//}

////画出路肩
//void Obmap::drawShoulder()
//{
//    this->mapDraw.qplot = this->qplot;
//    //size_t i = 0;
//    for (auto &it: vSegment)
//    {
//        mapDraw.segment(it);
//        //qDebug() << i++;
//    }

//}

////draw grid
//void Obmap::drawgrid(const int & SorA)
//{
//    this->mapDraw.qplot = this->qplot;

//    double halfStep;

//    //std::shared_ptr<gridMap> grid_ptr;

//    //grid_ptr->
//    gridMap &grid = this->Tgrid;
//    if (SorA==MapType::SearchMap)
//    {
//        //search mission
//        halfStep = this->gridStep / 2;
//    }
//    else
//    {
//        //
//        halfStep = this->AgridStep / 2;
//        grid = this->ATgrid;
//    }

//    for (auto &it : grid)
//    {
//        if (true)
//        {
//            QCPItemEllipse *circle = new QCPItemEllipse(this->qplot);
//            circle->topLeft->setCoords(it.second.pnt.x() - halfStep, it.second.pnt.y() + halfStep);
//            circle->bottomRight->setCoords(it.second.pnt.x() + halfStep, it.second.pnt.y() - halfStep);
//            QPen pen;
//            //if (it.second.type)
//            //{
//            //	pen.setColor(Qt::GlobalColor::darkMagenta);
//            //}
//            //else
//            //{
//            //	pen.setColor(Qt::GlobalColor::darkGreen);
//            //	QBrush brush;
//            //	brush.setColor(Qt::GlobalColor::cyan);
//            //	brush.setStyle(Qt::Dense1Pattern);
//            //	circle->setBrush(brush);
//            //}
//            switch (it.second.type)
//            {
//            case bgeo::vertType::WayVert:
//            {
//                pen.setColor(Qt::GlobalColor::darkMagenta);
//                break;
//            }
//            case bgeo::vertType::ObVert:
//            {
//                pen.setColor(Qt::GlobalColor::darkGreen);
//                QBrush brush;
//                brush.setColor(Qt::GlobalColor::cyan);
//                brush.setStyle(Qt::Dense1Pattern);
//                circle->setBrush(brush);
//                break;
//            }
//            case bgeo::vertType::EdgeObVert:
//            {
//                pen.setColor(Qt::GlobalColor::darkGreen);
//                QBrush brush;
//                brush.setColor(Qt::GlobalColor::green);
//                brush.setStyle(Qt::Dense1Pattern);
//                circle->setBrush(brush);
//                break;
//            }
//            case bgeo::vertType::NearVert:
//            {
//                pen.setColor(Qt::GlobalColor::darkRed);
//                QBrush brush;
//                brush.setColor(Qt::GlobalColor::darkRed);
//                brush.setStyle(Qt::Dense1Pattern);
//                circle->setBrush(brush);
//                break;
//            }
//            case bgeo::vertType::ShoulderVert:
//            {
//                pen.setColor(Qt::GlobalColor::green);
//                QBrush brush;
//                brush.setColor(Qt::GlobalColor::gray);
//                brush.setStyle(Qt::Dense1Pattern);
//                circle->setBrush(brush);
//                break;
//            }
//            default:
//                break;
//            }
//            circle->setPen(pen);
//        }
//        if (false)
//        {
//            QCPItemText *txt = new QCPItemText(this->qplot);
//            txt->position->setCoords(it.second.pnt.x(), it.second.pnt.y());
//            QString QSt_index = QString("%1-%2").arg(it.first.first).arg(it.first.second);
//            txt->setText(QSt_index);
//        }
//    }
//    qplot->replot();
//    //std::cout << "wtf" << std::endl;
//    qDebug() << "wtf";
//}

////draw the range of the workspace
//void Obmap::drawRange()
//{
//    this->mapDraw.qplot = this->qplot;
//    mapDraw.Ring(m_Range);
//}



//void Obmap::drawEdge()
//{
//    this->mapDraw.qplot = this->qplot;

//    std::pair<bgeo::EdgeIterator,bgeo::EdgeIterator> _b2e_ei = boost::edges(this->Tgraph);

//    for (auto eit = _b2e_ei.first; eit != _b2e_ei.second ; eit ++)
//    {
//        bgeo::EdgeDescriptor ed = *eit;
//        bgeo::VertexDescriptor sVertd = boost::source(ed, this->Tgraph);
//        bgeo::VertexDescriptor tVertd = boost::target(ed, this->Tgraph);

//        bgeo::VertexProperty &sVert = Tgraph[sVertd];
//        bgeo::VertexProperty &tVert = Tgraph[tVertd];

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

///
///draw  function end
///
///
///
///
///
////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//void Obmap::addOb(ob::PolygonOb obAdd)
//{
//    this->m_vPolyOb.push_back(obAdd);
//    this->m_ObNum = this->m_vPolyOb.size();
//}

//map to the search
bool Obmap::Map2grid()
{
//    std::vector<geo::Point> pntArry;
    std::vector<bgeo::DPoint> dpntArry;
    //for (auto & it : this->m_vPolyOb)
    //{
    //    it.ob2VPoint(pntArry);
    //}
    //for (size_t i = 0; i < pntArry.size(); i++)
    //{
    //    bgeo::DPoint dpnt(pntArry.at(i).x, pntArry.at(i).y);
    //    dpntArry.push_back(dpnt);
    //}
	using std::vector;
	auto ring2vsg = [](bgeo::DRing &B, vector<bgeo::DSegment> &vsg)
	{
		
		for (size_t i = 0; i < (B.size()-1); i++)
		{
			vsg.push_back(bgeo::DSegment(B.at(i), B.at(i + 1)));
		}
		vsg.push_back(bgeo::DSegment(B.back(), B.front()));
		return false;
	};

	vector<bgeo::DSegment> vDsg;
	for (auto &it : this->m_vDRing)
	{
		ring2vsg(it, vDsg);
	}

    auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
    auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

    //the max col and the max row
    this->m_MaxCol = ceil(bais_x / this->gridStep);
    this->m_MaxRow = ceil(bais_y / this->gridStep);

    bgeo::PointVert pntUnit;
    for (size_t i = 0; i < m_MaxCol; i++)
    {
        pntUnit.pnt = this->mWsPoint1;
        //auto &pntW= pntUnit.pnt;
        pntUnit.pnt.x(this->gridStep*i + pntUnit.pnt.x());
        for (size_t j = 0; j < m_MaxRow; j++)
        {
            pntUnit.pnt.y(this->gridStep*j + this->mWsPoint1.y());
            pntUnit.type = bgeo::vertType::WayVert;

            for (auto &it:this->m_vDRing)
            {
                auto _BWithIn = bg::within(pntUnit.pnt, it);
                if (_BWithIn)
                {
                    pntUnit.type = bgeo::vertType::ObVert;
                    goto insertPnt;
                }
            }
            for (auto &it : dpntArry)
            {
                auto dis = bg::distance(it, pntUnit.pnt);
                if (dis<(this->gridStep/2*0.5))
                {
                    pntUnit.type = bgeo::vertType::EdgeObVert;
                    goto insertPnt;
                }
            }

			for (auto &it : vDsg)
			{
				auto dis = bg::distance(pntUnit.pnt,it);
				if (dis<(this->gridStep))
				{
					pntUnit.type = bgeo::vertType::EdgeObVert;
					goto insertPnt;
				}
			}

            //for (auto &it : this->vSegment)
            //{
            //	double dis = bg::distance(pntUnit.pnt, it);
            //	if (dis < (this->gridStep/4))
            //	{
            //		pntUnit.type = bgeo::vertType::ShoulderVert;
            //		goto insertPnt;
            //	}
            //}


insertPnt:
            std::pair<size_t, size_t> pntIndex(i,j);
            pntUnit.PntIndex = pntIndex;
            Tgrid.insert(std::pair<std::pair<int, int>, bgeo::PointVert>(pntUnit.PntIndex, pntUnit));

        }
    }
    this->initSearchGridEdge();
    return false;
}


void Obmap::initSearchGridEdge()
{
    int i=0;
    for (auto & it : this->Tgrid)
    {
        auto vert_pro = bgeo::PointVert2PointVert(it.second);

        boost::add_vertex(vert_pro, this->Tgraph);
        std::pair<int,int> localIndex;
        localIndex=it.first;
        map2graph.insert(std::pair<std::pair<int,int>,int>(localIndex,i));
        graph2map.insert(std::pair<int,std::pair<int,int>>(i,localIndex));

//        qDebug()<<"i=="<<i;
//        qDebug()<<"localIndex.frist=="<<localIndex.first<<
//                  "     localIndex.second=="<<localIndex.second;
        i++;
    }
    //boost::add_edge()
    //std::cout << "wtf" << std::endl;
    //std::size_t i = 0;
    this->graphAdddge();
//    qDebug()<<"wtf";
}



//
bool Obmap::graphAdddge()
{
    std::pair<bgeo::VertexIterator,bgeo::VertexIterator> vi =boost::vertices(this->Tgraph);
    if(vi.first==vi.second)
    {
//        qDebug()<<"wtf";
    }
    else
    {
//        qDebug()<<"not equal";
    }
    std::size_t p = 0;
    for(bgeo::VertexIterator vit = vi.first ; vit != vi.second ; vit++ )
    {
        bgeo::VertexDescriptor vd =*vit;
        if(this->Tgraph[vd].Type==bgeo::vertType::WayVert)
        {
            auto localIndex  = graph2map[vd];
            auto vlocalIndex = getSearchNeighbor(localIndex);
            std::vector<int> vvd;
            for (auto &it :  vlocalIndex)
            {
                vvd.push_back(map2graph[it]);
            }

            for(auto &it : vvd)
            {
                if(this->Tgraph[it].EdgeState==false)
                {
                    bgeo::DSegment sg(this->Tgraph[it].pnt,this->Tgraph[vd].pnt);
                    if ( this->MapIntersection( sg ) )
                    {

                    }
                    else
                    {
                        bgeo::EdgeProperty ep;
                        ep.weight = bg::distance(Tgraph[vd].pnt,Tgraph[it].pnt);
                        boost::add_edge(it,vd,ep,this->Tgraph);
                    }
                }
            }
        }
        this->Tgraph[vd].EdgeState = true;
//        qDebug()<<"wtf"<<p;
        p++;
    }
    auto num_edges = boost::num_edges(this->Tgraph);
//    qDebug()<<"num_edges = = "<<num_edges;
    return false;
}

///
/// \brief Obmap::getSearchNeighbor
/// \param mindex
/// \return the grid which is not obstacle;
///
std::vector<ob::gridIndex> Obmap::getSearchNeighbor(ob::gridIndex const &mindex)
{
    //
    auto &grid = this->Tgrid;

    std::vector<ob::gridIndex> vIndex;


    //size_t dirIndex = 0;
    for (auto i = mindex.first - 1; i <= (mindex.first + 1); i++)
    {
        for (auto j = mindex.second - 1; j <= (mindex.second + 1); j++)
        {

            if (grid.count(ob::gridIndex(i, j)) == 1)
            {
                if ((i == mindex.first) && (j == mindex.second))
                {
                }
                else
                {
                    if (grid[gridIndex(i,j)].type==bgeo::vertType::WayVert)
                    {
                        vIndex.push_back(ob::gridIndex(i, j));
                    }
                }
            }
        }
    }
    return vIndex;
}

bool Obmap::MapIntersection(const bgeo::DSegment &sg)
{
    for(auto &it :this->vSegment)
    {
        if(bg::intersects(it,sg))
        {
            return true;
        }
    }
    return false;
}



bool Obmap::Map2Agrid()
{
   // std::vector<geo::Point> pntArry;
    std::vector<bgeo::DPoint> dpntArry;
    //for (auto & it : this->m_vPolyOb)
    //{
    //    it.ob2VPoint(pntArry);
    //}
    //for (size_t i = 0; i < pntArry.size(); i++)
    //{
    //    bgeo::DPoint dpnt(pntArry.at(i).x, pntArry.at(i).y);
    //    dpntArry.push_back(dpnt);
    //}

	using std::vector;
	auto ring2vsg = [](bgeo::DRing &B, vector<bgeo::DSegment> &vsg)
	{

		for (size_t i = 0; i < (B.size() - 1); i++)
		{
			vsg.push_back(bgeo::DSegment(B.at(i), B.at(i + 1)));
		}
		vsg.push_back(bgeo::DSegment(B.back(), B.front()));
		return false;
	};

	vector<bgeo::DSegment> vDsg;
	for (auto &it : this->m_vDRing)
	{
		ring2vsg(it, vDsg);
	}

    auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
    auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

    //最大行列
    this->m_AMaxCol = ceil(bais_x / this->AgridStep);
    this->m_AMaxRow = ceil(bais_y / this->AgridStep);

    bgeo::PointVert pntUnit;
    for (size_t i = 0; i < m_AMaxCol; i++)
    {
        pntUnit.pnt = this->mWsPoint1;
        //auto &pntW= pntUnit.pnt;
        pntUnit.pnt.x(this->AgridStep*i + pntUnit.pnt.x());
        for (size_t j = 0; j < m_AMaxRow; j++)
        {
            pntUnit.pnt.y(this->AgridStep*j + this->mWsPoint1.y());

            pntUnit.type = bgeo::vertType::WayVert;

            for (auto &it : this->m_vDRing)
            {
                auto _BWithIn = bg::within(pntUnit.pnt, it);
                if (_BWithIn)
                {
                    pntUnit.type = bgeo::vertType::ObVert;
                    goto insertPnt;
                }
            }
            for (auto &it : dpntArry)
            {
                auto dis = bg::distance(it, pntUnit.pnt);
                if (dis < (this->AgridStep / 2 * 0.8))
                {
                    pntUnit.type = bgeo::vertType::EdgeObVert;
                    goto insertPnt;
                }
            }

            for (auto &it :this->vSegment)
            {
                double dis = bg::distance(pntUnit.pnt, it);
                if (dis<(this->AgridStep))
                {
                    pntUnit.type = bgeo::vertType::ShoulderVert;
                    goto insertPnt;
                }
            }


			for (auto &it : vDsg)
			{
				auto dis = bg::distance(pntUnit.pnt, it);
				if (dis<(this->AgridStep))
				{
					pntUnit.type = bgeo::vertType::EdgeObVert;
					goto insertPnt;
				}
			}


            for (auto &it : dpntArry)
            {
                auto dis = bg::distance(it, pntUnit.pnt);
                if (dis < (this->AgridStep))
                {
                    pntUnit.type = bgeo::vertType::NearVert;
                    goto insertPnt;
                }
            }

insertPnt:
            std::pair<size_t, size_t> pntIndex(i, j);
            pntUnit.PntIndex = pntIndex;
            ATgrid.insert(std::pair<std::pair<int, int>, bgeo::PointVert>(pntUnit.PntIndex, pntUnit));
//            qDebug()<<"i=="<<i<<"j=="<<j;
        }
    }
    return false;
}
//bool Obmap::writeMapGrid()
//{
//    TiXmlDocument doc;
//    TiXmlDeclaration* decl = new TiXmlDeclaration("2.0", "", "");
//    doc.LinkEndChild(decl);
//    //  windows
//    //		SYSTEMTIME st = { 0 };
//    //		GetLocalTime(&st);
//    //      windows get the time
//    //NULL
//    //    auto sDay=std::to_string(st.wDay);
//    //    auto sMonth = std::to_string(st.wMonth);
//    //    auto sHour = std::to_string(st.wHour);
//
//    time_t tt=std::time(NULL);
//    std::tm *t=std::localtime(&tt);
//
//    auto sDay=std::to_string(t->tm_mday);
//    auto sMonth = std::to_string(t->tm_mon+1);
//    auto sHour = std::to_string(t->tm_hour);
//    std::string st_time = sMonth + "." + sDay +" hour:" +sHour;
//    const char * c_time = st_time.c_str();
//
//    TiXmlElement * time = new TiXmlElement("time");
//    doc.LinkEndChild(time);
//
//    TiXmlComment * commentTime = new TiXmlComment();
//    commentTime->SetValue(c_time);
//    time->LinkEndChild(commentTime);
//
//    auto d2c = [](const double &d) {char buf[200]; sprintf(buf, "%.10f", d); return buf; };
//
//
//    {
//        TiXmlElement * Sroot = new TiXmlElement("searchMap");
//        doc.LinkEndChild(Sroot);
//
//        TiXmlComment * comment = new TiXmlComment();
//        comment->SetValue("搜索的栅格地图");
//        Sroot->LinkEndChild(comment);
//
//        size_t i = 0;
//        std::pair<bgeo::VertexIterator,bgeo::VertexIterator> _b2e_vi = boost::vertices(this->Tgraph);
//        for (bgeo::VertexIterator vit = _b2e_vi.first ; vit != _b2e_vi.second ;   vit ++)
//        {
//            bgeo::VertexDescriptor vd =*vit;
//            bgeo::VertexProperty &vp = this ->Tgraph[vd];
//
//            TiXmlElement * vert = new TiXmlElement("Vert");
//            Sroot->LinkEndChild(vert);
//
//            vert->SetAttribute("first", vp.PntIndex.first);
//            vert->SetAttribute("second", vp.PntIndex.second);
//            //std::string str_x = std::to_string(it.second.pnt.x());
//            //const char * c_x = str_x.c_str();
//            //vert->SetAttribute("x", c_x);
//
//            //std::string str_y = std::to_string(it.second.pnt.y());
//            //const char * c_y = str_y.c_str();
//            //vert->SetAttribute("y", c_y);
//
//            double ulat, ulon;
//            Local2GPS(vp.pnt.x(), vp.pnt.y(), 0, &ulat, &ulon, nullptr);
//
//            //存入lat
//            //std::string str_lat = std::to_string(ulat);
//            //const char * c_lat = str_lat.c_str();
//
//            //unix
//
//            char buffer_lat[20];
//            gcvt(ulat,15,buffer_lat);
//            vert->SetAttribute("c_lat",buffer_lat);
//
//            char buffer_lon[20];
//            gcvt(ulon,15,buffer_lon);
//            vert->SetAttribute("c_lon",buffer_lon);
//
//
//            //const char * c_lat = d2c(ulat);
//
//            //vert->SetDoubleAttribute("c_lat", ulat);
//
//            //存入lon
//            //std::string str_lon = std::to_string(ulon);
//            //const char * c_lon = str_lon.c_str();
//            //const char * c_lon = d2c(ulon);
//            //vert->SetDoubleAttribute("c_lon", ulon);
//
//            vert->SetAttribute("type", vp.Type);
//            vert->SetAttribute("ID", vd);
//        }
//    }
//
//    {
//        TiXmlElement * Groot = new TiXmlElement("GraphEdge");
//        doc.LinkEndChild(Groot);
//
//        TiXmlComment * comment = new TiXmlComment();
//        comment->SetValue("SearchGraphEdge");
//        Groot->LinkEndChild(comment);
//
//
//        std::pair<bgeo::EdgeIterator,bgeo::EdgeIterator> _b2e_ei = boost::edges(this->Tgraph);
//
//        for (auto eit = _b2e_ei.first; eit != _b2e_ei.second ; eit ++)
//        {
//            bgeo::EdgeDescriptor ed = *eit;
//            bgeo::EdgeProperty &ep = this->Tgraph[ed];
//            bgeo::VertexDescriptor sVertd = boost::source(ed, this->Tgraph);
//            bgeo::VertexDescriptor tVertd = boost::target(ed, this->Tgraph);
//
//            bgeo::VertexProperty &sVert = Tgraph[sVertd];
//            bgeo::VertexProperty &tVert = Tgraph[tVertd];
//
//            TiXmlElement * edge = new TiXmlElement("Edge");
//            Groot->LinkEndChild(edge);
//
//            edge->SetAttribute("source",sVertd);
//            edge->SetAttribute("target",tVertd);
//
//
//            //unix
//            char buffer_wei[20];
//            gcvt(ep.weight,15,buffer_wei);
//            //vert->SetAttribute("c_lat",buffer_wei);
//
//            edge->SetAttribute("dis",buffer_wei);
//        }
//    }
//
//
//    {
//        TiXmlElement * Aroot = new TiXmlElement("aggregationMap");
//        doc.LinkEndChild(Aroot);
//
//        TiXmlComment * comment = new TiXmlComment();
//        comment->SetValue("集结的栅格地图");
//        Aroot->LinkEndChild(comment);
//
//        size_t i = 0;
//        for (auto &it : this->ATgrid)
//        {
//            TiXmlElement * vert = new TiXmlElement("Vert");
//            Aroot->LinkEndChild(vert);
//            vert->SetAttribute("first", it.second.PntIndex.first);
//            vert->SetAttribute("second", it.second.PntIndex.second);
//            //std::string str_x = std::to_string(it.second.pnt.x());
//            //const char * c_x = str_x.c_str();
//            //vert->SetAttribute("x", c_x);
//
//            //std::string str_y = std::to_string(it.second.pnt.y());
//            //const char * c_y = str_y.c_str();
//            //vert->SetAttribute("y", c_y);
//
//
//            double ulat, ulon;
//            Local2GPS(it.second.pnt.x(), it.second.pnt.y(), 0, &ulat, &ulon, nullptr);
//
//            //            //存入lat
//            //            const char * c_lat = d2c(ulat);
//            //            vert->SetAttribute("c_lat", c_lat);
//
//            //            //存入lon
//            //            const char * c_lon = d2c(ulon);
//            //            vert->SetAttribute("c_lon", c_lon);
//
//            //unix
//
//            char buffer_lat[20];
//            gcvt(ulat,15,buffer_lat);
//            vert->SetAttribute("c_lat",buffer_lat);
//
//            char buffer_lon[20];
//            gcvt(ulon,15,buffer_lon);
//            vert->SetAttribute("c_lon",buffer_lon);
//
//
//            vert->SetAttribute("type", it.second.type);
//            vert->SetAttribute("ID", i++);
//        }
//    }
//    {
//        TiXmlElement * Droot = new TiXmlElement("DebugMode");
//        doc.LinkEndChild(Droot);
//
//        TiXmlComment * comment = new TiXmlComment();
//        comment->SetValue("debug mode ");
//        Droot->LinkEndChild(comment);
//
//    }
//
//    doc.SaveFile("OBC.xml");
//
//    return false;
//}

//bool Obmap::loadMapGrid(const char *pFilename)
//{
//    TiXmlDocument doc(pFilename);
//    std::cout<<"create a doc "<<std::endl;
//    
//    bool loadOkay = doc.LoadFile();
//
//    if (loadOkay)
//    {
//        std::cout<<" the map load success"<<std::endl;
//        //获取根节点元素
//        TiXmlElement *RootElement = doc.RootElement();
//        //load search map;
//        {
//            RootElement = RootElement->NextSiblingElement();
//
//            TiXmlElement *vert = RootElement->FirstChildElement();
//
//            for (vert; vert; vert = vert->NextSiblingElement())
//            {
//                auto e_first = std::atoi(vert->Attribute("first"));
//                auto e_second = std::atoi(vert->Attribute("second"));
//                //double e_x = std::atof(vert->Attribute("x"));
//                //double e_y = std::atof(vert->Attribute("y"));
//                double e_x, e_y;
//                int e_type = std::atoi(vert->Attribute("type"));
//                int e_ID = std::atoi(vert->Attribute("ID"));
//
//                double e_lat = std::atof(vert->Attribute("c_lat"));
//                double e_lon = std::atof(vert->Attribute("c_lon"));
//
//                GPS2Local(e_lat, e_lon, 0, &e_x, &e_y, nullptr);
//
//                bgeo::PointVert pntUnit;
//                pntUnit.PntIndex.first = e_first;
//                pntUnit.PntIndex.second = e_second;
//                pntUnit.pnt.x(e_x);
//                pntUnit.pnt.y(e_y);
//                pntUnit.type = e_type;
//
//                bgeo::VertexProperty vpro;
//                vpro.EdgeState = false;
//                vpro.index = e_ID;
//                vpro.pnt.x(e_x);
//                vpro.pnt.y(e_y);
//                vpro.Type = e_type;
//                vpro.PntIndex.first =e_first;
//                vpro.PntIndex.second = e_second;
//
//                boost::add_vertex(vpro,this->Tgraph);
//                Tgrid.insert(std::pair<std::pair<int, int>, bgeo::PointVert>(pntUnit.PntIndex, pntUnit));
//
//
//            }
//        }
//        std::cout<<"the search map vertex has been load"<<std::endl;
//        //load searchEdge
//        {
//            RootElement = RootElement->NextSiblingElement();
//
//            TiXmlElement *vert = RootElement->FirstChildElement();
//
//            for (vert; vert; vert = vert->NextSiblingElement())
//            {
//                bgeo::EdgeProperty ep;
//                ep.weight = std::atof(vert->Attribute("dis"));
//                auto s_index = std::atoi(vert->Attribute("source"));
//                auto t_index = std::atoi(vert->Attribute("target"));
//                boost::add_edge(s_index,t_index,ep,this->Tgraph);
//            }
//
//        }
//        std::cout<<"the search map edge has been load"<<std::endl;
//
//        //load AggregationMap
//        {
//            RootElement = RootElement->NextSiblingElement();
//
//            TiXmlElement *vert = RootElement->FirstChildElement();
//
//            for (vert; vert; vert = vert->NextSiblingElement())
//            {
//                auto e_first = std::atoi(vert->Attribute("first"));
//                auto e_second = std::atoi(vert->Attribute("second"));
//                //double e_x = std::atof(vert->Attribute("x"));
//                //double e_y = std::atof(vert->Attribute("y"));
//                double e_x, e_y;
//                int e_type = std::atoi(vert->Attribute("type"));
//                int e_ID = std::atoi(vert->Attribute("ID"));
//
//
//                double e_lat = std::atof(vert->Attribute("c_lat"));
//                double e_lon = std::atof(vert->Attribute("c_lon"));
//
//                GPS2Local(e_lat, e_lon, 0, &e_x, &e_y, nullptr);
//
//
//                bgeo::PointVert pntUnit;
//                pntUnit.PntIndex.first = e_first;
//                pntUnit.PntIndex.second = e_second;
//                pntUnit.pnt.x(e_x);
//                pntUnit.pnt.y(e_y);
//                pntUnit.type = e_type;
//                this->ATgrid.insert(std::pair<std::pair<int, int>, bgeo::PointVert>(pntUnit.PntIndex, pntUnit));
//            }
//        }
//
//        std::cout<<"the aplan map has been load"<<std::endl;
//        //load the group mode Map;
//
//        {
//            RootElement = RootElement->NextSiblingElement();
//
//            TiXmlElement *vert = RootElement->FirstChildElement();
//
//            for (vert; vert; vert = vert->NextSiblingElement())
//            {
//                auto e_first = std::atoi(vert->Attribute("first"));
//                auto e_second = std::atoi(vert->Attribute("second"));
//                //double e_x = std::atof(vert->Attribute("x"));
//                //double e_y = std::atof(vert->Attribute("y"));
//                double e_x, e_y;
//                int e_type = std::atoi(vert->Attribute("type"));
//                int e_ID = std::atoi(vert->Attribute("ID"));
//
//
//                double e_lat = std::atof(vert->Attribute("c_lat"));
//                double e_lon = std::atof(vert->Attribute("c_lon"));
//
//                GPS2Local(e_lat, e_lon, 0, &e_x, &e_y, nullptr);
//
//
//                bgeo::PointVert pntUnit;
//                pntUnit.PntIndex.first = e_first;
//                pntUnit.PntIndex.second = e_second;
//                pntUnit.pnt.x(e_x);
//                pntUnit.pnt.y(e_y);
//                pntUnit.type = e_type;
//                this->GTgrid.insert(std::pair<std::pair<int, int>, bgeo::PointVert>(pntUnit.PntIndex, pntUnit));
//            }
//        }
//
//        std::cout<<"the group map has been load"<<std::endl;
//
//        return true;
//    }
//    else
//    {
//        std::cout<<" the map load failed "<<std::endl;
//        return false;
//    }
//}
gridIndex Obmap::pnt2Index(bgeo::DPoint const & pnt, int const &type)
{

    gridIndex rindex;
    rindex.first = -1;
    rindex.second = -1;

	gridIndex initIndex;
	initIndex.first = 0;
	initIndex.second = 0;

	  double _i_x = this->ATgrid[initIndex].pnt.x();
	  double  _i_y = this->ATgrid[initIndex].pnt.y();
    if (pnt.y()<_i_y)
    {
        return rindex;
    }
    if (pnt.x()<_i_x)
    {
        return rindex;
    }
    auto bais_x = pnt.x() - _i_x;
    auto bais_y = pnt.y() - _i_y;
    double step;
    if (type== MapType::AggregationMap)
    {
        step = this->AgridStep;
        bais_x = bais_x - step / 2;
        bais_y = bais_y - step / 2;
        auto p_col = ceil(bais_x / step);
        auto p_row = ceil(bais_y / step);

        if (p_col>this->m_AMaxCol)
        {
            return rindex;
        }
        if (p_row>this->m_AMaxRow)
        {
            return rindex;
        }
        rindex.first = p_col;
        rindex.second = p_row;
    }
    else
        //MapType::SearchMap
    {
        step = this->gridStep;
        auto p_col = ceil(bais_x / step);
        auto p_row = ceil(bais_y / step);

        if (p_col > this->m_MaxCol)
        {
            return rindex;
        }
        if (p_row > this->m_MaxRow)
        {
            return rindex;
        }


        rindex.first = p_col;
        rindex.second = p_row;
    }
    return rindex;

}


//bool Obmap
bool Obmap::empty(int const & t)
{
    if (t==MapType::AggregationMap)
    {
        return this->ATgrid.empty();
    }
    //MapType::SearchMap
    else
    {
        return this->Tgrid.empty();
    }
}


bool Obmap::intersects(bgeo::DLineString  &line)
{
    for (auto &it : this->vline)
    {
        if (bg::intersects(line, it))
        {
            return true;
        }
    }
    return false;
}
void Obmap::Ring2Vline()
{
    this->vline.clear();
    for (auto &it: this->m_vDRing)
    {
        for (size_t i = 0; i < (it.size()-1); i++)
        {
            bgeo::DLineString lineUnit;
            lineUnit.push_back(it.at(i));
            lineUnit.push_back(it.at(i + 1));
            this->vline.push_back(lineUnit);
        }
    }
    vline.size();
}

void Obmap::addShoulder(std::vector<double> vpx, std::vector<double> vpy, std::vector<double> vqx,std::vector<double> vqy)
{
    this->vSegment.clear();

    for (size_t i = 0; i < vpx.size(); i++)
    {
        bgeo::DPoint ptp(vpx.at(i), vpy.at(i));
        bgeo::DPoint ptq(vqx.at(i), vqy.at(i));
        bgeo::DSegment segmentUnit(ptp,ptq);
        this->vSegment.push_back(segmentUnit);
    }


}

bool Obmap::setOb(double const &ob_x, double  const &ob_y)
{

    bgeo::DPoint obPnt;
    obPnt.x(ob_x);
    obPnt.y(ob_y);

    auto centreObIndex =this->pnt2Index(obPnt,MapType::AggregationMap);

  /*  std::cout<< " the cenTreObIndex .first "<<  centreObIndex.first
    <<" the cenTreObIndex .second "<<centreObIndex.second << std::endl;
*/
    auto & grid = this->ATgrid;

    for (auto i = centreObIndex.first - 4; i <= (centreObIndex.first + 4); i++)
    {
        for (auto j = centreObIndex.second - 4; j <= (centreObIndex.second + 4); j++)
        {

            if (grid.count(ob::gridIndex(i, j)) == 1)
            {
                grid[gridIndex(i,j)].type = bgeo::vertType::ObVert;
           //     std::cout<< "i = "<<i << "   j = "<< j <<std::endl;
            }
        }
    }

    auto &Ggrid = this->GTgrid;

    for (auto i = centreObIndex.first - 4; i <= (centreObIndex.first + 4); i++)
    {
        for (auto j = centreObIndex.second - 4; j <= (centreObIndex.second + 4); j++)
        {

            if (Ggrid.count(ob::gridIndex(i, j)) == 1)
            {
                Ggrid[gridIndex(i,j)].type = bgeo::vertType::ObVert;
             //   std::cout<< "i = "<<i << "   j = "<< j <<std::endl;
            }
        }
    }

    return false;
}


Obmap MainMap;
}
