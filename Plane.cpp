#include "Plane.h"
#include <iostream>
#include <fstream>
#include <sstream>
vector<GLfloat> Plane::getEyeOffset() const
{
    return eyeOffset;
}

void Plane::setEyeOffset(const float &eyexoff, const float &eyeyOff, const float &eyezOff)
{
    this->eyeOffset.x = eyexoff;
    this->eyeOffset.y = eyeyOff;
    this->eyeOffset.z = eyezOff;

}



vector<GLfloat> Plane::getEyesPosition() const
{
    return eyesPosition;
}

bool Plane::setEyesPosition(const vector<GLfloat> &value)
{
    eyesPosition = value;
    return true;
}

bool Plane::getRenderMood() const
{
    return renderMood;
}

void Plane::setRenderMood(const bool &value)
{
    renderMood = value;
}

float Plane::getAngleTilt() const
{
    return angleTilt;
}

void Plane::setAngleTilt(const float &value)
{
    angleTilt = value;
}

void Plane::setUpMaterialLighting()
{
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
    float matShine[] = { 10.0 };
    // Material properties shared by all enviorment stuff in the scene
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_EMISSION, black);
}

void Plane::setcolourPlane(const unsigned int &colourNum)
{
    if(colourNum<= 3) {
        glColor3fv(yellow);

    }
    else if(colourNum <= 5) {
        glColor3fv(black);
    }
    else if(colourNum<= 6) {
        glColor3fv(lightPurple);

    }
    else if(colourNum<= 7)
    {
        glColor3fv(blue);

    }
    else if(colourNum <= 10)
    {
        glColor3fv(yellow);

    }
    else if(colourNum <= 11)
    {
        glColor3fv(black);
    }
    else if(colourNum <= 13)
    {
        glColor3fv(yellow);
    }
    else if(colourNum <= 25)
    {
        glColor3fv(blue);
    }
    else if(colourNum <= 32) {
        glColor3fv(yellow);
    }
    else {
        glColor3fv(blue);
    }
}




Plane::Plane(const std::string &fileName)
{

    this->displayListPLane = glGenLists(1);
    readFile(fileName);
    setRenderMood(true);
}


bool Plane::nextFrame()
{


    setNeedsRedraw(true);
    return true;
}

void Plane::draw()
{
    if(needsRedraw == true){
        preDrawSetup();
        setUpMaterialLighting();
        if (getRenderMood() == true) {
            //Render Lines Only No Lighting
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glLineWidth(0.5);
            glDisable(GL_LIGHTING);
            //Transformation
            glLoadIdentity();
            glTranslatef(0,-eyeOffset.y,-eyeOffset.z);
            glRotatef(angleTilt,0,0,1);
            glRotated(-90,0,1,0);
            glScaled(4,4,4);
            //Display
            glCallList(displayListPLane);
            //
            glEnable(GL_LIGHTING);
        }
        else { //Render Fillled Quads

            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glLoadIdentity();
             //Transformation
            glTranslatef(0,-eyeOffset.y,-eyeOffset.z);
            glRotatef(angleTilt,0,0,1);
            glRotated(-90,0,1,0);
            glScaled(4,4,4);
            //display draw
            glCallList(displayListPLane);

        }

        if (getRenderMood() == true){
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        postDrawDeSetup();
        setNeedsRedraw(false);

    }
}





void Plane::readFile(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::in);
    //Object Number
    int objectCount = -1;
    //File Type
    char vOrf = ' ';
    vector<GLdouble> pointverticeNorm;//Float vector
    GLuint   face= 0; //face index
    std::string fileLine =" "; //fileLine
    //Read File
    if(file.fail()){
        throw std::runtime_error("Erorr Opening: "+fileName);
    }
    glNewList(this->displayListPLane, GL_COMPILE);
    while(!file.eof()){
        std::getline(file,fileLine);
        std::istringstream line(fileLine);
        line >> vOrf;
        if(vOrf == 'v'){
            //line >> vOrf;
            line >>
                    pointverticeNorm.x >>
                    pointverticeNorm.y >>
                    pointverticeNorm.z;
            this->verticesPoint.push_back(std::move(pointverticeNorm));
        }
        else if (vOrf == 'n'){
            //line >> vOrf;
            line >>
                    pointverticeNorm.x >>
                    pointverticeNorm.y >>
                    pointverticeNorm.z;

            this->normalsPoint.push_back(std::move(pointverticeNorm));
        }
        else if (vOrf == 'g'){
            //line >> vOrf;
            objectCount++;
            setcolourPlane(objectCount);
            //increment the object for the plane being added
        }
        else if (vOrf == 'f'){
            //line >> vOrf;
            //std::cout<< fileLine << std::endl;
            glBegin(GL_POLYGON);
            while (line >> face)
            {

                glNormal3d(normalsPoint[face-1].x,normalsPoint[face-1].y,normalsPoint[face-1].z);
                glVertex3d(verticesPoint[face-1].x,verticesPoint[face-1].y,verticesPoint[face-1].z);

            }
            glEnd();
        }

    }

    glEndList();
    this->verticesPoint.clear();
    this->normalsPoint.clear();
    file.close();
}
