// ?updateObject@ContestableContain@@QAEXPAVObject@@_N@Z
// partial score=0.7 date=2026-09-09
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

enum CommandSourceType
{
	CONTEST_COMMAND_SOURCE = 2
};

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
class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase();

protected:
	Object *m_object;

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

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
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
// destructor's real STLport instantiations.  The refresh only needs the list
// heads, but retaining the member types keeps the proven offsets truthful.
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

private:
	unsigned char m_unreconstructed_99c[0x20];
	_STL::list<Object *> m_contestList; // +0x9BC
	_STL::list<Object *> m_contestListShadow; // +0x9C0
	_STL::map<Object *, ContestableMapEntry> m_objectData; // +0x9C4
	_STL::list<ContestableRecord> m_records; // +0x9D0
	UnsignedInt m_lastContestUpdateFrame; // +0x9D4
};

// 0x00026396 is the existing incremental-link thunk for the real
// ContestableContain::updateObject(Object *, Bool) implementation at
// 0x0021BAF0. The typed helper pin in reverse/symbols.csv preserves this
// independently verified ILT route until the callee is converted.

// ?updateObject@ContestableContain@@QAEXPAVObject@@_N@Z
void ContestableContain::updateObject(Object *object, Bool contesting)
{
	typedef _STL::map<Object *, ContestableMapEntry> ObjectDataMap;
	ContestableContain *self = this;
	Object *owner = self->m_object;
	ObjectDataMap::iterator current = self->m_objectData.find(object);
	if (current == m_objectData.end())
		return;

	Bool able = object->isAbleToAttack();
	Object *old = current->second.m_object;
	if (old != 0)
	{
		if (able && object->getAbleToAttackSpecificObject(
			static_cast<AbleToAttackType>(8), old,
			static_cast<CommandSourceType>(2)) ==
			static_cast<CanAttackResult>(3))
			return;

		ObjectDataMap::iterator oldEntry = self->m_objectData.find(old);
		if (oldEntry != m_objectData.end())
			--oldEntry->second.m_count;
		current->second.m_object = 0;
	}

	if (!able)
		return;

	unsigned char contestLimit = owner->m_contestLimit;
	_STL::list<Object *> *candidates = contesting ? &self->m_containList : &self->m_contestList;
	Object *best = 0;
	ObjectDataMap::iterator bestEntry = ObjectDataMap::iterator();
	for (_STL::list<Object *>::iterator it = candidates->begin();
		it != candidates->end(); ++it)
	{
		ObjectDataMap::iterator entry = self->m_objectData.find(*it);
		if (entry == m_objectData.end() || entry->second.m_count >= contestLimit)
			continue;

		if (owner->getAbleToAttackSpecificObject(
			static_cast<AbleToAttackType>(8), *it,
			static_cast<CommandSourceType>(2)) !=
			static_cast<CanAttackResult>(3))
			continue;

		best = *it;
		bestEntry = entry;
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
