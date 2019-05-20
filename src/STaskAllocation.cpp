
#include "ssconfig.hpp"
#include "gps2local.h"
#include "PointArray.h"
#include "STaskAllocation.h"
#include "Point.h"
#include <vector>
#include <algorithm>


namespace areaCut {

	using std::vector;
	struct fnStructx
	{
		bool operator()(Point A, Point B) { return (A.x < B.x); }
	}fnPointx;


	struct fnStructy
	{
		bool operator()(Point A, Point B) { return (A.y < B.y); }
	}fnPointy;

	bool  DebugBoolean = true;

	int STaskAllocation(vector<vector<Point>>& res, const vector<size_t> AgentAllocationRes, 
		const vector<vector<Point>> regionScale, 
		const int Size_regionScale, const int AgentNum)
	{
		std::ofstream conf_srh("xx_STaskAllocation.txt", std::ios::trunc);
		conf_srh.precision(11);

		int ORegionSize = Size_regionScale;

		conf_srh << "ORegionSize= " << ORegionSize << std::endl;

		if (ORegionSize < 1)
		{
			return -1;
			//表示输入的搜索区域数量小于1
		}

		if (ORegionSize == AgentNum)
		{
			for (size_t i = 0; i < AgentNum; i++)
			{
				auto _a_id = AgentAllocationRes[i];
				auto resUnit = regionScale[_a_id];
				res.push_back(resUnit);
			}
			return 1;
		}

		std::vector<size_t> VagArry;
		for (size_t i = 0; i < AgentNum; i++)
		{
			//AgentAllocationRes
			auto AgIter = std::find(VagArry.begin(), VagArry.end(), AgentAllocationRes[i]);

			conf_srh << "AgentAllocationRes " << i << " ==" << AgentAllocationRes[i] << std::endl;
			if (AgIter == VagArry.end())
			{
				VagArry.push_back(AgentAllocationRes[i]);
			}
		}

		if (VagArry.size() < Size_regionScale)
		{

			//存在一区域 没有被分配智能体
			return -2;
		}


		std::vector<std::vector<Point>> VregionIn = regionScale;
		std::vector<std::vector<Point>> VregionRes;
		//std::vector<Region4GPS> Vregion4GPS;//没有排序的输出区域坐标
		vector<Region4> Vregion4;
		vector<Region4> SVregion4;
		//std::vector<Region4GPS> SVregion4GPS; //排序之后的输出区域坐标

		double region_x, region_y;
		//for (size_t i = 0; i < ORegionSize; i++)
		//{
		//	std::vector<Point>  VregionPnt;
		//	conf_srh << "RegionInID == " << i << std::endl;
		//	conf_srh << "RegionInSize== " << regionScale[i].size << std::endl;

		//	for (size_t j = 0; j < regionScale[i].size; j++)
		//	{
		//		//换算点坐标
		//		Point RegionPnt;
		//		GPS2Local(regionScale[i].pts[j].lat, regionScale[i].pts[j].lon, 0,
		//			&RegionPnt.x, &RegionPnt.y, nullptr);
		//		VregionPnt.push_back(RegionPnt);

		//		conf_srh << "PointGPS Index" << j
		//			<< "  Region.lat  " << regionScale[i].pts[j].lat
		//			<< "  Region.lon  " << regionScale[i].pts[j].lon << std::endl;
		//		//(region_x,)
		//		conf_srh << "$$$$$$$$$$$$$$$$$$$$$" << std::endl;
		//		conf_srh << "PointLocal  " << j <<
		//			" PointLocal.x	" << RegionPnt.x
		//			<< " PointLocal.y " << RegionPnt.y << std::endl;
		//	}
		//	VregionIn.push_back(VregionPnt);
		//}

		std::vector<RegionMM> VregionMM;
		for (size_t i = 0; i < VregionIn.size(); i++)
		{

			auto largeX =
				(*std::max_element(VregionIn.at(i).begin(), VregionIn.at(i).end(), fnPointx)).x;
			auto smallX =
				(*std::min_element(VregionIn.at(i).begin(), VregionIn.at(i).end(), fnPointx)).x;

			auto largeY =
				(*std::max_element(VregionIn.at(i).begin(), VregionIn.at(i).end(), fnPointy)).y;
			auto smallY =
				(*std::min_element(VregionIn.at(i).begin(), VregionIn.at(i).end(), fnPointy)).y;
			conf_srh << "AddArea Index " << i << " largeX  " << largeX
				<< " smallX  " << smallX << std::endl;
			conf_srh << " largeY  " << largeY
				<< " smallY	" << smallY << std::endl;

			RegionMM regionMmUnit(largeX, smallX, largeY, smallY);

			VregionMM.push_back(regionMmUnit);
		}

		//计算输入区域中包含的智能体的数量
		for (size_t i = 0; i < AgentNum; i++)
		{
			(VregionMM.at(AgentAllocationRes[i])._m_AgentNum)++;
		}

		for (size_t i = 0; i < Size_regionScale; i++)
		{
			auto &InRegionAgentNum = VregionMM.at(i)._m_AgentNum;
			auto bais_x = VregionMM.at(i).max_x - VregionMM.at(i).min_x;
			auto bais_step_x = bais_x / InRegionAgentNum;
			for (size_t j = 0; j < InRegionAgentNum; j++)
			{
				RegionMM RegionUnit(VregionMM.at(i).min_x + (j + 1)*bais_step_x
					, VregionMM.at(i).min_x + j *bais_step_x
					, VregionMM.at(i).max_y
					, VregionMM.at(i).min_y
				);
				auto VregionPoint = RegionUnit.Square2Point();
				Region4 Re4Unit;
				Re4Unit._m_Vregion = VregionPoint;
				Re4Unit._m_AreaIndex = i;
				Vregion4.push_back(Re4Unit);
			}
		}

		SVregion4.resize(AgentNum);
		std::vector<size_t> VCountNum;
		VCountNum.resize(Size_regionScale);

		for (size_t i = 0; i < AgentNum; i++)
		{
			for (size_t j = 0; j < AgentNum; j++)
			{
				if (AgentAllocationRes[i] == Vregion4.at(j)._m_AreaIndex)
				{
					SVregion4.at(i) = Vregion4.at(j);
					SVregion4.at(i)._m_AgIndex = i;
					Vregion4.erase(Vregion4.begin() + j);
					break;
				}
			}
		}

		//转化为输出形式
		for (size_t i = 0; i < AgentNum; i++)
		{
			res.push_back(SVregion4.at(i)._m_Vregion);
		}
		conf_srh.close();
		return 1;

	}
}