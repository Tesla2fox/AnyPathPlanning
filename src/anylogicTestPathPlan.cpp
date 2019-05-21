//#include<iostream>
//#include <fstream>
//#include <thread>
//#include "ssconfig.hpp"
//#include "gps2local.h"
//#include <string>
//#include "CenPathPlanning.h"
//
//#define SUM_AGENT 4
//#define OB_NUM_TEST 20
//
//using namespace std;
//
//int main(void) {
//	//测试DLL
//	std::string SfileName = "D:\\qt_code\\multiPlan\\data\\OBC.xml";
//
//	//const char * CfileName =SfileName.c_str();
//
//	int len = SfileName.length();
//
//	auto CfileName = SfileName.c_str();
//	//auto CfileName = (char *)malloc((len + 1)*sizeof(char));
//
//	auto InitMark = InitPathPlanning(CfileName);
//
//
//
//	//PathInfo pathInfoTest;
//	PointTask targetLocation;
//	Local2GPS(-10, -10, 0, &targetLocation.target.lat, &targetLocation.target.lon, 0);
//	targetLocation.taskType = 2;
//	//设置目标点坐标 
//
//	PointArraryTask PntTsk;
//	PntTsk.size = SUM_AGENT;
//	double PntTskx[SUM_AGENT], PntTsky[SUM_AGENT];
//	double PntTsk_lon[SUM_AGENT], PntTsk_lat[SUM_AGENT];
//	PointGPS pnt_prt[4];
//	PntTsk.pts = pnt_prt;
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		Local2GPS(20, -40, 0, &PntTsk_lat[i], &PntTsk_lon[i], 0);
//		Local2GPS(18.2971639956, -8.01480965985, 0, &PntTsk_lat[i], &PntTsk_lon[i], 0);
//		Local2GPS(9.27638455867, 5.20820361217, 0, &PntTsk_lat[i], &PntTsk_lon[i], 0);
//
//		//9.27638455867, 5.20820361217
//		PntTsk.pts[i].lat = PntTsk_lat[i];
//		PntTsk.pts[i].lon = PntTsk_lon[i];
//		//PntTsk.pts[i].lat = 39.96277416;
//		//PntTsk.pts[i].lon = 116.30494919;
//
//		//PntTsk.pts[i].lat = 39.96277416;
//		//PntTsk.pts[i].lon = 116.30494919;
//		PntTsk.pts[i].lat = 39.96260192;
//		PntTsk.pts[i].lon = 116.30420096;
//
//	}
//	PntTsk.taskType = 1;
//	AgentInfo currentLocation;
//	currentLocation.agent.size = SUM_AGENT;
//	double currentLocationx[SUM_AGENT], currentLocationy[SUM_AGENT];
//	double currentLocation_lon[SUM_AGENT], currentLocation_lat[SUM_AGENT];
//	//currentLocation.agentID = 4;
//
//	//currentLocation.agentID = 10001;
//
//	currentLocationx[0] = -10;
//	currentLocationx[1] = -10;
//	currentLocationx[2] = -30;
//	currentLocationx[3] = -20;
//
//	currentLocationy[0] = -20;
//	currentLocationy[1] = -10;
//	currentLocationy[2] = -20;
//	currentLocationy[3] = -40;
//
//	PointGPS p_location[4];
//
//	currentLocation.agent.pts = p_location;
//	for (size_t i = 0; i < 4; i++)
//	{
//		Local2GPS(currentLocationx[i], currentLocationy[i], 0, &currentLocation_lat[i], &currentLocation_lon[i], 0);
//		currentLocation.agent.pts[i].lon = currentLocation_lon[i];
//		currentLocation.agent.pts[i].lat = currentLocation_lat[i];
//		currentLocation.agent.pts[i].lat = 39.96277416 ;
//		currentLocation.agent.pts[i].lon = 116.30494919 ;
//
//		currentLocation.agent.pts[i].lat = 39.96294477;
//		currentLocation.agent.pts[i].lon = 116.3048255;
//
//
//		currentLocation.agent.pts[i].lat = 39.96254491;
//		currentLocation.agent.pts[i].lon = 116.30405573;
//
//	}
//
//	//currentLocation.agentID = 10001;
//	//currentLocation.agent.ID = 10002;
//	long agentIDAry[4];
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		agentIDAry[i] = 10000 + i;
//	}
//
//	currentLocation.agent.ID = agentIDAry;
//	int GroupMode = false;
//	GroupMode = 1;
//
//	double pathLength[4] = { 0,1,2,3 };
//	//PathInfo *res=new PathInfo;
//	PathInfo res[SUM_AGENT];
//	PointGPS p_res[4][9000];
//	//PointArraryEx agent_res1[100];
//	//res->p_path.pts = p_res;
//	for (size_t i = 0; i < SUM_AGENT; i++)
//	{
//		res[i].p_path.pts = p_res[i];
//	}
//	//res->
//	int taskType = 1;//1=同时
//					 //0=分时
//					 //	
//	targetLocation.taskType = 1;
//
//	humanPathInfo hmArray[SUM_AGENT];
//	humanPathInfo humanpathUnit;
//
//	PointGPS p_wayGPS[10], p_avoidGPS[10];
//
//	humanpathUnit.way_Point.pts = p_wayGPS;
//	humanpathUnit.avoid_Point.pts = p_avoidGPS;
//
//	double humanpathUnit_way_lon[10];
//	double humanpathUnit_way_lat[10];
//	Local2GPS(40, -35, 0, &humanpathUnit_way_lat[0], &humanpathUnit_way_lon[0], 0);
//
//
//	humanpathUnit.way_Point.pts[0].lon = humanpathUnit_way_lon[0];
//	humanpathUnit.way_Point.pts[0].lat = humanpathUnit_way_lat[0];
//	//humanpathUnit.way_lat = humanpathUnit_way_lat;
//	//humanpathUnit.size_wayPoint = 1;
//	humanpathUnit.way_Point.size = 1;
//
//
//	double humanpathUnit_avoid_lon[10];
//	double humanpathUnit_avoid_lat[10];
//
//	Local2GPS(-30, -20, 0, &humanpathUnit_avoid_lat[0], &humanpathUnit_avoid_lon[0], 0);
//
//	humanpathUnit.avoid_Point.pts[0].lon = humanpathUnit_avoid_lon[0];
//	humanpathUnit.avoid_Point.pts[0].lat = humanpathUnit_avoid_lat[0];
//
//	humanpathUnit.avoid_Point.size = 0;
//
//	int mistakeType;
//
//	for (size_t i = 0; i < SUM_AGENT; i++)
//	{
//		hmArray[i] = humanpathUnit;
//	}
//
//	//mistakeType = centralizedMotionPlanning(res
//	//	, PntTsk,
//	//	currentLocation,
//	//	0,
//	//	hmArray);
//
//	mistakeType = 0;
//	double x_path_Gps;
//	double y_path_Gps;
//
//	if (mistakeType > 0)
//	{
//		ofstream conf_path("Path_message.txt", ios::trunc);
//		conf_path << "SUM= " << SUM_AGENT << endl;
//
//		for (size_t i = 0; i < SUM_AGENT; i++)
//		{
//
//			std::cout << "num=" << i << " " << res[i].p_path.size << endl;
//
//			conf_path << "num= " << res[i].p_path.size << endl;
//
//			for (size_t w = 0; w < res[i].p_path.size; w++)
//			{
//
//				GPS2Local(res[i].p_path.pts[w].lat, res[i].p_path.pts[w].lon, 0, &x_path_Gps, &y_path_Gps, 0);
//				conf_path << "x= " << x_path_Gps << endl;
//				conf_path << "y= " << y_path_Gps << endl;
//				std::cout << "x=" << x_path_Gps << std::endl;
//				std::cout << "y=" << y_path_Gps << std::endl;
//			}
//		}
//		conf_path.close();
//
//	}
//	std::cout << "this is main function centralizedMotionPlanning" << std::endl;
//
//
//	PointArrary regionScaleUint;
//	PointArrary rgn_ary[SUM_AGENT];
//	//double search_lat[64], search_lon[64];
//	PointGPS p_search[64];
//	regionScaleUint.pts = p_search;
//	//regionScaleUint.lon = search_lon;
//
//	regionScaleUint.size = 4;
//	double regionScalex[4];
//	regionScalex[0] = 40;
//	regionScalex[1] = 40;
//	regionScalex[2] = 30;
//	regionScalex[3] = 30;
//
//	double regionScaley[4];
//	regionScaley[0] = -30;
//	regionScaley[1] = -20;
//	regionScaley[2] = -20;
//	regionScaley[3] = -30;
//
//	for (size_t i = 0; i < regionScaleUint.size; i++)
//	{
//		Local2GPS(regionScalex[i], regionScaley[i], 0, &regionScaleUint.pts[i].lat, &regionScaleUint.pts[i].lon, 0);
//	}
//
//	regionScaleUint.pts[0].lat = 39.96260698;
//	regionScaleUint.pts[0].lon = 116.30395266;
//
//	regionScaleUint.pts[1].lat = 39.96260698;
//	regionScaleUint.pts[1].lon = 116.30505287;
//
//	regionScaleUint.pts[2].lat = 39.96284673;
//	regionScaleUint.pts[2].lon = 116.30505287;
//
//	regionScaleUint.pts[3].lat = 39.96284673;
//	regionScaleUint.pts[3].lon = 116.30395266;
//
//
//	regionScaleUint.pts[0].lat = 39.96251446;
//	regionScaleUint.pts[0].lon = 116.30357985;
//
//	regionScaleUint.pts[1].lat = 39.96251446;
//	regionScaleUint.pts[1].lon = 116.30387783;
//
//	regionScaleUint.pts[2].lat = 39.96285175;
//	regionScaleUint.pts[2].lon = 116.30387782;
//
//	regionScaleUint.pts[3].lat = 39.96285175;
//	regionScaleUint.pts[3].lon = 116.30357985;
//
//
//
//
//	for (size_t i = 0; i < SUM_AGENT; i++)
//	{
//		rgn_ary[i] = regionScaleUint;
//	}
//
//	currentLocation.detectRaidus = 20;
//
//	auto MarkType = centralizedSearchMotionPlanning(res, rgn_ary, currentLocation, 0, hmArray);
//
//	if (MarkType <= 0)
//	{
//		std::cout << "wtf" << endl;
//	}
//	else
//	{
//
//		ofstream conf_srh("Srh_message.txt", ios::trunc);
//		conf_srh << "SUM= " << SUM_AGENT << endl;
//
//		for (size_t i = 0; i < SUM_AGENT; i++)
//		{
//
//			std::cout << "num=" << i << " " << res[i].p_path.size << endl;
//
//
//
//
//			conf_srh << "num= " << res[i].p_path.size << endl;
//
//			for (size_t w = 0; w < res[i].p_path.size; w++)
//			{
//
//				GPS2Local(res[i].p_path.pts[w].lat, res[i].p_path.pts[w].lon, 0, &x_path_Gps, &y_path_Gps, 0);
//				conf_srh << "x= " << x_path_Gps << endl;
//				conf_srh << "y= " << y_path_Gps << endl;
//				std::cout << "x=" << x_path_Gps << std::endl;
//				std::cout << "y=" << y_path_Gps << std::endl;
//			}
//		}
//		conf_srh.close();
//
//	}
//	return 0;
//}


#include <vector>
#include <iostream>
#include "obmap.h"
#include "ssconfig.hpp"
#include "Aplan.h"
#include "Splan.h"
#include "dingTaskAllocation.h"
#include "STaskAllocation.h"
#include "stadfxEx.h"


using std::vector;
using std::cout;
using std::endl;
namespace ac = areaCut;


void main()
{
	double min_x = 0;
	double min_y = 0;
	double max_x = 1;
	double max_y = 1;

	ob::MainMap.setGridRange(min_x, min_y, max_x, max_y);
	double aSize = 2;
	double sSize = 3;
	ob::MainMap.setGridSize(aSize, sSize);


	std::cout << "wtf" << std::endl;
	int i;
	std::cin >> i;
}