// cl: /Igame/GameEngine/Source/Common
#include "color.h"

#include "debug.h"

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

// RGBColor conversion bodies are emitted inline by the donor BaseType.h
// in InGameUI.cpp; that retail-proven copy owns the ledger rows.

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

Debug &operator<<(Debug &debug, const RGBColor &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorReal &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorInt &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

namespace FXParticleSystem {

RGBColorKeyframe &RGBColorKeyframe::operator=(const RGBColorKeyframe &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int frame;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

}
