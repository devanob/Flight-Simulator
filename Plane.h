#ifndef Plane_H
#define Plane_H
#include <string>
#include <vector>
#include <fstream>
#include "OpenGlFuncTools.h"
#include "Orbital.h"
#include <ctime>
#include "DevMathvector.h"
#include <limits>
#include <iomanip>
class Plane : public Orbital
{
    std::vector<vector<GLdouble>> verticesPoint;
    std::vector<vector<GLdouble>> normalsPoint;
    vector<GLfloat> eyesPosition;
    vector<GLfloat> eyeOffset;
    public:


        Plane(const std::string & fileName);
        bool nextFrame();
        void draw();


        vector<GLfloat> getEyeOffset() const;
        void setEyeOffset(const float& eyexOff, const float& eyeyOff
                          , const float& eyezOff);

        vector<GLfloat> getEyesPosition() const;
        bool setEyesPosition(const vector<GLfloat> &value);

        bool getRenderMood() const;
        void setRenderMood(const bool& value);

        float getAngleTilt() const;
        void setAngleTilt(const float& value);

private:
        void setUpMaterialLighting();
        float angleTilt;
        bool renderMood; //true = Wire // false =bsolid
        GLuint displayListPLane;
        void setcolourPlane(const unsigned int& colourNum);
        std::vector<vector<GLfloat>> subColourPlane;
        void readFile(const std::string& fileName);


};

#endif // Plane_H
