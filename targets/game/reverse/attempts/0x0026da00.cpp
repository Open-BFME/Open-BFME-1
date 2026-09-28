// ?d_0026da00@@YAXXZ
// partial score=0.956 date=2026-09-28
// Remaining: extra retail zero store +0x15 and null-target branch merger.
// 415/425 bytes; normalized instruction similarity 0.956, positional byte score 0.277647.
// cl: /DNDEBUG /MD /EHsc
// Retail 0026DA00: weapon target/position dispatch. All layouts below are
// address-derived views witnessed by this body, not semantic class identities.
#include "../../../../game/Libraries/Source/WWVegas/WWMath/coord3d.h"
class Object;
class Weapon;
class FiringTracker { friend struct Tracker0026DA00; void coolDown(bool); };
class Overridable { public: const Overridable* getFinalOverride() const; };
class Object { public: void* unidentified_001BFE20() const; void rva001CE6F0(int); };
enum WeaponStatus {};
class Weapon { public:
    WeaponStatus getStatus() const;
    bool rva001EA5F0(const Object*,int,const Object*,int*);
    Object* forceFireWeapon(const Object*,const struct Coord3D*);
};
class Rva001CD990FiringTracker { public: void rva001B3510(const Weapon*,int,const void*,unsigned char); };
class BfmeOwnBZ { public: void bfmeInitBZ(); };
class SpecialPowerModuleInterface;
class Rva002A6180 { public: SpecialPowerModuleInterface* forward(); };
struct Position0026DA00 { float x,y,z; bool equal(const Position0026DA00& p) const { return reinterpret_cast<const Coord3D*>(this)->IsExactlyEqualTo(*reinterpret_cast<const Coord3D*>(&p)); } };
struct Target0026DA00;
struct Interface0026DA00 {
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual Target0026DA00* target();
};
struct Power0026DA00 {
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void invoke();
};
struct Template0026DA00 {
    int field00;
    Template0026DA00* field04;
    char pad08[0xcc];
    unsigned fieldD4;
    Template0026DA00* finalOverride() { return (Template0026DA00*)reinterpret_cast<Overridable*>(this)->getFinalOverride(); }
};
struct Weapon0026DA00 {
    char pad00[8]; int field08;
    int status() const { return reinterpret_cast<const Weapon*>(this)->getStatus(); }
    bool fire(Target0026DA00* a,int b,Target0026DA00* c,int* d) { return reinterpret_cast<Weapon*>(this)->rva001EA5F0((Object*)a,b,(Object*)c,d); }
    Target0026DA00* force(Target0026DA00* a,const Position0026DA00* b) { return (Target0026DA00*)reinterpret_cast<Weapon*>(this)->forceFireWeapon((Object*)a,(const Coord3D*)b); }
};
struct Tracker0026DA00 {
    void cool(bool b) { reinterpret_cast<FiringTracker*>(this)->coolDown(b); }
    void fired(Weapon0026DA00* a,int b,const Position0026DA00* c,unsigned char d) { reinterpret_cast<Rva001CD990FiringTracker*>(this)->rva001B3510((Weapon*)a,b,c,d); }
};
struct Target0026DA00 {
    int field00; Template0026DA00* field04;
    char pad08[0x30]; Position0026DA00 field38;
    char pad44[0x30]; int m_id;
    char pad78[0x174]; Tracker0026DA00* field1EC;
    Interface0026DA00* interfacePtr() const { return (Interface0026DA00*)reinterpret_cast<const Object*>(this)->unidentified_001BFE20(); }
    void deadline(int n) { reinterpret_cast<Object*>(this)->rva001CE6F0(n); }
};
struct Data0026DA00 { char pad00[0x260]; int field260; bool field264; };
class GameLogic { public:
    char pad00[0x3c]; int field3C;
    Object* findObjectByID(int);
};
extern GameLogic* TheBfmeGameLogic;
struct WeaponDispatch0026DA00 {
    int field00; Data0026DA00* field04; Target0026DA00* field08;
    char pad0C[0xa0]; int fieldAC; Position0026DA00 fieldB0;
    char padBC[0x2c]; Weapon0026DA00* fieldE8;
    void finish() { reinterpret_cast<BfmeOwnBZ*>(this)->bfmeInitBZ(); }
    Power0026DA00* power() { return (Power0026DA00*)reinterpret_cast<Rva002A6180*>(this)->forward(); }
    void execute();
};

void WeaponDispatch0026DA00::execute() {
    Data0026DA00* data=field04;
    Target0026DA00* object=field08;
    int id=0;
    object->field1EC->cool(true);
    Target0026DA00* target=(Target0026DA00*)TheBfmeGameLogic->findObjectByID(fieldAC);
    id=target ? target->m_id : 0;
    if(target) {
        Template0026DA00* t=target->field04;
        if(t && t->field04) t=t->field04->finalOverride();
        if(t->fieldD4 & 0x1000) {
            Interface0026DA00* i=target->interfacePtr();
            if(i) {
                Target0026DA00* other=i->target();
                if(other) { id=other->m_id; target=other; }
            }
        }
    }
    if(fieldE8 && fieldE8->status()==0) {
        fieldE8->field08=object->m_id;
        if(target) {
            fieldE8->fire(object,id,target,0);
            if(object->field1EC) object->field1EC->fired(fieldE8,id,0,1);
        } else {
            Position0026DA00 zero={0,0,0};
            if(!fieldB0.equal(zero) && !data->field264) {
                fieldE8->force(object,&fieldB0);
                if(object->field1EC) object->field1EC->fired(fieldE8,0,&fieldB0,1);
            } else {
                const Position0026DA00* pos=&object->field38;
                fieldE8->force(object,pos);
                if(object->field1EC) object->field1EC->fired(fieldE8,0,pos,1);
            }
        }
        object->deadline(TheBfmeGameLogic->field3C+field04->field260);
    }
    finish();
    Power0026DA00* p=power();
    if(p) p->invoke();
}

