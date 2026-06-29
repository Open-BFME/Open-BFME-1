#include "color.h"

RGBColor &RGBColor::operator=(const RGBColor &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

void RGBColor::setFromInt(int color)
{
    static const float scale = 1.0f / 255.0f;
    red = (float)((color >> 16) & 0xFF) * scale;
    green = (float)((color >> 8) & 0xFF) * scale;
    blue = (float)(color & 0xFF) * scale;
}

bool operator==(const RGBColor &left, const RGBColor &right)
{
    return left.red == right.red &&
        left.green == right.green &&
        left.blue == right.blue;
}

bool operator!=(const RGBColor &left, const RGBColor &right)
{
    return !(left == right);
}

RGBAColorInt &RGBAColorInt::operator=(const RGBAColorInt &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

RGBAColorReal &RGBAColorReal::operator=(const RGBAColorReal &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

namespace FXParticleSystem {

RGBColorKeyframe::RGBColorKeyframe()
{
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[3] = 0;
}

}
