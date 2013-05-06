#include "Test.hpp"
void Test::run()
{
    PixelColor pc1 = PixelColor(100,100,100);
    printColor(pc1);
    pc1.normalizeTo(255);
    printColor(pc1);
    PixelColor pc2 = PixelColor(255,255,600);
    pc2.normalizeTo(255);
    printColor(pc2);

}

void Test::printColor(PixelColor c)
{
    std::cout << "Red:" <<c.r << " Green:" << c.g << " Blue:"<<c.b << std::endl;
}
