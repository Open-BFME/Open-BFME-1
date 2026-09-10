// ?update@AIIdleState@@UAE?AW4StateReturnType@@XZ
// partial score=0.68 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
// BFME AIIdleState::update at retail RVA 0x00188090.
//
// The matched BFME AIFaceState::update tail-jumps through j_00003b39 when it
// returns to idle.  That thunk resolves to this body.  The first call below
// is the already matched AIIdleState::doInitIdleState body at 0x00172180;
// the sleep fields and the AI command subobject offsets are likewise taken
// from the retail body, not from the generated dump's anonymous name.

typedef unsigned char Bool;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateID
{
	AI_IDLE_MOVE = 0x28
};

enum WeaponSlotType
{
	WEAPON_SLOT_CURRENT = 0
};

enum KindOfType
{
	KINDOF_CAN_BE_REPULSED = 0x2D
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum MoodMatrixAction
{
	MM_ACTION_IDLE = 0
};

class StateMachine;
class Object;
class Weapon;
class WeaponTemplate;
class AIUpdateInterface;

class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual StateReturnType setState(StateID state) = 0;

	unsigned char m_padding004[0x0C];
	Object *m_owner;
	unsigned char m_padding014[0x2C];
	Bool m_locked;
};

class WeaponTemplate
{
public:
	Bool isLeechRangeWeapon() const;
};

class Weapon
{
public:
	WeaponTemplate *m_template;
	Bool isWithinFrameWindow() const;
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Bool isKindOf(KindOfType kind) const;
	Real getVisionRange() const;

	unsigned char m_padding000[0x94];
	unsigned char m_status;
	unsigned char m_padding095[3];
	UnsignedInt m_flags98;
	unsigned char m_padding09C[0x1A4 - 0x9C];
	UnsignedInt m_disabledFlags;
	unsigned char m_padding1A8[0x204 - 0x1A8];
	AIUpdateInterface *m_ai;
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AICommandInterface
{
public:
	void aiHunt(CommandSourceType source);
	void aiMoveToObject(Object *object, CommandSourceType source);
	void aiAttackObject(Object *object, int maxShots, CommandSourceType source);
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
	Object *checkForCrateToPickup();
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	Object *getNextMoodTarget(Bool includeCurrent, Bool includeFriends);

	unsigned char m_padding184[0x1FC - 0x184];
	UnsignedInt m_nextMoodCheckTime;
	unsigned char m_padding200[0x335 - 0x200];
	Bool m_attackStarted;
};

class AI
{
	public:
	Object *findClosestRepulsor(const Object *object, Real range);
};

class BfmeGameLogic
{
public:
	unsigned char m_padding000[0x3C];
	UnsignedInt m_frame;
};

class State
{
public:
	virtual StateReturnType update();

	unsigned char m_padding004[0x18];
	StateMachine *m_machine;
	};

class AIIdleState : public State
{
public:
	virtual StateReturnType update();

	unsigned char m_padding020[4];
	UnsignedShort m_initialSleepOffset;
	Bool m_shouldLookForTargets;
	Bool m_inited;
	int m_targetingType;
	Bool m_bfmeIdleState2C;
	void doInitIdleState();
};

extern void j_00003f58();
extern void j_00014b4b();
extern void j_0001a735();
extern void j_0001c882();
extern void j_000265a8();
extern void j_00028f74();
extern void j_0002b30f();
extern void j_0002bdb4();
extern void j_0002edcf();
extern void j_00031a7f();
extern void j_0003251f();
extern void j_0003fb1b();
extern void j_00041074();

#define TheAI (*(AI **)0x012EF214)
#define TheBfmeGameLogic (*(BfmeGameLogic **)0x012F0898)

typedef Weapon *(Object::*GetCurrentWeaponCall)(WeaponSlotType *);
typedef Bool (__fastcall *WeaponWindowCall)(Weapon *);
typedef void (__fastcall *DoInitIdleStateCall)(AIIdleState *);
typedef void (AICommandInterface::*AIHuntCall)(CommandSourceType);
typedef Bool (__fastcall *IsLeechRangeCall)(WeaponTemplate *);
typedef Bool (Object::*IsKindOfCall)(KindOfType) const;
typedef Real (__fastcall *GetVisionRangeCall)(Object *);
typedef Object *(AI::*FindClosestRepulsorCall)(const Object *, Real);
typedef Object *(__fastcall *CheckForCrateCall)(AIUpdateInterface *);
typedef void (AICommandInterface::*AIMoveToObjectCall)(Object *, CommandSourceType);
class AIUpdateCallTarget
{
};
typedef UnsignedInt (AIUpdateCallTarget::*GetMoodAdjustmentCall)(MoodMatrixAction) const;
typedef Object *(AIUpdateCallTarget::*GetNextMoodTargetCall)(Bool, Bool);
typedef void (AICommandInterface::*AIAttackObjectCall)(Object *, int, CommandSourceType);

StateReturnType AIIdleState::update()
{
	Object *ownerBefore = m_machine->m_owner;
	union
	{
		void *asVoid;
		GetCurrentWeaponCall asMember;
	} getWeaponCast;
	getWeaponCast.asVoid = (void *)j_00031a7f;
	Weapon *weapon =
		(ownerBefore->*getWeaponCast.asMember)((WeaponSlotType *)0);

	if (weapon && ((WeaponWindowCall)j_0003fb1b)(weapon))
		return STATE_CONTINUE;

	((DoInitIdleStateCall)j_0001a735)(this);

	UnsignedInt timeToSleep = 10 + m_initialSleepOffset;
	UnsignedInt oldSleepOffset = m_initialSleepOffset;
	m_initialSleepOffset = 0;

	if (m_shouldLookForTargets && !m_machine->m_locked)
	{
		Object *owner = m_machine->m_owner;
		AIUpdateInterface *ai = owner->m_ai;

		if ((owner->m_flags98 & 0x100) != 0)
		{
			AICommandInterface *commands =
				reinterpret_cast<AICommandInterface *>((char *)ai + 0x20);
			commands->aiHunt(CMD_FROM_AI);
			return STATE_CONTINUE;
		}

		if ((owner->m_status & 0x20) == 0 && weapon &&
			!((IsLeechRangeCall)j_00028f74)(weapon->m_template) &&
			owner->isKindOf(KINDOF_CAN_BE_REPULSED) &&
			ai->isIdle())
		{
			Object *enemy = TheAI->findClosestRepulsor(owner,
				((GetVisionRangeCall)j_00014b4b)(owner));
			if (enemy)
			{
				m_machine->setState(AI_IDLE_MOVE);
				return STATE_CONTINUE;
			}
		}

		Object *crate = ((CheckForCrateCall)j_000265a8)(ai);
		if (crate)
		{
			AICommandInterface *commands =
				reinterpret_cast<AICommandInterface *>((char *)ai + 0x20);
			commands->aiMoveToObject(crate, CMD_FROM_AI);
			return STATE_CONTINUE;
		}

		UnsignedInt disabled = owner->m_disabledFlags;
		if ((disabled & 0x14) == 0 && (disabled & 0x100) == 0 &&
			(ai->getMoodMatrixActionAdjustment(MM_ACTION_IDLE) & 0x10) == 0)
		{
			Object *enemy = ai->getNextMoodTarget(1, 1);
			if (enemy)
			{
				AICommandInterface *commands =
					reinterpret_cast<AICommandInterface *>((char *)ai + 0x20);
				commands->aiAttackObject(enemy, 0x7FFFFFFF, CMD_FROM_AI);
				ai->m_attackStarted = 1;
			}
		}

		UnsignedInt now = TheBfmeGameLogic->m_frame;
		UnsignedInt nextMoodCheckTime = ai->m_nextMoodCheckTime;
		if (nextMoodCheckTime > now)
		{
			UnsignedInt moodSleep = nextMoodCheckTime - now;
			if (moodSleep < timeToSleep)
			{
				timeToSleep = moodSleep;
				m_initialSleepOffset = (UnsignedShort)oldSleepOffset;
			}
		}
	}

	return (StateReturnType)timeToSleep;
}
