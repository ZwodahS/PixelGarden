#ifndef _GAME_PIXELCOLOR_H_
#define _GAME_PIXELCOLOR_H_
struct PixelColor
{
    int r;
    int g;
    int b;
    PixelColor();
    PixelColor(int r, int g, int b);
    
    PixelColor& operator+=(const PixelColor& rhs);
    PixelColor& operator-=(const PixelColor& rhs);
    PixelColor& operator/=(const float divisor);
    PixelColor& normalizeTo(int value);
};

PixelColor operator+(PixelColor lhs, const PixelColor& rhs);
PixelColor operator-(PixelColor lhs, const PixelColor& rhs);
PixelColor operator/(PixelColor lhs, const float division);
#endif
