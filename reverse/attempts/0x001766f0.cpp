// ?d_001766f0@@YAXXZ
// partial score=0.65 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x001766F0: the pre-firing attack move-state update.  The state keeps
// the victim it locked on to by id, decides whether the current goal is ahead
// of the owner, and drives the weapon through its pre-attack status before
// delegating to the internal move update.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponStatus.h
// BFME carries one status past the Zero Hour list; it is spelled by value.
enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1,
	BETWEEN_FIRING_SHOTS = 2,
	RELOADING_CLIP = 3,
	PRE_ATTACK = 4,
	BFME_WEAPON_STATUS_5 = 5
};

enum { BFME_OBJECT_FLAG_PRE_FIRING = 0x10000000 };
enum { BFME_OBJECT_STATUS_UNTARGETABLE = 0x00040000 };
enum { BFME_OBJECT_STATUS_BIT_PRE_FIRING = 0x0d };
enum { BFME_OBJECT_STATUS_MASK_BIT = 28 };

extern const Real BfmeZeroRange;

class Object;
class Player;
class Weapon;
class BfmeOutOfWeaponRangeObject;

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <Int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int index)
	{
		m_bits.set(index);
	}
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	WeaponStatus getStatus() const;
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	Bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const BfmeOutOfWeaponRangeObject *victim, Int forceAttacking) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BFMEVirtualSlots<129>
{
public:
	virtual void notifyVictimIsDead() = 0;             // vtable +0x204

	void destroyPath();
	void friend_setGoalObject(Object *object);

	UnsignedByte m_unreconstructed_004[0x140 - 0x04];
	void *m_path;                                      // retail this+0x140
};

// The victim setter sits at its own recovered thunk, so it is reached through
// the view the ledger already pins for it.
class BfmeAIUpdateVictimThunk
{
public:
	void clearCurrentVictim(const Object *victim);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BFMEVirtualSlots<11>
{
public:
	virtual void bfmePreFireAt(Object *goal, ObjectID victimID) = 0;   // vtable +0x2C

	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Real getDistanceSquared(const Object *other) const;
	void setFiringConditionForCurrentWeapon() const;
	void setStatusBit(Int bit, Bool set);
	void preFireCurrentWeapon(const Object *victim, const Coord3D *position);
	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	Bool queryRva001CAEE0(const Player *player) const;

	ObjectID getID() const
	{
		return *(const ObjectID *)((const UnsignedByte *)this + 0x74);
	}

	UnsignedByte m_unreconstructed_004[0x38 - 0x04];
	Coord3D m_position;                                // retail Object+0x38
	UnsignedByte m_unreconstructed_044[0x90 - 0x44];
	UnsignedInt m_flags;                               // retail Object+0x90
	UnsignedInt m_status;                              // retail Object+0x94
	UnsignedByte m_unreconstructed_098[0xbc - 0x98];
	Real m_radius;                                     // retail Object+0xBC
	UnsignedByte m_unreconstructed_0c0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;                           // retail Object+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheBfmeGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine : public BFMEVirtualSlots<14>
{
public:
	virtual void bfmeNotifyVictim(Object *victim) = 0; // vtable +0x38

	Object *getGoalObject();

	UnsignedByte m_unreconstructed_004[0x10 - 0x04];
	Object *m_owner;                                   // retail this+0x10
};

extern UnsignedByte g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();

typedef void (__cdecl *Rva001766F0CritterDesyncLog)(void *, const char *);

static void rva001766F0_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((Rva001766F0CritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public BFMEVirtualSlots<17>
{
public:
	virtual Bool computePath();                        // vtable +0x44
	virtual StateReturnType update();

protected:
	UnsignedByte m_unreconstructed_004[0x1c - 0x04];
	StateMachine *m_machine;                           // retail this+0x1C
	UnsignedByte m_unreconstructed_020[0x68 - 0x20];
	ObjectID m_victimID;                               // retail this+0x68
	Bool m_isPreFiring;                                // retail this+0x6C
};

class Rva001766F0State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

StateReturnType Rva001766F0State::update()
{
	StateMachine *machine = m_machine;
	Object *source = machine->m_owner;
	AIUpdateInterface *ai = source->m_ai;
	Object *victim = TheBfmeGameLogic->findObjectByID(m_victimID);
	Object *previous = victim;
	if (!victim)
	{
		victim = machine->getGoalObject();
		if (!victim)
		{
			ai->notifyVictimIsDead();
			((BfmeAIUpdateVictimThunk *)ai)->clearCurrentVictim(victim);
			return STATE_FAILURE;
		}
		m_victimID = victim->getID();
	}

	Object *goal = m_machine->getGoalObject();
	Real radius;
	WeaponSlotType slot;
	Weapon *weapon = source->getCurrentWeapon(&slot);
	if (!weapon)
		return STATE_FAILURE;

	Bool goalIsAhead = false;
	if (goal && goal != previous)
	{
		const Coord3D *forward = ((Thing *)source)->getUnitDirectionVector2D();
		Real dx = goal->m_position.x - source->m_position.x;
		Real dy = goal->m_position.y - source->m_position.y;
		if (dy * forward->y + dx * forward->x > BfmeZeroRange)
			goalIsAhead = true;
	}

	if ((source->m_flags & BFME_OBJECT_FLAG_PRE_FIRING) && previous
		&& source->getDistanceSquared(previous) < source->m_radius + source->m_radius)
	{
		ai->destroyPath();
	}

	WeaponStatus status = weapon->getStatus();
	if (m_isPreFiring)
	{
		if (status != PRE_ATTACK)
		{
			if (status == READY_TO_FIRE)
			{
				if (goalIsAhead)
				{
					if (goal != previous)
					{
						radius = source->m_radius;
						if (radius * radius > source->getDistanceSquared(goal))
						{
							ai->friend_setGoalObject(victim);
							source->setFiringConditionForCurrentWeapon();
							source->bfmePreFireAt(goal, m_victimID);
						}
						else
						{
							m_isPreFiring = false;
						}
					}
					else
					{
						m_isPreFiring = false;
					}
				}
			}
			else if (status == BFME_WEAPON_STATUS_5)
			{
				m_isPreFiring = false;
			}
		}
	}
	else if (status == READY_TO_FIRE && goal != victim && goalIsAhead)
	{
		m_isPreFiring = true;
		source->setStatusBit(BFME_OBJECT_STATUS_BIT_PRE_FIRING, true);
		source->preFireCurrentWeapon(goal, 0);
	}

	source->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		BFME_OBJECT_STATUS_MASK_BIT), false);

	if (victim->m_status & BFME_OBJECT_STATUS_UNTARGETABLE)
		return STATE_FAILURE;

	if (victim->queryRva001CAEE0(((BfmeObjectCall *)source)->getControllingPlayer()))
		return STATE_FAILURE;

	AIUpdateInterface *sourceAI = source->m_ai;
	((BfmeAIUpdateVictimThunk *)sourceAI)->clearCurrentVictim(victim);

	if (!sourceAI->m_path
		&& ((BfmeOutOfWeaponRangeWeapon *)weapon)->isWithinAttackRange(
			(const BfmeOutOfWeaponRangeObject *)source,
			(const BfmeOutOfWeaponRangeObject *)victim, 0))
	{
		return STATE_SUCCESS;
	}

	rva001766F0_log("CritterDesync: ComputePath17");

	if (computePath() == false)
		return STATE_FAILURE;

	StateReturnType code = AIInternalMoveToState::update();
	if (code == STATE_CONTINUE)
		return STATE_CONTINUE;

	if (code == STATE_SUCCESS && previous)
	{
		m_machine->bfmeNotifyVictim(previous);
		sourceAI->friend_setGoalObject(previous);
	}

	return STATE_SUCCESS;
}
