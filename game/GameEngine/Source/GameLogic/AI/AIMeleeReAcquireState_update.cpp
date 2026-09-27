// ?update@AIMeleeReAcquireState@@UAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc
// stlport

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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

	Bool operator!=(const BitFlags &other) const;

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

	void set(const BitFlags &other)
	{
		m_bits |= other.m_bits;
	}

	void clear(const BitFlags &other)
	{
		m_bits &= ~other.m_bits;
	}

	Bool test(Int index) const
	{
		return m_bits.test(index);
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

class ObjectHelper
{
public:
	void sleepUntil(UnsignedInt frame);
};

class PartitionData
{
public:
	void makeDirty();
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Player *getControllingPlayer() const;
	__declspec(noinline) void setStatus(const ObjectStatusMaskType &mask, Bool set);

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x90 - 0x44];
	ObjectStatusMaskType m_status;
	char m_pad09c[0x1d4 - 0x9c];
	ObjectHelper *m_repulsorHelper;
	char m_pad1d8[0x204 - 0x1d8];
	AIUpdateInterface *m_ai;
	char m_pad208[0x214 - 0x208];
	int m_field214;
	char m_pad218[0x344 - 0x218];
	unsigned char m_flags344;
	char m_pad345[0x3b0 - 0x345];
	PartitionData *m_partitionData;
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

extern GameLogic *TheGameLogic;

inline __declspec(noinline) void Object::setStatus(
	const ObjectStatusMaskType &objectStatus, Bool set)
{
	ObjectStatusMaskType &status = m_status;
	ObjectStatusMaskType oldStatus = status;

	if (set)
	{
		status.set(objectStatus);
	}
	else
	{
		status.clear(objectStatus);
	}

	if (status != oldStatus)
	{
		if (set && objectStatus.test(8) && m_repulsorHelper)
		{
			m_repulsorHelper->sleepUntil(TheGameLogic->m_frame + 10);
		}

		if (oldStatus.test(2) != m_status.test(2))
		{
			if (m_partitionData)
			{
				m_partitionData->makeDirty();
			}
		}
	}
}


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

extern AI *TheAI;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	PartitionFilter *link(PartitionFilter *next);

protected:
	UnsignedInt m_vptr;
	PartitionFilter *m_next;
};

static __forceinline void setFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<UnsignedInt *>(filter) = value;
}

class __declspec(novtable) Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	~Rva001DCBB0Filter()
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
		setFilterVptr(this, 0x010956E4);
		m_allowNonBuildings = allowNonBuildings;
		m_allowInsignificant = allowInsignificant;
	}
	~PartitionFilterInsignificantBuildings()
	{
		setFilterVptr(this, 0x01083B5C);
	}


	Bool m_allowNonBuildings;
	Bool m_allowInsignificant;
};

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Int state)
	{
		setFilterVptr(this, 0x010956C4);
		m_object = object;
		m_flags = flags;
		m_state = state;
	}

	~PartitionFilterRelationship()
	{
		setFilterVptr(this, 0x01083B5C);
	}

	Object *m_object;
	Int m_flags;
	Int m_state;
};

class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *object);
	~PartitionFilterRejectBuildings()
	{
		setFilterVptr(this, 0x01083B5C);
	}


	const Object *m_object;
	Bool m_acquireEnemies;
};

class __declspec(novtable) Rva0017DDA0PairFilter : public PartitionFilter
{
public:
	Rva0017DDA0PairFilter(Object *object, Weapon *weapon,
		TAiData **aiDataOut)
	{
		setFilterVptr(this, 0x01097744);
		m_object = object;
		m_weapon = weapon;
		_ReadWriteBarrier();
		*aiDataOut = TheAI->m_aiData;
	}

	~Rva0017DDA0PairFilter()
	{
		setFilterVptr(this, 0x01083B5C);
	}


	Object *m_object;
	Weapon *m_weapon;
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

	Weapon *weapon;
	if (((reinterpret_cast<const unsigned char *>(owner)[0x94] & 0x20) != 0 &&
			owner->m_field214 != 0) ||
		(weapon = owner->getCurrentWeapon(0)) == 0 ||
		m_machine == 0)
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

	Object *found;
	{
		Coord3D position;
		volatile Coord3D &destinationPosition = position;
		const volatile Coord3D &sourcePosition = owner->m_position;
		destinationPosition.x = sourcePosition.x;
		destinationPosition.y = sourcePosition.y;
		position.z = sourcePosition.z;

		TAiData *aiData;
		found = ThePartitionManager->getClosestObject(
			&position, aiData->m_meleeAcquireRadius * 2.0f, 1,
			Rva0017DDA0PairFilter(owner, weapon, &aiData).link(
				PartitionFilterRejectBuildings(owner).link(
					PartitionFilterRelationship(owner, 2, 0).link(
						PartitionFilterInsignificantBuildings(true, false).link(
							&Rva001DCBB0Filter(owner, 0))))));
	}
	m_machine->setGoalObject(found);
	owner->m_ai->friend_setGoalObject(found);
	m_nextAcquireFrame = TheBfmeGameLogic->m_frame;
	return STATE_SUCCESS;
}
