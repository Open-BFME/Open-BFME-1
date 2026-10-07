// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// Retail 0x00241F10 complete 686-byte thiscall ending ret 4; EA names it
// HordeContain::attackTargetNow (ea_evidence.csv), virtual by the ILT oracle.
// Receiver is the HordeContain secondary interface: owner at this-0xdc, member list at this-0xac.
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <map>
#include "coord.h"
#include "../../../command_source_type.h"

typedef float Real;

class Object;
class Weapon;
enum WeaponSlotType {};

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
    bool bfmeBlocksFormationRefresh();
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

class Rva001E1770ByteField {
public:
    unsigned char get() const;
};

class ByteField : public Rva001E1770ByteField {
};

class Weapon {
public:
    virtual void slot00() = 0;
    ByteField *m_field;
    Real getAttackRange(const Object *target) const;
};

#define BFME_HAVE_COORD3D 1
#define OBJECT_TU_MEMBERS \
    Weapon *getCurrentWeapon(WeaponSlotType *slot = 0); \
    void *unidentified_001BFE20() const;
#include "../../object.h"

class AICommandInterface {
public:
    void aiIdle(CommandSourceType source);
    void aiAttackObject(Object *target, int maxShots, CommandSourceType source);
};

class Pathfinder {
public:
    void removeGoal003E3D20(Object *object);
};

class AI {
public:
    char pad000[12];
    Pathfinder *pathfinder;
};

extern AI *TheAI;

class BfmeOutOfWeaponRangeObject;
bool rva0014ca60(BfmeOutOfWeaponRangeObject *source, BfmeOutOfWeaponRangeObject *target);

class BfmeOwnedD {
public:
    void *bfmeDeleteSelf(unsigned int flags);
};

class Rva001CBDC0Receiver {
public:
    void clear(int value) { ((BfmeOwnedD *)this)->bfmeDeleteSelf(value); }
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

// The int set at owner data +0x250 calls its tree find out of line; this specialization declares it.
namespace _STL {
template <> class _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > {
public:
    template <class _KT> _Rb_tree_iterator<int, _Const_traits<int> > find(const _KT &key) const;
    _Rb_tree_node_base *_M_header;
    unsigned int _M_node_count;
};
}
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > IntSetTree00241F10;

extern void j_0003f544();

struct Node00241F10 { unsigned color; Node00241F10 *parent,*left,*right; int key,value; };
struct Iterator00241F10 { Node00241F10 *node; Iterator00241F10(){} Iterator00241F10(const Iterator00241F10& rhs):node(rhs.node){} };
struct BfmeMemberIndexIterator : Iterator00241F10 {};
class BfmeMemberIndexMap { public: BfmeMemberIndexIterator find(const int &id); };
struct IndexMap00241F10 : BfmeMemberIndexMap {};
struct TargetMap00241F10 {
    bool contains(int key) { const IntSetTree00241F10 &keys=*(const IntSetTree00241F10*)this; _STL::_Rb_tree_iterator<int, _STL::_Const_traits<int> > found=keys.find(key); return found._M_node!=keys._M_header; }
};

class HordeContain {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10(int value) = 0;
    // Retail reaches 0x00241F10 only through the vtable slot at RVA 0x00CAED5C.
    virtual void attackTargetNow(Object *target);
    char pad004[0x34 - 0x04];
    Rva00241F10RefreshHook *refreshHook;
    char pad038[4];
    std::map<int, int> memberIndices;
    unsigned char *memberSlots;

    int slotKey(int id) { BfmeMemberIndexIterator index=((IndexMap00241F10*)&memberIndices)->find(id); return *(int*)(memberSlots+index.node->value*16); }
    // Retail passes this-0xe4 in ECX to the landed 0x00232210 body, which the ledger names stdcall.
    bool isCurrentTarget(AIUpdateInterface *ai, Object *target) { union { void (*p)(); bool (HordeContain::*m)(AIUpdateInterface *, Object *); } c; c.p = j_0003f544; return (this->*c.m)(ai, target); }
};

// Template of an object after its override chain, null when the object has none.
static __forceinline Overridable *objectTemplate00241F10(Object *obj) {
    Overridable *t=(Overridable*)obj->m_template;
    if(!t) return 0;
    if(t->m_override) return (Overridable*)t->m_override->getFinalOverride();
    return t;
}

void HordeContain::attackTargetNow(Object *target) {
 Object *owner=*(Object**)((char*)this-0xdc);
 if(objectTemplate00241F10(owner)->flagsD4 & 0x400000) {
  Weapon *w=owner->getCurrentWeapon();
  if(!w || w->m_field->get()) return;
 }
 Object *object=*(Object**)((char*)this-0xdc);
 if(*(int*)((char*)object+0x9c)>=0) TheAI->pathfinder->removeGoal003E3D20(object);
 if(refreshHook) slot10(0);
 Rva00241F10Lookup *targetLookup=(Rva00241F10Lookup*)((char*)*(void**)((char*)this-0xe0)+0x250);
 Object *source;
 if(objectTemplate00241F10(target)->flagsD4 & 0x1000) source=target; else source=target->m_containedBy;
 typedef std::list<Object*> MemberList;
 MemberList &members=*(MemberList*)((char*)this-0xac);
 for(MemberList::iterator it=members.begin();it!=members.end();++it) {
  Object *member=*it;
  { int id=member->m_id; if(memberIndices.find(id)==memberIndices.end()) continue; }
  AIUpdateInterface *ai=member->m_ai;
  if(!ai || ai->bfmeBlocksFormationRefresh()) continue;
  Weapon *weapon=member->getCurrentWeapon();
  if(weapon && member->getCurrentWeapon()->m_field->get()) {
   if(ai->blocksFormationRefresh()) ((AICommandInterface*)((char*)ai+0x20))->aiIdle(CMD_FROM_AI);
   if(!(member->m_status[0] & 0x10000000)) ((Rva001CBDC0Receiver*)member)->clear(0);
   continue;
  }
  int key=slotKey(member->m_id);
  if(!((TargetMap00241F10*)targetLookup)->contains(key)) continue;
  if(((HordeContain*)((char*)this-0xe4))->isCurrentTarget(ai,target)) continue;
  Object *candidate=target;
  weapon=member->getCurrentWeapon();
  if(source) {
   TargetContainer *container=(TargetContainer*)source->unidentified_001BFE20();
   if(container) {
    Real range=0;
    if(weapon && !weapon->m_field->get()) range=weapon->getAttackRange(member);
    candidate=container->select(0,&member->m_cachedPos,range);
   }
  }
  if(rva0014ca60((BfmeOutOfWeaponRangeObject*)member,(BfmeOutOfWeaponRangeObject*)candidate)) {
   ((AICommandInterface*)((char*)ai+0x20))->aiAttackObject(candidate,0x7fffffff,CMD_FROM_AI);
  } else {
   TheAI->pathfinder->removeGoal003E3D20(member);
   *(unsigned char*)((char*)this+4)=1;
  }
 }
}

