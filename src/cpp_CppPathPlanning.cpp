#include <vector>
#include <iostream>
#include "cpp_CppPathPlanning.h"
#include "obmap.h"
#include "ssconfig.hpp"
#include "Aplan.h"
#include "Splan.h"
#include "dingTaskAllocation.h"
#include "STaskAllocation.h"
#include "stadfxEx.h"
#include "Gwrite.hpp"

using std::vector;
using std::cout;
using std::endl;
namespace ac = areaCut;

JNIEXPORT jint JNICALL Java_cpp_CppPathPlanning_MapUpdate(JNIEnv *env, jclass, jdoubleArray jx, jdoubleArray jy, jint jtype)
{

	jdouble * jdouble_xptr = env->GetDoubleArrayElements(jx, NULL);
	int len_x = env->GetArrayLength(jx);

	jdouble * jdouble_yptr = env->GetDoubleArrayElements(jy, NULL);
	int len_y = env->GetArrayLength(jy);

	if (jtype == 0)
	{
		ob::MainMap.Map2grid();
		ob::MainMap.Map2Agrid();

		ob::MainMap.savePic();
		auto aMapSize = ob::MainMap.ATgrid.size();
		auto sMapSize = ob::MainMap.Tgrid.size();

		std::cout << " the groupMap size is " << sMapSize << std::endl;
		std::cout << " the amap size is " << aMapSize << std::endl;

		deg::conf_debug<< " the groupMap size is " << sMapSize << std::endl;
		deg::conf_debug << " the amap size is " << aMapSize << std::endl;
		return 0;
	}
	if (jtype == -1)
	{
		ob::MainMap.setGridRange(jdouble_xptr[0], jdouble_yptr[0], jdouble_xptr[1], jdouble_yptr[1]);

		std::cout << "min_x = " << jdouble_xptr[0] << std::endl;
		std::cout << "min_y = " << jdouble_yptr[0] << std::endl;
		std::cout << "max_x = " << jdouble_xptr[1] << std::endl;
		std::cout << "max_y = " << jdouble_yptr[1] << std::endl;



		deg::conf_debug << "min_x = " << jdouble_xptr[0] << std::endl;
		deg::conf_debug << "min_y = " << jdouble_yptr[0] << std::endl;
		deg::conf_debug << "max_x = " << jdouble_xptr[1] << std::endl;
		deg::conf_debug << "max_y = " << jdouble_yptr[1] << std::endl;

		return -1;
	}
	if (jtype == -2)
	{
		ob::MainMap.setGridSize(jdouble_xptr[0], jdouble_yptr[0]);
		std::cout << "aSize = " << jdouble_xptr[0] << std::endl;
		std::cout << "SSize = " << jdouble_yptr[0] << std::endl;

		deg::conf_debug << "aSize = " << jdouble_xptr[0] << std::endl;
		deg::conf_debug << "SSize = " << jdouble_yptr[0] << std::endl;

		return -2;
	}
	vector<double> vx, vy;
	deg::conf_debug << "ring" << endl;
	for (size_t i = 0; i < len_x; i++)
	{
		vx.push_back(jdouble_xptr[i]);
		vy.push_back(jdouble_yptr[i]);
	}
	writeDebug(deg::conf_debug, "x", vx);
	writeDebug(deg::conf_debug, "y", vy);

	deg::conf_debug << "ring" << endl;
	ob::MainMap.addObRing(vx, vy);
	return -100;
}

JNIEXPORT jobjectArray JNICALL Java_cpp_CppPathPlanning_CenScoutMotionPlanning(JNIEnv *env, jclass, jobjectArray Regions_x, jobjectArray Regions_y, jdoubleArray jstart_x, jdoubleArray jstart_y)
{
	deg::conf_debug << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	deg::conf_debug << "CenScoutPathPlanning begin " << endl;
	vector<double> vx, vy;
	jdouble * jdouble_startxPtr = env->GetDoubleArrayElements(jstart_x, NULL);
	int len_startX = env->GetArrayLength(jstart_x);
	cout << "len_startX = " << len_startX << endl;

	jdouble * jdouble_startyPtr = env->GetDoubleArrayElements(jstart_y, NULL);
	int len_startY = env->GetArrayLength(jstart_x);
	cout << "len_startY = " << len_startY << endl;

	for (size_t i = 0; i < len_startY; i++)
	{
		vx.push_back(jdouble_startxPtr[i]);
		vy.push_back(jdouble_startyPtr[i]);
		deg::conf_debug << "index is " << i << " start_x = " << jdouble_startxPtr[i] <<
			 " start_y	= " << jdouble_startyPtr[i] << endl;
	}
	cout << "the start location have successsed " << endl;


	jsize regionCount = env->GetArrayLength(Regions_x);
	
	vector<vector<double>> regs_x, regs_y;
	vector<vector<ac::Point>> regionScale;
 	
	for (size_t i = 0; i < regionCount; i++)
	{
		vector<double> vreg_x, vreg_y;
		vector<ac::Point> vPnt;
		jdoubleArray reg_x = jdoubleArray(env->GetObjectArrayElement(Regions_x, i));
		jdoubleArray reg_y = jdoubleArray(env->GetObjectArrayElement(Regions_y, i));

		jdouble * jdouble_reg_xPtr = env->GetDoubleArrayElements(reg_x, NULL);
		int len_reg_x = env->GetArrayLength(reg_x);

		jdouble * jdouble_reg_yPtr = env->GetDoubleArrayElements(reg_y, NULL);
		int len_reg_y = env->GetArrayLength(reg_y);

		deg::conf_debug << "region <<<<<<<<<<<<<<<<<" << endl;
		for (size_t j = 0; j < len_reg_x; j++)
		{
			cout << "index = " << i << "reg_x " << jdouble_reg_xPtr[j] << endl;
			vreg_x.push_back(jdouble_reg_xPtr[j]);
			cout << "index = " << i << "reg_y " << jdouble_reg_yPtr[j] << endl;

			deg::conf_debug << "index is " << i << " reg_x = " << jdouble_reg_xPtr[j] <<
				" reg_y	= " << jdouble_reg_yPtr[j] << endl;

			vreg_y.push_back(jdouble_reg_yPtr[j]);
			ac::Point pnt(jdouble_reg_xPtr[j], jdouble_reg_yPtr[j]);
			vPnt.push_back(pnt);
		}
		regs_x.push_back(vreg_x);
		regs_y.push_back(vreg_y);
		regionScale.push_back(vPnt);
	}
	deg::conf_debug << "new object success" << endl;
	cout << "new object success <<<<<<<<<<<<<<" << endl;

	auto taskAllocationRes = ding::dingTaskAllocation(vx, vy, regs_x, regs_y);


	for (size_t i = 0; i < taskAllocationRes.size(); i++)
	{
		deg::conf_debug << " ," << taskAllocationRes[i];
		cout << "	," << taskAllocationRes[i];
	}
	deg::conf_debug<<"taskAllocation success" << endl;
	std::cout << "taskAllocation success" << endl;

	
	//vector<ac::RegionMM> res;
	vector<vector<ac::Point>> Sres;
	const int agentNum = len_startY;
	ac::STaskAllocation(Sres, taskAllocationRes, regionScale, regionCount, agentNum);

	//deg::conf_debug << "Point Debug" << endl;
	//for (size_t i = 0; i < Sres.size(); i++)
	//{
	//	
	//}
	jclass initClass = env->FindClass("[D");


	if (initClass == NULL)
	{
		//cout << "M0-0" << endl;
	}

	//jdoubleArray res;
	jobjectArray jObjarray = env->NewObjectArray(len_startX, initClass, NULL);

	//return jObjarray;
	cout << "cut area successs" << endl;
	deg::conf_debug << " cut arae success" << endl;

	//jclass initClass = env->FindClass("java/lang/Double");
		
	//cout << "bug si here" << endl;


	for (size_t i = 0; i < len_startX; i++)
	{

		vector<double> vxu, vyu;
		//cout << "Regindex is " << i << endl;
		deg::conf_debug << "RegIndex is " << i ;
		deg::conf_draw << "RegIndex is " << i;
		for (size_t j = 0; j < Sres[i].size(); j++)
		{
			vxu.push_back(Sres[i][j].x);
			vyu.push_back(Sres[i][j].y);
			deg::conf_debug << " index  is " << i <<
				"	x = " << Sres[i][j].x
				<< " y = " << Sres[i][j].y
				<< endl;
			deg::conf_draw << " index  is " << i <<
				"	x = " << Sres[i][j].x
				<< " y = " << Sres[i][j].y
				<< endl;
		}
		vxu.push_back(Sres[i][0].x);
		vyu.push_back(Sres[i][0].y);

		deg::conf_debug << " the last index  "  <<
			"	x = " << Sres[i][0].x
			<< " y = " << Sres[i][0].y
			<< endl;

		deg::conf_draw << " index  is " << i <<
			"	x = " << Sres[i][0].x
			<< " y = " << Sres[i][0].y
			<< endl;

		deg::conf_draw << "end Reg" << endl;

		pl::Splan main_splan;
		main_splan.loadMap(ob::MainMap);

		main_splan.setPosition(vx[i], vy[i]);
//		main_splan.setExternRange(regs_x, regs_y);
		main_splan.setRange(vxu, vyu);
		main_splan.Plan();

		vector<double> vxp, vyp;

		main_splan.getPath(vxp, vyp);


		deg::conf_debug << " path size is " << vxp.size() << endl;

		deg::conf_draw << " path size is " << vxp.size() << endl;

		jdoubleArray output = env->NewDoubleArray(vxp.size() * 2 + 1);

		jdouble destArrayElems[30000];
		destArrayElems[0] = vxp.size();
		for (size_t j = 0; j < vxp.size(); j++)
		{
			destArrayElems[2 * j + 1] = vxp.at(j);
			destArrayElems[2 * j + 2] = vyp.at(j);
			deg::conf_debug << " the index is " << j
				<< "   x = " << vxp[j] << "		y = " << vyp[j]
				<< endl;
		}
		deg::conf_draw << "PathX" << i;
		for (size_t j = 0; j < vxp.size(); j++)
		{
			deg::conf_draw << " " << vxp[j];
		}
		deg::conf_draw << "	" << endl;

		deg::conf_draw << "PathY" << i;
		for (size_t j = 0; j < vxp.size(); j++)
		{
			deg::conf_draw << " " << vyp[j];
		}
		deg::conf_draw << "	" << endl;


		deg::conf_draw << "end path" << endl;
		env->SetDoubleArrayRegion(output, 0, vxp.size()*2+1, destArrayElems);
		env->SetObjectArrayElement(jObjarray, i, output);
		//env->DeleteLocalRef(output);
		//cout << "input is bug " << endl;
	}
	deg::conf_debug << "cenScoutPathPlanning is success" << endl;
	return jObjarray;
}

JNIEXPORT jdoubleArray JNICALL Java_cpp_CppPathPlanning_ScoutMotionPlanning(JNIEnv *env, jclass, jdoubleArray jx, jdoubleArray jy, jdouble start_x, jdouble start_y)
{
	std::ofstream conf_debug("xx_debug_path.txt", std::ios::trunc);
	conf_debug.precision(12);
	
	pl::Splan main_splan;
	main_splan.loadMap(ob::MainMap);

	vector<double> vRegx, vRegy;

	jdouble * jdouble_xptr = env->GetDoubleArrayElements(jx, NULL);
	int len_x = env->GetArrayLength(jx);

	jdouble * jdouble_yptr = env->GetDoubleArrayElements(jy, NULL);
	int len_y = env->GetArrayLength(jy);


	for (size_t i = 0; i < len_x; i++)
	{
		vRegx.push_back(jdouble_xptr[i]);
		vRegy.push_back(jdouble_yptr[i]);
	}
	main_splan.setPosition(start_x, start_y);
	main_splan.setRange(vRegx, vRegy);
	main_splan.Plan();
	vector<double> vx;
	vector<double> vy;

	main_splan.getPath(vx, vy);

	conf_debug << "#######################local##########" << std::endl;

	conf_debug << "PathNumLocal " << vx.size() << std::endl;

	for (size_t w = 0; w < vx.size(); w++)
	{
		conf_debug << "PathCord.x  " << vx.at(w) << std::endl;
		conf_debug << "PathCord.y  " << vy.at(w) << std::endl;
	}
	conf_debug << "############################GPS###########" << std::endl;

	jdoubleArray output = env->NewDoubleArray(vx.size() * 2 + 1);
	jboolean isCopy2 = JNI_FALSE;
	jdouble* destArrayElems = env->GetDoubleArrayElements(output, &isCopy2);

	destArrayElems[0] = vx.size();
	for (size_t i = 0; i < vx.size(); i++)
	{
		destArrayElems[2 * i + 1] = vx.at(i);
		destArrayElems[2 * i + 2] = vy.at(i);
	}
	env->SetDoubleArrayRegion(output, 0, vx.size() * 2 + 1, destArrayElems);
	return output;
}

JNIEXPORT jdoubleArray JNICALL Java_cpp_CppPathPlanning_MotionPlanning(JNIEnv * env, jclass, jdouble start_x, jdouble start_y, jdouble target_x, jdouble target_y, 
	jobjectArray dynamicObstaclePntX, jobjectArray dynamicObstaclePntY, jdoubleArray naviPntX, jdoubleArray naviPntY)
{

	jsize dynamicObstacleNum = env->GetArrayLength(dynamicObstaclePntX);

	//No dynamic obstacles

	auto AplanMap = ob::MainMap;
	for (size_t i = 0; i < dynamicObstacleNum; i++)
	{
		vector<double> vreg_x, vreg_y;
		vector<ac::Point> vPnt;
		bgeo::DRing vObReg;
		jdoubleArray ob_reg_x = jdoubleArray(env->GetObjectArrayElement(dynamicObstaclePntX, i));
		jdoubleArray ob_reg_y = jdoubleArray(env->GetObjectArrayElement(dynamicObstaclePntY, i));

		jdouble * jdouble_reg_xPtr = env->GetDoubleArrayElements(ob_reg_x, NULL);
		int len_reg_x = env->GetArrayLength(ob_reg_x);

		jdouble * jdouble_reg_yPtr = env->GetDoubleArrayElements(ob_reg_y, NULL);
		int len_reg_y = env->GetArrayLength(ob_reg_y);

		for (size_t j = 0; j < len_reg_x; j++)
		{
			vObReg.push_back(bgeo::DPoint(jdouble_reg_xPtr[j], jdouble_reg_xPtr[j]));
		}
		AplanMap.addDynamicObRing(vObReg);
	}
	pl::Aplan main_aplan;
	main_aplan.loadMap(AplanMap);

	jdouble * jdouble_naviPtrX = env->GetDoubleArrayElements(naviPntX, NULL);
	int navi_len_x = env->GetArrayLength(naviPntX);

	jdouble * jdouble_naviPtrY = env->GetDoubleArrayElements(naviPntY, NULL);
	int navi_len_y = env->GetArrayLength(naviPntY);

	vector<double> vx;
	vector<double> vy;

	jdoubleArray falseOutput = env->NewDoubleArray(1);
	jboolean fasleIsCopy2 = JNI_FALSE;
	jdouble* fasleDestArrayElems = env->GetDoubleArrayElements(falseOutput, &fasleIsCopy2);



	if (navi_len_x  == 0)
	{
		main_aplan.getStartPnt(start_x, start_y);
		main_aplan.getTargetPnt(target_x, target_y);
		main_aplan.AstarPlan();
		if (main_aplan.failIndex < 0)
		{
			fasleDestArrayElems[0] = main_aplan.failIndex;
			env->SetDoubleArrayRegion(falseOutput, 0, 1, fasleDestArrayElems);
			return falseOutput;
		}
		main_aplan.getPath(vx, vy);
	}

	if (navi_len_x > 0)
	{
		vector<double> vHumanWay_x, vHumanWay_y;
		for (size_t i = 0; i < navi_len_x; i++)
		{
			vHumanWay_x.push_back(jdouble_naviPtrX[i]);
			vHumanWay_y.push_back(jdouble_naviPtrY[i]);
		}

		main_aplan.getStartPnt(start_x, start_y);
		main_aplan.getTargetPnt(vHumanWay_x.front(), vHumanWay_y.front());
		main_aplan.AstarPlan();
		if (main_aplan.failIndex < 0)
		{
			fasleDestArrayElems[0] = main_aplan.failIndex;
			env->SetDoubleArrayRegion(falseOutput, 0, 1, fasleDestArrayElems);
			return falseOutput;
		}
		else{
			main_aplan.getPath(vx, vy);
		}
		auto mid_human_wayPointSize = navi_len_x - 1;
		for (size_t i = 0; i < mid_human_wayPointSize; i++)
		{
			main_aplan.getStartPnt(vHumanWay_x[i], vHumanWay_y[i]);
			main_aplan.getTargetPnt(vHumanWay_x[i + 1], vHumanWay_y[i + 1]);
			main_aplan.AstarPlan();
			if (main_aplan.failIndex < 0)
			{
				fasleDestArrayElems[0] = main_aplan.failIndex;
				env->SetDoubleArrayRegion(falseOutput, 0, 1, fasleDestArrayElems);
				return falseOutput;
			}
			else
			{
				main_aplan.getPath(vx, vy);
			}
		}
		main_aplan.getStartPnt(vHumanWay_x.back(), vHumanWay_y.back());
		main_aplan.getTargetPnt(target_x, target_y);
		main_aplan.AstarPlan();
		if (main_aplan.failIndex < 0)
		{
			fasleDestArrayElems[0] = main_aplan.failIndex;
			env->SetDoubleArrayRegion(falseOutput, 0, 1, fasleDestArrayElems);
			return falseOutput;
		}
		else
		{
			main_aplan.getPath(vx, vy);
		}

	}
	jdoubleArray output = env->NewDoubleArray(vx.size() * 2 + 1);
	jboolean isCopy2 = JNI_FALSE;
	jdouble* destArrayElems = env->GetDoubleArrayElements(output, &isCopy2);

	destArrayElems[0] = vx.size();
	for (size_t i = 0; i < vx.size(); i++)
	{
		destArrayElems[2 * i + 1] = vx.at(i);
		destArrayElems[2 * i + 2] = vy.at(i);
	}

	env->SetDoubleArrayRegion(output, 0, vx.size() * 2 + 1, destArrayElems);

	return output;

}











