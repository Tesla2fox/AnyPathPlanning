#pragma once

#if defined(__EXPORT_LIB)
#if defined(_MSC_VER)
#define _LIB_PATHPLAN_API __declspec(dllexport) 
#else 
#define _LIB_PATHPLAN_API __attribute__((__visibility__("default")))
#endif
#elif defined(_MSC_VER)
#define _LIB_PATHPLAN_API __declspec(dllimport) 
#else
#define _LIB_PATHPLAN_API
#endif
#include "PointArray.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
		size_t   size;
		PointGPS *pts;
		int taskType;

}PointArraryTask;

typedef struct {
	PointGPS target;
	int taskType; //当前在执行任务的类型
}PointTask; // 拆成 1个PointGPS + 1个int

typedef struct {
	PointArraryEx p_path; 
	long agentID;
	double length;  //路径的长度
	int    stop;   //0 智能体运动停止
					// 1 智能体可以运动
}PathInfo;


typedef struct {
	PointArraryExID agent;
	long agentID;		//智能体的ID
	double detectRaidus;//智能体的探测半径
	double Ob_Radius;   //智能体的避碰半径 
}AgentInfo;




typedef struct {
	PointArrary way_Point;
	////指导点的经纬度
	//指导点的数量
	//所有的指导点信息的集合 来源是界面

	PointArrary avoid_Point;
	//规避点 经纬度
	//规避点的数量
	//所有的规避点信息的集合 来源是界面

}humanPathInfo;// 人为决策干预的路径规划

/*
* 集中式人为干预下的点对点运动规划函数 MotionPlanning
* -功能：分布式搜索运动规划
* -输入：
*		PathInfo * 代表规划好的路径
		 通过PathInfo  返回 规划的路径点 
			targetLocation  目标点经纬度
*        currentLocation, 智能体当前位置坐标和当前速度
*		 GroupMode 判断是否是编队模式
*		 pathLength 其他各个智能体剩余路径的长度
         humanpathinfo 人为干预信息
* -输出：路径规划是否成功  1 代表成功
*							其他编号代表错误类型
*                          -1 代表 目标点为障碍物
*							-2 代表 起始点为障碍物
*							-3 代表 人为干预的指导点为障碍物
*/

_LIB_PATHPLAN_API int centralizedMotionPlanning(
	PathInfo *res,
	const PointArraryTask targetLocation,
	const AgentInfo currentLocation,
	int GroupMode,
	const humanPathInfo *humanpathinfo);
/*
* 分布式人为干预下的搜索运动规划函数 distributedSearchMotionPlanningHuman
* -功能：分布式搜索运动规划
* -输入：regionScale, 目标区域坐标
*		PathInfo * 代表规划好的路径
*        currentLocation, 智能体当前位置坐标和当前速度
*		 GroupMode 集合中心点
*		 pathLength 其他各个智能体剩余路径的长度
		 humanpathinfo 人为干预信息
* -输出：路径规划是否成功  1 代表成功
*							其他编号代表错误类型
*/
_LIB_PATHPLAN_API int  centralizedSearchMotionPlanning(
	PathInfo *res,
	const PointArrary *regionScale,
	const AgentInfo currentLocation,
	const int GroupMode,
	const humanPathInfo *humanpathinfo);




//写地图信息的函数
//障碍物的X坐标lat
//障碍物的Y坐标lon
//障碍物的rad半径m
//障碍物 agent_radius 代表 车的避碰距离 
//返回障碍物编号信息
//如果返回值为-1代表写入失败
_LIB_PATHPLAN_API int SetEnvironment(double lat, double lon, double rad, double agent_radius);


//

//configflie 代表文件的完整路径
//例如  "E:\\QTcode\\Synth\\obC.txt"
_LIB_PATHPLAN_API int InitPathPlanning(const char *configflie);
#ifdef __cplusplus
}
#endif
