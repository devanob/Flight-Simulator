#ifndef MOUTAINOBJECTS_H
#define MOUTAINOBJECTS_H
#include "OpenGlFuncTools.h"
#include <vector>
#include <random>
#define MoutainGridSize  160

#define gridOffset 0
class MoutainObjects
{
public:
    MoutainObjects(const std::string &fileName);
    unsigned int squareGridSize;
    float squareSideLenth;
    float MAX_HEIGHT;
    bool  needsRedraw;
    bool nextFrame();
    bool addTextures;
    bool renderMode;
    void draw();
    void subdraw(const vector<GLfloat>& scale, const vector<GLfloat>& translate);
    std::vector<std::vector<vector<GLfloat>>> heightMap;
    std::vector<std::vector<vector<GLfloat>>> pointNorm;
    std::vector<std::vector<vector<GLfloat>>> colourVertix;
    std::vector<std::vector<vector<GLfloat>>> textureCoords;
    //Get And Set needsRedraw
    bool getNeedsRedraw() const;
    void setNeedsRedraw(bool value);
    //Get And SEt Textures
    bool getAddTextures() const;
    void setAddTextures(bool value);
    //Get An Set TextureMode
    bool getRenderMode() const;
    void setRenderMode(bool value);

private:

    vector<GLfloat> mountVexScale;
    void loadTexture(const std::string &fileName);
    unsigned int mountainTextureId;
    //float maxHeight;
    //void colourFunction();
    void setUpMaterialLighting();
    void generateNorms(const vector<unsigned int> &A,
                       const vector<unsigned int> &B,
                       const vector<unsigned int> &C,
                       const vector<unsigned int> &D);
    void generateMountains(const vector<unsigned int>& A,
                           const vector<unsigned int>& B,
                           const vector<unsigned int>& C,
                           const vector<unsigned int>& D, unsigned int level);
    void generatePoints();
    void gentextureCoords();
     void gencolourDepthMap();

    std::random_device randDevice;  //Will be used to obtain a seed for the random number engine
    std::mt19937 genSeed;

};

#endif // MOUTAINOBJECTS_H
