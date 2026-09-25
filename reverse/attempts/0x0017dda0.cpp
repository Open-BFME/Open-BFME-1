// ?update@AIMeleeReAcquireState@@UAE?AW4StateReturnType@@XZ
// partial score=0.39 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponSlotType {};

class Player;
class Weapon;
class Object;

template <Int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class AIUpdateInterface
{
public:
	void friend_setGoalObject(Object *object);
};

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Player *getControllingPlayer() const;
	void setStatus(const ObjectStatusMaskType &mask, Bool set);

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x94 - 0x44];
	unsigned char m_condition94;
	char m_pad095[0x204 - 0x95];
	AIUpdateInterface *m_ai;
	char m_pad208[0x214 - 0x208];
	int m_field214;
	char m_pad218[0x344 - 0x218];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	Object *getGoalObject();

	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void setGoalObject(Object *object);

	char m_pad000[0x0c];
	Object *m_owner;
};

class GameLogic
{
public:
	char m_pad000[0x3c];
	UnsignedInt m_frame;
};

class TAiData
{
public:
	char m_pad000[0x94];
	float m_meleeAcquireRadius;
};

class AI
{
public:
	char m_pad000[0x14];
	TAiData *m_aiData;
};

class __declspec(novtable) PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

static __forceinline void setFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<volatile UnsignedInt *>(filter) = value;
}

class __declspec(novtable) Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);

	__forceinline ~Rva001DCBB0Filter()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	Player *m_player;
	unsigned char m_match;
};

class __declspec(novtable) PartitionFilterInsignificantBuildings : public PartitionFilter
{
public:
	PartitionFilterInsignificantBuildings(Bool allowNonBuildings,
		Bool allowInsignificant)
	{
		m_next = 0;
		setFilterVptr(this, 0x010956E4);
		m_allowNonBuildings = allowNonBuildings;
		m_allowInsignificant = allowInsignificant;
	}

	__forceinline ~PartitionFilterInsignificantBuildings()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	Bool m_allowNonBuildings;
	Bool m_allowInsignificant;
};

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
	{
		m_next = 0;
		setFilterVptr(this, 0x010956C4);
		m_object = object;
		m_flags = flags;
		m_match = match;
	}

	__forceinline ~PartitionFilterRelationship()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *object);

	__forceinline ~PartitionFilterRejectBuildings()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	const Object *m_object;
	Bool m_acquireEnemies;
};

class __declspec(novtable) Rva0017DDA0PairFilter : public PartitionFilter
{
public:
	Rva0017DDA0PairFilter(Object *object, void *value)
	{
		m_next = 0;
		setFilterVptr(this, 0x01097744);
		m_object = object;
		m_value = value;
	}

	__forceinline ~Rva0017DDA0PairFilter()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	Object *m_object;
	void *m_value;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float range,
		Int distanceCalculation, PartitionFilter *filters);
};

extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;

class AIMeleeReAcquireState
{
public:
	virtual StateReturnType update();

private:
	char m_pad004[0x18];
	StateMachine *m_machine;
	char m_pad020[4];
	UnsignedInt m_nextAcquireFrame;
};

StateReturnType AIMeleeReAcquireState::update()
{
	const UnsignedInt frame = TheBfmeGameLogic->m_frame;
	if (frame - m_nextAcquireFrame < 1)
		return STATE_FAILURE;

	Object *owner = m_machine->m_owner;
	owner->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 28),
		false);

	if ((owner->m_condition94 & 0x20) != 0 && owner->m_field214 != 0)
		return STATE_FAILURE;

	Weapon *weapon = owner->getCurrentWeapon(0);
	if (weapon == 0)
		return STATE_FAILURE;

	if (m_machine == 0)
		return STATE_FAILURE;

	Object *goal = m_machine->getGoalObject();
	if (goal != 0 && (goal->m_flags344 & 1) == 0 &&
		!((BFMEObjectStealthQuery *)goal)->isStealthedAndUndetected(
			(const Object *)owner->getControllingPlayer()))
	{
		m_machine->setGoalObject(goal);
		owner->m_ai->friend_setGoalObject(goal);
		m_nextAcquireFrame = TheBfmeGameLogic->m_frame;
		return STATE_SUCCESS;
	}

	Coord3D position;
	position.x = owner->m_position.x;
	position.y = owner->m_position.y;
	position.z = owner->m_position.z;
	volatile char scratchPad[8];
	scratchPad[0] = 0;

	Rva001DCBB0Filter playerFilter(owner, 0);
	PartitionFilterInsignificantBuildings insignificantFilter(true, false);
	PartitionFilterRelationship relationshipFilter(owner, 2, false);
	PartitionFilterRejectBuildings buildingFilter(owner);
	Rva0017DDA0PairFilter finalFilter(owner, 0);

	PartitionFilter *filters =
		reinterpret_cast<PartitionFilter *>(&insignificantFilter)->link(
			reinterpret_cast<PartitionFilter *>(&playerFilter));
	filters = reinterpret_cast<PartitionFilter *>(&relationshipFilter)->link(filters);
	filters = reinterpret_cast<PartitionFilter *>(&buildingFilter)->link(filters);
	filters = reinterpret_cast<PartitionFilter *>(&finalFilter)->link(filters);

	Object *found = ThePartitionManager->getClosestObject(
		&position, TheAI->m_aiData->m_meleeAcquireRadius * 2.0f, 1, filters);

	{
		setFilterVptr(&finalFilter, 0x01083B5C);
		setFilterVptr(&buildingFilter, 0x01083B5C);
		setFilterVptr(&relationshipFilter, 0x01083B5C);
		setFilterVptr(&insignificantFilter, 0x01083B5C);
		setFilterVptr(&playerFilter, 0x01083B5C);
	}
	m_machine->setGoalObject(found);
	owner->m_ai->friend_setGoalObject(found);
	m_nextAcquireFrame = TheBfmeGameLogic->m_frame;
	return STATE_SUCCESS;
}
