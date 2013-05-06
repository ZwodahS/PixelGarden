#include "f_debug.hpp"
#include <iostream>

#define DEBUG_LOG

namespace debug
{
    void print(PixelColor pc)
    {
#ifdef DEBUG_LOG
        std::cout << "[R:"<<pc.r<<"] [G:"<<pc.g<<"] [B:"<<pc.b << "]" << std::endl;
#endif
    }

    void print(std::string prefix,PixelColor pc)
    {
#ifdef DEBUG_LOG
        std::cout << "(" << prefix << ")" << "[R:"<<pc.r<<"] [G:"<<pc.g<<"] [B:"<<pc.b << "]" << std::endl;
#endif
    }
}
