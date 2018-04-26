#pragma once
#include "Point.h"
#include <vector>
namespace areaCut {
	using std::vector;
	//void StaskAllocation()
	//
	//集中式搜索区域的任务分配函数STaskAllocation
	//- 功能：实现搜索区域的划分
	//- 输入：*regionRes 代表分配完成的区域;
	//		AgentAllocationRes 代表任务分配的结果;	
	//		regionScale 代表已经画好区域
	//      Size_regionScale 代表画区域的数量
	//      AgentNum  代表移动智能体的数量
	//-输出：任务分配是否成功 1代表成功
	//其他编号代表错误类型
	int STaskAllocation(vector<vector<Point>> &res,
		const vector<size_t> AgentAllocationRes,
		const vector<vector<Point>>regionScale,
		const int Size_regionScale,
		const int AgentNum);
}
