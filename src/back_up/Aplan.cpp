#include "Aplan.h"


namespace pl {


	ANode::ANode()
	{
	}

	ANode::~ANode()
	{
	}

	void ANode::caldisF()
	{
		disH = bg::distance(this->vertPnt.pnt, this->targetPnt);
		this->disF = this->disG + this->disH;
		//return disF;
	}
	void ANode::setdisG(double const &dval)
	{
		this->disH = dval;
	}

	ANode::ANode(bgeo::PointVert vert, bgeo::DPoint tar, double disg, int dir)
	{
		this->disG = disg;
		this->vertPnt = vert;
		this->targetPnt = tar;
		this->direction = dir;
		this->caldisF();
	}

	ANode::ANode(bgeo::PointVert vert, bgeo::DPoint tar, double disg, int dir, ob::gridIndex par)
	{
		this->disG = disg;
		this->parent = par;
		this->vertPnt = vert;
		this->targetPnt = tar;
		this->direction = dir;
		this->caldisF();
	}


	bool ANodeFunction(ANode a, ANode b)
	{
		auto af = a.getdisF();
		auto bf = b.getdisF();
		if (af < bf)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	Aplan::Aplan()
	{
		this->initDisMap();
	}


	Aplan::~Aplan()
	{

	}

	bool Aplan::initDisMap()
	{
		this->m_disMap.insert(Anchor2Dis(aiTop, 0.5));
		this->m_disMap.insert(Anchor2Dis(aiLeft, 0.5));
		this->m_disMap.insert(Anchor2Dis(aiRight, 0.5));
		this->m_disMap.insert(Anchor2Dis(aiBottom, 0.5));
		this->m_disMap.insert(Anchor2Dis(aiTopLeft, 0.707));
		this->m_disMap.insert(Anchor2Dis(aiTopRight, 0.707));
		this->m_disMap.insert(Anchor2Dis(aiBottomRight, 0.707));
		this->m_disMap.insert(Anchor2Dis(aiBottomLeft, 0.707));
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	//draw function

//	void Aplan::drawPath()
//	{
//		this->planDraw.qplot = this->qplot;
//		planDraw.LineString(this->m_path);
//	}

//	void Aplan::slowDraw()
//	{
//		this->planDraw.qplot = this->qplot;
//		planDraw.slowLine(this->m_path);
//	}

//	void Aplan::drawS2T()
//	{
//		QCPCurve *lineStringCurve = new QCPCurve(qplot->xAxis, qplot->yAxis);
//		QVector<QCPCurveData> lineStringCurveData;

//		lineStringCurveData.push_back(QCPCurveData(0, m_startPnt.x(), m_startPnt.y()));
//		lineStringCurveData.push_back(QCPCurveData(0, m_targetPnt.x(), m_targetPnt.y()));
//		lineStringCurve->data()->set(lineStringCurveData, false);

//		qplot->xAxis->setScaleRatio(qplot->yAxis);
//		QPen pen;
//		pen.setColor(Qt::GlobalColor::green);
//		pen.setWidth(2);
//		lineStringCurve->setPen(pen);
//        qplot->replot();
//    }

//    void Aplan::drawCloseList()
//    {
//        size_t i = 0;
//        for(auto &it : this->m_closeList)
//        {
//            QCPItemEllipse *circle = new QCPItemEllipse(this->qplot);
//            auto &pnt = it.second.vertPnt.pnt;
//            circle->topLeft->setCoords(pnt.x() - 0.25, pnt.y() + 0.25);
//            circle->bottomRight->setCoords(pnt.x() + 0.25, pnt.y() - 0.25);

//            i++;
//            qDebug()<<"i = "<<i;
//        }
//        this->qplot->replot();

//    }

	//
	////
	//////////////////////////////////////////////////////////////////////////

		bool Aplan::setGroupMode(bool const &grpMode)
		{
			this->groupMode= grpMode;
			return this->groupMode;
		}



	bool Aplan::init(double s_x, double s_y, double t_x, double t_y)
	{
		this->m_startPnt.x(s_x);
		this->m_startPnt.y(s_y);
		this->m_targetPnt.x(t_x);
		this->m_targetPnt.y(t_y);
		return false;
	}

	bool Aplan::loadMap(ob::Obmap  & map)
	{
		if (map.empty(ob::MapType::AggregationMap))
		{
			return false;
		}
		else
		{
			this->m_map = map;
			return true;
		}
	}
	bool Aplan::getStartPnt(double const & x, double const & y)
	{
		this->m_startPnt.x(x);
		this->m_startPnt.y(y);
		return false;
	}

	bool Aplan::getTargetPnt(double const & x, double const & y)
	{
		this->m_targetPnt.x(x);
		this->m_targetPnt.y(y);
		return false;
	}
	bool Aplan::target2Grid()
	{
		this->m_Tindex = this->m_map.pnt2Index(this->m_targetPnt, ob::MapType::AggregationMap);
		if ((m_Tindex.first == -1) && (m_Tindex.second == -1))
			//Target is in the obstacle
		{
            this->failIndex = -2;
			return false;
		}
		else
		{
			if (m_map.ATgrid[m_Tindex].type == bgeo::vertType::WayVert)
			{
				return true;
			}
			else
			{
				if(m_map.ATgrid[m_Tindex].type == bgeo::vertType::NearVert)
				{
					return true;
				}
				else
				{
					this->failIndex = -2;
					return false;
				}
			}
		}
	}
	bool Aplan::start2Grid()
	{
		this->m_Sindex = this->m_map.pnt2Index(this->m_startPnt, ob::MapType::AggregationMap);
		if ((m_Sindex.first == -1) && (m_Sindex.second == -1))
			//start point is in the obstacle
		{
            this->failIndex = -1;
			return false;
		}
		else
		{
			if (this->m_map.ATgrid[m_Sindex].type == bgeo::vertType::WayVert)
			{
				return true;
			}
			else
			{
				if(m_map.ATgrid[m_Sindex].type == bgeo::vertType::NearVert)
				{
					return true;
				}
				else
				{
					this->failIndex = -1;
					return false;
				}			
		}
	}
	}

	bool Aplan::AstarPlan()
	{
		this->m_path.clear();
		this->m_openSet.clear();
		this->m_openList.clear();

		this->m_closeList.clear();
		this->m_closeSet.clear();
		this->m_closeVect.clear();

		if ((target2Grid()) && (start2Grid()))
		{

			std::cout << "spnt.x = " << this->m_startPnt.x() << "	spnt.y = " << this->m_startPnt.y();
			std::cout << "sgrid.x = " << this->m_map.ATgrid[m_Sindex].pnt.x() << " sgrid.x = " << this->m_map.ATgrid[m_Sindex].pnt.y();

			std::cout << "tpnt.x = " << this->m_targetPnt.x() << "	tpnt.y = " << this->m_targetPnt.y();
			std::cout << "tgrid.x = " << this->m_map.ATgrid[m_Tindex].pnt.x() << " tgrid.x = " << this->m_map.ATgrid[m_Tindex].pnt.y();


			if (AstarSearch())
			{
				if (AstarPathFinder())
				{
					return true;
				}
				else
				{
                    this->failIndex = -4;
					return false;
				}
			}
			else
			{
                this->failIndex = -4;
				return false;
			}
			
		}
		else
		{
			return false;
		}
	}

    bool Aplan::getPath(std::vector<double> &vx, std::vector<double> &vy)
    {
        for(auto &it :this->m_path)
        {
            auto u_x = it.x();
            auto u_y = it.y();
            vx.push_back(u_x);
            vy.push_back(u_y);
        }
        return false;
    }

	bool Aplan::AstarSearch()
	{
		auto &grid = this->m_map.ATgrid;
		if(groupMode == true)
		{
			std::cout<<" plan in the group mode "<< std::endl;
			grid = this->m_map.GTgrid;
		}
		ANode sNode(grid[m_Sindex], m_targetPnt, 0, AnchorIndex::aicentre, m_Sindex);
        //m_openSet.insert(m_Sindex);
        m_openSet.push_back(m_Sindex);
		m_openList.push_back(sNode);
		size_t searchTimes = 0;
        size_t maxSearch = 10000;

        bool already_find = false;
        double extra_search_ratio = 0.3;
        size_t extra_search = 0;
        size_t extra_counter = 0;
        // qDebug()<<" TIndex.first = " <<m_Tindex.first <<" Tindex.second ="<< m_Tindex.second;

        while (!m_openList.empty())
		{
			std::vector<int> vdirIndex;
			auto aIndex = m_openList.front().vertPnt.PntIndex;
			auto PreDir = m_openList.front().direction;
            double currDis = m_openList.front().disG;

            // Move the first item of openList to closedList
            m_closeVect.push_back(m_openList.front());
            m_closeList.insert(mNode(m_openList.front().vertPnt.PntIndex, m_openList.front()));
            m_openSet.remove(ob::gridIndex{aIndex.first, aIndex.second});
            m_openList.pop_front();

            auto vIndex = getNeighbor(aIndex, vdirIndex);
            // qDebug()<<"aIndex.first = "<<aIndex.first <<" aIndex.second ="<<aIndex.second;


                /// the index vector
            //            vIndex

            /// the direction vector
            /// vdirIndex
			searchTimes++;
            if (searchTimes > this->maxSearhTimes)
			{
                //qDebug()<<"over the maxSearchTimes";
				std::cout<<"over the maxmaxSearchTimes"<<std::endl;
				goto Fcase;
			}
			size_t dirIndex = 0;
            //for (auto &it : vIndex)
            for (; dirIndex < vIndex.size(); ++dirIndex)
			{
                auto& it = vIndex[dirIndex];

                if (grid[it].type == bgeo::vertType::ShoulderVert ||
                    grid[it].type == bgeo::vertType::ObVert ||
					grid[it].type == bgeo::vertType::EdgeObVert)
                    continue;

                bool notInOpenSet = std::find(m_openSet.begin(), m_openSet.end(), it) == m_openSet.end();
                bool notInClosedList = (m_closeList.count(it) == 0);

                double disg = currDis + m_disMap[vdirIndex.at(dirIndex)];
                if (PreDir != vdirIndex.at(dirIndex)){
                    disg += 0.15;
                }
                if (grid[it].type == bgeo::vertType::NearVert) {
                    disg += 1;
                }
                if (notInOpenSet && notInClosedList)
				{

                    ANode u_node(grid[it], m_targetPnt, disg, vdirIndex.at(dirIndex), aIndex);
                    SortedAddToOpenList(u_node);
                    //m_openSet.insert(it);
                    m_openSet.push_back(it);
				}
                else
                {
                    if (!notInOpenSet) {
                        auto existed = std::find_if(m_openList.begin(), m_openList.end(), [&](const ANode& xx){
                            return xx.vertPnt.PntIndex.first == it.first &&
                                   xx.vertPnt.PntIndex.second == it.second;
                        });
                        if (disg < existed->disG) {
                            m_openList.erase(existed);

                            ANode u_node(grid[it], m_targetPnt, disg, vdirIndex.at(dirIndex), aIndex);
                            SortedAddToOpenList(u_node);
                        }
                    }
                    else {
                        auto existed = m_closeList.find(it);
                        if (disg < existed->second.disG) {
                            m_closeList.erase(existed);

                            ANode u_node(grid[it], m_targetPnt, disg, vdirIndex.at(dirIndex), aIndex);
                            SortedAddToOpenList(u_node);
                            //m_openSet.insert(it);
                            m_openSet.push_back(it);
                        }
                    }
                }
                //dirIndex++;
			}

			if ((aIndex.first == m_Tindex.first) && (aIndex.second == m_Tindex.second))
			{
                already_find = true;
                extra_search = (size_t)(searchTimes * extra_search_ratio);
//                            break;
			}
            if (already_find) {
                extra_counter++;
                if (searchTimes == maxSearch - 1 ||
                    extra_counter == extra_search){
                    break;
                }
            }
		}
		return true;

		Fcase:
		return false;
	}

	bool Aplan::AstarPathFinder()
	{
		std::stack<bgeo::DPoint> sDPoint;
		std::stack<int> sDirIndex;
		auto u_node = m_closeList[m_Tindex];
		sDPoint.push(u_node.vertPnt.pnt);
		sDirIndex.push(u_node.direction);

//		qDebug() << "u_first= " << u_node.vertPnt.PntIndex.first << " u_second " << u_node.vertPnt.PntIndex.second;

//		qDebug() << " u_x " << u_node.vertPnt.pnt.x() << " u_y " << u_node.vertPnt.pnt.y();

		auto spnt = this->m_map.ATgrid[m_Sindex].pnt;
		size_t successIndex = 0;
		do
		{
			successIndex++;
            if (successIndex>this->maxSearhTimes)
			{
				return false;
			}
			//qDebug() << "u_first= " << u_node.vertPnt.PntIndex.first<< " u_second " << u_node.vertPnt.PntIndex.second;
			//qDebug() << "p_first= " << u_node.parent.first << " p_second " << u_node.parent.second;
			//qDebug() << "s_first" << m_Sindex.first << "s_second" << m_Sindex.second;
			u_node = m_closeList[u_node.parent];
			sDPoint.push(u_node.vertPnt.pnt);
			sDirIndex.push(u_node.direction);
		} while (!bgeo::DPointEqual(u_node.vertPnt.pnt, spnt));
		std::vector<bgeo::DPoint> vpathTem;
		std::vector<int> vdirIndex;
		do
		{
			vpathTem.push_back(sDPoint.top());
			sDPoint.pop();
			vdirIndex.push_back(sDirIndex.top());
			sDirIndex.pop();
		} while (!sDPoint.empty());

		//m_path.push_back(m_startPnt);
		std::list<bgeo::DPoint> l_path;
		m_path.push_back(m_startPnt);
		for (size_t i = 1; i < (vdirIndex.size() - 1); i++)
		{
			if (vdirIndex.at(i) == vdirIndex.at(i + 1))
			{
			}
			else
			{
				m_path.push_back(vpathTem.at(i));
			}
		}
		m_path.push_back(vpathTem.back());

		this->m_map.Ring2Vline();

		
		
		return true;
	}

	//return ID
	int Aplan::shortenList(std::list<bgeo::DPoint> & ldpoint, int const & ID)
	{
		
		return 0;		
	}
	bool Aplan::AstarShorten()
	{
		std::vector<bgeo::DPoint> pathTemp;

		return false;
	}
	void Aplan::SortedAddToOpenList(ANode const & mNode)
	{
		if (!m_openList.empty())
		{
			if (mNode.disF < m_openList.front().disF)
			{
				m_openList.push_front(mNode);
				return;
			}
			if (mNode.disF >= m_openList.back().disF)
			{
				m_openList.push_back(mNode);
				return;
			}
			for (auto it = m_openList.begin(); it != m_openList.end(); it++)
			{
				if (mNode.disF < it->disF)
				{
					auto p = it;
					//p--;
					m_openList.insert(p, mNode);
					return;
				}
			}
		}
		m_openList.push_back(mNode);
	}
	std::vector<ob::gridIndex>  Aplan::getNeighbor(ob::gridIndex const &mindex)
	{
		auto &grid = this->m_map.ATgrid;

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
						vIndex.push_back(ob::gridIndex(i, j));
					}
				}
				//dirIndex++;
			}
		}
		return vIndex;
	}

	std::vector<ob::gridIndex> Aplan::getNeighbor(ob::gridIndex const &mindex, std::vector<int> &vdirIndex)
	{
		auto &grid = this->m_map.ATgrid;
		vdirIndex.clear();

		std::vector<ob::gridIndex> vIndex;
		size_t dirIndex = 0;
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
						vdirIndex.push_back(dirIndex);
						vIndex.push_back(ob::gridIndex(i, j));
					}
				}
				dirIndex++;
			}
		}
		return vIndex;
	}

}
