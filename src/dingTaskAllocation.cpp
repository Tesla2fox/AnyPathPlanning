
#include "dingTaskAllocation.h"
#include "taskLocation.h"
#include <iostream>

using namespace std;
namespace ding {
	std::vector<size_t> dingTaskAllocation(vector<double> const & vx, vector<double> const & vy, vector<vector<double>> const & reg_x, vector<vector<double>> const & reg_y)
	{
		for (size_t i = 0; i < vx.size(); i++)
		{
			std::cout << "x = " << vx[i] << std::endl;
			std::cout << "y = " << vy[i] << std::endl;
		}
		for (size_t i = 0; i < reg_x.size(); i++)
		{
			std::cout << "index is " << i << endl;
			for (size_t j = 0; j < reg_x[i].size(); j++)
			{
				cout << "reg_x = " << reg_x[i][j] << endl;
				cout << "reg_y = " << reg_y[i][j] << endl;
			}

		}		
		int numOfUgv = vx.size();
		int numOfTask = reg_x.size();
			/*申请内存*/
		double **rewardMatix = new double*[numOfTask];
		for (int i = 0; i<numOfTask; i++)
			rewardMatix[i] = new double[numOfUgv];

		int **allocationResult = new int*[numOfTask];
		for (int i = 0; i<numOfTask; i++)
			allocationResult[i] = new int[numOfUgv];


		cout << "wtf1" << endl;
		for (int i = 0; i<numOfTask; i++) {
			for (int k = 0; k<numOfUgv; k++) {
					allocationResult[i][k] = 0;
					rewardMatix[i][k] = 0;
				}
			}
			/*初始化*/
			UGV *ugv = new UGV[numOfUgv];
			for (int i = 0; i<numOfUgv; i++) {
				double x = vx[i];
				double y = vy[i];
				int id = i;
				ugv[i].setID(id);
				ugv[i].setPoint(x, y);
			}

			Area *task = new Area[numOfTask];
			for (int i = 0; i<numOfTask; i++) {
				double area[100];
				int areaNum = reg_x[i].size();
				for (int k = 0; k<areaNum; k++) {
					double x = reg_x[i][k];
					double y = reg_y[i][k];
					area[2 * k] = x;
					area[2 * k + 1] = y;
				}
				int id = i;
				task[i].setAreaNum(areaNum);
				task[i].setAreaID(id);
				task[i].setAreaPoint(area);
				double x = 0;
				double y = 0;
				for (int j = 0; j<areaNum; j++) {
					x = x + area[2 * j];
					y = y + area[2 * j + 1];
				}

				task[i].setTaskPoint(x / areaNum, y / areaNum);
			}

			cout << "wtf2" << endl;

			/*Stage 1*/
			for (int i = 0; i<numOfTask; i++) {
				for (int j = 0; j<numOfUgv; j++) {
					rewardMatix[i][j] = objectFunction(task[i], ugv[j]);
				}
			}

			for (int i = 0; i<numOfTask; i++) {
				int k = findMaxReward(rewardMatix[i], numOfUgv);
				allocationResult[i][k] = 1;
				for (int m = 0; m<numOfTask; m++) {
					rewardMatix[m][k] = -1000;
				}
			}

			//for(int i=0;i<numOfTask;i++){
			//		for(int j=0;j<numOfUgv;j++)
			//		cout<<rewardMatix[i][j]<<',';
			//		cout<<endl;
			//	}

			cout << "wtf3" << endl;

			/*Stage 2*/
			if (numOfUgv > numOfTask&&numOfTask != 1) {
				double **newRewardMatix = new double*[numOfUgv - numOfTask];
				for (int i = 0; i < numOfUgv - numOfTask; i++) {
					newRewardMatix[i] = new double[numOfTask + 1];
				}
				int m = 0;
				for (int i = 0; i < numOfUgv; i++) {
					int flag = 0;
					for (int k = 0; k < numOfTask; k++)
						flag = flag || allocationResult[k][i];
					if (!flag) {
						newRewardMatix[m][numOfTask] = i;
						for (int k = 0; k < numOfTask; k++) {
							newRewardMatix[m][k] = objectFunction(task[k], ugv[i]);
						}
						m++;
					}
				}

				double *MaxMin;
				MaxMin = new double[numOfUgv - numOfTask];

				for (int i = 0; i < numOfUgv - numOfTask; i++) {
					MaxMin[i] = findMaxMin(newRewardMatix[i], numOfTask);
				}

				for (int i = 0; i < numOfUgv - numOfTask; i++) {
					int newUgvIndex = findMaxReward(MaxMin, numOfUgv - numOfTask);
					int taskIndex = findMaxReward(newRewardMatix[newUgvIndex], numOfTask);
					int ugvIndex = int(newRewardMatix[newUgvIndex][numOfTask]);
					allocationResult[taskIndex][ugvIndex] = 1;
					MaxMin[newUgvIndex] = 0;
				}
				delete[]MaxMin;
				for (int i = 0; i < numOfUgv - numOfTask; i++)
					delete[] newRewardMatix[i];
				delete[] newRewardMatix;
			}
			if (numOfTask == 1) {
				for (int i = 0; i < numOfUgv; i++)
					allocationResult[0][i] = 1;
			}
			vector<size_t> res;
			for (int i = 0; i<numOfUgv; i++) {
				int j = 0;
				for (; j<numOfTask; j++) {
					if (allocationResult[j][i] == 1)
						break;
				}
				//int k = task[j].getID();
				res.push_back(task[j].getID());
			}
			//释放
			for (int i = 0; i<numOfTask; i++) {
				delete[]rewardMatix[i];
				delete[]allocationResult[i];
			}
			delete[]rewardMatix;
			delete[]allocationResult;
			delete[]task;
			delete[]ugv;
			cout << "wtf4" << endl;

;
		return res;
	}

}