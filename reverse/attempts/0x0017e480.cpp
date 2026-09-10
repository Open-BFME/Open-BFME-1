// ?update@AIHuntState@@UAE?AW4StateReturnType@@XZ
// partial score=0.45 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// Retail AIHuntState::update at 0x0017E480 (800 bytes).  The BFME state
// machine stores goal IDs at +0x20 and resolves them through the game-logic
// singleton; this TU keeps that layout local to the body.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	BFME_AI_ATTACK_OBJECT = 10,
	BFME_AI_PICK_UP_CRATE = 0x27
};

class Object;
class Team;
class Player;
class ThingTemplate;
class AttackPriorityInfo;
class BfmeContain;
class BfmeAIUpdate;

// The retail State vtable's slot 7 is isIdle (+0x1c).  This is the state
// predicate reached by the observed current-state call at +0x34; its name is
// intentionally left as a slot because the concrete derived state is not
// proven by this body.
class BfmeCurrentState
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual Bool slot34() = 0;

	UnsignedInt m_id;
};

// StateMachine virtual slots proven by the retail calls in this body:
// setState at +0x20 and setGoalObject at +0x38.
class BfmeStateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual StateReturnType setState(UnsignedInt state) = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	unsigned char m_fields04[0x0c];
	Object *m_owner;
	unsigned char m_fields14[0x08];
	BfmeCurrentState *m_currentState;
	UnsignedInt m_goalObjectID;
	unsigned char m_fields24[0x1c];
	Bool m_locked;
};

class BfmeStateMachineUpdate
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual StateReturnType updateStateMachine() = 0;
};

// AIUpdateInterface::isGiantBird is the retail slot at +0x130.
template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class BfmeAIUpdate : public BfmeVirtualSlots<76>
{
public:
	virtual Bool isGiantBird() const = 0;

	unsigned char m_fields04[0x6c];
	const AttackPriorityInfo *m_attackInfo;
};

// The containment call is a virtual call at +0x68.  Its return type and the
// following object query are the only facts needed here.
class BfmeContain : public BfmeVirtualSlots<26>
{
public:
	virtual Object *slot26() = 0;
};

// The containment result's virtual call at +0x130 takes the hunt goal and
// returns a byte predicate.  Keep it as an ABI slot rather than assigning a
// semantic class name not established by the caller.
class BfmeContainedQuery : public BfmeVirtualSlots<76>
{
public:
	virtual Bool slot76(Object *goal) = 0;
};

class Overridable
{
public:
	virtual void slot00() = 0;
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class ThingTemplate : public Overridable
{
public:
	unsigned char m_fields08[0xd4 - 8];
	UnsignedInt m_flags;
};

class TeamPrototype
{
public:
	unsigned char m_fields00[0x1c2];
	Bool m_attackCommonTarget;
};

class Team
{
public:
	virtual void slot00() = 0;
	TeamPrototype *m_prototype;
};

class Player
{
public:
	virtual void slot00() = 0;
	unsigned char m_fields04[0x299];
	Bool m_unitsShouldHunt;
};

// Object offsets used by the retail body: template +0x04, status +0x90,
// containment module +0x1fc, AI update +0x204, team +0x23c.
class Object
{
public:
	virtual void slot00() = 0;
	ThingTemplate *m_template;
	unsigned char m_fields08[0x88];
	UnsignedInt m_status;
	UnsignedInt m_status1;
	unsigned char m_fields98[0x164];
	BfmeContain *m_contain;
	unsigned char m_fields200[4];
	BfmeAIUpdate *m_ai;
	unsigned char m_fields208[0x34];
	Team *m_team;
};

class GameLogic
{
public:
	unsigned char m_fields00[0x3c];
	UnsignedInt m_frame;
};

class AI;

extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;

extern void j_0000e570(void);
extern void j_000022bb(void);
extern void j_00002ef0(void);
extern void j_000084b8(void);
extern void j_0001450b(void);
extern void j_0001641e(void);
extern void j_00020824(void);
extern void j_000265a8(void);
extern void j_000296a9(void);
extern void j_0002a88d(void);
extern void j_0002dd2b(void);
extern void j_0003251f(void);
extern void j_000331c7(void);
extern void j_0003f990(void);

struct BfmeGetGoalCall
{
	Object *call();
};

static __forceinline Object *bfmeGetGoalObject(BfmeStateMachine *machine)
{
	typedef Object *(BfmeGetGoalCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000e570;
	return (reinterpret_cast<BfmeGetGoalCall *>(machine)->*fn.member)();
}

struct BfmeNoArgBoolCall
{
	Bool call();
};

static __forceinline Bool bfmeNoArgBool(void *object)
{
	typedef Bool (BfmeNoArgBoolCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000331c7;
	return (reinterpret_cast<BfmeNoArgBoolCall *>(object)->*fn.member)();
}

struct BfmeKindOfCall
{
	Bool call(UnsignedInt kind);
};

static __forceinline Bool bfmeIsKindOf(Object *object, UnsignedInt kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(UnsignedInt);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<BfmeKindOfCall *>(object)->*fn.member)(kind);
}

struct BfmeCrateCall
{
	Object *call();
};

static __forceinline Object *bfmeCheckForCrate(BfmeAIUpdate *ai)
{
	typedef Object *(BfmeCrateCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000265a8;
	return (reinterpret_cast<BfmeCrateCall *>(ai)->*fn.member)();
}

struct BfmeControllingPlayerCall
{
	Player *call();
};

static __forceinline Player *bfmeGetControllingPlayer(Object *object)
{
	typedef Player *(BfmeControllingPlayerCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020824;
	return (reinterpret_cast<BfmeControllingPlayerCall *>(object)->*fn.member)();
}

struct BfmeTeamTargetCall
{
	Object *call();
};

static __forceinline Object *bfmeGetTeamTarget(Team *team)
{
	typedef Object *(BfmeTeamTargetCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000296a9;
	return (reinterpret_cast<BfmeTeamTargetCall *>(team)->*fn.member)();
}

struct BfmeSetTeamTargetCall
{
	void call(const Object *object);
};

static __forceinline void bfmeSetTeamTarget(Team *team, Object *object)
{
	typedef void (BfmeSetTeamTargetCall::*Function)(const Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002a88d;
	(reinterpret_cast<BfmeSetTeamTargetCall *>(team)->*fn.member)(object);
}

struct BfmeTemplateCall
{
	ThingTemplate *call();
};

static __forceinline ThingTemplate *bfmeGetTemplate(Object *object)
{
	typedef ThingTemplate *(BfmeTemplateCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000084b8;
	return (reinterpret_cast<BfmeTemplateCall *>(object)->*fn.member)();
}

struct BfmePriorityCall
{
	Int call(const ThingTemplate *thingTemplate);
};

static __forceinline Int bfmeGetPriority(const AttackPriorityInfo *info,
	const ThingTemplate *thingTemplate)
{
	typedef Int (BfmePriorityCall::*Function)(const ThingTemplate *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001641e;
	return (reinterpret_cast<BfmePriorityCall *>(const_cast<AttackPriorityInfo *>(info))->*fn.member)(thingTemplate);
}

struct BfmeFindClosestCall
{
	Object *call(const Object *owner, float range, UnsignedInt qualifiers,
		const AttackPriorityInfo *info, void *filter);
};

static __forceinline Object *bfmeFindClosest(AI *ai, const Object *owner,
	float range, UnsignedInt qualifiers, const AttackPriorityInfo *info,
	void *filter)
{
	typedef Object *(BfmeFindClosestCall::*Function)(const Object *, float,
		UnsignedInt, const AttackPriorityInfo *, void *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003f990;
	return (reinterpret_cast<BfmeFindClosestCall *>(ai)->*fn.member)(
		owner, range, qualifiers, info, filter);
}

struct BfmeVoiceCall
{
	void call(Object *victim);
};

static __forceinline void bfmePlayAttackVoice(BfmeAIUpdate *ai, Object *victim)
{
	typedef void (BfmeVoiceCall::*Function)(Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00002ef0;
	(reinterpret_cast<BfmeVoiceCall *>(ai)->*fn.member)(victim);
}

struct BfmeIdleCall
{
	Bool call();
};

static __forceinline Bool bfmeIsIdle(BfmeStateMachine *machine)
{
	typedef Bool (BfmeIdleCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001450b;
	return (reinterpret_cast<BfmeIdleCall *>(machine)->*fn.member)();
}

class AIHuntState
{
public:
	virtual StateReturnType update();

	unsigned char m_fields04[0x18];
	BfmeStateMachine *m_machine;
	unsigned char m_fields20[4];
	BfmeStateMachine *m_huntMachine;
	UnsignedInt m_nextEnemyScanTime;
};

// ?update@AIHuntState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIHuntState::update()
{
	register Object *contained;
	register AIHuntState *self = this;
	if (self->m_machine->m_goalObjectID != 0
		&& self->m_huntMachine->m_goalObjectID
			!= self->m_machine->m_goalObjectID)
	{
		Object *goal = bfmeGetGoalObject(self->m_machine);
		if (goal == 0)
		{
			self->m_machine->setGoalObject(0);
		}
		else
		{
			self->m_huntMachine->setGoalObject(goal);
			BfmeCurrentState *current = self->m_huntMachine->m_currentState;
			if (current == 0 || current->m_id != 0)
			{
			}
			else
			{
				self->m_huntMachine->setState(BFME_AI_ATTACK_OBJECT);
			}
			self->m_nextEnemyScanTime = TheBfmeGameLogic->m_frame + 15;
		}
	}

	BfmeStateMachine *machine = self->m_machine;
	Object *owner = machine->m_owner;
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	Bool statusBit = (owner->m_status & 0x10000000) != 0;
	Object *teamVictim = bfmeGetGoalObject(self->m_huntMachine);

	ThingTemplate *ownerTemplate = owner->m_template;
	if (ownerTemplate != 0 && ownerTemplate->m_nextOverride != 0)
	{
		ownerTemplate = const_cast<ThingTemplate *>(reinterpret_cast<const ThingTemplate *>(
			ownerTemplate->m_nextOverride->getFinalOverride()));
	}
	if ((ownerTemplate->m_flags & 0x1000) != 0)
	{
		BfmeContain *contain = owner->m_contain;
		if (contain != 0)
		{
			contained = contain->slot26();
			if (contained != 0 && teamVictim != 0
				&& !bfmeIsKindOf(teamVictim, 7))
			{
				Bool query = ((BfmeContainedQuery *)contained)->slot76(teamVictim);
				if (query)
					goto update_state_machine;
			}
		}
	}

	if (statusBit)
		goto update_state_machine;
	if (now < self->m_nextEnemyScanTime)
		goto update_state_machine;

	if (bfmeNoArgBool(owner) && !bfmeIsKindOf(owner, 0x19))
		return STATE_FAILURE;

	BfmeAIUpdate *ai = owner->m_ai;
	Object *crate = bfmeCheckForCrate(ai);
	if (crate != 0)
	{
		self->m_huntMachine->setGoalObject(crate);
		self->m_huntMachine->setState(BFME_AI_PICK_UP_CRATE);
		return STATE_CONTINUE;
	}

	Bool scan = ai->isGiantBird();
	if (!scan)
	{
		BfmeCurrentState *current = self->m_huntMachine->m_currentState;
		if (current == 0 || current->slot34() || bfmeIsIdle(self->m_huntMachine))
			scan = true;
	}
	if (!scan)
	{
		self->m_nextEnemyScanTime = now + 15;
		goto update_state_machine;
	}

	const AttackPriorityInfo *info = ai->m_attackInfo;
	if (owner->m_team->m_prototype->m_attackCommonTarget)
		teamVictim = bfmeGetTeamTarget(owner->m_team);

	Object *victim = 0;
	if (teamVictim != 0 && info == 0)
	{
		victim = teamVictim;
	}
	else
	{
		victim = bfmeFindClosest(TheAI, owner, 9999.9f, 0x4a, info, 0);
		if (victim == 0)
		{
			Player *player = bfmeGetControllingPlayer(owner);
			if (player != 0 && bfmeGetControllingPlayer(owner)->m_unitsShouldHunt)
			{
				victim = bfmeFindClosest(TheAI, owner, 9999.9f, 0x4a, 0, 0);
			}
		}
		if (owner->m_team->m_prototype->m_attackCommonTarget)
		{
			if (teamVictim != 0 && info != 0)
			{
				if (victim == 0)
					victim = teamVictim;
				Int teamPriority = bfmeGetPriority(info, bfmeGetTemplate(teamVictim));
				Int victimPriority = victim != 0
					? bfmeGetPriority(info, bfmeGetTemplate(victim)) : 0;
				if (teamPriority >= victimPriority)
					victim = teamVictim;
			}
			bfmeSetTeamTarget(owner->m_team, victim);
		}
	}

	Object *oldGoal = bfmeGetGoalObject(self->m_huntMachine);
	if (oldGoal != victim)
	{
		self->m_huntMachine->setGoalObject(victim);
		if (oldGoal == 0)
			bfmePlayAttackVoice(ai, victim);
	}
	if (bfmeIsIdle(self->m_huntMachine) && victim != 0)
		self->m_huntMachine->setState(BFME_AI_ATTACK_OBJECT);

update_state_machine:
	self->m_machine->m_locked = true;
	StateReturnType result =
		((BfmeStateMachineUpdate *)self->m_huntMachine)->updateStateMachine();
	self->m_machine->m_locked = false;
	return result > STATE_CONTINUE ? STATE_CONTINUE : result;
}
