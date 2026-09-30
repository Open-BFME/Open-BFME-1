// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Include
// Retail secondary-interface slot 43 of HordeGarrisonContain; method name unproven.
// The neighbour at 0x002218A0 establishes Coord set/sub plus Vector3 dot idiom.
#include "vector3.h"
struct Rva00221960Coord {
    float x,y,z;
    void set(const Rva00221960Coord* a) { x=a->x; y=a->y; z=a->z; }
    void sub(const Rva00221960Coord* a) { x-=a->x; y-=a->y; z-=a->z; }
};
struct Rva00221960Point { char head[0x38]; Rva00221960Coord pos; };
struct Rva00221960Info { char head[0x138]; float threshold; };
class Rva00221960Owner { public: char test(Rva00221960Point* a,Rva00221960Point* b); };
char Rva00221960Owner::test(Rva00221960Point* a,Rva00221960Point* b) {
    if (a && b) {
        Rva00221960Info* info=*(Rva00221960Info**)((char*)this-0x1c);
        if (info->threshold<0.0f) return 0;
        Rva00221960Point* owner=*(Rva00221960Point**)((char*)this-0x18);
        if (a->pos.z-owner->pos.z>info->threshold) return 0;
        Rva00221960Coord ab; ab.set(&b->pos); ab.sub(&a->pos); ab.z=0.0f;
        Rva00221960Coord ao; ao.set(&owner->pos); ao.sub(&a->pos); ao.z=0.0f;
        if (Vector3::Dot_Product(Vector3(ao.x,ao.y,ao.z),Vector3(ab.x,ab.y,ab.z))<0.0f) return 0;
        return 1;
    }
    return 0;
}
