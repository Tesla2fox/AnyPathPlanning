#include "taskLocation.h"
namespace ding {
	double objectFunction(Task task, UGV ugv) {
		double x = task.getXPoint() - ugv.getXPoint();
		double y = task.getYPoint() - ugv.getYPoint();
		//double cap=task.getCap1()*ugv.getPro1()+task.getCap2()*ugv.getPro2();
		return -sqrt(pow(x, 2) + pow(y, 2));
	}
	double objectFunction(Area task, UGV ugv) {
		double x = task.getXPoint() - ugv.getXPoint();
		double y = task.getYPoint() - ugv.getYPoint();
		//double cap=task.getCap1()*ugv.getPro1()+task.getCap2()*ugv.getPro2();
		double s = task.getArea();
		return -sqrt(pow(x, 2) + pow(y, 2)) / task.getArea();
	}
}
