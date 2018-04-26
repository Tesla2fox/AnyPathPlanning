#include "dingTaskAllocation.h"
#include<math.h> 
#include <stdio.h>
#include <stdlib.h>
#include<vector>
namespace ding {
	class UGV
	{
	public:
		UGV() {
			xPoint = 0;
			yPoint = 0;
			pro1 = 0;
			pro2 = 0;

		}
		void setPoint(double x, double y) {
			xPoint = x;
			yPoint = y;
		}
		void setID(long int uID) {
			ID = uID;
		}
		double getXPoint() {
			return xPoint;
		}
		double getYPoint() {
			return yPoint;
		}
		double getPro1() {
			return pro1;
		}
		double getPro2() {
			return pro2;
		}
		long int getID() {
			return ID;
		}
	private:
		double xPoint, yPoint, pro1, pro2;
		long int ID;

	};

	class Task
	{
	public:
		Task() {
			xPoint = 0;
			yPoint = 0;
			cap1 = 0;
			cap2 = 0;
		}
		void setTaskPoint(double x, double y) {
			xPoint = x;
			yPoint = y;
		}
		void setTaskID(int x) {
			ID = x;
		}
		double getXPoint() {

			return xPoint;
		}
		double getYPoint() {
			return yPoint;
		}
		double getCap1() {
			return cap1;
		}
		double getCap2() {
			return cap2;
		}
		int getID() {
			return ID;
		}
	private:
		double xPoint, yPoint, cap1, cap2;
		int ID;
	};

	typedef struct stuPoint
	{
		double x;
		double y;
	}myPoint;

	class Area
	{
	private:
		double xPoint, yPoint, cap1, cap2, area;
		int areaId, numArea;
		std::vector<myPoint>vecPoly;

	public:
		double areaPoint[4][2];
		Area() {
			xPoint = 0;
			yPoint = 0;
			cap1 = 0;
			cap2 = 0;
		}
		void setTaskPoint(double x, double y) {
			xPoint = x;
			yPoint = y;
		}
		void setAreaPoint(double* areaVector) {
			for (int i = 0; i < numArea; i++) {
				myPoint myVertex;
				myVertex.x = areaVector[i * 2];
				myVertex.y = areaVector[i * 2 + 1];
				vecPoly.push_back(myVertex);
			}
			area = intAreaCalc(vecPoly);
		}
		void setAreaID(int id) {
			areaId = id;
		}
		void setAreaNum(int num) {
			numArea = num;
		}
		double getArea() {

			return area;
		}
		double getXPoint() {

			return xPoint;
		}
		double getYPoint() {
			return yPoint;
		}
		double getCap1() {
			return cap1;
		}
		double getCap2() {
			return cap2;
		}
		int getID() {
			return areaId;
		}
		double intAreaCalc(std::vector<myPoint> &) {
			int iCycle, iCount;
			double	iArea;
			iCycle = 0;
			iArea = 0;
			iCount = vecPoly.size();

			for (iCycle = 0; iCycle < iCount; iCycle++)
			{
				iArea = iArea + (vecPoly[iCycle].x*vecPoly[(iCycle + 1) % iCount].y - vecPoly[(iCycle + 1) % iCount].x*vecPoly[iCycle].y);
			}
			//printf("area=%f", area);
			return abs(0.5*iArea);
		}

	};

	double objectFunction(Area task, UGV ugv);
	double objectFunction(Task task, UGV ugv);
	int findMaxReward(double *rewardMatix, int numberOfUgv);
	double findMaxMin(double *rewardMatix2, int numberOfTask);
	//void uVector(PointGPS  *movePonit, int numOfUgv, int k, double *u );
	double f(double d);
	double f1(double d);
}