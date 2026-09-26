// cl: /DNDEBUG /MD /EHsc
//
// AIGiantBirdAttackState::update, retail RVA 0x002BEA50.  The constructor at
// 0x002BE400 installs vtable 0x010C78D8, whose update slot reaches this body
// through thunk 0x000036DE.  The state checks its owner and target, waits for
// a reloading weapon, then fires the current weapon at the target.

typedef int Int;

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

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1,
	BETWEEN_FIRING_SHOTS = 2,
	RELOADING_CLIP = 3,
	PRE_ATTACK = 4
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
};

class BfmeModelConditionFlags
{
public:
	enum Init
	{
		K_INIT = 0
	};

	BfmeModelConditionFlags(Init, unsigned int bit)
	{
		m_bits[4] = 1u << bit;
	}

	~BfmeModelConditionFlags()
	{
	}

	bool testForAny(const BfmeModelConditionFlags &that) const
	{
		return (m_bits[4] & that.m_bits[4]) != 0;
	}

	void setAny(const BfmeModelConditionFlags &that)
	{
		m_bits[4] |= that.m_bits[4];
	}

	unsigned int m_bits[5];
};

class AIUpdateInterface
{
public:
	unsigned char m_unreconstructed00[0x3f0];
	unsigned int m_flags3f0;
	unsigned int m_unreconstructed3f4;
	Int m_targetID3f8;
};

class Object
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void fireCurrentWeapon(Object *target, Int targetID) = 0;

	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void setFiringConditionForCurrentWeapon() const;
	void notifyModelConditionChanged();

	unsigned char m_unreconstructed04[0x70];
	Int m_id;
	unsigned char m_unreconstructed78[0x98];
	BfmeModelConditionFlags m_modelConditionFlags;
	unsigned char m_unreconstructed124[0xe0];
	AIUpdateInterface *m_ai;
	unsigned char m_unreconstructed208[0x13c];
	unsigned char m_privateStatus;
	unsigned char m_unreconstructed345[3];
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class StateMachine
{
public:
	unsigned char m_unreconstructed00[0x10];
	Object *m_owner;
};

class State
{
public:
	virtual void unused00() = 0;

	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class AIGiantBirdAttackState : public State
{
public:
	virtual StateReturnType update();
};

extern void j_0000978c();
extern void j_0001f253();
extern void j_0002191d();
extern void j_00023e0c();
extern void j_00031a7f();

typedef Object *(GameLogic::*FindObjectByIDCall)(Int id);
typedef Weapon *(Object::*GetCurrentWeaponCall)(WeaponSlotType *slot);
typedef WeaponStatus (Weapon::*GetStatusCall)() const;
typedef void (Object::*SetFiringConditionCall)() const;
typedef void (Object::*NotifyModelConditionChangedCall)();

StateReturnType AIGiantBirdAttackState::update()
{
	Object *object = m_machine->m_owner;
	unsigned char deadMask = 1;
	if ((object->m_privateStatus & deadMask) != 0)
		return STATE_FAILURE;

	AIUpdateInterface *ai = object->m_ai;
	if (ai == 0)
		return STATE_FAILURE;
	unsigned char aiFlag = (unsigned char)(ai->m_flags3f0 >> 3);
	if ((aiFlag & deadMask) == 0)
		return STATE_FAILURE;

	union
	{
		void *asVoid;
		FindObjectByIDCall asMember;
	} findObjectCast;
	findObjectCast.asVoid = (void *)j_0001f253;
	Object *target = (TheBfmeGameLogic->*findObjectCast.asMember)(ai->m_targetID3f8);
	if (target == 0 || (target->m_privateStatus & 1) != 0)
		goto stateSuccess;

	union
	{
		void *asVoid;
		GetCurrentWeaponCall asMember;
	} getCurrentWeaponCast;
	getCurrentWeaponCast.asVoid = (void *)j_00031a7f;
	Weapon *weapon = (object->*getCurrentWeaponCast.asMember)((WeaponSlotType *)0);
	if (weapon == 0)
		return STATE_FAILURE;

	union
	{
		void *asVoid;
		GetStatusCall asMember;
	} getStatusCast;
	getStatusCast.asVoid = (void *)j_0000978c;
	if ((weapon->*getStatusCast.asMember)() == READY_TO_FIRE)
	{
		union
		{
			void *asVoid;
			SetFiringConditionCall asMember;
		} setFiringConditionCast;
		setFiringConditionCast.asVoid = (void *)j_00023e0c;
		(object->*setFiringConditionCast.asMember)();
		object->fireCurrentWeapon(target, target->m_id);
		BfmeModelConditionFlags firingMask(BfmeModelConditionFlags::K_INIT, 17);
		if (!object->m_modelConditionFlags.testForAny(firingMask))
		{
			object->m_modelConditionFlags.setAny(firingMask);
			union
			{
				void *asVoid;
				NotifyModelConditionChangedCall asMember;
			} notifyModelConditionChangedCast;
			notifyModelConditionChangedCast.asVoid = (void *)j_0002191d;
			(object->*notifyModelConditionChangedCast.asMember)();
		}
		goto stateContinue;
	}
	if ((weapon->*getStatusCast.asMember)() == RELOADING_CLIP)
		goto stateSuccess;

stateContinue:
	return STATE_CONTINUE;
stateSuccess:
	return STATE_SUCCESS;
}
