#ifndef OPENGLDRAWINGFUNCTION_H
#define OPENGLDRAWINGFUNCTION_H
#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include "GL/freeglut.h"
#include <random>
#include <ctime>
#include <fstream>

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

// Routine to read an uncompressed 24-bit color RGB bmp file into a
// 32-bit color RGBA bitmap file (A value being set to 1).
struct BitMapFile
{
   int sizeX;
   int sizeY;
   unsigned char *data;
};
///Normalize Vector
template<class type>
void vectorNormalize(vector<type>& vectorN);

template<class type>
void vectorNormalize(vector<type> &vectorN)
{

    GLdouble length = 0.0;
    length += std::pow(vectorN.x,2);
    length += std::pow(vectorN.y,2);
    length += std::pow(vectorN.z,2);
    length = std::pow(length,0.5);
    vectorN.x /= length;
    vectorN.y /= length;
    vectorN.z /= length;

}

//Cross Product Of Two Vectors
template<class type>
vector<type> vectorCrossProduct(const vector<type> &vector1, const vector<type> &vector2 )
{
    vector<type> vectorA = vector1;;
    vector<type> vectorB = vector2;
    vector<type> vectorCross;
    vectorCross.x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
    vectorCross.y = -((vectorA.x * vectorB.z) - (vectorA.z * vectorB.x));
    vectorCross.z = ((vectorA.x * vectorB.y) - (vectorA.y * vectorB.x));
    return vectorCross;


}

template <class type>
type vectorDotProduct(const vector<type> &vector1, const vector<type> &vector2 );

template <class type>
vector<type> vectorNormal(const vector<type> &vector0, const vector<type> &vector1,
                                const vector<type> &vector2)
{
    vector<type> vectorNorm;
    vector<type> v0v1; // vector v0 -> v1
    v0v1.x = vector1.x - vector0.x;
    v0v1.y = vector1.y - vector0.y;
    v0v1.z = vector1.z - vector0.z;
    //
    vector<type> v0v2; // vector v0 -> v2
    v0v2.x = vector2.x - vector0.x;
    v0v2.y = vector2.y - vector0.y;
    v0v2.z = vector2.z - vector0.z;

    vectorNorm = vectorCrossProduct(v0v1,v0v2);
    vectorNormalize(vectorNorm);
    return vectorNorm;




}
template<class type>
void printVector(vector<type> &vectorN){
    std::cout <<" X: " << vectorN.x << " Y: " << vectorN.y <<" Z: " << vectorN.z << std::endl;
}

///
BitMapFile *getbmp(const std::string& filename);
vector<GLfloat> perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
extern GLfloat yellow[];
extern GLfloat black[];
extern GLfloat lightPurple[];
extern GLfloat blue[];
extern GLfloat red[] ;
extern GLfloat green[];
extern GLfloat white[];
extern GLfloat grey[];
extern GLfloat seaBlue[];
extern GLfloat orange[];
extern GLfloat clear[];
///
/// \brief loadExternalTextures- Loads Texture Into Memory
/// \param fileName
/// \return
///
unsigned int  loadExternalTextures(const std::string& fileName);

template <class typeVector, class typeFactor>
vector<typeVector> operator*(const typeFactor& factor, const vector<typeVector>& vectorRHS){
    vector<typeVector> tempVec = vectorRHS;
    tempVec.x *=  factor;
    tempVec.y *= factor;
    tempVec.z *= factor;
    return tempVec;
}

#endif // OPENGLDRAWINGFUNCTION_H
