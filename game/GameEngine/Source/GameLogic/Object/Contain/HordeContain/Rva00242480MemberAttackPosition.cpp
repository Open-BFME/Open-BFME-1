// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0x00242480 complete 342-byte thiscall ending ret 4, reached only
// through the HordeContain vtable slot at RVA 0x00CAED58 (ILT 0x0000392C), the
// slot before HordeContain::attackTargetNow (0x00241F10, slot RVA 0x00CAED5C).
// Same receiver as that sibling (owner at this-0xdc, member list at this-0xac,
// member index map at this+0x3c, slot records at this+0x48) and the same
// out-of-line finds. Each eligible member is ordered to attack the position.
// No name: the ILT oracle refutes attackPositionNow/attackPosition spellings,
// so the address-derived owner stays.
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

class AIUpdateInterface : public AIUpdateSlots<96> {
public:
    virtual bool query184() = 0;				// vtable +0x184
};

class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_override;
    char pad008[0xd4 - 0x08];
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
};

#define BFME_HAVE_COORD3D 1
#define OBJECT_TU_MEMBERS \
    Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
#include "../../object.h"

class AICommandInterface {
public:
    void aiAttackPosition(const Coord3D *pos, int maxShots, CommandSourceType source);
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
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > IntSetTree00242480;

struct Node00242480 { unsigned color; Node00242480 *parent,*left,*right; int key,value; };
struct Iterator00242480 { Node00242480 *node; Iterator00242480(){} Iterator00242480(const Iterator00242480& rhs):node(rhs.node){} };
struct BfmeMemberIndexIterator : Iterator00242480 {};
class BfmeMemberIndexMap { public: BfmeMemberIndexIterator find(const int &id); Node00242480 *m_header; };
struct IndexMap00242480 : BfmeMemberIndexMap {};
struct TargetMap00242480 {
    bool contains(int key) { const IntSetTree00242480 &keys=*(const IntSetTree00242480*)this; _STL::_Rb_tree_iterator<int, _STL::_Const_traits<int> > found=keys.find(key); return found._M_node!=keys._M_header; }
};
struct Rva00242480Lookup { int unused; };

class Rva00242480HordeContain {
public:
    void method(const Coord3D *pos);
    char pad000[0x3c];
    std::map<int, int> memberIndices;		// this+0x3C
    unsigned char *memberSlots;			// this+0x48

    int slotKey(int id) { BfmeMemberIndexIterator index=((IndexMap00242480*)&memberIndices)->find(id); return *(int*)(memberSlots+index.node->value*16); }
};

// Template of an object after its override chain, null when the object has none.
static __forceinline Overridable *objectTemplate00242480(Object *obj) {
    Overridable *t=(Overridable*)obj->m_template;
    if(!t) return 0;
    if(t->m_override) return (Overridable*)t->m_override->getFinalOverride();
    return t;
}

void Rva00242480HordeContain::method(const Coord3D *pos) {
 Object *owner=*(Object**)((char*)this-0xdc);
 if(objectTemplate00242480(owner)->flagsD4 & 0x400000) {
  Weapon *w=owner->getCurrentWeapon();
  if(!w || w->m_field->get()) return;
 }
 Rva00242480Lookup *targetLookup=(Rva00242480Lookup*)((char*)*(void**)((char*)this-0xe0)+0x250);
 typedef std::list<Object*> MemberList;
 MemberList &members=*(MemberList*)((char*)this-0xac);
 for(MemberList::iterator it=members.begin();it!=members.end();++it) {
  Object *member=*it;
  { int id=member->m_id; if(memberIndices.find(id)==memberIndices.end()) continue; }
  AIUpdateInterface *ai=member->m_ai;
  if(!ai) continue;
  int key=slotKey(member->m_id);
  if(!((TargetMap00242480*)targetLookup)->contains(key)) continue;
  if(ai->query184()) continue;
  ((AICommandInterface*)((char*)member->m_ai+0x20))->aiAttackPosition(pos,0x7fffffff,CMD_FROM_AI);
 }
}

// Retail 0x002230A0 (71 B, RET 8): STLport's int-key _Rb_tree::find over the
// member index map, reached from the slotKey lookup above. Its row was a
// gen-alias to a byte-equal map<int,GameSpyStagingRoom*> instantiation in
// PeerDefs.cpp; the pinned view name stays.
// ?find@BfmeMemberIndexMap@@QAE?AUBfmeMemberIndexIterator@@ABH@Z
__declspec(noinline) BfmeMemberIndexIterator BfmeMemberIndexMap::find(const int &id)
{
    Node00242480 *y = m_header;
    Node00242480 *x = m_header->parent;
    while (x != 0)
        if (!(x->key < id))
            y = x, x = x->left;
        else
            x = x->right;
    BfmeMemberIndexIterator it;
    it.node = y;
    if (y == m_header || id < y->key)
        it.node = m_header;
    return it;
}
