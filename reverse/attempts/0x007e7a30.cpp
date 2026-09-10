// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "matrix4d.h"

Matrix4D::Matrix4D(const Coord3D &v, float angle)
{
    float sine;
    float cosine;
    __asm {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }

    values[0] = v.x * v.x + cosine * (1.0f - v.x * v.x);
    values[1] = v.x * v.y * (1.0f - cosine) - v.z * sine;
    values[2] = v.z * (v.x * (1.0f - cosine)) + v.y * sine;
    values[3] = 0.0f;

    values[4] = v.x * v.y * (1.0f - cosine) + v.z * sine;
    values[5] = v.y * v.y + cosine * (1.0f - v.y * v.y);
    values[6] = v.z * (v.y * (1.0f - cosine)) - v.x * sine;
    values[7] = 0.0f;

    values[8] = v.z * (v.x * (1.0f - cosine)) - v.y * sine;
    values[9] = v.z * (v.y * (1.0f - cosine)) + v.x * sine;
    values[10] = v.z * v.z + cosine * (1.0f - v.z * v.z);
    values[11] = 0.0f;
    values[12] = 0.0f;
    values[13] = 0.0f;
    values[14] = 0.0f;
    values[15] = 1.0f;
}
