#pragma once

#include <vector>

namespace ding {
	using std::vector;
	std::vector<size_t> dingTaskAllocation(vector<double> const &vx,
		vector<double> const &vy,
		vector<vector<double>> const &reg_x,
		vector<vector<double>> const &reg_y);
}
