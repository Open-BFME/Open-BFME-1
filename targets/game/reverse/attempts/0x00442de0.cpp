// ?d_00442de0@@YAXXZ
// partial score=0.6070528967 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#include <list>
#include <math.h>
#include <new>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}


// Retail 0x00442DE0..0x00442F6D: complete thiscall body, ret 8.
// Address-qualified owner: no matched caller proves an InGameUI method name.
// +0x1304 is a list of two-int points; +0x1308..+0x1314 are XY bounds.
// Mouse+0x10EC is witnessed m_dragTolerance (name_oracle).
// Coord3D ctor/dtor inline bodies above agree with coord3d.cpp.
class Mouse;
extern Mouse *TheMouse;

struct Rva00442DE0Point { int x, y; };
class Rva00442DE0Owner {
    char opaque[0x1304];
    _STL::list<Rva00442DE0Point> points;
    int minX, minY, maxX, maxY;
public:
    void appendPoint(int x, int y);
};

void Rva00442DE0Owner::appendPoint(int x, int y)
{
    if (points.size() == 0) {
        minX = x; maxX = x;
        minY = y; maxY = y;
    } else {
        Rva00442DE0Point last = points.back();
        Coord3D delta;
        delta.x = float(x - last.x);
        delta.y = float(y - last.y);
        float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
        delta.z = 0.0f;
        float tolerance = (float)(int)(*(unsigned int*)((char*)TheMouse + 0x10ec) / 3);
        if (distance < tolerance) return;
        if (distance > tolerance * 10.0f) {
            delta.normalize();
            float scale = tolerance * 9.9f;
            delta.x = scale * delta.x;
            delta.y = scale * delta.y;
            x = (int)delta.x + last.x;
            y = (int)delta.y + last.y;
        }
        if (x < minX) minX = x;
        else if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        else if (y > maxY) maxY = y;
    }
    Rva00442DE0Point point; point.x=x; point.y=y;
    points.push_back(point);
}
