#ifndef FlightSimulator_H
#define FlightSimulator_H
#include "OpenGlFuncTools.h"
#include <iostream>
#include <memory>
#include <QuadEnvironment.h>
#include "Plane.h"
#include "MoutainObjects.h"
#include "SeaSkyTerrain.h"

#define GRIDSIZE 150
///FramesRateControl
//#define FRAMEPERSEC 30;
//#define FRAMEMILLISECND  (1/(FRAMEPERSEC - 5 ))
///
/// \brief The FlightSimulator class
///This is Graphics Handlier For this Render System
/// This Class handles the intialization of the glutLoop Functions
/// Handles The Drawing Of Menue And Shape Animation Class


class FlightSimulator
{
public:
    //Enviroment Function And Flags Begin//
    std::unique_ptr<QuadEnvironment> quadEnviro;
    std::unique_ptr<Plane> planeObj;
    std::unique_ptr<MoutainObjects> Moutain;
    std::unique_ptr<SeaSkyTerrain> seasky;
    //Which Objects To Draw
    bool drawQaud;
    bool drawskySea;
    bool drawMountains;
    bool drawFog;
    //Enviroment Function And Flags End//
    static FlightSimulator* thisInstance;
    //static FlightSimulator* thisInstance;
    bool nexFrame();
    vector<GLfloat> eyePosition; // the point where the eyes is located
    vector<GLfloat> LookAtVector; // the  vector for the lookatCentre
    vector<GLfloat> upVector; // the up vector <Perependicular>
    //Function and members foor the speed and movement vector
    vector<GLfloat> movementVector;//movmement vector
    float speed;
    float speedIncrement;
    //adjust CameraVector
    void adjustCameraPositionVector();
    static float MAX_TURNING_ANGLE ; // the angle of turning max
    static float MAX_TILT_ANGLE ; // the angle of tilting max
    static float MAX_SPEED;
    static float MINSPEED;
    static float zoomInFactor;
    double angleTurn; // the current angle of turning
    ////
    double LowerX; //the size of the innner Solar System height
    double UpperX; //the size of the inner Solar System width
    //Zooming Feature
    float angleFOV;
    bool zoomIn;
    bool zoomOut;
    void lookAt();
    void generateTurnAngle(const int& MousePositionWidth);
    double toleranceOfTurning; //detemrines how much of the mouse should be be in either direction
    //before a turn is generated

     // angle to rotating to rotate
    ///
    /// \brief thisInstance
    ///The inner instance of this class contain non- static method that deal
    /// with the menue and AnimationHandlier unlike the outer version fo theis class
    /// without a allocated instance non-static members are avaible

    ///
    /// \brief menu
    ///This handles the interaction with the menue
    //Plane* spaceShip;
    bool setPlanePos();
    //Lighting SetUP

    ////
    /// \brief shapeAnim Handles The Animations Of The steps
    ///
    /// \brief WindowWidth
    ///The Current Size Of Real World window for resizing(Width)
    unsigned int WindowWidth;
    ///
    /// \brief WindowHeight The Current Size Of Real World window for resizing(Height)
    ///
    unsigned int WindowHeight;
    ////
    /// \brief FlightSimulator - Intializing the Outer Class of this class
    /// \param argc - the command line argument
    /// \param argv - the command line argument
    /// \param WindowWidth - the Width Of the Window
    /// \param WindowHeight - the Height Of the Window
    ///
    FlightSimulator(int argc, char **argv, const unsigned int& WindowWidth,
    const unsigned int& WindowHeight );
    ///
    /// \brief FlightSimulator-Handles Intiaization Of The Inner This Instance Class
    /// \param WindowWidth - The Width Of the Window
    /// \param WindowHeight - The Height Of The Window
    ///
    FlightSimulator(const unsigned int &WindowWidth, const unsigned int &WindowHeight);
    ///Handles Mouse Control OF the Menue/IS Wrapper To MouseControl
    /// ///
    ///  button is the buton pressed
    /// x is the coordinates of the mouse when it is press in pixel coorindinates
    ///
    /// \brief mouseControl - The inner this instance of this class than control the Pixel Cooridinates
    ///  /// \param button - the button pressed
    /// \param state - the state of the button pressed
    /// \param x - x Pixel Coorinates
    /// \param y -  y Pixel Cooridinates
    ///
    void setUpProspective();
    void KeyboardFunc(const unsigned char& key,
                             const int& x, const int& y);
    static void wrapperKeyboardFunc(unsigned char key,
                             const int x, const int y);
    ///
    /// \brief WarpDraw Warps Around the Draw Function of draw function
    ///
    static void WarpDraw();
     void draw();
     ///
     /// \brief setup - Sets Up the glut System for interaction
     /// \param argc - command line arguments
     /// \param argv - command line arguments
     /// \param width - the width of the window
     /// \param height - the height of the window
     ///
    void setup(int argc, char **argv, const int& width, const int& height);
    ///
    /// \brief WrapResize - Wraps Around the Resize method
    /// \param width -the width of the window
    /// \param height- the height of the window
    ///
    static void WrapResize(int width,int height);
    ///
    /// \brief resize- redraw the current screen when the window is resize
    ///\param width -the width of the window
    /// \param height- the height of the window
    ///
    void resize(const int& width, const int& height);
    ///
    /// \brief executeProgram
    ///executes the glutMainLoop
    void executeProgram();
    ///Wrappe Idle Funciton
    static void WarapperIdleFunc();
    ///
    /// \brief WrapperAnimate - Wrapper For the Animate Function
    /// \param i
    ///
    static void WrapperAnimate(int i);
    ///
    /// \brief animate- Animates both The menue and animation of this program
    /// set at a rate of ~30 frames per second
    /// \param i - unused parametre
    //Reugular KeyBoard Control
    static void WrapperRegularKeyUp(unsigned char key, int x, int y);
    void regularKeyUp(const unsigned char& key, const int& x, const int& y);

    //Special Keybaord Control
    static void WrapperspecialFunc(int key, int x, int y);
    void specialFunc(const int& key, const int& x, const int& y);
    static void WrapperFuncUp(int key, int x, int y);
    void specialFuncUp(const int& key, const int& x, const int& y);
    //Motion Contorl
    static void WrappermouseMotionControl(int x, int y);
    void mouseMotionControl(const int& x, const int& y);
    ///Camera Control Flags And Plane Movment And Speed //
    bool inCreaseSpeed;
    bool reduceSpeed;
    bool cameraForwards;
    bool cameraBackWards;
    bool cameraLeft;
    bool cameraRight;
    bool cameraUp;
    bool cameraDown;
    //Draw Enviornment//
    void animate(const unsigned& i );

    ~FlightSimulator();

    bool getCameraForwards() const;
    void setCameraForwards(bool value);
    bool getCameraBackWards() const;
    void setCameraBackWards(bool value);
    bool getCameraLeft() const;
    void setCameraLeft(bool value);
    bool getCameraRight() const;
    void setCameraRight(bool value);
    bool getCameraUp() const;
    void setCameraUp(bool value);
    bool getCameraDown() const;
    void setCameraDown(bool value);
    bool getDrawStars() const;
    void setDrawStars(bool value);
    void setInCreaseSpeed(bool value);
    void setReduceSpeed(bool value);
    bool getInCreaseSpeed() const;
    bool getReduceSpeed() const;
    bool getDrawQaud() const;
    void setDrawQaud(bool value);
    bool getDrawskySea() const;
    void setDrawskySea(bool value);
    bool getDrawFog() const;
    void setDrawFog(bool value);
    bool getDrawMountains() const;
    void setDrawMountains(bool value);
    float getAngleFOV() const;
    void setAngleFOV(float value);
    bool getZoomIn() const;
    void setZoomIn(bool value);
    bool getZoomOut() const;
    void setZoomOut(bool value);
};


#endif // FlightSimulator_H
