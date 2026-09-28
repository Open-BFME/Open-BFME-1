// ?d_002435f0@@YAXXZ
// partial score=0.9877883311 date=2026-09-28
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport

#include <math.h>
// Opaque HordeContain formation-slot rebalance at retail 0x002435F0.

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva002435F0MemberNode
{
	Rva002435F0MemberNode *next;
	Rva002435F0MemberNode *previous;
	void *value;
};

struct Rva002435F0MemberList
{
	Rva002435F0MemberNode *node;
};

class Rva002435F0OpenContainInterface
{
public:
#define RVA002435F0_SLOT(N) virtual void slot##N() = 0
	RVA002435F0_SLOT(00); RVA002435F0_SLOT(01); RVA002435F0_SLOT(02); RVA002435F0_SLOT(03);
	RVA002435F0_SLOT(04); RVA002435F0_SLOT(05); RVA002435F0_SLOT(06); RVA002435F0_SLOT(07);
	RVA002435F0_SLOT(08); RVA002435F0_SLOT(09); RVA002435F0_SLOT(10); RVA002435F0_SLOT(11);
	RVA002435F0_SLOT(12); RVA002435F0_SLOT(13); RVA002435F0_SLOT(14); RVA002435F0_SLOT(15);
	RVA002435F0_SLOT(16); RVA002435F0_SLOT(17); RVA002435F0_SLOT(18); RVA002435F0_SLOT(19);
	RVA002435F0_SLOT(20); RVA002435F0_SLOT(21); RVA002435F0_SLOT(22); RVA002435F0_SLOT(23);
	RVA002435F0_SLOT(24); RVA002435F0_SLOT(25); RVA002435F0_SLOT(26); RVA002435F0_SLOT(27);
	RVA002435F0_SLOT(28); RVA002435F0_SLOT(29); RVA002435F0_SLOT(30); RVA002435F0_SLOT(31);
	RVA002435F0_SLOT(32); RVA002435F0_SLOT(33); RVA002435F0_SLOT(34); RVA002435F0_SLOT(35);
	RVA002435F0_SLOT(36); RVA002435F0_SLOT(37); RVA002435F0_SLOT(38); RVA002435F0_SLOT(39);
	RVA002435F0_SLOT(40); RVA002435F0_SLOT(41); RVA002435F0_SLOT(42); RVA002435F0_SLOT(43);
	RVA002435F0_SLOT(44); RVA002435F0_SLOT(45); RVA002435F0_SLOT(46); RVA002435F0_SLOT(47);
	RVA002435F0_SLOT(48); RVA002435F0_SLOT(49); RVA002435F0_SLOT(50); RVA002435F0_SLOT(51);
	RVA002435F0_SLOT(52); RVA002435F0_SLOT(53); RVA002435F0_SLOT(54); RVA002435F0_SLOT(55);
	RVA002435F0_SLOT(56); RVA002435F0_SLOT(57); RVA002435F0_SLOT(58); RVA002435F0_SLOT(59);
	RVA002435F0_SLOT(60); RVA002435F0_SLOT(61); RVA002435F0_SLOT(62); RVA002435F0_SLOT(63);
	RVA002435F0_SLOT(64);
	virtual const Rva002435F0MemberList *getContainedItemsList() const = 0;
#undef RVA002435F0_SLOT
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	char pad000[4];
};

class Rva002435F0Link
{
public:
	char pad000[4];
	Overridable *overrideValue;
};

enum WeaponSlotType
{
	Rva002435F0WeaponSlotUnknown = 0
};

class Weapon
{
public:
	char pad000[4];
	int value;
};

#define BFME_HAVE_COORD3D 1
#define OBJECT_TU_MEMBERS int getID() const { return m_id; } Weapon *getCurrentWeapon(WeaponSlotType *slot); const Coord3D *getPosition() const {return &m_cachedPos;}
#include "object.h"

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **key);
 int &lookup(const int &key);

	unsigned char body[0xc];
};

struct Rva00233F30Offset { float x,y; };
struct BfmeRva44E60Record { BfmeRva44E60Record(const BfmeRva44E60Record&); int m_dword00; Rva00233F30Offset m_pair04; float m_float0C; };
class Rva00233F30 { public: BfmeRva44E60Record rva002350c0(Int index); };

#pragma comment(linker, "/alternatename:?fillFormationPosition@Rva002435F0Owner@@QAEPAVCoord3D@@PAV2@H@Z=?j_00019736@@YAXXZ")

class Rva002435F0View
{
public:
	void run();

	char pad000[0x3c];
	BfmeSubDSU m_indices;
	unsigned char *slotBegin;
	unsigned char *slotEnd;
};

#define RVA002435F0_THRESHOLD 0.3f

static __forceinline Int getIndex(Rva002435F0View *view, Object *object)
{
	return view->m_indices.lookup(object->getID());
}

static __forceinline Overridable *resolveOverride(Object *object)
{
	Rva002435F0Link *link = (Rva002435F0Link*)object->m_template;
	if (link == 0)
		return 0;
	if(link->overrideValue) return (Overridable*)link->overrideValue->getFinalOverride();
 return (Overridable*)link;
}

static __forceinline float distance2D(Coord3D &p, const Coord3D &q) {
 p.x-=q.x; p.y-=q.y; return (float)sqrt(p.x*p.x+p.y*p.y);
}
void Rva002435F0View::run() {
 const Rva002435F0MemberList *members=((Rva002435F0OpenContainInterface*)((char*)this-0xc4))->getContainedItemsList();
 const Coord3D *basePosition=(const Coord3D*)(*(char**)((char*)this-0xdc)+0x38);
 for(Rva002435F0MemberNode *outer=members->node->next;outer!=members->node;outer=outer->next) {
  Object *member=(Object*)outer->value;
  int index=getIndex(this,member);
  if((unsigned)index>(unsigned)((slotEnd-slotBegin)>>4)) return;
  BfmeRva44E60Record rec=((Rva00233F30*)((char*)this-0xe4))->rva002350c0(index);
  Coord3D memberSlot;
  memberSlot.x=rec.m_pair04.x+basePosition->x; memberSlot.y=rec.m_pair04.y+basePosition->y;
  for(Rva002435F0MemberNode *inner=outer->next;inner!=members->node;inner=inner->next) {
   Object *other=(Object*)inner->value;
   if(resolveOverride(other)!=resolveOverride(member)) continue;
   if(other->getCurrentWeapon(0) && member->getCurrentWeapon(0)) { int value=other->getCurrentWeapon(0)->value; if(value!=member->getCurrentWeapon(0)->value) continue; }
   int otherIndex=getIndex(this,other);
   if((unsigned)otherIndex>(unsigned)((slotEnd-slotBegin)>>4)) continue;
   BfmeRva44E60Record rec2=((Rva00233F30*)((char*)this-0xe4))->rva002350c0(otherIndex);
   Coord3D otherSlot;
   otherSlot.x=rec2.m_pair04.x+basePosition->x; otherSlot.y=rec2.m_pair04.y+basePosition->y;
   Coord3D position;position.x=member->getPosition()->x;position.y=member->getPosition()->y;position.z=member->getPosition()->z;
   float memberDistance=distance2D(position,memberSlot);
   position=*other->getPosition();
   float otherToMember=distance2D(position,memberSlot);
   if(otherToMember<memberDistance) {
    position=*other->getPosition();
    float otherDistance=distance2D(position,otherSlot);
    position=*member->getPosition();
    float memberToOther=distance2D(position,otherSlot);
    if(memberToOther<(memberDistance-otherToMember)*RVA002435F0_THRESHOLD+otherDistance) {
     m_indices.lookup(other->getID())=index;
     m_indices.lookup(member->getID())=otherIndex;
     index=otherIndex;
    }
   }
  }
 }
}

#pragma comment(linker, "/alternatename:?lookup@BfmeSubDSU@@QAEAAHABH@Z=?j_0001f91f@@YAXXZ")
