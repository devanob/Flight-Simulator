#ifndef QUADENVIRONMENT_H
#define QUADENVIRONMENT_H
#include "OpenGlFuncTools.h"
#include <iostream>

class QuadEnvironment
{
public:
    QuadEnvironment(const unsigned int & gridSize, const unsigned int& factorSize);
    void draw();
    //Set Grid Size And Factors //
    void setGridSize(const int& value);
    void setFactorSize(const int& value);
    //Render Mode Functions //
    bool getRenderMood() const;
    void setRenderMood(const bool& value);
    //flag for redrawing
    bool needsRedraw;
    bool nextFrame();
    ~QuadEnvironment();
    //Method For setting and getting flag
    bool getNeedsRedraw() const;
    bool setNeedsRedraw(const bool &value);

private:
    GLuint displayListQuadEnv;
    void setUpLighting();
    void setUpMaterialLighting();
    GLUquadricObj *sphere;
    bool renderMood; //true = Wire // false =bsolid
    std::vector<vector<GLfloat>> QuadVertices; //Quad Sqaure Points
    int gridSize ;
    int factorSize;
    void generatePoints();
    vector<GLfloat> colour;
};

#endif // QUADENVIRONMENT_H
