#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>
#include <random>
#include <ctime>
#pragma pack(push, 1) // packs the struct
template <class type>
struct vectorClass
{
    type x;
    type y;

};

///
template  <class type>
void NormalizeVector(vectorClass<type>& vector);
//

template <class type>
class PerlinNoise2D
{
public:
   PerlinNoise2D(const int &gridSize);
   type noise(const type& x, const type& y);
private:
   type smoothFunction(const type& smoothingCoef,const type& interp1, const type& interp2);
   type dotProductDistance(const type& pointX,const type& pointY,const unsigned int &GridX, const unsigned int &GridY);
   std::vector<std::vector<vectorClass<type>>> perlinGrid;
   void generateGridVector();
   void setUpGrid();
   int gridSize;


};

//
#include <iostream>

template <class type>
PerlinNoise2D<type>::PerlinNoise2D(const int &gridSize){
    this->gridSize = gridSize;
    this->setUpGrid();
    this->generateGridVector();

}

template<class type>
type PerlinNoise2D<type>::noise(const type &x, const type &y)
{

    int x0 = int(fmod(x,gridSize-1));
    int x1 = x0 + 1;
    int y0 = int(fmod(y,gridSize-1));
    int y1 = y0 +1;
    type xMod = fmod(x,gridSize-1);
    type yMod =fmod(y,gridSize-1);
//    std::cout << "Mod" << std::endl;
//    std::cout << xMod << std::endl;
//    std::cout << yMod <<std::endl;
//    std::cout << "mod Ends" << std::endl;
//    std::cout << x0 << std::endl;
//    std::cout << x1 << std::endl;
//    std::cout << y0 << std::endl;
//    std::cout << y1 << std::endl;
    //Compute Gradient dot Product
    type interpoS = this->dotProductDistance(xMod,yMod,x0,y0);
    type interpoT = this->dotProductDistance(xMod,yMod,x1,y0);
    type interpoU = this->dotProductDistance(xMod,yMod,x0,y1);
    type interpoV = this->dotProductDistance(xMod,yMod,x1,y1);
//    std::cout << std::endl;
//    std::cout << interpoS << std::endl;
//    std::cout << interpoT << std::endl;
//    std::cout << interpoU << std::endl;
//     std::cout << interpoV << std::endl;
//    //
    type SmoothFactorX = 3.0*std::pow( xMod - x0 , 2.0) - 2.0*std::pow( xMod - x0,3.0);
    type SmoothFactorY = 3.0*std::pow( yMod - y0 , 2.0) - 2.0*std::pow( yMod - y0,3.0);
//    std::cout << "Smooth Factor " << "Begin" << std::endl;
//        std::cout << SmoothFactorX << std::endl;
//         std::cout << SmoothFactorY << std::endl;
//    std::cout << "Smooth Factor " << "Begin" << std::endl;
    type stInterpolant = this->smoothFunction(SmoothFactorX,interpoS,interpoT);
    type uvInterpolant = this->smoothFunction(SmoothFactorX,interpoU,interpoV);

    type finalNose = this->smoothFunction(SmoothFactorY,stInterpolant,uvInterpolant);
    return finalNose;




}

template<class type>
type PerlinNoise2D<type>::smoothFunction(const type &smoothingCoef, const type &interp1, const type &interp2)
{
    return interp1 + smoothingCoef*(interp2 - interp1);
}

template<class type>
type PerlinNoise2D<type>::dotProductDistance(const type &pointX, const type &pointY, const unsigned int &GridX, const unsigned int &GridY)
{
    type dx = pointX - GridX;
    type dy = pointY - GridY;
    //std::cout <<"Dot Product " << dx * perlinGrid[GridX][GridY].x + dy * perlinGrid[GridX][GridY].y << std::endl;
    return dx * perlinGrid[GridX][GridY].x + dy * perlinGrid[GridX][GridY].y;

}

template<class type>
void PerlinNoise2D<type>::generateGridVector()
{
    std::random_device randDevice;  //Will be used to obtain a seed for the random number engine
    std::mt19937 genSeed;
    genSeed =  std::mt19937(randDevice());
    std::uniform_real_distribution<type> randDistri(-100, 100);
    vectorClass<type> vectorGrid;
    for (int row = 0 ; row < this->gridSize ; row++)
        for (int col = 0 ; col < this->gridSize ; col++){
            vectorGrid.x = randDistri(genSeed);
            vectorGrid.y = randDistri(genSeed);
            NormalizeVector(vectorGrid);
            this->perlinGrid[row][col] = vectorGrid;
            std::cout << perlinGrid[row][col].x;
            std::cout <<"  " << perlinGrid[row][col].y << std::endl;
            std::cout << std::endl;
        }


}

template<class type>
void PerlinNoise2D<type>::setUpGrid(){
    perlinGrid.resize(gridSize);
    for (int i = 0 ; i < gridSize ; i++)
        perlinGrid[i] = std::vector<vectorClass<type>>(gridSize);
}

template<class type>
void NormalizeVector(vectorClass<type> &vector)
{
    type sum = std::pow(vector.x,2.0);
    sum += std::pow(vector.y,2.0);
    sum = std::sqrt(sum);
    vector.x = vector.x / sum;
    vector.y  = vector.y /sum;
}


#endif // PERLINNOISE_H
