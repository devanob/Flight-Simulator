#ifndef PLANET_H
#define PLANET_H
#include "Orbital.h"
#include "Moon.h"
#include <vector>
class Planet : public Orbital
{
public:
    Planet(const float& objradius, const float& OrbitalRadius,
    const float& xCentre,const float& yCentre, const float& zCentre, const float& rotationsPerSec);
    float addMoons();
    void drawMoons();
    bool nextFrame();
    void draw();
    bool getDrawMoonOrbital() const;
    void setDrawMoonOrbital(bool value);

private:
    void drawCircle();
    bool drawMoonOrbital;
    float angleRotation;
    float currentAngle;
    std::vector<Moon*> moons;

};

#endif // PLANET_H
