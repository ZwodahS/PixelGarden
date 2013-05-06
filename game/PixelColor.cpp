#include "PixelColor.hpp"
PixelColor::PixelColor()
{
    int r = 0;
    int g = 0;
    int b = 0;
}
PixelColor::PixelColor(int r , int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}


PixelColor& PixelColor::operator+=(const PixelColor& rhs)
{
    this->r += rhs.r;
    this->g += rhs.g;
    this->b += rhs.b;
    return *this;
}
PixelColor& PixelColor::operator-=(const PixelColor& rhs)
{
    this->r -= rhs.r;
    this->g -= rhs.g;
    this->b -= rhs.b;
    return *this;
}

PixelColor& PixelColor::operator/=(const float div)
{
    this->r = (int)(r/div);
    this->g = (int)(g/div);
    this->b = (int)(b/div);
    return *this;
}

PixelColor& PixelColor::normalizeTo(int value)
{
    if(r >= g && r >= b)
    {
        if(r > value)
        {
            float multiplier = 1.0f * (r/value);
            r = value;
            g = (int)(g/multiplier);
            b = (int)(b/multiplier);
        }
    }
    else if(g >= b )
    {
        if(g > value)
        {
            float multiplier = 1.0f * (g/value);
            r = (int)(r/multiplier);
            g = value;
            b = (int)(b/multiplier);
        }
    }
    else
    {
        if(b > value)
        {
            float multiplier = 1.0f * (r/value);
            r = (int)(r/multiplier);
            g = (int)(g/multiplier);
            b = value;
        }
    }
    return *this;
}


PixelColor operator+(PixelColor lhs, const PixelColor& rhs)
{
    return lhs += rhs;
}

PixelColor operator-(PixelColor lhs, const PixelColor& rhs)
{
    return lhs -= rhs;
}

PixelColor operator/(PixelColor lhs, const float division)
{
    return lhs /= division;
}
