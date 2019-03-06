#include "opengldrawingfunction.h"
///
/// \brief writeBitmapString
/// \param font - the current font
/// \param text - the text to be displaydd
/// \param x - positon x
/// \param y - positon y
/// \param z - positon z
///
void writeBitmapString(void *font, const std::string &text, const int &x, const int &y, const int &z){
    {
        glRasterPos3f(x,y,z);
        for (unsigned int i = 0 ; i < text.size(); i++){
            glutBitmapCharacter(font, text[i]);
        }
    }
}

float generateNumber(const float &lowerBound, const float &upperBound){
    int range = std::abs(upperBound - lowerBound);
    float randNum = lowerBound + (rand() % (range+1));
    return randNum;

}









