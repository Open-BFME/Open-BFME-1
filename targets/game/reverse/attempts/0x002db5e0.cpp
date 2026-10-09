// ?rva002DB5E0@DamageNugget@@UAEXPAURva002DB5E0Weapon@@PBUCoord3D@@@Z
// partial score=0.4687 date=2026-10-09
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/GameLogic/Object
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <algorithm>
#include "StringInline.h"
#include "GameLogicObjectLookup.h"
class Player;
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
#define THING_TU_MEMBERS void setPosition(const Coord3D*);
#define OBJECT_TU_MEMBERS Player* getControllingPlayer() const; void setProducer(const Object*); Module* findModule(NameKeyType) const;
#include "object.h"
class NameKeyGenerator {
public:
    NameKeyType nameToKey(const char*);
};
extern NameKeyGenerator* TheNameKeyGenerator;
extern GameLogic* TheGameLogic;
class BfmeGlob940E {
public:
    void bfmeCall940E(void*);
};
class Team;
class Player {
public:
    char pad00[0x230];
    Team* at230;
};
template<int N> class BitFlags {
public:
    BitFlags() {}
    _STL::bitset<N> bits;
};
class BfmeThingFactory {
public:
    const ThingTemplate* findTemplate(const AsciiString&);
};
class ThingFactory {
public:
    Object* newObject(const ThingTemplate*, Team*, const BitFlags<86>&, unsigned);
    const ThingTemplate* findTemplate(const AsciiString&);
};
extern ThingFactory* TheThingFactory;
class Rva002DB5E0GlobalData {
public:
    char pad00[0x14];
    AsciiString at14;
};
class GlobalData;
extern GlobalData* TheGlobalData;
class BfmeDelayedLuaEvent {
public:
    unsigned at00;
    float at04;
    unsigned char at08;
    char pad09[3];
    int m_objectID;
    AsciiString m_name;
    int m_type;
};
struct BfmeDelayedLuaEventList {
    BfmeDelayedLuaEventList();
    virtual ~BfmeDelayedLuaEventList();
    BfmeDelayedLuaEvent m_events[3];
};
class Gen_0028BFF0 {
public:
    void bfmeSetup(int, void*, unsigned, int, unsigned char, unsigned char);
};
struct Rva002DB5E0WeaponTemplate {
    char pad00[0x4d8];
    unsigned at4d8;
};
struct Rva002DB5E0Weapon {
    unsigned at00;
    Rva002DB5E0WeaponTemplate* at04;
    int at08;
    char pad0c[0x10];
    unsigned at1c;
};
class DamageNugget {
public:
    virtual void unused00();
    virtual void unused04();
    virtual void unused08();
    virtual void unused0c();
    virtual void rva002DB5E0(Rva002DB5E0Weapon*, const Coord3D*);
    char pad04[0x54];
    float m_58;
    float m_5c;
};
// ?rva002DB5E0@DamageNugget@@UAEXPAURva002DB5E0Weapon@@PBUCoord3D@@@Z present-unmatched
void DamageNugget::rva002DB5E0(Rva002DB5E0Weapon* weapon, const Coord3D* position)
{
    const ThingTemplate* objectTemplate = TheThingFactory->findTemplate(((Rva002DB5E0GlobalData*)TheGlobalData)->at14);
    if (!objectTemplate) return;
    int id = weapon->at08;
    Object* source = TheGameLogic->findObjectByID(id);
    if (!source) return;
    BitFlags<86> status;
    Object* object = TheThingFactory->newObject(objectTemplate, source->getControllingPlayer()->at230, status, 0);
    object->setProducer(source);
    object->setPosition(position);
    static NameKeyType key = TheNameKeyGenerator->nameToKey("DelayedLuaEventUpdate");
    Module* module = object->findModule(key);
    GameLogic* logic = TheGameLogic;
    if (!module) {
        ((BfmeGlob940E*)logic)->bfmeCall940E(object);
        return;
    }
    unsigned frame = *(unsigned*)((char*)logic + 0x3c);
    unsigned duration = weapon->at1c - frame;
    unsigned char enabled = (weapon->at04->at4d8 >> 1) & 1;
    unsigned char pending = (weapon->at04->at4d8 >> 2) & 1;
    BfmeDelayedLuaEventList events;
    events.m_events[0].m_type = 3;
    events.m_events[0].m_objectID = source->m_id;
    events.m_events[1].at04 = (float)duration;
    events.m_events[2].at04 = m_58;
    events.m_events[1].m_type = 1;
    events.m_events[2].m_type = 1;
    const float one = 1.0f;
    const float& value = m_5c > one ? m_5c : one;
    ((Gen_0028BFF0*)module)->bfmeSetup(9, &events, 0, *(const int*)&value, enabled, pending);
}
