#ifndef OPENGLDRAWINGFUNCTION_H
#define OPENGLDRAWINGFUNCTION_H
#include <cmath>
#include <string>
#include "GL/freeglut.h"
#include <random>
#include <ctime>

void writeBitmapString(void *font, const std::string& text,
       const int& x,const  int& y,
       const int&  z);

#pragma pack(push, 1) // packs the struct
template<class type> // class packs used
struct vector
{
    type x;
    type y;
    type z;

};
float generateNumber(const float& lowerBound,
                     const float& upperBound);
#pragma pack(pop)
const double degreeToRads = M_PI / 180.0 ;
#endif // OPENGLDRAWINGFUNCTION_H
