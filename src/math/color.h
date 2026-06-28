#pragma once

struct RGBColor {
    float red;
    float green;
    float blue;
};

bool operator==(const RGBColor &left, const RGBColor &right);
bool operator!=(const RGBColor &left, const RGBColor &right);

namespace FXParticleSystem {

struct RGBColorKeyframe {
    RGBColorKeyframe();

    float red;
    float green;
    float blue;
    float frame;
};

}
