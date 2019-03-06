#include "OpenGlFuncTools.h"
///
/// \brief writeBitmapString
/// \param font - the current font
/// \param text - the text to be displaydd
/// \param x - positon x
/// \param y - positon y
/// \param z - positon z
///
void writeBitmapString(void *font, const std::string &text, const int &x, const int &y, const int &z){

        glRasterPos3f(x,y,z);
  }



float generateNumber(const float &lowerBound, const float &upperBound){
    int range = std::abs(upperBound - lowerBound);
    float randNum = lowerBound + (rand() % (range+1));
    return randNum;

}




// Routine to read an uncompressed 24-bit color RGB bmp file into a
// 32-bit color RGBA bitmap file (A value being set to 1).
BitMapFile *getbmp(const std::string &filename)
{
    int offset, headerSize;

    // Initialize bitmap files for RGB (input) and RGBA (output).
    BitMapFile *bmpRGB = new BitMapFile;
    BitMapFile *bmpRGBA = new BitMapFile;

    // Read input bmp file name.
    std::ifstream infile(filename.c_str(), std::ios::binary);

    if (!infile.is_open())
        throw std::runtime_error("Cannot Open File : " + filename);

    // Get starting point of image data in bmp file.
    infile.seekg(10);
    infile.read((char *)&offset, 4);

    // Get header size of bmp file.
    infile.read((char *)&headerSize,4);

    // Get image width and height values from bmp file header.
    infile.seekg(18);
    infile.read((char *)&bmpRGB->sizeX, 4);
    infile.read((char *)&bmpRGB->sizeY, 4);

    // Determine the length of zero-byte padding of the scanlines
    // (each scanline of a bmp file is 4-byte aligned by padding with zeros).
    int padding = (3 * bmpRGB->sizeX) % 4 ? 4 - (3 * bmpRGB->sizeX) % 4 : 0;

    // Add the padding to determine size of each scanline.
    int sizeScanline = 3 * bmpRGB->sizeX + padding;

    // Allocate storage for image in input bitmap file.
    int sizeStorage = sizeScanline * bmpRGB->sizeY;
    bmpRGB->data = new unsigned char[sizeStorage];

    // Read bmp file image data into input bitmap file.
    infile.seekg(offset);
    infile.read((char *) bmpRGB->data , sizeStorage);

    // Reverse color values from BGR (bmp storage format) to RGB.
    int startScanline, endScanlineImageData, temp;
    for (int y = 0; y < bmpRGB->sizeY; y++)
    {
       startScanline = y * sizeScanline; // Start position of y'th scanline.
       endScanlineImageData = startScanline + 3 * bmpRGB->sizeX; // Image data excludes padding.
       for (int x = startScanline; x < endScanlineImageData; x += 3)
       {
          temp = bmpRGB->data[x];
          bmpRGB->data[x] = bmpRGB->data[x+2];
          bmpRGB->data[x+2] = temp;
       }
    }

    // Set image width and height values and allocate storage for image in output bitmap file.
    bmpRGBA->sizeX = bmpRGB->sizeX;
    bmpRGBA->sizeY = bmpRGB->sizeY;
    bmpRGBA->data = new unsigned char[4*bmpRGB->sizeX*bmpRGB->sizeY];

    // Copy RGB data from input to output bitmap files, set output A to 1.
    for(int j = 0; j < 4*bmpRGB->sizeY * bmpRGB->sizeX; j+=4)
    {
        bmpRGBA->data[j] = bmpRGB->data[(j/4)*3];
        bmpRGBA->data[j+1] = bmpRGB->data[(j/4)*3+1];
        bmpRGBA->data[j+2] = bmpRGB->data[(j/4)*3+2];
        bmpRGBA->data[j+3] = 0xFF;
    }

    return bmpRGBA;
}

vector<GLfloat> perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{

    GLdouble fW, fH;
    fH = std::tan( fovY / 360 * M_PI ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
    vector<GLfloat> lowerXUpPerX;
    lowerXUpPerX.x = -fW;
    lowerXUpPerX.y = fW;
    return lowerXUpPerX;


}
GLfloat yellow[]={1.0, 1.0, 0.0, 1.0};
GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
GLfloat lightPurple[] = {0.87, 0.58, 0.98, 1.0};
GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat grey[] = {0.05, 0.05, 0.05, 1.0};
GLfloat seaBlue[] = {0.0, 0.3, 0.8, 1.0};
GLfloat orange[] = {1.0, 0.5, 0.0, 1.0};
GLfloat clear[] = {1.0, 1.0, 1.0, 0.0};





unsigned int loadExternalTextures(const std::string &fileName)
{
    unsigned int textID[1];
    glGenTextures(1, textID);
   // Local storage for bmp image data.
   BitMapFile *image;

   // Load the image.
   image = getbmp(fileName);

   // Create texture object texture[0].
   glBindTexture(GL_TEXTURE_2D, textID[0]);

   // Specify image data for currently active texture object.
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                image->sizeX, image->sizeY, 0,
                GL_RGBA, GL_UNSIGNED_BYTE,
                image->data);

   // Set texture parameters for wrapping.
   glTexParameteri(GL_TEXTURE_2D,
                   GL_TEXTURE_WRAP_S,
                   GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,
                   GL_TEXTURE_WRAP_T,
                   GL_REPEAT);

   // Set texture parameters for filtering.
   glTexParameteri(GL_TEXTURE_2D,
                   GL_TEXTURE_MIN_FILTER,
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,
                   GL_TEXTURE_MAG_FILTER,
                   GL_NEAREST);
   return textID[0];
}




