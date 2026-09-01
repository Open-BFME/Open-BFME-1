// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@@Z
// partial score=0.9 date=2026-09-01
// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@@Z
// partial score=0.90 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath
#include "matrix4d.h"

Matrix4D &Matrix4D::Set(const Coord3D &translation)
{
    unsigned int zero = 0;
    unsigned int one = 0x3f800000;
    unsigned int *raw = (unsigned int *)values;

    raw[3] = zero;
    raw[7] = zero;
    raw[11] = zero;
    raw[1] = zero;
    raw[2] = zero;
    raw[4] = zero;
    raw[6] = zero;
    raw[8] = zero;
    raw[9] = zero;
    raw[12] = zero;
    raw[13] = zero;
    raw[14] = zero;
    raw[0] = one;
    raw[5] = one;
    raw[10] = one;
    raw[15] = one;
    values[3] = translation.x;
    values[7] = translation.y;
    values[11] = translation.z;
    return *this;
}
