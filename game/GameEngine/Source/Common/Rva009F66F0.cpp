// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail 009F66F0..009F67EC. INT3 before entry. Three cdecl arguments;
// the data xref at VA012DBD70 points to this entry. The following function
// starts at 009F67ED with an independent SEH prologue.
#include <math.h>
#include <float.h>
#include "coord.h"

enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
struct Rva009F66F0Shape {
    int type;
    float height, majorRadius;
    char rest[0x18];
};
class GeometryInfo {
public:
    GeometryInfo(GeometryType, bool, float, float, float);
    virtual ~GeometryInfo();
    bool bfmeIntersects(const Coord3D &, float, const GeometryInfo &,
        const Coord3D &, float) const;
    void recompute() { calcBoundingStuff(); }
    char pad04[0x28];
    Rva009F66F0Shape *first, *last, *limit;
    char pad38[0x24];
private:
    void calcBoundingStuff();
};
class Rva009F66F0Provider {
public:
    virtual const GeometryInfo *geometry();
    virtual const Coord3D *position();
    virtual float angle();
};

float Rva009F66F0(const Coord3D *position, Rva009F66F0Provider *provider, float radiusSquared)
{
    static GeometryInfo geometry(GEOMETRY_SPHERE, true, 2.0f, 2.0f, 2.0f);
    if (geometry.last - geometry.first != 0)
        geometry.first->majorRadius = (float)sqrt(radiusSquared);
    geometry.recompute();
    const GeometryInfo *target = provider->geometry();
    if (target->bfmeIntersects(*provider->position(), provider->angle(),
        geometry, *position, 0.0f))
        return 0.0f;
    return FLT_MAX;
}
