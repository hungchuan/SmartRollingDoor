#include <math.h>
#include "general.h"


float rad(double d)

{

const float pi = M_PI;

return d * pi / 180.0;

}
//================================================================================================
float getDistanceGD(float dLati1,float dLong1,float dLati2,float dLong2)

{

    const float EARTH_RADIUS = 6378.137;

    float radLat1 = rad(dLati1);

    float radLat2 = rad(dLati2);

    float a = radLat1 - radLat2;

    float b = rad(dLong1) - rad(dLong2);

    float s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));

    s = s * EARTH_RADIUS;

    s = round(s * 10000000) / 10000;

    return s;

}
//================================================================================================


