// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail0026B950/103B. Caller0026B9D0 restores its saved TaintSpecialPower
// receiver before this call, outside the optional OCL branch.
// newObject's third argument is BitFlags<86>, not a Coord3D; both occupy12B.
// Keep the banked bfmeBindCP method name; its semantic identity remains unknown.
// Object+23C is the witnessed m_team. Slot20 remains unnamed.
#include "ascii_string.h"
#include <bitset>
struct Coord3D;
class Team;
class ThingTemplate;
template <unsigned N> class BitFlags
{
    std::bitset<N> m_bits;
public:
    BitFlags() {}
};
class Thing
{
public:
    void setPosition(const Coord3D *);
#define SLOT(n) virtual void slot##n();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
    SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
#undef SLOT
    virtual void slot20(Team *);
};
class Object : public Thing
{
public:
    unsigned char m_prefix004[0x238];
    Team *m_team;
};
class ThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *, Team *, const BitFlags<86> &, unsigned);
};
extern ThingFactory *TheThingFactory;
class TaintSpecialPower
{
public:
    void bfmeBindCP(const Coord3D *, void *);
    unsigned char m_prefix000[8];
    Object *m_ownerObject;
};
void TaintSpecialPower::bfmeBindCP(const Coord3D *location, void *name)
{
    const ThingTemplate *thingTemplate =
        TheThingFactory->findTemplate(*static_cast<const AsciiString *>(name));
    if (thingTemplate)
    {
        BitFlags<86> status;
        Object *created = TheThingFactory->newObject(thingTemplate, 0, status, 0);
        if (created)
        {
            created->setPosition(location);
            created->slot20(m_ownerObject->m_team);
        }
    }
}
