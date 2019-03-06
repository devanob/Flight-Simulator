#include "Orbital.h"

Orbital::Orbital()
{
    setObjRadius(0.0f);
    setOrbitalRadius(0.0f);
    this->setCentreAbout(0,0,0);
    this->setActualPosition(0,0,0);
    colour.x =0.0;    colour.y =0.0;
    colour.z= 0.0;
    setColour(colour);
}

Orbital::Orbital(const float &Objradius, const float &OrbitalRadius)
{
    this->ObjRadius = Objradius;
    this->OrbitalRadius = OrbitalRadius;
    vector<GLfloat> colour;
    colour.x =1.0;
    colour.y =1.0;
    colour.z= 1.0;
    setColour(colour);

}

void Orbital::preDrawSetup()
{
  glMatrixMode(GL_MODELVIEW); //loads the model view matrix
  glPushMatrix();  //pushes the current model view matrix down
  //glScaled(2,2,2);
}

void Orbital::postDrawDeSetup()
{
    glPopMatrix();//pops the current model view matrix
}

void Orbital::setCentreAbout(const float &x, const float &y, const float &z)
{
    this->centreAbout.x = x; // set the x y z centre about rotation vector
    this->centreAbout.y = y;
    this->centreAbout.z = z;
}

void Orbital::setActualPosition(const float &x, const float &y, const float &z)
{
    this->actualPosition.x = x;// set the x y actualPosition vector
    this->actualPosition.y = y;
    this->actualPosition.z = z;
}

vector<GLfloat> Orbital::getCentreAbout() const
{
    return centreAbout;
}

vector<GLfloat> Orbital::getActualPosition() const
{
    return actualPosition;
}

double Orbital::getObjRadius() const
{
    return ObjRadius;
}

void Orbital::setObjRadius(double value)
{
    ObjRadius = value;
}

double Orbital::getOrbitalRadius() const
{
    return OrbitalRadius;
}

void Orbital::setOrbitalRadius(double value)
{
    OrbitalRadius = value;
}

void Orbital::setColour(const vector<GLfloat> value)
{
    colour = value;
}



void Orbital::setNeedsRedraw(const bool &value)
{
    needsRedraw = value;
}

vector<GLfloat> Orbital::getColour() const
{
    return colour;
}




