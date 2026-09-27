// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include <algorithm>
#include <bitset>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "GameLogic/ObjectIter.h"

// Retail RVA 0x00202490; PassiveAreaEffectBehavior primary vtable
// VA 0x010A5304 slot 11 -> ILT RVA 0x00022E44 -> this 539-byte body.
// Constructor 0x00202100 installs that table; primary fields data+4,
// object+8 and ObjectID list+0x24 agree with the landed update/destructor.
// Original method name is unproved, so its address is retained.
// Filter/iterator ABI is shared with the landed 0x00265150 query.

class Object;
class Player;

// BFME's partition filters have a three-slot surface: scalar destructor,
// predicate, and getPlayerMask.  The ZH header has only the abstract predicate;
// this view preserves the BFME slots without inventing predicate bodies.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// Retail vtable 0x01085DD0; slot 1 is the matched +0x344 bit-3
// same-map-status comparison.
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

// Retail vtable 0x01083B80; slot 1 is the matched inverse +0x344 bit-0
// effective-dead test.  The neutral address-derived name avoids claiming a
// canonical owner for this BFME vtable.
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// Retail vtable 0x010A5158.  The matched slot-1 body is
// BfmeThingRJ::bfmeCheckRJ(void*); fields are the proven +8/+C/+10 shape.
class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

// The relationship table and all three of its methods are independently
// matched.  This is the canonical name for the BFME-compatible view.
class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

// The matched 0x009F2960 wrapper has a four-byte hidden result followed by
// (position, radius, order, filter-head, flag).  The generic decorated
// wrapper name does not assert the semantic owner; this BFME ABI view does.
class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

// Only the fields touched by this body are named.  ObjectID remains the
// canonical Common/GameType type; the private BFME Object layout is viewed
// directly at its proven offsets.
class Object
{
public:
	Player *getControllingPlayer(void) const;

	unsigned char m_00_to_38[0x38];
	Coord3D m_position;
	unsigned char m_44_to_74[0x30];
	ObjectID m_id;
};


class BfmeKindOfMask {
 _STL::bitset<176> bits;
public: BfmeKindOfMask(int a,int b) { bits.set(a); bits.set(b); }
};
class BfmeKindOfTester { public: bool isAnyKindOf(const BfmeKindOfMask&) const; };
struct AreaData00202490 { char pad00[8]; float radius08; char pad0C[0x14]; char sub20; };
class PassiveAreaEffectBehavior { public:
 void collectTargets00202490();
 unsigned field00; AreaData00202490* data04; Object* object08;
 char pad0C[0x18]; _STL::list<ObjectID> ids24;
};
void PassiveAreaEffectBehavior::collectTargets00202490() {
 Object* object=object08;
 AreaData00202490* data=data04;
 ids24.clear();
 PartitionFilterRelationship relationship(object,4,false);
 Rva0025ED50RootFilter root;
 Rva0025ED50ObjectFilter sameMap(object);
 Rva00265150RJFilter match(&data->sub20,object->getControllingPlayer(),true);
 relationship.link(&root);
 relationship.link(&sameMap);
 relationship.link(&match);
 Rva0025ED50WideResult iterator=ThePartitionManager->iterate(&object->m_position,data->radius08,ITER_FASTEST,&relationship,true);
 Object* other;
 while(iterator.next(other)) {
  if(other==object) continue;
  if(((BfmeKindOfTester*)other)->isAnyKindOf(BfmeKindOfMask(47,150))) continue;
  ObjectID id=other->m_id;
  if(_STL::find(ids24.begin(),ids24.end(),id)==ids24.end()) ids24.push_front(id);
 }
}
