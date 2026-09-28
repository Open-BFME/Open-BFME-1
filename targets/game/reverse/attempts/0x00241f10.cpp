// ?d_00241f10@@YAXXZ
// partial score=0.7419825073 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <map>
#include "coord.h"

typedef float Real;

class Object;
class Weapon;
class WeaponSlotType;

template<int N>
class AIUpdateSlots : public AIUpdateSlots<N - 1> {
public:
    virtual void unused(char (*)[N]) = 0;
};

template<>
class AIUpdateSlots<0> {
public:
    virtual void unused(char (*)[0]) = 0;
};

class AIUpdateInterface : public AIUpdateSlots<98> {
public:
    virtual bool blocksFormationRefresh() = 0;
};

class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_override;
    char pad008[0xcc - 0x08];
    unsigned int flagsCC;
    char padD0[4];
    unsigned int flagsD4;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class ByteField {
public:
    unsigned char get() const;
};

class Weapon {
public:
    virtual void slot00() = 0;
    ByteField *m_field;
    Real getAttackRange(const Object *target) const;
};

#define BFME_HAVE_COORD3D 1
#include "object.h"

class AICommandInterface {
public:
    void aiIdle(int source);
    void aiAttackObject(Object *target, int maxShots, int source);
};

class Pathfinder {
public:
    void removeGoal(Object *object);
};

class AI {
public:
    char pad000[12];
    Pathfinder *pathfinder;
};

extern AI *TheAI;

class Rva001CBDC0Receiver {
public:
    void clear(int value);
};

class Rva00241F10RefreshHook {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void refresh(int value) = 0;
};

class Rva00241F10Lookup {
public:
    std::map<void *, int> entries;
};

class Rva00241F10View {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10(int value) = 0;
    char pad004[0x34 - 0x04];
    Rva00241F10RefreshHook *refreshHook;
    char pad038[4];
    std::map<int, int> memberIndices;
    unsigned char *memberSlots;

    void update(Object *target);
};

extern void j_00015d02();
extern void j_00024d70();
extern void j_00028f74();
extern void j_0002e631();
extern void j_00031a7f();
extern void j_0003f544();
extern void j_00041dad();
extern void j_00044774();
extern void j_0004c37();
extern void j_000d3b9();
extern void j_000e4a8();
extern void j_0001f000();
extern void j_0002edcf();

typedef void (Pathfinder::*RemoveGoalCall)(Object *);
typedef void (AICommandInterface::*IdleCall)(int);
typedef void (AICommandInterface::*AttackCall)(Object *, int, int);
typedef Weapon *(Object::*CurrentWeaponCall)(WeaponSlotType *);
typedef unsigned char (ByteField::*ByteGetCall)() const;
typedef Real (Weapon::*AttackRangeCall)(const Object *) const;
typedef void *(Object::*OpaqueObjectCall)() const;
typedef bool (__cdecl *TargetPredicateCall)(void *, void *);
typedef bool (Rva00241F10View::*CurrentTargetCall)(AIUpdateInterface *, Object *);
typedef void (*RawCall)();

template<class T>
static T memberCall(RawCall raw) {
    union {
        RawCall raw;
        T member;
    } call;
    call.raw = raw;
    return call.member;
}

class TargetContainer {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void slot3c() = 0;
    virtual void slot40() = 0;
    virtual void slot44() = 0;
    virtual Object *select(int mode, const Coord3D *position, Real range) = 0;
};

struct Node00241F10 { unsigned color; Node00241F10 *parent,*left,*right; int key,value; };
struct Iterator00241F10 { Node00241F10 *node; Iterator00241F10(){} Iterator00241F10(const Iterator00241F10& rhs):node(rhs.node){} };
struct IndexMap00241F10 { Iterator00241F10 find(const int&); };
struct TargetMap00241F10 { Iterator00241F10 find(const int&); };
typedef bool (AIUpdateInterface::*Blocked00241F10)();
void Rva00241F10View::update(Object *target) {
 Object *owner=*(Object**)((char*)this-0xdc);
 Overridable *ownerTemplate=(Overridable*)owner->m_template;
 if(ownerTemplate && ownerTemplate->m_override) ownerTemplate=(Overridable*)ownerTemplate->m_override->getFinalOverride();
 if(ownerTemplate->flagsD4 & 0x400000) {
  Weapon *w=(owner->*memberCall<CurrentWeaponCall>(j_00031a7f))(0);
  if(!w || (w->m_field->*memberCall<ByteGetCall>(j_00028f74))()) return;
 }
 Object *object=*(Object**)((char*)this-0xdc);
 if(*(int*)((char*)object+0x9c)>=0) (TheAI->pathfinder->*memberCall<RemoveGoalCall>(j_00015d02))(object);
 if(refreshHook) slot10(0);
 Rva00241F10Lookup *targetLookup=(Rva00241F10Lookup*)((char*)*(void**)((char*)this-0xe0)+0x250);
 Overridable *t=(Overridable*)target->m_template;
 if(t && t->m_override) t=(Overridable*)t->m_override->getFinalOverride();
 Object *source;
 if(t->flagsD4 & 0x1000) source=target; else source=(Object*)target->m_containedBy;
 typedef std::list<Object*> MemberList;
 MemberList &members=*(MemberList*)((char*)this-0xac);
 for(MemberList::iterator it=members.begin();it!=members.end();++it) {
  Object *member=*it;
  { int id=member->m_id; if(memberIndices.find(id)==memberIndices.end()) continue; }
  AIUpdateInterface *ai=member->m_ai;
  if(!ai || (ai->*memberCall<Blocked00241F10>(j_00044774))()) continue;
  Weapon *weapon=(member->*memberCall<CurrentWeaponCall>(j_00031a7f))(0);
  if(weapon && (((member->*memberCall<CurrentWeaponCall>(j_00031a7f))(0))->m_field->*memberCall<ByteGetCall>(j_00028f74))()) {
   if(ai->blocksFormationRefresh()) (((AICommandInterface*)((char*)ai+0x20))->*memberCall<IdleCall>(j_00024d70))(2);
   if(!(member->m_status[0] & 0x10000000)) (((Rva001CBDC0Receiver*)member)->*memberCall<void(Rva001CBDC0Receiver::*)(int)>(j_000e4a8))(0);
   continue;
  }
  int key=member->m_id;
  Iterator00241F10 index=((IndexMap00241F10*)&memberIndices)->find(key);
  key=*(int*)(memberSlots+index.node->value*16);
  Iterator00241F10 found=((TargetMap00241F10*)targetLookup)->find(key);
  if(found.node==*(Node00241F10**)targetLookup) continue;
  if((((Rva00241F10View*)((char*)this-0xe4))->*memberCall<CurrentTargetCall>(j_0003f544))(ai,target)) continue;
  Object *candidate=target;
  weapon=(member->*memberCall<CurrentWeaponCall>(j_00031a7f))(0);
  if(source) {
   TargetContainer *container=(TargetContainer*)(source->*memberCall<OpaqueObjectCall>(j_000d3b9))();
   if(container) {
    Real range=0;
    if(weapon && !(weapon->m_field->*memberCall<ByteGetCall>(j_00028f74))()) range=(weapon->*memberCall<AttackRangeCall>(j_0002e631))(member);
    candidate=container->select(0,&member->m_cachedPos,range);
   }
  }
  if(memberCall<TargetPredicateCall>(j_0004c37)(member,candidate)) {
   (((AICommandInterface*)((char*)ai+0x20))->*memberCall<AttackCall>(j_0002edcf))(candidate,0x7fffffff,2);
  } else {
   (TheAI->pathfinder->*memberCall<RemoveGoalCall>(j_00015d02))(member);
   *(unsigned char*)((char*)this+4)=1;
  }
 }
}

#pragma comment(linker, "/alternatename:?find@IndexMap00241F10@@QAE?AUIterator00241F10@@ABH@Z=?j_0001f000@@YAXXZ")
#pragma comment(linker, "/alternatename:?find@TargetMap00241F10@@QAE?AUIterator00241F10@@ABH@Z=?j_00041dad@@YAXXZ")
