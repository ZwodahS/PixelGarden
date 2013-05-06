#include "f_debug.hpp"
#include <iostream>
namespace debug
{
    void print(PixelColor pc)
    {
        std::cout << "[R:"<<pc.r<<"] [G:"<<pc.g<<"] [B:"<<pc.b << "]" << std::endl;
    }

    void print(std::string prefix,PixelColor pc)
    {
        std::cout << "(" << prefix << ")" << "[R:"<<pc.r<<"] [G:"<<pc.g<<"] [B:"<<pc.b << "]" << std::endl;
    }
}
