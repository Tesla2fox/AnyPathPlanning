#include "taskLocation.h"
namespace ding {
	double intAreaCalc(std::vector<myPoint> &vecPoly)
	{
		int iCycle, iCount;
		double	iArea;
		iCycle = 0;
		iArea = 0;
		iCount = vecPoly.size();

		for (iCycle = 0; iCycle < iCount; iCycle++)
		{
			iArea = iArea + (vecPoly[iCycle].x*vecPoly[(iCycle + 1) % iCount].y - vecPoly[(iCycle + 1) % iCount].x*vecPoly[iCycle].y);
		}
		return abs(0.5*iArea);
	}
	double findMaxMin(double *rewardMatix2, int numberOfTask)
	{
		double max1;  //最大  
		double max2;  //次大  
		if (rewardMatix2[0] > rewardMatix2[1])
			max1 = rewardMatix2[0], max2 = rewardMatix2[1];
		else
			max1 = rewardMatix2[1], max2 = rewardMatix2[0];
		for (int i = 1; i < numberOfTask; i++)
		{
			if (rewardMatix2[i] > max1)  //比最大的都大  
			{
				max2 = max1;
				max1 = rewardMatix2[i];
			}
			else if (rewardMatix2[i] > max2 && rewardMatix2[i] < max1)  //a[i]应该是新老二，老大不变  
				max2 = rewardMatix2[i];
		}
		return max1 - max2;
	}
	int findMaxReward(double *rewardMatix, int numberOfUgv) {
		double m = rewardMatix[0];
		int k = 0;
		for (int j = 1; j < numberOfUgv; j++) {
			if (rewardMatix[j] > m) {
				m = rewardMatix[j];
				k = j;
			}
		}
		return k;
	}
}