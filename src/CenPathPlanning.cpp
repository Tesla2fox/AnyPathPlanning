
//#include "pathPlanning.h"
#include "CenPathPlanning.h"
#include "gps2local.h"
#include "ssconfig.hpp"
#include "obmap.h"
#include "Aplan.h"
#include "splan.h"
#include "iostream"
#include <algorithm>
#include <string>

bool DebugBoolean = true;


// inin the  path planning function
/// set  environment
int InitPathPlanning(const char *configflie)
{
    //ob::MainMap.loadMapGrid(configflie);
    
	std::ofstream conf_debug("xx_readMap.txt", std::ios::trunc);
	conf_debug.precision(12);

    std::cout<<"begin to load the map "<<std::endl;
	conf_debug<< "begin to load the map " << std::endl;
    ob::MainMap.loadMapGrid(configflie);

    std::cout<<"wtf"<<std::endl;
    auto &AplanMap =  ob::MainMap;
    auto wtfSize =ob::MainMap.ATgrid.size();
    auto GroupMapSize = ob::MainMap.GTgrid.size();

	conf_debug << " the aplan num is " << wtfSize << std::endl;
	conf_debug << " the group num is " << GroupMapSize << std::endl;
 	
	conf_debug << " The VERSION IS 2.0 " << std::endl;

   // std::cout<<" the groupMap size is "<< GroupMapSize << std::endl;
   // std::cout <<" the amap size is "<< wtfSize<<std::endl;
    
    return 1;
}

int centralizedMotionPlanning(
		PathInfo *res,
		const PointArraryTask targetLocation,
		const	AgentInfo currentLocation,
		int GroupMode,
		const	humanPathInfo *humanpathinfo)
{
	std::ofstream conf_debug("xx_debug_path.txt", std::ios::trunc);
	conf_debug.precision(12);
	std::cout << "targetSize = " << targetLocation.size << std::endl;
	
	conf_debug << "####################" << std::endl;
	conf_debug << "v.2.0" << std::endl;
	conf_debug << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

	conf_debug.precision(12);

	for (size_t q = 0; q < targetLocation.size; q++)
	{

		std::cout << " the agent id " << q << std::endl;

		conf_debug << "the agent id is "<<q << std::endl;
		PathInfo & pathInfoDis = res[q];
		double x_avoid, y_avoid;



		pl::Aplan main_aplan;
		auto AplanMap = ob::MainMap;
		for (size_t i = 0; i < humanpathinfo[q].avoid_Point.size; i++) {
			GPS2Local(humanpathinfo[q].avoid_Point.pts[i].lat, humanpathinfo[q].avoid_Point.pts[i].lon, 0, &x_avoid, &y_avoid, NULL);
			AplanMap.setOb(x_avoid, y_avoid);
			if (DebugBoolean)
			{
				std::cout << "x_avoid = " << x_avoid << " y_avoid = " << y_avoid << std::endl;
				std::cout << std::setprecision(10) << "Planner{humanAvoidPoint.lat}" << humanpathinfo[q].avoid_Point.pts[i].lat <<
					"	Planner{humanAvoidPoint.lon}"
					<< humanpathinfo[q].avoid_Point.pts[i].lon << std::endl;

				conf_debug << "Time " << i << "Planner{humanAvoidPoint.lat}" << humanpathinfo[q].avoid_Point.pts[i].lat <<
					"	Planner{humanAvoidPoint.lon}"
					<< humanpathinfo[q].avoid_Point.pts[i].lon << std::endl;

			}
		}
		//load map
		main_aplan.loadMap(AplanMap);

		//    main_aplan.loadMap(ob::MainMap);
		auto &agent = currentLocation.agent;
		//auto agentInte = std::find(agent.ID, agent.ID + agent.size, currentLocation.agentID);
		////
		//if (DebugBoolean)
		//{
		//	printf("[PathPlan] AgentIDx = %ld (myID=%ld)\n", agentInte - agent.ID, currentLocation.agentID);

		//}
		//if (agentInte == (agent.ID + agent.size)) {
		//	//NO ID
		//	return -5;
		//}
		//auto agentNum = agentInte - agent.ID;

		size_t agentNum = q;
		std::vector<double> vagent_x, vagent_y;
		for (std::size_t i = 0; i < currentLocation.agent.size; i++)
		{
			double x_unit, y_unit;
			GPS2Local(currentLocation.agent.pts[i].lat, currentLocation.agent.pts[i].lon, 0, &x_unit, &y_unit, NULL);
			vagent_x.push_back(x_unit);
			vagent_y.push_back(y_unit);
			if (DebugBoolean)
			{

				conf_debug << "Time Debug" << "Planner{currentLocation.agent.pts[agentNum].lat}  "
					<< currentLocation.agent.pts[agentNum].lat
					<< "	Planner{currentLocation.agent.pts[agentNum].lon}  "
					<< currentLocation.agent.pts[agentNum].lon << std::endl;
			}
		}
		double target_x, target_y;
		//目标点
		GPS2Local(targetLocation.pts[q].lat, targetLocation.pts[q].lon, 0, &target_x, &target_y, NULL);

		double start_x, start_y;



		if (GroupMode == 0)
		{
			GPS2Local(currentLocation.agent.pts[agentNum].lat, currentLocation.agent.pts[agentNum].lon, 0, &start_x, &start_y, NULL);
			main_aplan.setGroupMode(false);
		}
		else
		{
			double x_sum = 0;
			double y_sum = 0;
			for (std::size_t i = 0; i < vagent_x.size(); i++)
			{
				x_sum += vagent_x.at(i);
				y_sum += vagent_y.at(i);
			}
			start_x = x_sum / vagent_x.size();
			start_y = y_sum / vagent_y.size();
			main_aplan.setGroupMode(true);
		}

		conf_debug << "##############" << std::endl;
		conf_debug << " the start.x " << start_x << std::endl;
		conf_debug << " the start.y " << start_y << std::endl;


		conf_debug << "##############" << std::endl;
		conf_debug << " the target.x " << target_x << std::endl;
		conf_debug << " the target.y " << target_y << std::endl;



		conf_debug << "##############" << std::endl;
		conf_debug << " targetLocation.pts[q].lat " << targetLocation.pts[q].lat << std::endl;
		conf_debug << " targetLocation.pts[q].lon " << targetLocation.pts[q].lon << std::endl;



		std::vector<double> vx;
		std::vector<double> vy;
		if (humanpathinfo[q].way_Point.size == 0)
		{
			main_aplan.getStartPnt(start_x, start_y);
			main_aplan.getTargetPnt(target_x, target_y);
			main_aplan.AstarPlan();
			
			if (main_aplan.failIndex < 0)
			{
				conf_debug << " the failIndex is " << main_aplan.failIndex <<std::endl;
				return main_aplan.failIndex;
			}
			else
			{
				main_aplan.getPath(vx, vy);

			}
		}

		// if there are the way point  of the human
		if (humanpathinfo[q].way_Point.size > 0)
		{
			std::cout << " way_Point " << std::endl;
			std::vector<double> vhumanWay_x, vhumanWay_y;
			for (size_t i = 0; i < humanpathinfo[q].way_Point.size; i++) {

				double x_way, y_way;
				GPS2Local(humanpathinfo[q].way_Point.pts[i].lat, humanpathinfo[q].way_Point.pts[i].lon, 0, &x_way, &y_way, NULL);
				
				
				conf_debug << "Time " << i << "Planner{humanWayPoint.lat}" << humanpathinfo[q].way_Point.pts[i].lat <<
					"	Planner{humanWayPoint.lon}"
					<< humanpathinfo[q].way_Point.pts[i].lon << std::endl;


				vhumanWay_x.push_back(x_way);
				vhumanWay_y.push_back(y_way);
			}

			main_aplan.getStartPnt(start_x, start_y);
			main_aplan.getTargetPnt(vhumanWay_x.front(), vhumanWay_y.front());
			main_aplan.AstarPlan();
			if (main_aplan.failIndex < 0)
			{
				conf_debug << " the failIndex is " << main_aplan.failIndex << std::endl;
				return main_aplan.failIndex;
			}
			else
			{
				main_aplan.getPath(vx, vy);
			}

			auto mid_human_wayPointSize = humanpathinfo[q].way_Point.size - 1;
			for (size_t i = 0; i < mid_human_wayPointSize; i++)
			{
				main_aplan.getStartPnt(vhumanWay_x.at(i), vhumanWay_y.at(i));
				main_aplan.getTargetPnt(vhumanWay_x.at(i + 1), vhumanWay_y.at(i + 1));
				main_aplan.AstarPlan();
				if (main_aplan.failIndex < 0)
				{
					//the way point may be is the ob
					conf_debug << " the failIndex is " << main_aplan.failIndex << std::endl;
					conf_debug << "the way point is wrong" << std::endl;
					return -3;
				}
				else {
					main_aplan.getPath(vx, vy);
				}
			}
			main_aplan.getStartPnt(vhumanWay_x.back(), vhumanWay_y.back());
			main_aplan.getTargetPnt(target_x, target_y);
			main_aplan.AstarPlan();
			if (main_aplan.failIndex < 0)
			{
				conf_debug << " the failIndex is " << main_aplan.failIndex << std::endl;
				return main_aplan.failIndex;
			}
			else
			{
				main_aplan.getPath(vx, vy);
			}

		}

		///debug message
		///
		pathInfoDis.p_path.size = vx.size();

		if (vx.size() > 29)
		{
			return -9;
			// over the 30 point;
		}
		for (std::size_t i = 0; i < vx.size(); i++)
		{
			Local2GPS(vx.at(i), vy.at(i), 0, &res[q].p_path.pts[i].lat, &res[q].p_path.pts[i].lon, 0);
		}

		if (DebugBoolean)
		{
			conf_debug << "#######################local##########" << std::endl;

			conf_debug << "PathNumLocal " << vx.size() << std::endl;

			for (size_t w = 0; w < vx.size(); w++)
			{
				conf_debug << "PathCord.x  " << vx.at(w) << std::endl;
				conf_debug << "PathCord.y  " << vy.at(w) << std::endl;
			}
			conf_debug << "############################GPS###########" << std::endl;
			conf_debug << "PointGps ==" << res->p_path.size << std::endl;
			for (size_t w = 0; w < res[q].p_path.size; w++)
			{
				conf_debug << "PathPointGPS.lat=== " << res->p_path.pts[w].lat << std::endl;
				conf_debug << "PathPointGPS.lon=== " << res->p_path.pts[w].lon << std::endl;
			}
		}
	}
    return 1;

}

int  centralizedSearchMotionPlanning(
	PathInfo *res,
	const PointArrary *regionScale,
	const AgentInfo currentLocation,
	int GroupMode,
	const humanPathInfo *humanpathinfo)

{
    std::ofstream conf_debug("xx_Debug_srh.txt", std::ios::trunc);
	conf_debug.precision(12);
	if (DebugBoolean)
    {
        std::cout << "###################################" << std::endl;
        std::cout << " search planning {planner}" << std::endl;
        std::cout << "v.2.0" << std::endl;

        conf_debug << "currentLocation.detectRaidus =" <<
                      currentLocation.detectRaidus << std::endl;

        conf_debug << "####################" << std::endl;
        conf_debug << "v.2.0" << std::endl;
        conf_debug << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }

    //    PathInfo &path_info = *res;

	
	for (size_t q = 0; q < currentLocation.agent.size; q++)
	{


		conf_debug << "agent ID is  " << q << std::endl;

		auto &agent = currentLocation.agent;
		//auto agentInte = std::find(agent.ID, agent.ID + agent.size, currentLocation.agentID);

		////
		//if (DebugBoolean)
		//{
		//	printf("[PathPlan] AgentIDx = %ld (myID=%ld)\n", agentInte - agent.ID, currentLocation.agentID);

		//}
		//if (agentInte == (agent.ID + agent.size)) {
		//	//NO ID
		//	return -5;
		//}
		//auto agentNum = agentInte - agent.ID;

		size_t agentNum = q;

		std::vector<double> vagent_x, vagent_y;
		for (std::size_t i = 0; i < currentLocation.agent.size; i++)
		{
			double x_unit, y_unit;
			GPS2Local(currentLocation.agent.pts[i].lat, currentLocation.agent.pts[i].lon, 0, &x_unit, &y_unit, NULL);
			vagent_x.push_back(x_unit);
			vagent_y.push_back(y_unit);
			if (DebugBoolean)
			{

				conf_debug << "Time Debug" <<i << "   Planner{currentLocation.agent.pts[agentNum].lat}  "
					<< currentLocation.agent.pts[agentNum].lat
					<< "	Planner{currentLocation.agent.pts[agentNum].lon}  "
					<< currentLocation.agent.pts[agentNum].lon << std::endl;
			}
		}

		pl::Splan Main_splan;
		auto SMainMap = ob::MainMap;
		Main_splan.loadMap(SMainMap);

		double start_x, start_y;

		if (GroupMode == 0)
		{
			GPS2Local(currentLocation.agent.pts[agentNum].lat, currentLocation.agent.pts[agentNum].lon, 0, &start_x, &start_y, NULL);
			if (DebugBoolean)
			{
				std::cout << " the start.x " << start_x << std::endl;
				std::cout << " the start.y " << start_y << std::endl;

				conf_debug << " the start.x " << start_x << std::endl;
				conf_debug << " the start.y " << start_y << std::endl;

			}

			//set the agent  currentLocation
			bool setPos = Main_splan.setPosition(start_x, start_y);
			if (!setPos)
			{
				// the agent pos is the ob;
				return -2;
			}
		}
		else
		{
			return -10;
			//no exit groupMode;
		}


		if (regionScale[q].size < 0)
		{
			//设定的搜索区域存在问题
			return -8;
		}

		std::vector<double> vRegx, vRegy;
		for (size_t i = 0; i < regionScale[q].size; i++)
		{
			double region_x, region_y;
			GPS2Local(regionScale[q].pts[i].lat, regionScale[q].pts[i].lon, 0, &region_x, &region_y, 0);
			std::cout << "the region_x is " << region_x << std::endl;
			std::cout << " the region y is " << region_y << std::endl;
			vRegx.push_back(region_x);
			vRegy.push_back(region_y);
			if (DebugBoolean)
			{
				conf_debug << "region " << i << "   Planner{region.lat}" << regionScale[q].pts[i].lat <<
					"	Planner{regionScale.pts[i].lon}"
					<< regionScale[q].pts[i].lon << std::endl;
				// std::cout<< " region.x " << i << "Planner{region.lon}"
				printf("regionScaleSuccess%ld\n", i);

			}
		}
		vRegx.push_back(vRegx.front());
		vRegy.push_back(vRegy.front());


		//set the search region
		Main_splan.setRange(vRegx, vRegy);

		// agent path planning
		Main_splan.Plan();

		for (size_t i = 0; i < Main_splan._vFailIndex.size(); i++)
		{
			std::cout << "_vFailIndex" << i << Main_splan._vFailIndex.at(i) << std::endl;
			conf_debug << "_vFailIndex   " << i <<"   ="<< Main_splan._vFailIndex.at(i) << std::endl;
		}

		if (Main_splan.failIndex < 0)
		{
			conf_debug << " the failedIndex is " << Main_splan.failIndex << std::endl;

			return Main_splan.failIndex;
			//
			//failIndex = -8  setRange failed
			//failIndex = -7  没有找到初始搜索区域中的初始点
			//failIndex = -10  初始化区域中的点没有邻居
		}
		std::vector<double> vx, vy;

		Main_splan.getPath(vx, vy);


		res[q].p_path.size = vx.size();

		if (vx.size() > 900)
		{
			return -11;
			// over the 900 point;
		}
		for (std::size_t i = 0; i < vx.size(); i++)
		{
			Local2GPS(vx.at(i), vy.at(i), 0, &res[q].p_path.pts[i].lat, &res[q].p_path.pts[i].lon, 0);
		}

		if (DebugBoolean)
		{
			conf_debug << "#######################local##########" << std::endl;

			conf_debug << "PathNumLocal " << vx.size() << std::endl;

			for (size_t w = 0; w < vx.size(); w++)
			{
				conf_debug << "PathCord.x  " << vx.at(w) << std::endl;
				conf_debug << "PathCord.y  " << vy.at(w) << std::endl;
			}
			conf_debug << "############################GPS###########" << std::endl;
			conf_debug << "PointGps ==" << res[q].p_path.size << std::endl;
			for (size_t w = 0; w < res[q].p_path.size; w++)
			{
				conf_debug << "PathPointGPS.lat=== " << res[q].p_path.pts[w].lat << std::endl;
				conf_debug << "PathPointGPS.lon=== " << res[q].p_path.pts[w].lon << std::endl;
			}
		}
	}
    return 1;
}
