

#include "QuadEnvironment.h"

QuadEnvironment::QuadEnvironment(const unsigned int &gridSize, const unsigned int &factorSize)
{
    setGridSize(gridSize);
    setFactorSize(factorSize);
    //Set colour Of Grid
    //Intialize Glu Sphere
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    //gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    //
    setRenderMood(true);
    generatePoints();


}

void QuadEnvironment::draw()
{

    if (getNeedsRedraw() == true){
        glDisable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        setUpLighting();//Set Up The Lighting For this Enviroment
        setUpMaterialLighting();
        //glPopMatrix();
        glColor4fv((GLfloat*)&seaBlue);
        if (getRenderMood() == true) { //Render Lines Only
            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glBegin(GL_QUADS); //Render Quads
            for (unsigned int i =0; i < QuadVertices.size() ; i++){
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3f(QuadVertices[i].x, QuadVertices[i].y, QuadVertices[i].z);
            }
            glEnd();
            glEnable(GL_LIGHTING);
        }
        else { //Render Fillled Quads
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glCallList(this->displayListQuadEnv);
        }


        glDisable(GL_LIGHTING);
        //Draw Sphere And Coordinates
        glLineWidth(1);
        glColor3f(1,1,1);
        glTranslated(0,0.5,0);
        gluSphere(sphere, 0.0, 10, 10); //draw Sphere Centre 0,0
        //draw axis
        //draw Line X Axis
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2*factorSize,0,0);
        glEnd();
        //draw line Y Axis
        glBegin(GL_LINES);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2*factorSize,0);
        glEnd();
        //draw Line Z axis
        glBegin(GL_LINES);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2*factorSize);
        glEnd();
        glPopMatrix();
        glLineWidth(1);
        glEnable(GL_LIGHTING);
        setNeedsRedraw(false);
    }


}

void QuadEnvironment::setGridSize(const int&  value)
{
    gridSize = value;
}

void QuadEnvironment::setFactorSize(const int &value)
{
    factorSize = value;
}

bool QuadEnvironment::getRenderMood() const
{
    return renderMood;
}

void QuadEnvironment::setRenderMood(const bool &value)
{
    renderMood = value;
}

bool QuadEnvironment::nextFrame()
{
    setNeedsRedraw(true);
}

bool QuadEnvironment::getNeedsRedraw() const
{
    return needsRedraw;
}

bool QuadEnvironment::setNeedsRedraw(const bool &value)
{
    needsRedraw = value;
}

void QuadEnvironment::setUpLighting()
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

void QuadEnvironment::setUpMaterialLighting()
{
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
    float matShine[] = {50.0 };
    // Material properties shared by all enviorment stuff in the scene
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);


    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_EMISSION, seaBlue);
}


QuadEnvironment::~QuadEnvironment()
{
    gluDeleteQuadric(sphere);//destroys the quadric


}
void QuadEnvironment::generatePoints()
{
    vector<GLfloat> pointQuad;
    for (int z = -gridSize/2 ; z < gridSize/2 ; z++){
        for (int x = -gridSize/2; x < gridSize/2; x++){
            //point 1
            pointQuad.x = x;
            pointQuad.z = z;
            pointQuad.y = 0.0;
            this->QuadVertices.push_back(pointQuad);
            //point 2
            pointQuad.x = x;
            pointQuad.z = z+1;
            pointQuad.y = 0.0;
            this->QuadVertices.push_back(pointQuad);
            //point 3
            pointQuad.x = x+1;
            pointQuad.z = z+1;
            pointQuad.y = 0.0;
            this->QuadVertices.push_back(pointQuad);
            //point 4
            pointQuad.x = x+1;
            pointQuad.z = z;
            pointQuad.y = 0.0;
            this->QuadVertices.push_back(pointQuad);


        }
    }
    //Stretch The Grid Size By A Factor factorSize
    for (auto& vertice : this->QuadVertices){
        vertice.x *=factorSize;
        vertice.z *=factorSize;
    }
    this->displayListQuadEnv = glGenLists(1);
    glNewList(this->displayListQuadEnv, GL_COMPILE);
    glBegin(GL_QUADS); //Render Quads
    for (unsigned int i =0; i < QuadVertices.size() ; i++){
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(QuadVertices[i].x, QuadVertices[i].y, QuadVertices[i].z);
    }
    glEnd();
    glEndList();


}
