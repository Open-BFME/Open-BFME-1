#pragma once

#include "coord3d.h"

class Matrix4D {
public:
    Coord3D &GetXVector(Coord3D &out) const;
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &GetTranslationVector(Coord3D &out) const;

    float values[16];
};
