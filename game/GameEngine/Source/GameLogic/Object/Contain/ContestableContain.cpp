// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// ContestableContain's periodic contest refresh, retail 0x0021BCA0.
//
// The owner is fixed by the retail thunk at 0x0002F919: the sole named
// caller, Rva0021D4A0::check, passes the complete ContestableContain object
// (its secondary interface has this+0x10) and refreshes it when the cached
// frame at this+0x9D4 expires.  The refresh walks OpenContain's real
// contained-object list, then ContestableContain's object list, and advances
// that cache by thirty logic frames.

#include <list>
#include <map>

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum AbleToAttackType
{
	CONTEST_ATTACK_TYPE = 8
};

#include "../../command_source_type.h"

enum CanAttackResult
{
	CONTEST_ATTACK_RESULT_POSSIBLE = 3
};

class Object
{
public:
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource) const;
};

// Relation resolver, RvaC4390Second_resolve.cpp (ILT 0x00035995).
struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int index);
};

// updateObject reads one byte at +0x1A8 through the module-data pointer at
// this+4, while the ContestableContainModuleData factory allocates 0x1A8 bytes.
struct ContestLimitModuleData0021BAF0
{
	unsigned char m_unreconstructed_000[0x1a8];
	unsigned char m_contestLimit;
};

// The BFME GameLogic frame is the field used by the surrounding
// ContestableContain state machine at GameLogic+0x3C.
class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return m_frame;
	}

private:
	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// OpenContain's multiple-inheritance prefix is the same layout recovered by
// ContestableContainDestructorThunk.cpp.  Its first real data member begins
// at +0x38; the remaining opaque base data ends at +0x3FC.
// Primary vtable slot 0x6C is the object query the contest lookup falls back
// on; the other slots are unmodelled and keep only their offsets.
class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase();
	virtual void slot_004() = 0;
	virtual void slot_008() = 0;
	virtual void slot_00c() = 0;
	virtual void slot_010() = 0;
	virtual void slot_014() = 0;
	virtual void slot_018() = 0;
	virtual void slot_01c() = 0;
	virtual void slot_020() = 0;
	virtual void slot_024() = 0;
	virtual void slot_028() = 0;
	virtual void slot_02c() = 0;
	virtual void slot_030() = 0;
	virtual void slot_034() = 0;
	virtual void slot_038() = 0;
	virtual void slot_03c() = 0;
	virtual void slot_040() = 0;
	virtual void slot_044() = 0;
	virtual void slot_048() = 0;
	virtual void slot_04c() = 0;
	virtual void slot_050() = 0;
	virtual void slot_054() = 0;
	virtual void slot_058() = 0;
	virtual void slot_05c() = 0;
	virtual void slot_060() = 0;
	virtual void slot_064() = 0;
	virtual void slot_068() = 0;
	virtual void *primarySlot_06c(Object *object) const = 0;

protected:
	const ContestLimitModuleData0021BAF0 *m_moduleData; // ObjectModule ctor 0x00113C60 stores it at +4

private:
	unsigned char m_pad[4];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase();
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase();

private:
	unsigned char m_pad[12];
};

// OpenContain's ContainModuleInterface subobject at +0x20: ContestableContain's
// secondary vtable 0x010AB140 holds 0x0021BA10 (ILT 0x0003C277) at slot 0xC8,
// guarded by the slot 0xC4 predicate.  Only those two slots are modelled.
class ContainModuleInterface
{
public:
	virtual void slot_000() = 0;
	virtual void slot_004() = 0;
	virtual void slot_008() = 0;
	virtual void slot_00c() = 0;
	virtual void slot_010() = 0;
	virtual void slot_014() = 0;
	virtual void slot_018() = 0;
	virtual void slot_01c() = 0;
	virtual void slot_020() = 0;
	virtual void slot_024() = 0;
	virtual void slot_028() = 0;
	virtual void slot_02c() = 0;
	virtual void slot_030() = 0;
	virtual void slot_034() = 0;
	virtual void slot_038() = 0;
	virtual void slot_03c() = 0;
	virtual void slot_040() = 0;
	virtual void slot_044() = 0;
	virtual void slot_048() = 0;
	virtual void slot_04c() = 0;
	virtual void slot_050() = 0;
	virtual void slot_054() = 0;
	virtual void slot_058() = 0;
	virtual void slot_05c() = 0;
	virtual void slot_060() = 0;
	virtual void slot_064() = 0;
	virtual void slot_068() = 0;
	virtual void slot_06c() = 0;
	virtual void slot_070() = 0;
	virtual void slot_074() = 0;
	virtual void slot_078() = 0;
	virtual void slot_07c() = 0;
	virtual void slot_080() = 0;
	virtual void slot_084() = 0;
	virtual void slot_088() = 0;
	virtual void slot_08c() = 0;
	virtual void slot_090() = 0;
	virtual void slot_094() = 0;
	virtual void slot_098() = 0;
	virtual void slot_09c() = 0;
	virtual void slot_0a0() = 0;
	virtual void slot_0a4() = 0;
	virtual void slot_0a8() = 0;
	virtual void slot_0ac() = 0;
	virtual void slot_0b0() = 0;
	virtual void slot_0b4() = 0;
	virtual void slot_0b8() = 0;
	virtual void slot_0bc() = 0;
	virtual void slot_0c0() = 0;
	virtual Bool slot_0c4() const = 0;
	virtual Bool rva0021BA10(Object *object, Object **target) const = 0;
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public ContainModuleInterface,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
protected:
	_STL::list<Object *> m_containList; // +0x38, upstream ContainedItemsList

private:
	unsigned char m_pad[0x3c0];
};

class Coord3D
{
private:
	float m_value[3];
};

class __declspec(novtable) GarrisonContain : public OpenContain
{
private:
	Coord3D m_garrisonPoint[3][40]; // base ends at +0x99C
};

// These are the payload types already recovered from the ContestableContain
// destructor's real STLport instantiations.  updateObject reads the entry's
// target pointer at node+0x14 and its byte counter at node+0x18.
struct ContestableMapEntry
{
	Object *m_object;
	unsigned char m_count;
	unsigned char m_pad[3];
};

struct ContestableRecord
{
	int a[2];
};

class ContestableContain : public GarrisonContain
{
public:
	void updateContestStatus();
	void updateObject(Object *object, Bool contesting);
	virtual Bool rva0021BA10(Object *object, Object **target) const;

private:
	unsigned char m_unreconstructed_99c[0x20];
	_STL::list<Object *> m_contestList; // +0x9BC
	_STL::list<Object *> m_contestListShadow; // +0x9C0
	_STL::map<Object *, ContestableMapEntry> m_objectData; // +0x9C4
	_STL::list<ContestableRecord> m_records; // +0x9D0
	UnsignedInt m_lastContestUpdateFrame; // +0x9D4
};

// updateContestStatus reaches updateObject (0x0021BAF0) through the
// incremental-link thunk 0x00026396.

// ?updateObject@ContestableContain@@QAEXPAVObject@@_N@Z
void ContestableContain::updateObject(Object *object, Bool contesting)
{
	typedef _STL::map<Object *, ContestableMapEntry> ObjectDataMap;
	const ContestLimitModuleData0021BAF0 *owner = m_moduleData;
	ObjectDataMap::iterator current = m_objectData.find(object);
	if (current == m_objectData.end())
		return;

	Bool able = object->isAbleToAttack();
	Object *old = current->second.m_object;
	if (old != 0)
	{
		if (able && object->getAbleToAttackSpecificObject(
			CONTEST_ATTACK_TYPE, old,
			CMD_FROM_AI) ==
			CONTEST_ATTACK_RESULT_POSSIBLE)
			return;

		ObjectDataMap::iterator oldEntry = m_objectData.find(old);
		if (oldEntry != m_objectData.end())
			--oldEntry->second.m_count;
		current->second.m_object = 0;
	}

	if (!able)
		return;

	_STL::list<Object *> *candidates = contesting ? &m_containList : &m_contestList;
	unsigned char bestCount = owner->m_contestLimit;
	Object *best = 0;
	ObjectDataMap::iterator bestEntry = 0;
	for (_STL::list<Object *>::iterator it = candidates->begin();
		it != candidates->end(); ++it)
	{
		ObjectDataMap::iterator entry = m_objectData.find(*it);
		if (entry != m_objectData.end() && entry->second.m_count < bestCount &&
			entry->second.m_count < owner->m_contestLimit &&
			object->getAbleToAttackSpecificObject(
				CONTEST_ATTACK_TYPE, *it,
				CMD_FROM_AI) ==
				CONTEST_ATTACK_RESULT_POSSIBLE)
		{
			best = *it;
			bestCount = entry->second.m_count;
			bestEntry = entry;
		}
	}

	current->second.m_object = best;
	if (best != 0)
		++bestEntry->second.m_count;
}

// ?updateContestStatus@ContestableContain@@QAEXXZ
void ContestableContain::updateContestStatus()
{
	for (_STL::list<Object *>::iterator it = m_containList.begin();
		it != m_containList.end(); ++it)
	{
		updateObject(*it, false);
	}

	for (_STL::list<Object *>::iterator it = m_contestList.begin();
		it != m_contestList.end(); ++it)
	{
		updateObject(*it, true);
	}

	m_lastContestUpdateFrame = TheGameLogic->getFrame() + 30;
}

// ?rva0021BA10@ContestableContain@@UBE_NPAVObject@@PAPAV2@@Z
// Contest-map lookup, retail 0x0021BA10: the const find it calls (ILT
// 0x0000F22C, body 0x0021B110) is the byte twin of updateObject's mutable
// find at 0x0021B0B0.  On a miss the object's relation (resolve(0)) is tried
// once when the primary slot 0x6C query accepts the object.  The method name
// is not recovered and keeps the address.
Bool ContestableContain::rva0021BA10(Object *object, Object **target) const
{
	typedef _STL::map<Object *, ContestableMapEntry> ObjectDataMap;
	if (!slot_0c4() || object == 0)
		return false;

	ObjectDataMap::const_iterator it = m_objectData.find(object);
	if (it == m_objectData.end())
	{
		if (primarySlot_06c(object) != 0)
		{
			object = (Object *)((RvaC4390Second *)object)->resolve(0);
			it = m_objectData.find(object);
			if (it != m_objectData.end())
			{
				*target = (*it).second.m_object;
				return true;
			}
		}
		return false;
	}
	*target = (*it).second.m_object;
	return true;
}
