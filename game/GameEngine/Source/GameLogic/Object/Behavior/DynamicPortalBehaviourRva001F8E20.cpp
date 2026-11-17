// ?method@Rva001F8E20Owner@@QAEXPAUCoord3D@@@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/GameEngine/Source/Common/Thing
#include "Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
    const Coord3D *getPosition() const { return &m_cachedPos; } \
    void transformPoint(const Coord3D *in, Coord3D *out);
#include "thing.h"
#undef THING_TU_MEMBERS
#include <math.h>


struct Rva001F8E20Data
{
    char pad[0xcc];
    Coord3D pos;
};

class Rva001F8E20Owner
{
public:
    void *vptr;
    Rva001F8E20Data *data;
    Thing *object;

    void method(Coord3D *out);
};

// ?method@Rva001F8E20Owner@@QAEXPAUCoord3D@@@Z
void Rva001F8E20Owner::method(Coord3D *out)
{
    Rva001F8E20Data *moduleData = data;
    Coord3D in = {1.0f, 0.0f, 0.0f};
    Coord3D delta;
    object->transformPoint(&in, &delta);

    Thing *receiver = object;
    delta.x -= receiver->getPosition()->x;
    delta.y -= receiver->getPosition()->y;
    float ay = (float)fabs(delta.y), ax = (float)fabs(delta.x);
    const float &maximum = ax > ay ? ax : ay;
    float scale = 1.0f / maximum;
    delta.x *= scale;
    delta.y *= scale;
    delta.z = 0.0f * scale;

    in = moduleData->pos;
    double len = sqrt((double)(delta.z * delta.z + delta.x * delta.x) + delta.y * delta.y);
    in.x *= len;
    in.y *= len;
    Coord3D result;
    receiver->transformPoint(&in, &result);
    out->x = result.x;
    out->y = result.y;
    out->z = result.z;
}
