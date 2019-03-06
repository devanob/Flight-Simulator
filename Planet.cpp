
#include "Planet.h"
#include <iostream>
Planet::Planet(const float &objradius, const float &OrbitalRadius,
               const float& xCentre, const float& yCentre, const float& zCentre, 
               const float &rotationsPerSec) :
               Orbital(objradius,OrbitalRadius)
{
    this->setActualPosition(0,0,0);
    this->setCentreAbout(xCentre,yCentre,zCentre);
    this->angleRotation = (rotationsPerSec * 360) / 30.0;
    currentAngle = 0.0;
    setNeedsRedraw(true);
    this->setDrawMoonOrbital(false);
    //DEFAULT Color;
}

float Planet::addMoons()
{
    float randNum = rand() / (float)RAND_MAX;
    while (randNum > 0.50 || randNum == 0.0)
        randNum = rand() / (float)RAND_MAX;
    float moonOrbit = getObjRadius() * 2*(moons.size() + 1);
    this->moons.push_back(new Moon(getObjRadius() * 0.25,
                              moonOrbit,
                              0,0,0,
                              randNum)
                          );
    return moonOrbit;
}

void Planet::drawMoons()
{
    for(unsigned int i  = 0; i < moons.size() ; i++){
        moons[i]->draw();
    }
}

bool Planet::nextFrame()
{
    currentAngle += angleRotation;
    if (currentAngle > 360){
        currentAngle = 0.0;
    }
    vector<GLfloat> currentPostion;
    if (moons.size() > 0 ){
        currentPostion.x = getOrbitalRadius() * std::cos(-currentAngle * degreeToRads);
        currentPostion.z = getOrbitalRadius() * std::sin(-currentAngle * degreeToRads);
        currentPostion.y = 0.0;
        setActualPosition(currentPostion.x,
                          currentPostion.y,
                          currentPostion.z);
        for (unsigned int i = 0 ; i < moons.size() ; i++){
            moons[i]->setCentreAbout(actualPosition.x,
                                     actualPosition.y,
                                     actualPosition.z);
        }
        for (unsigned int i = 0 ; i < moons.size() ; i++){
            moons[i]->nextFrame();

        }
    }


    setNeedsRedraw(true);

    return true;
}

void Planet::draw()
{
   if (needsRedraw == true){
       //Draw PLanet
       preDrawSetup();///starting drawing  planet
           glRotated(currentAngle,0.0, 1.0, 0.0);
           glTranslated(getOrbitalRadius(), 0.0,0.0);
           glColor4f(getColour().x, getColour().y, getColour().z,1.0);
           glutSolidSphere(getObjRadius(), 100,100);
       postDrawDeSetup();///stop drawing planet
       /////draw Rings
       ///start drawing moon ring orbit
       drawCircle();
       ///Draw Moons
       drawMoons();
    }
}

bool Planet::getDrawMoonOrbital() const
{
    return drawMoonOrbital;
}

void Planet::setDrawMoonOrbital(bool value)
{
    drawMoonOrbital = value;
}



void Planet::drawCircle()
{
    if(getDrawMoonOrbital() == true && moons.size() > 0){
        preDrawSetup();
        glLineWidth(1);
        glTranslated(getActualPosition().x,
                     getActualPosition().y,
                     getActualPosition().z
                     );
        vector<GLfloat> ringCircle;
        glColor3f(1.0,1.0,1.0);
        for(unsigned int i = 0 ; i < this->moons.size() ; i++){
            glBegin(GL_LINE_LOOP);
            for (unsigned int angle = 0 ; angle <=360 ; angle+=3 ){
                ringCircle.x = moons[i]->getOrbitalRadius() * std::cos(degreeToRads*angle);
                ringCircle.z = moons[i]->getOrbitalRadius() * std::sin(degreeToRads*angle);
                ringCircle.y=  0.0;
                glVertex3f(ringCircle.x,ringCircle.y,ringCircle.z);
            }
            glEnd();
       }
       postDrawDeSetup();
    }
    


}
