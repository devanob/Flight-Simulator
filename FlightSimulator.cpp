#include "FlightSimulator.h"
#include "OpenGlFuncTools.h"
#include <cstdio>

FlightSimulator::FlightSimulator(const unsigned int &WindowWidth, const unsigned int &WindowHeight)
{
    this->WindowHeight  = WindowHeight;
    this->WindowWidth = WindowWidth;
    //set Eye Position
    eyePosition.x =10;
    eyePosition.y =10;
    eyePosition.z =200;
    //Set LookAt Vector
    LookAtVector.x = -eyePosition.x;
    LookAtVector.y = -eyePosition.y;
    LookAtVector.z = -eyePosition.z;
    vectorNormalize(LookAtVector);
    //Set Up Environment SquareQaud
    this->quadEnviro = std::unique_ptr<QuadEnvironment>(new QuadEnvironment(GRIDSIZE,4));
    this->planeObj = std::unique_ptr<Plane>(new Plane("cessna.txt"));
    this->Moutain = std::unique_ptr<MoutainObjects>(new MoutainObjects("mount03.bmp"));
    this->seasky = std::unique_ptr<SeaSkyTerrain>(new SeaSkyTerrain("sky08.bmp","sea02.bmp"));
    this->planeObj->setEyeOffset(0,2.5,15);

    //SetUpVector
    upVector.x = 0.0f;
    upVector.y = 1.0f;
    upVector.z = 0.0f;
    //setUp Prospective
    setUpProspective();
    //Set up LookAt
    lookAt();
    //Set Movment To default False
    setCameraLeft(false);
    setCameraRight(false);
    setCameraUp(false);
    setCameraDown(false);
    //Set X axis factor
    this->speed = MINSPEED;
    this->speedIncrement= 1/60.;
    this->angleTurn = 0.0;
    this->toleranceOfTurning = 0.0;
    angleFOV =  30; //the field of veiew is by default 45
    //Default Drawing Of Object Until Changed By The User
    setDrawMountains(false);
    setDrawFog(false);
    setDrawskySea(false);
    setDrawQaud(true);




}

void FlightSimulator::setUpProspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WindowWidth, WindowHeight);
    vector<GLfloat> lUx = perspectiveGL(angleFOV,this->WindowWidth / (float) this->WindowHeight, 10.0,805.0);
    this->LowerX = lUx.x;
    this->UpperX = lUx.y;
}

bool FlightSimulator::getDrawQaud() const
{
    return drawQaud;
}

void FlightSimulator::setDrawQaud(bool value)
{
    drawQaud = value;
}

bool FlightSimulator::getDrawskySea() const
{
    return drawskySea;
}

void FlightSimulator::setDrawskySea(bool value)
{
    drawskySea = value;
}

bool FlightSimulator::getDrawFog() const
{
    return drawFog;
}

void FlightSimulator::setDrawFog(bool value)
{
    drawFog = value;
}



bool FlightSimulator::getDrawMountains() const
{
    return drawMountains;
}

void FlightSimulator::setDrawMountains(bool value)
{
    drawMountains = value;
}

bool FlightSimulator::nexFrame()
{
    if (getZoomIn() == true){
        if (angleFOV <= 30.0)
            angleFOV = 30.0;
        else {
            angleFOV-=zoomInFactor;
            this->setUpProspective();
        }

    }
    else if (getZoomOut() == true){
        if (angleFOV>= 90.0)
            angleFOV = 90.0;
        else {
            this->setUpProspective();
            angleFOV+=zoomInFactor;
        }
    }
    if (getCameraUp() == true || getCameraDown() == true ||
            getCameraLeft() == true  || getCameraRight() == true){
        this->lookAt();
    }
    if (getInCreaseSpeed() == true){
        if (speed >= MAX_SPEED){
            speed = MAX_SPEED;
        }
        else {
            speed+=speedIncrement;
        }

    }
    if (getReduceSpeed() == true){
        if (speed <= MINSPEED){
            speed = MINSPEED;
        }
        else {
            speed-=speedIncrement;
        }
    }
    planeObj->nextFrame();
    //Pick Which Environment To Draw
    if (getDrawQaud() == true){
        this->quadEnviro->nextFrame();
    }
    else {
        this->seasky->nextFrame();
    }
    //get Moutain if needed
    if (getDrawMountains() == true){
        this->Moutain->nextFrame();
    }
    if (getDrawFog() == true){
        //fog control goes here
    }
    return true;

}

void FlightSimulator::adjustCameraPositionVector()
{
    if (angleTurn == 0.0)
        return;
    else{
        vector<GLfloat> temp;
        temp.x = LookAtVector.x;
        temp.z = LookAtVector.z;
        LookAtVector.x = temp.x*std::cos(degreeToRads*angleTurn) - temp.z*std::sin(degreeToRads*angleTurn);
        LookAtVector.z = temp.x*std::sin(degreeToRads*angleTurn) + temp.z*std::cos(degreeToRads*angleTurn);
    }
}

bool FlightSimulator::getZoomOut() const
{
    return zoomOut;
}

void FlightSimulator::setZoomOut(bool value)
{
    zoomOut = value;
}

bool FlightSimulator::getZoomIn() const
{
    return zoomIn;
}

void FlightSimulator::setZoomIn(bool value)
{
    zoomIn = value;
}

float FlightSimulator::getAngleFOV() const
{
    return angleFOV;
}

void FlightSimulator::setAngleFOV(float value)
{
    angleFOV = value;
}






void FlightSimulator::lookAt()
{
    //setUpProspective();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (getCameraUp() == true){
        eyePosition.y += 0.09;
    }
    else if (getCameraDown() == true){
        eyePosition.y -= 0.09;
    }
    ///Turn
    if (getCameraLeft() == true){
        adjustCameraPositionVector();
    }
    else if(getCameraRight() == true){
        adjustCameraPositionVector();

   }
    //printVector(LookAtVector);
    eyePosition.x += speed*LookAtVector.x;
    eyePosition.z += speed*LookAtVector.z;
    gluLookAt(eyePosition.x,
              eyePosition.y,
              eyePosition.z,
              eyePosition.x + LookAtVector.x,
              eyePosition.y + LookAtVector.y,
              eyePosition.z + LookAtVector.z,
              upVector.x,
              upVector.y,
              upVector.z
              );
}

void FlightSimulator::generateTurnAngle(const int& MousePositionWidth)
{
    float totalRealWordWidth = std::abs(UpperX - LowerX);//The total real wordl width

    float realCoords = LowerX + ((MousePositionWidth /(float) WindowWidth)
            * totalRealWordWidth); // the coords in the real world

    if (realCoords < 0 && realCoords < -(toleranceOfTurning*totalRealWordWidth)/2.){
        angleTurn = std::abs(realCoords) / ((1.0-toleranceOfTurning/2)*totalRealWordWidth/2.);
        this->planeObj->setAngleTilt(MAX_TILT_ANGLE*angleTurn);
        angleTurn*=-MAX_TURNING_ANGLE;
        setCameraLeft(true);
        setCameraRight(false);
        return;
    }
    else if (realCoords > 0 && realCoords > (toleranceOfTurning*totalRealWordWidth)/2.){
        angleTurn = std::abs(realCoords) / ((1.0-toleranceOfTurning/2.)*totalRealWordWidth/2.);
        this->planeObj->setAngleTilt(-MAX_TILT_ANGLE*angleTurn);
        angleTurn*=MAX_TURNING_ANGLE;
        setCameraRight(true);
        setCameraLeft(false);
        return;
    }


    else {
        angleTurn = 0.0;
        setCameraLeft(false);
        setCameraRight(false);
        return;
    }

}


bool FlightSimulator::setPlanePos()
{
    return true;
}



FlightSimulator::FlightSimulator(int argc, char **argv, const unsigned int &WindowWidth, const unsigned int &WindowHeight)
{

    if (thisInstance == nullptr){ // if no inner class is created
        setup(argc,argv, WindowWidth,WindowHeight);
        thisInstance = new FlightSimulator(WindowWidth,WindowHeight);
    }
    else {
        delete thisInstance; // if a new class is created when already created this is clas is crated
        setup(argc,argv, WindowWidth,WindowHeight);
        thisInstance = new FlightSimulator(WindowWidth,WindowHeight);
    }
}

void FlightSimulator::KeyboardFunc(const unsigned char & key,
                                        const int& x, const int& y)
{
    if (key == 'w'){
        this->quadEnviro->setRenderMood(!quadEnviro->getRenderMood());
        this->planeObj->setRenderMood(!planeObj->getRenderMood());
        this->Moutain->setRenderMode(!Moutain->getRenderMode());
        this->seasky->setRenderMode(!this->seasky->getRenderMode());
    }
    if (key == 't'){
        this->Moutain->setAddTextures(!Moutain->getAddTextures());
    }
    if (key == 'm'){
        setDrawMountains(!getDrawMountains());
    }
    if (key == 's')
        setDrawQaud(!getDrawQaud());
    if (key == 'x')
        setZoomIn(true);
    else if (key == 'z')
        setZoomOut(true);
    if (key == 'a')
        this->seasky->setAnimate(!seasky->getAnimate());



}

void FlightSimulator::wrapperKeyboardFunc(unsigned char key, const int x, const int y)
{
    thisInstance->KeyboardFunc(key,x,y);
}


void FlightSimulator::WarpDraw()
{
    thisInstance->draw();
}

void FlightSimulator::draw()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    this->quadEnviro->draw();
    this->seasky->draw();
    this->planeObj->draw();
    this->Moutain->draw();
    glutSwapBuffers();

}

void FlightSimulator::setup(int argc, char **argv, const int &width, const int &height)
{

    glutInit(&argc, argv);
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    //glutInitContextVersion(4, 5);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Final Project:Flight Simulator");
    glutDisplayFunc(FlightSimulator::WarpDraw);
    glutKeyboardFunc(FlightSimulator::wrapperKeyboardFunc);
    glutReshapeFunc(FlightSimulator::WrapResize);
    glutSpecialFunc(FlightSimulator::WrapperspecialFunc);
    glutSpecialUpFunc(FlightSimulator::WrapperFuncUp);
    glutKeyboardUpFunc(FlightSimulator::WrapperRegularKeyUp);
     glutPassiveMotionFunc(FlightSimulator::WrappermouseMotionControl);
    glutTimerFunc(1, WrapperAnimate, 1);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glEnable( GL_POLYGON_SMOOTH ) ;
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST ) ;
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Specify how texture values combine with current surface color values.
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    //glEnable(GL_TEXTURE_2D);





}

void FlightSimulator::WrapResize(int width, int height)
{
    thisInstance ->resize(width,height);
}

void FlightSimulator::resize(const int &width, const int &height)
{
    this->WindowWidth = width;
    this->WindowHeight = height;
    setUpProspective();
    glutPostRedisplay();

}

void FlightSimulator::executeProgram()
{
    glutMainLoop();
}

void FlightSimulator::WarapperIdleFunc()
{

}

void FlightSimulator::WrapperAnimate(int i)
{
    thisInstance->animate(i);
}

void FlightSimulator::WrapperRegularKeyUp(unsigned char key, int x, int y)
{
    thisInstance->regularKeyUp(key,x,y);
}

void FlightSimulator::regularKeyUp(const unsigned char &key, const int &x, const int &y)
{
    if (key == 'f')
        glutFullScreenToggle();
    if (key == 'z')
        setZoomOut(false);
    else if (key == 'x')
        setZoomIn(false);

}

void FlightSimulator::WrapperspecialFunc(int key, int x, int y)
{
    thisInstance->specialFunc(key,x,y);
}

void FlightSimulator::WrapperFuncUp(int key, int x, int y)
{
    thisInstance->specialFuncUp(key,x,y);
}

void FlightSimulator::specialFunc(const int &key, const int &x, const int &y)
{

     if (key == GLUT_KEY_PAGE_UP)
         setInCreaseSpeed(true);
     if (key == GLUT_KEY_PAGE_DOWN)
         setReduceSpeed(true);
     if (key == GLUT_KEY_UP)
         setCameraUp(true);
     if (key == GLUT_KEY_DOWN)
         setCameraDown(true);


}

void FlightSimulator::specialFuncUp(const int &key, const int &x, const int &y)
{


    if (key == GLUT_KEY_PAGE_UP)
         setInCreaseSpeed(false);
     if (key == GLUT_KEY_PAGE_DOWN)
        setReduceSpeed(false);
     if (key == GLUT_KEY_UP)
         setCameraUp(false);
     if (key == GLUT_KEY_DOWN)
         setCameraDown(false);
}

void FlightSimulator::WrappermouseMotionControl(int x, int y)
{
    thisInstance->mouseMotionControl(x,y);

}

void FlightSimulator::mouseMotionControl(const int &x, const int &y)
{
    this->generateTurnAngle(x);
    //std::cout <<"END mouse";
}

bool FlightSimulator::getReduceSpeed() const
{
    return reduceSpeed;
}





bool FlightSimulator::getInCreaseSpeed() const
{
    return inCreaseSpeed;
}

void FlightSimulator::setInCreaseSpeed(bool value)
{
    inCreaseSpeed = value;
}

void FlightSimulator::setReduceSpeed(bool value)
{
    this->reduceSpeed = value;
}



bool FlightSimulator::getCameraDown() const
{
    return cameraDown;
}

void FlightSimulator::setCameraDown(bool value)
{
    cameraDown = value;
}

bool FlightSimulator::getCameraUp() const
{
    return cameraUp;
}

void FlightSimulator::setCameraUp(bool value)
{
    cameraUp = value;
}

bool FlightSimulator::getCameraRight() const
{
    return cameraRight;
}

void FlightSimulator::setCameraRight(bool value)
{
    cameraRight = value;
}

bool FlightSimulator::getCameraLeft() const
{
    return cameraLeft;
}

void FlightSimulator::setCameraLeft(bool value)
{
    cameraLeft = value;
}

bool FlightSimulator::getCameraBackWards() const
{
    return cameraBackWards;
}

void FlightSimulator::setCameraBackWards(bool value)
{
    cameraBackWards = value;
}

bool FlightSimulator::getCameraForwards() const
{
    return cameraForwards;
}

void FlightSimulator::setCameraForwards(bool value)
{
    cameraForwards = value;
}

void FlightSimulator::animate(const unsigned &i)
{
    //if there is animation to play
    this->nexFrame();
    glutTimerFunc(1,WrapperAnimate,i);
        glutPostRedisplay();//render the next frame of the animation

}







FlightSimulator::~FlightSimulator()
{


}
 FlightSimulator* FlightSimulator::thisInstance =nullptr;
float FlightSimulator::MAX_TURNING_ANGLE = 0.8;
float FlightSimulator::MAX_TILT_ANGLE = 45.0;
float FlightSimulator::MAX_SPEED = 0.466;
float FlightSimulator::MINSPEED = 1/30.;
float FlightSimulator::zoomInFactor = 0.25;
