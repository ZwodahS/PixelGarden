#ifndef _GAME_DEBUG_H_
#define _GAME_DEBUG_H_
#include "PixelColor.hpp"
#include <string>
namespace debug
{
    void print(PixelColor pc);
    void print(std::string prefix, PixelColor pc);
}
#endif
