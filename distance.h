#ifndef _DISTANCE_H
#define _DISTANCE_H

#ifdef __cplusplus
extern "C" {
#endif

#define Home_lati 24.8967
#define Home_long 121.2085
#define Home_Distance 130

enum gps_data
{
 GPS_Lati = 0,
 GPS_Long,
};

float getDistanceGD(float dLati1,float dLong1,float dLati2,float dLong2);

#ifdef __cplusplus
} // extern "C"
#endif

#endif 

