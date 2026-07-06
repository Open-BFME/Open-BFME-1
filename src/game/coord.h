#pragma once

// Common game coordinate types (BFME uses plain PODs for these). Reconstructed
// to the layouts the matched game code expects.
struct Coord3D {
    float x;
    float y;
    float z;
};

struct Coord2D {
    float x;
    float y;
};

struct ICoord3D {
    int x;
    int y;
    int z;
};

struct ICoord2D {
    int x;
    int y;
};

struct Region3D {
    Coord3D lo;
    Coord3D hi;
};

struct Region2D {
    Coord2D lo;
    Coord2D hi;
};

struct IRegion2D {
    ICoord2D lo;
    ICoord2D hi;
};
