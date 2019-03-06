#include "SeaSkyTerrain.h"

SeaSkyTerrain::SeaSkyTerrain(const std::string &skyfile, const std::string &seaFile)
{
    //Load Both The Sea And Sky Texture
    this->seaTextureId = loadExternalTextures(seaFile);
    this->skyTextureId = loadExternalTextures(skyfile);
    //Set Up Sea Object
    this->disksea =gluNewQuadric();         // Create A Pointer To The Quadric Object
    gluQuadricTexture(disksea , GL_TRUE);      // Create Texture Coords
    gluQuadricNormals(disksea, GLU_SMOOTH);   // Create Smooth Normals
    //Set Up Sky Object
    this->cylinderSky=gluNewQuadric();         // Create A Pointer To The Quadric Object
    animate = 0;
    setAnimate(false);
    setRenderMode(true);
}

void SeaSkyTerrain::draw()
{
    if (this->getNeedsRedraw() == true){
        glPushMatrix();
        setUpLighting();
        if (renderMode == true){
            glDisable(GL_TEXTURE_2D);
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        else {

            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        setUpMaterialLighting();

        //Sea
        //Render Sky

        glRotated(-90,1,0,0);
        glColor3fv(seaBlue);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, this->seaTextureId);
        gluQuadricTexture(this->disksea, getRenderMode() ? GLU_FALSE : GLU_TRUE);
        gluQuadricNormals(this->disksea, GLU_SMOOTH);
        gluDisk(this->disksea,0,500,35,35);
        glTranslated(0,0,-1);
        glRotated(angle,0,0,1);
        glColor3f(1,0,0);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, this->skyTextureId);
        gluQuadricTexture(this->cylinderSky, getRenderMode() ? GLU_FALSE : GLU_TRUE);
        gluQuadricNormals(this->cylinderSky, GLU_SMOOTH);
        gluCylinder(this->cylinderSky,500,200,400,35,35);

        setNeedsRedraw(false);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

bool SeaSkyTerrain::nextFrame()
{
    if (getAnimate()  == true){
        if (angle >= 360.0 )
            angle=0.0;
        else
            angle+=angle_increment;
    }
    setNeedsRedraw(true);
    return true ;
}

bool SeaSkyTerrain::getRenderMode() const
{
    return renderMode;
}

void SeaSkyTerrain::setRenderMode(bool value)
{
    renderMode = value;
}

void SeaSkyTerrain::setUpMaterialLighting()
{


    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
    float matShine[] = { 50 };
    // Material properties shared by all enviorment stuff in the scene
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,black);


    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().

    //if (!getRenderMode()){
        //glDisable(GL_COLOR_MATERIAL);
        //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,white);
        //glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,white);
    //}
    //else {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    //}  // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);



}

bool SeaSkyTerrain::getNeedsRedraw() const
{
    return needsRedraw;
}

void SeaSkyTerrain::setNeedsRedraw(bool value)
{
    needsRedraw = value;
}

void SeaSkyTerrain::setUpLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1, 1, 1, 0.0 };
    float lightPos0[] = { 1,1,0, 0};
    //draw Sphere Centre 0,0


    float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
    //Light Position
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);

    //
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
    glShadeModel(GL_SMOOTH);
    //Distance Light
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);

    //Enable normalization
    glEnable(GL_NORMALIZE);
}

bool SeaSkyTerrain::getAnimate() const
{
    return animate;
}

void SeaSkyTerrain::setAnimate(bool value)
{
    animate = value;
}

float SeaSkyTerrain::angle_increment = 0.1;
