// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "GameLogic/ObjectIter.h"

// Retail RVA 0x00265150 is 468 bytes through the final ret at +0x1D3.
// The owner is left address-labelled: its +4 data pointer, +8 object pointer,
// +E8 ObjectID list, +F4 inner-filter radius and +F8 outer-query radius are
// all proven by the retail loads. The matched 355-byte query at 25ED50 proves
// the shared filter and iterator ABI, not this owner's original class name.

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

// Retail vtable 0x010B6B64.  Its matched slot-1 body is
// Rva00264B80DistanceCheck::isOutside(const Rva00264B80Point*), which uses an
// Object-compatible +0x38 point view.  This class is only the BFME virtual
// ABI/layout view used by the filter chain; no unproven predicate is emitted.
class Rva00265150DistanceFilter : public PartitionFilter
{
public:
	Rva00265150DistanceFilter(Real radius, const Coord3D *position)
		: m_radius(radius), m_position(position) {}
	virtual ~Rva00265150DistanceFilter() {}
	virtual Bool allow(Object *);

	Real m_radius;
	const Coord3D *m_position;
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

struct Rva00265150Data
{
	unsigned char m_00_to_280[0x280];
	unsigned char m_subobject_280;
};

class Rva00265150Owner
{
public:
	void callAt00265150();

	unsigned char m_00_to_04[0x04];
	Rva00265150Data *m_data;
	Object *m_object;
	unsigned char m_0c_to_e8[0xdc];
	_STL::list<ObjectID> m_ids;
	unsigned char m_ec_to_f4[0x08];
	Real m_radius_f4;
	Real m_radius_f8;
};

typedef char Rva00265150ListSizeCheck[
	(sizeof(_STL::list<ObjectID>) == 4) ? 1 : -1];

void Rva00265150Owner::callAt00265150()
{
	Object *object = m_object;
	Rva00265150Data *data = m_data;

	Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
		&object->m_position, m_radius_f8, ITER_FASTEST,
		PartitionFilterRelationship(object, 4, false).link(
			Rva00265150RJFilter(
				&data->m_subobject_280,
				object->getControllingPlayer(), true).link(
					Rva0025ED50RootFilter().link(
						Rva0025ED50ObjectFilter(object).link(
							&Rva00265150DistanceFilter(
								m_radius_f4, &object->m_position))))),
		true);

	Object *other;
	while (iterator.next(other))
	{
		if (other == 0 || other == object)
			continue;

		// Retail snapshots the ObjectID before the STL node allocation.
		ObjectID id = other->m_id;
		m_ids.push_back(id);
	}
}

