#ifndef ORBITAL_H
#define ORBITAL_H
#include <GL/freeglut.h>
#include <vector>
#include "OpenGlFuncTools.h"

///
/// \brief The Orbital class
///A Base Class For Other Solar System Objects
class Orbital
{
public:
    ///
    /// \brief Orbital
    ///The Default Contructor
    Orbital();
    ///
    /// \brief Orbital - Contructor For Generic Planet, Sun, Etc
    /// \param Objradius - The Radius of the oribital
    /// \param OrbitalRadius - The Outer Orbit Radius From the centre
    /// \param colour - the colour f the oribital
    /// \param centre - the centre of the oribtial
    /// \param centreAbout- The Centre Of rotation
    ///
    Orbital(const float& Objradius, const float& OrbitalRadius);
    ///
    /// \brief NextFrame- prepares the next frame for drawing
    /// \return bool if more frames are to be truth
    ///
    virtual bool nextFrame() = 0;
    ///
    /// \brief draw- draw the the current draw
    /// \return void
    ///
    virtual void draw()= 0;
    ///
    /// \brief PreDrawSetup-PrePreps the model view matrix stack for drawing
    /// \return
    ///
    virtual void preDrawSetup();
    ///
    /// \brief PostDrawDeSetup-PostPreps the model view matrix stack for drawing
    /// \return
    ///
    virtual void postDrawDeSetup();
    ///
    /// \brief SetCentreAbout- centre the rotation of object
    /// \param x - x centre of rotation
    /// \param y - y centre of rotation
    /// \param z - z centre of rotation
    ///
    void setCentreAbout(const float& x,const float& y,const float& z );
    ///
    /// \brief SetActualPosition- set the actualy postion of obj in #d space
    /// \param x -  x position  of rotation
    /// \param y - y position  of rotation
    /// \param z - z position  of rotation
    ///
    void setActualPosition(const float& x,const float& y,const float& z );
    ///
    /// \brief getCentreAbout- get the centre of rotation
    /// \return - vector of the centre of rotation
    ///
    vector<GLfloat> getCentreAbout() const;
    ///
    /// \brief getActualPosition - get the actual position
    ///   /// \return a vector of the
    ///
    vector<GLfloat> getActualPosition() const;
    ///
    /// \brief getObjRadius- get the radius of the object
    /// \return returns object radius as float
    ///
    double getObjRadius() const;
    ///
    /// \brief setObjRadius- the current obj radius
    /// \param value
    ///
    void setObjRadius(double value);
    ///
    /// \brief getOrbitalRadius- the radius Orbital Radius
    /// \return  - the Oribital Radius s float
    ///
    double getOrbitalRadius() const;
    ///
    /// \brief setOrbitalRadius-set the Orbital Radius
    /// \param value
    ///
    void setOrbitalRadius(double value);
    void setColour(const vector<GLfloat> value);
    ///
    /// \brief setNeedsRedraw - sets if this object needs to be redrawn
    /// \param value = bool  true = redraw false = dont redraw
    ///
    void setNeedsRedraw(const bool& value);

    vector<GLfloat> getColour() const;

protected:
    double ObjRadius; //The raidus of the current
    double OrbitalRadius; //The radius oribital of the object
    vector<GLfloat> colour;// the colour of the object Orbital
    vector<GLfloat> centre; // the centre of the object
    vector<GLfloat> centreAbout; //the centre about rotation
    vector<GLfloat> actualPosition; // the actual point in space
    bool  needsRedraw;
};

#endif // ORBITAL_H
