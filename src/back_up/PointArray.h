#pragma once

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
	double lat, lon;
}PointGPS;

typedef struct{
	size_t   size;
	PointGPS *pts;
}PointArrary;



typedef struct {
	size_t   size;
	PointGPS *pts;
	double   *vel;
}PointArraryEx;

typedef struct{
    size_t   size;
	PointGPS *pts;
	double   *vel;
    long     *ID;
}PointArraryExID;


#ifdef __cplusplus
}
#endif