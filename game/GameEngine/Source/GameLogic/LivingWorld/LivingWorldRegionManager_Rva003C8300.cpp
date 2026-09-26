// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x003C8300, 46 bytes. The matched 0x003C8160 callee receives this
// manager and returns a LivingWorldRegion pointer. Retail forwards that EAX
// unchanged; 0x003C83E0 consumes it as the next update's item argument.

struct Coord3D { float x, y, z; };
struct Rva003C8300Pair { int first, second; };
class LivingWorldRegion;

class Rva003C8300State
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07();
    virtual void slot08(const Rva003C8300Pair *pair, Coord3D *out);
};

extern "C" Rva003C8300State *g_bfmeStateDF;

class LivingWorldRegionManager
{
public:
    LivingWorldRegion *rva003C8300(const Rva003C8300Pair *pair);
};

extern void j_00046150();

// The retail call is to this existing ILT, not directly to 0x003C8160.
// Its target's pointer return and Coord3D* argument are independently matched.
static __forceinline LivingWorldRegion *callRegionLookup(
    LivingWorldRegionManager *manager, Coord3D *position)
{
    typedef LivingWorldRegion *(LivingWorldRegionManager::*Lookup)(Coord3D *);
    union { void (*plain)(); Lookup member; } route;
    route.plain = j_00046150;
    return (manager->*route.member)(position);
}

LivingWorldRegion *LivingWorldRegionManager::rva003C8300(
    const Rva003C8300Pair *pair)
{
    Coord3D position;
    g_bfmeStateDF->slot08(pair, &position);
    return callRegionLookup(this, &position);
}
