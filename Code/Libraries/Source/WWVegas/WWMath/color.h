#pragma once

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor {
    float red;
    float green;
    float blue;

    RGBColor &operator=(const RGBColor &that);
    int getAsInt() const;
    void setFromInt(int color);
};

bool operator==(const RGBColor &left, const RGBColor &right);
bool operator!=(const RGBColor &left, const RGBColor &right);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBAColorInt {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;

    RGBAColorInt &operator=(const RGBAColorInt &that);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBAColorReal {
    float red;
    float green;
    float blue;
    float alpha;

    RGBAColorReal &operator=(const RGBAColorReal &that);
};

namespace FXParticleSystem {

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
struct RGBColorKeyframe {
    RGBColorKeyframe()
    {
        ((unsigned int *)this)[2] = 0;
        ((unsigned int *)this)[1] = 0;
        ((unsigned int *)this)[0] = 0;
        ((unsigned int *)this)[3] = 0;
    }
    RGBColorKeyframe &operator=(const RGBColorKeyframe &that);

    float red;
    float green;
    float blue;
    float frame;
};

}
