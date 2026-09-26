// Retail RVA 0x00260180..0x00260502 is the 898-byte slot-15 primary action
// installed by the matched LevelGrantSpecialPower constructor at 0x0025FD20.
// The original method name is not independently known, so the slot keeps its
// address-derived name. The complete boundary ends in a plain ret at 0x260501.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include "Common/KindOf.h"
#include "GameLogic/ObjectIter.h"

class Object;
class Player;
typedef BitFlags<192> Rva00260180KindOfMask;
typedef BitFlags<86> Rva00260180ObjectStatusMask;
typedef char Rva00260180StatusMaskSizeCheck[
	(sizeof(Rva00260180ObjectStatusMask) == 12) ? 1 : -1];

// Retail sets bit 5 of the second 32-bit word: BitFlags' absolute index 37.
const Int Rva00260180RejectedStatusBit = 32 + 5;

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

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const Rva00260180KindOfMask &mustSet,
		const Rva00260180KindOfMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva00260180KindOfMask m_mustSet;
	Rva00260180KindOfMask m_mustClear;
};

class PartitionFilterRejectByObjectStatus : public PartitionFilter
{
public:
	PartitionFilterRejectByObjectStatus(
		const Rva00260180ObjectStatusMask &mustSet,
		const Rva00260180ObjectStatusMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterRejectByObjectStatus() {}
	virtual Bool allow(Object *);

	Rva00260180ObjectStatusMask m_mustSet;
	Rva00260180ObjectStatusMask m_mustClear;
};

class Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object) : m_object(object) {}
	virtual ~Rva00260180SelfFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, Player *player, Bool match)
		: m_subobject(subobject), m_player(player), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);

	void *m_subobject;
	Player *m_player;
	Bool m_match;
};

struct Rva00260180IterEntry
{
	Object *object;
	UnsignedInt word04;
};

struct Rva00260180IterData
{
	std::vector<Rva00260180IterEntry> entries;
	Rva00260180IterEntry *current;
	Int references;
};

struct Rva00260180OwningIterator
{
	Rva00260180IterData *value;

	Rva00260180OwningIterator();
	Rva00260180OwningIterator(const Rva00260180OwningIterator &);
	~Rva00260180OwningIterator()
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

class PartitionManager
{
public:
	Rva00260180OwningIterator iterateAt00260180(
		const Coord3D *, Real, IterOrderType, PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva00260060Owner
{
public:
	void update(Object *);
};

struct LevelGrantData
{
	unsigned char m_00_to_25c[0x25c];
	Real m_radius;
	unsigned char m_rjData[8];
	Rva00260180KindOfMask m_kindOf;
	Bool m_useKindOf;
};

class LevelGrantSpecialPower
{
public:
	virtual void actionAt00260180();
	void prepareAt002A9850();

	LevelGrantData *m_data;
	Object *m_object;
	unsigned char m_0c_to_b0[0xa4];
	Coord3D m_queryPosition;
};

void LevelGrantSpecialPower::actionAt00260180()
{
	prepareAt002A9850();
	Object *object = m_object;
	LevelGrantData *data = m_data;

	if (data->m_useKindOf)
	{
		Rva00260180OwningIterator iterator =
			ThePartitionManager->iterateAt00260180(
				&m_queryPosition, data->m_radius, ITER_FASTEST,
				Rva00260180SelfFilter(object)
					.link(&PartitionFilterRelationship(object, 4, false))
					->link(&Rva0025ED50RootFilter())
					->link(&Rva0025ED50ObjectFilter(object))
					->link(&PartitionFilterAcceptByKindOf(
						data->m_kindOf,
						*reinterpret_cast<const Rva00260180KindOfMask *>(
							&KINDOFMASK_NONE)))
					->link(&PartitionFilterRejectByObjectStatus(
						Rva00260180ObjectStatusMask(
							Rva00260180ObjectStatusMask::kInit,
							Rva00260180RejectedStatusBit),
						Rva00260180ObjectStatusMask())),
				true);

		Object *other;
		while (iterator.next(other))
		{
			if (other)
				reinterpret_cast<Rva00260060Owner *>(this)->update(other);
		}
	}
	else
	{
		Rva00260180OwningIterator iterator =
			ThePartitionManager->iterateAt00260180(
				&m_queryPosition, data->m_radius, ITER_FASTEST,
				Rva00260180SelfFilter(object)
					.link(&PartitionFilterRelationship(object, 4, false))
					->link(&Rva0025ED50RootFilter())
					->link(&Rva0025ED50ObjectFilter(object))
					->link(&Rva00265150RJFilter(
						&data->m_rjData,
						object->getControllingPlayer(), true))
					->link(&PartitionFilterRejectByObjectStatus(
						Rva00260180ObjectStatusMask(
							Rva00260180ObjectStatusMask::kInit,
							Rva00260180RejectedStatusBit),
						Rva00260180ObjectStatusMask())),
				true);

		Object *other;
		while (iterator.next(other))
		{
			if (other)
				reinterpret_cast<Rva00260060Owner *>(this)->update(other);
		}
	}
}
