// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.8 date=2026-09-01
// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.80 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath
#include "coord3d.h"

Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.y * right.z - left.z * right.y;
    y = left.z * right.x - left.x * right.z;
    z = left.x * right.y - left.y * right.x;
    return *this;
}
