// ?d_00442de0@@YAXXZ
// partial score=0.9018 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#include <list>
#include <math.h>
#include <new>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(int x, int y, int z)
{
    this->x = (float)x;
    this->y = (float)y;
    this->z = (float)z;
}


// Retail 0x00442DE0..0x00442F6D: complete thiscall body, ret 8, point passed by value.
// Address-qualified owner: no matched caller proves an InGameUI method name.
// +0x1304 is a list of two-int points; +0x1308..+0x1314 are XY bounds.
// Mouse+0x10EC is witnessed m_dragTolerance (name_oracle).
// Coord3D inline bodies above agree with coord3d.cpp.
struct Rva00442DE0Point { int x, y; };
class Mouse;
extern Mouse *TheMouse;

class Rva00442DE0Owner {
    char opaque[0x1304];
    _STL::list<Rva00442DE0Point> points;
    int minX, minY, maxX, maxY;
public:
    void appendPoint(Rva00442DE0Point pos);
};

void Rva00442DE0Owner::appendPoint(Rva00442DE0Point pos)
{
    Rva00442DE0Point pt = pos;
    if (points.size() == 0) {
        minX = pt.x; maxX = pt.x;
        minY = pt.y; maxY = pt.y;
    } else {
        const Rva00442DE0Point &last = points.back();
        int lastX = last.x;
        int lastY = last.y;
        Coord3D delta(pt.x - lastX, pt.y - lastY, 0);
        float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
        float tolerance = (float)(int)(*(unsigned int*)((char*)TheMouse + 0x10ec) / 3);
        if (distance < tolerance) return;
        if (distance > tolerance * 10.0f) {
            delta.normalize();
            float scale = tolerance * 9.9f;
            delta.x = scale * delta.x;
            delta.y = scale * delta.y;
            pt.x = (int)delta.x + lastX;
            pt.y = (int)delta.y + lastY;
        }
        if (pt.x < minX) minX = pt.x;
        else if (pt.x > maxX) maxX = pt.x;
        if (pt.y < minY) minY = pt.y;
        else if (pt.y > maxY) maxY = pt.y;
    }
    points.push_back(pt);
}
