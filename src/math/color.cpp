#include "color.h"

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

namespace FXParticleSystem {

RGBColorKeyframe::RGBColorKeyframe()
{
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[3] = 0;
}

}
