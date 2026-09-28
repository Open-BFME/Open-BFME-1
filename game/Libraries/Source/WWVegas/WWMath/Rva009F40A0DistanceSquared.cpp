// cl: /O2
#include "coord3d.h"
class Rva009F40A0PositionProvider {
public:
 virtual void slot0();
 virtual const Coord3DBase *position();
};
float Rva009F40A0DistanceSquared(const Coord3DBase *a,
 Rva009F40A0PositionProvider *provider)
{
 const Coord3DBase *b = provider->position();
 float dz = b->z - a->z;
 float dy = b->y - a->y;
 float dx = b->x - a->x;
 return dx * dx + dy * dy + dz * dz;
}
