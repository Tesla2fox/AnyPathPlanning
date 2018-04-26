
#include <vector>
#include <iostream>
#include "cpp_CppPathPlanning.h"
#include "obmap.h"
#include "ssconfig.hpp"
#include "Aplan.h"
#include "Splan.h"
#include "dingTaskAllocation.h"

using std::vector;
using std::cout;
using std::endl;
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

		auto aMapSize = ob::MainMap.ATgrid.size();
		auto sMapSize = ob::MainMap.Tgrid.size();

		std::cout << " the groupMap size is " << sMapSize << std::endl;
		std::cout << " the amap size is " << aMapSize << std::endl;
		return 0;
	}
	if (jtype == -1)
	{
		ob::MainMap.setGridRange(jdouble_xptr[0], jdouble_yptr[0], jdouble_xptr[1], jdouble_yptr[1]);

		std::cout << "min_x = " << jdouble_xptr[0] << std::endl;
		std::cout << "min_y = " << jdouble_yptr[0] << std::endl;

		std::cout << "max_x = " << jdouble_xptr[1] << std::endl;
		std::cout << "max_y = " << jdouble_yptr[1] << std::endl;

		return -1;
	}
	if (jtype == -2)
	{
		ob::MainMap.setGridSize(jdouble_xptr[0], jdouble_yptr[0]);
		std::cout << "aSize = " << jdouble_xptr[0] << std::endl;
		std::cout << "sSize = " << jdouble_yptr[0] << std::endl;
		return -2;
	}
	vector<double> vx, vy;
	for (size_t i = 0; i < len_x; i++)
	{
		vx.push_back(jdouble_xptr[i]);
		vy.push_back(jdouble_yptr[i]);
	}
	ob::MainMap.addObRing(vx, vy);
	return -100;
}

JNIEXPORT jobjectArray JNICALL Java_cpp_CppPathPlanning_CenScoutMotionPlanning(JNIEnv *env, jclass, jobjectArray Regions_x, jobjectArray Regions_y, jdoubleArray jstart_x, jdoubleArray jstart_y)
{

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
	}
	cout << "the start location have successsed " << endl;


	jsize regionCount = env->GetArrayLength(Regions_x);
	
	vector<vector<double>> regs_x, regs_y;

	for (size_t i = 0; i < regionCount; i++)
	{
		vector<double> vreg_x, vreg_y;
		jdoubleArray reg_x = jdoubleArray(env->GetObjectArrayElement(Regions_x, i));
		jdoubleArray reg_y = jdoubleArray(env->GetObjectArrayElement(Regions_y, i));

		jdouble * jdouble_reg_xPtr = env->GetDoubleArrayElements(reg_x, NULL);
		int len_reg_x = env->GetArrayLength(reg_x);

		for (size_t j = 0; j < len_reg_x; j++)
		{
			cout << "index = " << i << "reg_x " << jdouble_reg_xPtr[j] << endl;
			vreg_x.push_back(jdouble_reg_xPtr[j]);
		}

		jdouble * jdouble_reg_yPtr = env->GetDoubleArrayElements(reg_y, NULL);
		int len_reg_y = env->GetArrayLength(reg_y);
		for (size_t j = 0; j < len_reg_y; j++)
		{
			cout << "index = " << i << "reg_y " << jdouble_reg_yPtr[j] << endl;
			vreg_y.push_back(jdouble_reg_yPtr[j]);
		}
		regs_x.push_back(vreg_x);
		regs_y.push_back(vreg_y);
	}
	cout << "new object success" << endl;



	auto taskAllocationRes = ding::dingTaskAllocation(vx, vy, regs_x, regs_y);


	//jclass initClass = env->FindClass("java/lang/Double");

	jclass initClass = env->FindClass("[D");


	if (initClass == NULL)
	{
		cout << "M0-0" << endl;
	}

	//jdoubleArray res;
	jobjectArray jObjarray = env->NewObjectArray(len_startX,initClass,NULL);
	//cout << "bug si here" << endl;


	for (size_t i = 0; i < len_startX; i++)
	{

		jdoubleArray output = env->NewDoubleArray(25);
		jdouble tmp[256];
		for (size_t j = 0; j < 25; j++)
		{
			tmp[j] = j;
		}

		
		//jboolean isCopy2 = JNI_FALSE;
		//jdouble* destArrayElems = env->GetDoubleArrayElements(output, &isCopy2);

		//cout << "new object success" << endl;

		//for (size_t j = 0; j < 25; j++)
		//{
		//	destArrayElems[j] = j;
		//}
		env->SetDoubleArrayRegion(output, 0, 25, tmp);
		env->SetObjectArrayElement(jObjarray, i, output);
		env->DeleteLocalRef(output);
	}


	return jObjarray;

	for (size_t i = 0; i < len_startX; i++)
	{
		cout << "wtf" << endl;
		jdoubleArray pp = jdoubleArray(env->GetObjectArrayElement(jObjarray, i));
		//jdoubleArray reg_y = jdoubleArray(env->GetObjectArrayElement(Regions_y, i));
		cout << "wtf" << endl;


		jdouble * pp_Ptr = env->GetDoubleArrayElements(pp, NULL);
		cout << "wtf" << endl;

		int pp_size = env->GetArrayLength(pp);

		cout << "ppsize = " << pp_size << endl;

		for (size_t j = 0; j < pp_size; j++)
		{
			cout << "index = " << i << " pp = " << pp_Ptr << endl;
		}
	}


	cout << "return ??" << endl;

	
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

JNIEXPORT jdoubleArray JNICALL Java_cpp_CppPathPlanning_MotionPlanning(JNIEnv * env, jclass, jdouble start_x, jdouble start_y, jdouble target_x, jdouble target_y)
{
	std::ofstream conf_debug("xx_debug_path.txt", std::ios::trunc);
	conf_debug.precision(12);
	pl::Aplan main_aplan;
	main_aplan.loadMap(ob::MainMap);

	main_aplan.getStartPnt(start_x, start_y);
	main_aplan.getTargetPnt(target_x, target_y);

	main_aplan.AstarPlan();

	vector<double> vx;
	vector<double> vy;

	main_aplan.getPath(vx, vy);


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










