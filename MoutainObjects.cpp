#include "MoutainObjects.h"
#include "perlinnoise.h"
MoutainObjects::MoutainObjects(const std::string& fileName)
{

    //Set The Random Number Generator
    this->genSeed =  std::mt19937(this->randDevice());
    this->MAX_HEIGHT = 5;
    std::uniform_real_distribution<double> randDistri(0, MAX_HEIGHT);
    //Square

    //MAX Height
    this->squareSideLenth =30;
    generatePoints();
    vector<unsigned int> A;
    vector<unsigned int> B;
    vector<unsigned int> C;
    vector<unsigned int> D;
    //
    A.x = 0+gridOffset;
    A.y = 0+gridOffset;
    //
    B.x = 0 + gridOffset ;
    B.y =MoutainGridSize -1 - gridOffset;
    //
    C.x = MoutainGridSize -1 - gridOffset;
    C.y = 0 + gridOffset;
    //
    D.x = MoutainGridSize -1 - gridOffset;
    D.y = MoutainGridSize -1-gridOffset;
    //Gerate Randomns Heigth At the four corners

    //TextureID-Loard
    this->mountainTextureId = loadExternalTextures(fileName);
    //Generate Moutains
    generateMountains(A,B,C,D,0);
    generateNorms(A,B,C,D);
    gentextureCoords();
    gencolourDepthMap();
    //Set The Default Values
    setNeedsRedraw(false);
    setAddTextures(false);
    setRenderMode(true);
    std::uniform_real_distribution<double> scaleFactor(0, 10);

    this->mountVexScale.x = scaleFactor(genSeed);
    this->mountVexScale.y = scaleFactor(genSeed);
    this->mountVexScale.z= scaleFactor(genSeed);


    
}

bool MoutainObjects::nextFrame()
{
    setNeedsRedraw(true);
    return true ;
}

bool MoutainObjects::getRenderMode() const
{
    return renderMode;
}

void MoutainObjects::setRenderMode(bool value)
{
    renderMode = value;
}

bool MoutainObjects::getAddTextures() const
{
    return addTextures;
}

void MoutainObjects::setAddTextures(bool value)
{
    addTextures = value;
}

bool MoutainObjects::getNeedsRedraw() const
{
    return needsRedraw;
}

void MoutainObjects::setNeedsRedraw(bool value)
{
    needsRedraw = value;
}

void MoutainObjects::draw()
{
    if (getNeedsRedraw() == true){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        if (renderMode == true){
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }


        if (this->addTextures == true){ //if the scenes needs texutures
            glEnable(GL_TEXTURE_2D);
            // Activate texture object.
           glBindTexture(GL_TEXTURE_2D, mountainTextureId);
           //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
           glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        }
        else {
            glDisable(GL_TEXTURE_2D);
        }
        setUpMaterialLighting();
        //Mountain 1
        vector<GLfloat> scale;
        scale.x = 2.5;
        scale.y = 2;
        scale.z = 2.5;
        vector<GLfloat> translate;
        translate.x = 0;;
        translate.y = 2;
        translate.z = 0;
        subdraw(scale,translate);
        glDisable(GL_TEXTURE_2D);//Disable The Texture Since No One Else Needed Them
        glPopMatrix();//
        setNeedsRedraw(false);
    }

}

void MoutainObjects::subdraw(const vector<GLfloat>& scale, const vector<GLfloat>& translate)
{
    glPushMatrix();
    glTranslated(translate.x, 0, translate.z);
    glScalef(scale.x,scale.y,scale.z);
    for (unsigned int  row = 0 ; row  <  MoutainGridSize-1 ; row++){
        glBegin(GL_QUADS);
            for (unsigned int col = 0 ; col < MoutainGridSize-1 ; col++){
                //Normal & Vertix & TextCoords & colour  Point 1
                glColor3fv((GLfloat*)&colourVertix[row][col]);
                glTexCoord2f(textureCoords[row][col].x, textureCoords[row][col].y);
                glNormal3fv((GLfloat*)&pointNorm[row][col]);
                glVertex3fv((GLfloat*)&heightMap[row][col]);
                //Normal & Vertix & TextCoords & colour Point 2
                glColor3fv((GLfloat*)&colourVertix[row][col+1]);
                glTexCoord2f(textureCoords[row][col+1].x, textureCoords[row][col+1].y);
                glNormal3fv((GLfloat*)&pointNorm[row][col+1]);
                glVertex3fv((GLfloat*)&heightMap[row][col+1]);
                //Normal & Vertix & TextCoords & colour Point 3
                glColor3fv((GLfloat*)&colourVertix[row+1][col+1]);
                glTexCoord2f(textureCoords[row+1][col+1].x, textureCoords[row+1][col+1].y);
                glNormal3fv((GLfloat*)&pointNorm[row+1][col+1]);
                glVertex3fv((GLfloat*)&heightMap[row+1][col+1]);
                //Normal & Vertix & TextCoords & colour Point 4
                glColor3fv((GLfloat*)&colourVertix[row+1][col]);
                glTexCoord2f(textureCoords[row+1][col].x, textureCoords[row+1][col].y);
                glNormal3fv((GLfloat*)&pointNorm[row+1][col]);
                glVertex3fv((GLfloat*)&heightMap[row+1][col]);
         }
        glEnd();
    }

    glPopMatrix();

}

void MoutainObjects::setUpMaterialLighting()
{
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
    float matShine[] = { 0.078125*128 };
    // Material properties shared by all enviorment stuff in the scene
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,black);


    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().

    if (getAddTextures() == true){
        glDisable(GL_COLOR_MATERIAL);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,white);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,white);
    }
    else {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    }

}

void MoutainObjects::generateNorms(const vector<unsigned int>& A,const vector<unsigned int>& B,
                                   const vector<unsigned int>& C, const vector<unsigned int>& D){
    this->pointNorm.resize(MoutainGridSize);
    for (auto& gridRow : pointNorm)
        gridRow.resize(MoutainGridSize);
    for (unsigned int  row = 0 ; row  <  MoutainGridSize-1; row++){
        for (unsigned int col = 0 ; col < MoutainGridSize-1; col++){
            if (row == C.x ){ // if points are at the bottom of the grid C || D
                if (row == D.x && col == D.y){ // if the point is the last row and col
                    pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                         heightMap.at(row-1).at(col),heightMap.at(row).at(col-1));
                }
                else { //else bottom regular row
                    pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                         heightMap.at(row-1).at(col),heightMap.at(row).at(col+1));
                }
            }
            else if (col == B.y){
                pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                     heightMap.at(row).at(col-1),heightMap.at(row+1).at(col));
            }
            //Outside Grid
            if (row == MoutainGridSize -1 ){ // if points are at the bottom of the grid OutSide
                if (row == MoutainGridSize -1  && col == MoutainGridSize -1 ){ // if the point is the last row and col
                    pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                         heightMap.at(row-1).at(col),heightMap.at(row).at(col-1));
                }
                else { //else bottom regular row
                    pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                         heightMap.at(row-1).at(col),heightMap.at(row).at(col+1));
                }
            }
            //End
            else if (col == MoutainGridSize -1 ){
                pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                     heightMap.at(row).at(col-1),heightMap.at(row+1).at(col));
            }
            else {
                pointNorm.at(row).at(col) = vectorNormal(heightMap.at(row).at(col),
                                     heightMap.at(row).at(col+1),heightMap.at(row+1).at(col));
            }

        }
    }




}

void MoutainObjects::generateMountains(const vector<unsigned int>& A,
                                       const vector<unsigned int>& B,
                                       const vector<unsigned int>& C,
                                       const vector<unsigned int>& D, unsigned int level)
{
    int noise = 10;
    PerlinNoise2D<double> perNoise(noise);
    double factor = (float) noise/ (MoutainGridSize);
    for (int  row = 1 ; row < this->heightMap.size()-1; row++)
        for (int col =1  ; col < this->heightMap.size()-1; col++){
            double x = factor  * col;
            double y = factor * row;

            this->heightMap[row][col].y =10*perNoise.noise(x, y);
           // std::cout << this->heightMap[row][col].z << std::endl;
        }
}

void MoutainObjects::generatePoints()
{
    //Generate Points Grid
    this->heightMap.resize(MoutainGridSize);
    for (auto& gridRow : heightMap)
        gridRow.resize(MoutainGridSize);

    vector<GLfloat> pointQuad;
    int col = 0;
    int row  = 0;
    float y = 0;
    float x =0;
    for (row = 0 , y  = 0  ; y < squareSideLenth ; y += squareSideLenth / MoutainGridSize,row++ ){
       for(col = 0, x  =0; x < squareSideLenth ;x += squareSideLenth / MoutainGridSize, col++){
           pointQuad.x = x;
           pointQuad.z = y;
           pointQuad.y = 0.0;
           heightMap[row][col] =pointQuad;
       }
    
    }
    std::cout << "vecTor Size" << heightMap.size();

}

void MoutainObjects::gentextureCoords()
{
    //Generate Text Coords
    this->textureCoords.resize(MoutainGridSize);
    for (auto& gridRow : textureCoords)
        gridRow.resize(MoutainGridSize);
    for (unsigned int  row = 0 ; row  <  MoutainGridSize-1; row++){
        for (unsigned int col = 0 ; col < MoutainGridSize-1; col++){
            //Normalize Each TextCoords To A Value x =[0,1] y = [0,1]
            textureCoords.at(row).at(col).x = (this->heightMap.at(row).at(col).x + (this->squareSideLenth /2.0)) / squareSideLenth;
            textureCoords.at(row).at(col).y = (this->heightMap.at(row).at(col).y + (this->squareSideLenth /2.0)) / squareSideLenth;
        }
    }
}

void MoutainObjects::gencolourDepthMap()
{
    float maxHeight = 0;
    this->colourVertix.resize(MoutainGridSize);
    for (auto& gridRow : colourVertix)
        gridRow.resize(MoutainGridSize);

    //Get The Peak In The Mountain
    for (unsigned int  row = 0 ; row  <  MoutainGridSize-1; row++){
        for (unsigned int col = 0 ; col < MoutainGridSize-1; col++){
         maxHeight = std::max(maxHeight,heightMap[row][col].y);
        }
    }
    float topGreen = maxHeight * (3.0/4);
    float bottomWhite= topGreen;
    float topWhite = maxHeight;
    vector<GLfloat> green;
    green.x =0; //R
    green.y = 1; //G
    green.z = 0;//B
    //
    vector<GLfloat> white;
    white.x =1; //R
    white.y = 1; //G
    white.z = 1;//B
    //Now To Set Colour Mapping Linearly With Height
    for (unsigned int  row = 0 ; row  <  MoutainGridSize-1; row++){
        for (unsigned int col = 0 ; col < MoutainGridSize-1; col++){
            float height = heightMap[row][col].y;
            if (height  < 0.0){
                colourVertix[row][col] = green;
            }
            else if (height <= topGreen){
                colourVertix[row][col] =  ((1.0 - (height / topGreen)) +0.3) * green;
            }
            else if (height > bottomWhite){
                colourVertix[row][col] =  (((height - bottomWhite) / (topWhite - bottomWhite))+0.3) * white;
            }
        }
    }


}




