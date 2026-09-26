// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
// Retail 0038A770: source placeObjectAtPosition, compiler-private static ABI.
// Calls at 0038AB17/0038AC65: player in ECX; string then Coord3D* on stack;
// both callers add esp,8. AsciiString is nontrivial and four bytes wide.
// Source identity: GameLogic.cpp's placeNetworkBuildingsForPlayer calls the
// static placeObjectAtPosition helper in both the building and unit branches.
// The asset context's byte at +0 is independently read by body 00144DC0;
// its original type name is unknown. Its inline constructor preserves the
// scoped lifetime that lets VC7.1 share storage with the orientation temporary.
#include "StringInline.h"
#include "coord.h"

extern void j_0002fb80();
extern void j_00015d7a();
extern void j_00017a12();
extern void j_0004494a();
extern void j_000294e2();
extern void Rva009EBAC0(int);

class AssetList0038A770 {
public:
    AssetList0038A770() {
        union { void (*entry)(); void (AssetList0038A770::*member)(); } call;
        call.entry=j_0002fb80; (this->*call.member)();
    }
    ~AssetList0038A770() {
        union { void (*entry)(); void (AssetList0038A770::*member)(); } call;
        call.entry=j_00015d7a; (this->*call.member)();
    }
    char data[20];
};
class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *vtable;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable {
public:
    char pad008[0xc8-8]; unsigned char field0C8;
    char pad0C9[0x3b0-0xc9]; Real m_placementViewAngle;
    Real getPlacementViewAngle() const { return m_placementViewAngle; }
    void getAssets0038A770(AssetList0038A770 &list, bool &flag) const {
        union { void (*entry)(); void (ThingTemplate::*member)(AssetList0038A770 &,bool &) const; } call;
        call.entry=j_00017a12; (this->*call.member)(list,flag);
    }
};
class Thing {
public:
    void setOrientation(Real);
    void setPosition(const Coord3D *);
    const ThingTemplate *getTemplate() const {
        return m_template == 0 ? m_template : m_template->m_nextOverride ?
            (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride() : m_template;
    }
    void *vtable;
    ThingTemplate *m_template;
};
class Create0038A770 {
public:
    virtual void slot000()=0;
    virtual void onBuildComplete()=0;
};
class Module0038A770 {
public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual Create0038A770 *getCreate()=0;
};
class LocomotorSet {};
class AIUpdate0038A770 {
public:
    char pad000[0x1a8]; LocomotorSet locomotors;
};
class Object : public Thing {
public:
    char pad008[0x1f0-8]; void **field1F0;
    char pad1F4[0x204-0x1f4]; AIUpdate0038A770 *m_ai;
};
class Team {
public:
    // name_oracle: Team+31=m_active and Team+32=m_created, confidence 1.00.
    char pad000[0x31]; bool m_active,m_created;
    void setActive() { if (!m_active) { m_created=true; m_active=true; } }
};
class Player {
public:
    char pad000[0x230]; Team *field230;
    Team *getDefaultTeam() const { return field230; }
};
class PlayerTemplate;
struct Status0038A770 {
    _STL::bitset<86> bits;
};
class ThingFactory {
public:
    ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *objectTemplate,Team *team,const Status0038A770 &status,unsigned flags) {
        union { void (*entry)(); Object *(ThingFactory::*member)(const ThingTemplate *,Team *,const Status0038A770 &,unsigned); } call;
        call.entry=j_0004494a; return (this->*call.member)(objectTemplate,team,status,flags);
    }
};
extern ThingFactory *TheThingFactory;
class GlobalData { public: char pad000[0x11fc]; bool field11FC; };
extern GlobalData *TheWritableGlobalData;
class Pathfinder {
public:
    void addObjectToPathfindMap(Object *);
    bool adjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
};
class AI { public: char pad000[12]; Pathfinder *pathfinder; };
extern AI *TheAI;

static __declspec(noinline) Object *placeObjectAtPosition(int slotNum, AsciiString name,
    Coord3D &pos, Player *player, const PlayerTemplate *playerTemplate)
{
    const ThingTemplate *objectTemplate=TheThingFactory->findTemplate(name);
    if (!objectTemplate) return 0;
    if (!TheWritableGlobalData->field11FC) {
        struct Context0038A770 { bool value; Context0038A770():value(false) {} } flag;
        AssetList0038A770 assets;
        objectTemplate->getAssets0038A770(assets,flag.value);
        Rva009EBAC0((int)&assets);
    }
    Object *object=TheThingFactory->newObject(objectTemplate,player->getDefaultTeam(),Status0038A770(),0);
    if (object) {
        object->setOrientation(object->getTemplate()->getPlacementViewAngle());
        object->setPosition(&pos);
        Team *team=player->getDefaultTeam();
        for (void **module=object->field1F0;*module;++module) {
            Create0038A770 *create=((Module0038A770 *)((char *)*module+12))->getCreate();
            if (!create) continue;
            create->onBuildComplete();
        }
        if (team) team->setActive();
        TheAI->pathfinder->addObjectToPathfindMap(object);
        AIUpdate0038A770 *ai=object->m_ai;
        if (ai && !(object->getTemplate()->field0C8&4)) {
            if (TheAI->pathfinder->adjustDestination(object,ai->locomotors,&pos,0)) {
                Pathfinder *pathfinder=TheAI->pathfinder;
                union { void (*entry)(); void (Pathfinder::*member)(Object *,const Coord3D *,int,const char *,int); } call;
                call.entry=j_000294e2;
                (pathfinder->*call.member)(object,&pos,1,
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp",0x4fc);
                object->setPosition(&pos);
            }
        }
    }
    return object;
}

// Emission anchor retaining the original static helper's source argument order.
// Unclaimed: only the helper's machine body is compared against retail.
Object *emitPlace0038A770(int slot, const AsciiString &name,Coord3D &pos,Player *player,const PlayerTemplate *playerTemplate)
{
    return placeObjectAtPosition(slot,name,pos,player,playerTemplate);
}
