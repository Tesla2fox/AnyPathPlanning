#include "polygonob.h"
namespace ob {
	PolygonOb::PolygonOb()
	{

	}


	PolygonOb::PolygonOb(std::vector<double> d_1, std::vector<double> d_2, int GPSorLocal , int ObType)
	{
		switch (GPSorLocal) {
		case GPSPolygonOb:
		{

			//this->m_vect=
			this->m_vlat = d_1;
            this->m_vlon = d_2;
			m_GPS2local();
			break;
		}
		case LocalPolygonOb:
		{
			this->m_vecx = d_1;
			this->m_vecy = d_2;
			m_local2GPS();
			break;
		}
		default:
			break;
		}
		this->m_type = ObType;
		this->m_pntNum = this->m_vecx.size();
        for (std::size_t i = 0; i < m_pntNum; i++)
		{
			m_Vpnt.push_back(geo::Point(m_vecx.at(i), m_vecy.at(i)));
		}
	}

	//
	void PolygonOb::m_GPS2local()
	{
		m_vecx.resize(m_vlat.size());
		m_vecy.resize(m_vlat.size());
        for (std::size_t i = 0; i < this->m_vlat.size(); i++)
		{
			GPS2Local(m_vlat[i], m_vlon[i], 0, &m_vecx[i], &m_vecy[i], nullptr);
		}

	}
	void PolygonOb::m_local2GPS()
	{
		m_vlat.resize(m_vecx.size());
		m_vlon.resize(m_vecy.size());
        for (std::size_t i = 0; i < this->m_vlat.size(); i++)
		{
			GPS2Local(m_vlat[i], m_vlon[i], 0, &m_vecx[i], &m_vecy[i], nullptr);
		}
	}

	//引用了QT的类型
//	bool PolygonOb::DrawPolyOb(QCustomPlot  * Qgraph)
//	{
//		QCPCurve *ObCurve = new QCPCurve(Qgraph->xAxis, Qgraph->yAxis);
//		//QVector
//		QVector<QCPCurveData> ObCurveData;
//		for (size_t i = 0; i < this->m_pntNum; i++)
//		{
//			ObCurveData.push_back(QCPCurveData(i, this->m_vecx.at(i),this->m_vecy.at(i)));
//		}
//        //
//        ObCurve->data()->set(ObCurveData,false);
//		QPen pen;
//		pen.setStyle(Qt::SolidLine);
//		pen.setWidth(2);
//		switch (this->m_type)
//		{
//		case obHuge:
//		{
//			pen.setColor(Qt::GlobalColor::green);
//			break;
//		}
//		case obPigHole:
//		{
//			pen.setColor(Qt::GlobalColor::darkBlue);
//			break;
//		}
//		case obWood:
//		{
//			pen.setColor(Qt::GlobalColor::red);
//			break;
//		}
//		case obYang:
//		{
//			pen.setColor(Qt::GlobalColor::darkYellow);
//			break;
//		}
//		case obLittle:
//		{
//			pen.setColor(Qt::GlobalColor::darkGray);
//			break;
//		}
//		default:
//			break;
//		}
//		ObCurve->setPen(pen);
//		Qgraph->xAxis->setScaleRatio(Qgraph->yAxis);
//        ObCurve->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));

//		Qgraph->replot();
//		return true;
//	}

	int PolygonOb::ob2VPoint(std::vector<geo::Point> & Vpnt)
	{
		this->m_pntNum = this->m_Vpnt.size();
		switch (this->m_type)
		{
		//高台
		case obLittle:
		case obPigHole:
		{

            for (std::size_t i = 0; i < this->m_pntNum; i++)
			{
				geo::Point pntUnit;
				pntUnit.x = this->m_vecx.at(i);
				pntUnit.y = this->m_vecy.at(i);
				Vpnt.push_back(pntUnit);
			}
			break;
		}
		case obHuge:
		case obWood:
		case obYang:
		{
            for (std::size_t i = 0; i < (this->m_pntNum - 1); i++)
			{
				geo::Line unitLine(m_Vpnt.at(i), m_Vpnt.at(i + 1));

				unitLine.Line2VPoint(Vpnt, 0.5);
			}
			break;
		}

		default:
			break;
		}
		return this->m_pntNum;
	}
}
