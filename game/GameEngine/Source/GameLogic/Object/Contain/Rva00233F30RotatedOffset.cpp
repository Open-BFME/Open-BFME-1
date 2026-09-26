// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail 0x00233F30 (154 bytes, ret 8).  Three callers (one is 0x002350C0)
// pass ECX, a hidden result address and a direction, and use the returned
// EAX.  The body takes the direction's length (scaled by the settings float
// at +0x2DC when TheTerrainLogic's slot 47 accepts the object's position),
// rotates by the direction's angle plus the object's angle at +0x44, and
// returns cos/sin times that length by value.  The result is a named local
// with an inline field-wise copy constructor: retail keeps x in memory and y
// on the FPU and copies both into the return slot.  Owner and result type
// are unproven, so both names keep the address.
#include "Lib/BaseType.h"
class TerrainLogic;
extern TerrainLogic* TheTerrainLogic;
#include "Lib/trig.h"

struct Rva00233F30Offset
{
    Rva00233F30Offset() {}
    Rva00233F30Offset(const Rva00233F30Offset &that) : x(that.x), y(that.y) {}
    Real x;
    Real y;
};
struct Rva00233F30 {
    char reserved[4];
    void* settings;
    void* object;
    Rva00233F30Offset rotatedOffset(const Coord2D* direction);
};

class Rva00233F30TerrainSlots {
public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void slot9() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual bool slot47(const Coord3D*) = 0;
};

Rva00233F30Offset Rva00233F30::rotatedOffset(const Coord2D* direction)
{
    float distance = direction->length();
    const Coord3D* position = reinterpret_cast<const Coord3D*>(reinterpret_cast<const char*>(object) + 0x38);
    if (reinterpret_cast<Rva00233F30TerrainSlots*>(TheTerrainLogic)->slot47(position))
        distance *= *reinterpret_cast<const float*>(reinterpret_cast<const char*>(settings) + 0x2dc);
    float angle = direction->toAngle() + *reinterpret_cast<const float*>(reinterpret_cast<const char*>(object) + 0x44);
    Coord2D unit;
    unit.x = Cos(angle);
    unit.y = Sin(angle);
    Rva00233F30Offset result;
    result.x = unit.x * distance;
    result.y = unit.y * distance;
    return result;
}
