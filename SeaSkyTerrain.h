#ifndef SEASKYTERRAIN_H
#define SEASKYTERRAIN_H
#include <string>
#include "OpenGlFuncTools.h"
#include <GL/freeglut.h>
///
/// \brief The SeaSkyTerrain class- Enviroment For Sky And Sea
///
class SeaSkyTerrain
{
public:
    static float angle_increment;
    SeaSkyTerrain(const std::string& skyfile, const std::string& seaFile);
    void draw();
    bool nextFrame();
    bool getRenderMode() const;
    void setRenderMode(bool value);
    void setUpMaterialLighting();
    bool getNeedsRedraw() const;
    void setNeedsRedraw(bool value);
    void setUpLighting();

    bool getAnimate() const;
    void setAnimate(bool value);

private:
    bool animate;
    float angle;
    bool renderMode; //Wire OR Soldi Render
    bool needsRedraw;
    //sea Tuexture and base shape
    GLUquadricObj *disksea;
    unsigned int seaTextureId;
    //sky Tuexture and base shape
    GLUquadricObj *cylinderSky;
    unsigned int skyTextureId;
};

#endif // SEASKYTERRAIN_H
