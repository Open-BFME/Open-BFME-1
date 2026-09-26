// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of ?update@AIAttackFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// at retail RVA 0x00188CD0, 342 bytes.
//
// IDENTITY.  The body is slot 6 of the vtable at VA 0x0109B220, which the
// ledger pins as ??_7AIAttackFollowWaypointPathState@@6B@ from the exact
// constructor at 0x00183C90.  Slot 6 is update on every state vtable the
// ledger has resolved, among them AIAttackAreaState at 0x01098398 and
// AIAttackMeleeHordeWaitState at 0x01097B68.
//
// LAYOUT READ FROM THE BYTES.  The state keeps its machine at +0x1C, the
// group-offset flag at +0x69 and the attack-follow machine at +0x6C.  The
// machine keeps its owner at +0x10 and its current state at +0x1C, and the
// current state answers the idle question from vtable slot 7.  The owner keeps
// its model-condition words at +0x114 and +0x120 and its AI at +0x204, which is
// how game/GameEngine/Source/Common/S3ModelConditionFlagClears.cpp already
// spells the same inlined condition clear.
//
// CALLEES.  ILT 0x000265A8 reaches the matched
// ?checkForCrateToPickup@AIUpdateInterface@@QAEPAVObject@@XZ at 0x00272F70, ILT
// 0x00003F58 is the pinned getNextMoodTarget, ILT 0x0002191D is the matched
// Object::notifyModelConditionChanged at 0x001BE1C0, and ILT 0x0003A17A is the
// desync logger game/GameEngine/Source/Common/CRCParameterCheckLog.cpp defines.
// ILT 0x00019DC1 is the base class computeGoal.  ILT 0x00047EEC reaches the
// base class update at its 0x001888B0 entry, which is a different address from
// the ledger row that already carries the AIFollowWaypointPathState update name
// at 0x001888D9, so the entry is declared here under an address-derived name.
// Both are pinned in targets/game/reverse/symbols.csv.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class CRCParameterCheck;

extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

#define BFME_SLOT(n) virtual void slot##n() = 0;

class BfmeCurrentState
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014) BFME_SLOT(018)
	virtual Bool isIdle() const = 0;			// +0x1c
};

class BfmeStateMachine
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	virtual StateReturnType updateStateMachine() = 0;	// +0x10
	BFME_SLOT(014) BFME_SLOT(018) BFME_SLOT(01c)
	virtual StateReturnType setState(UnsignedInt state) = 0;	// +0x20
	BFME_SLOT(024) BFME_SLOT(028) BFME_SLOT(02c)
	BFME_SLOT(030) BFME_SLOT(034)
	virtual void setGoalObject(Object *object) = 0;		// +0x38

	unsigned char m_pad04[0x10 - 4];
	Object *m_owner;					// +0x10
	unsigned char m_pad14[0x1c - 0x14];
	BfmeCurrentState *m_currentState;			// +0x1c

	Bool isInIdleState() const
	{
		return m_currentState ? m_currentState->isIdle() : true;
	}
};

class AIUpdateInterface
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014) BFME_SLOT(018) BFME_SLOT(01c)
	BFME_SLOT(020) BFME_SLOT(024) BFME_SLOT(028) BFME_SLOT(02c)
	BFME_SLOT(030) BFME_SLOT(034) BFME_SLOT(038) BFME_SLOT(03c)
	BFME_SLOT(040) BFME_SLOT(044) BFME_SLOT(048) BFME_SLOT(04c)
	BFME_SLOT(050) BFME_SLOT(054) BFME_SLOT(058) BFME_SLOT(05c)
	BFME_SLOT(060) BFME_SLOT(064) BFME_SLOT(068) BFME_SLOT(06c)
	BFME_SLOT(070) BFME_SLOT(074) BFME_SLOT(078) BFME_SLOT(07c)
	BFME_SLOT(080) BFME_SLOT(084) BFME_SLOT(088) BFME_SLOT(08c)
	BFME_SLOT(090) BFME_SLOT(094) BFME_SLOT(098) BFME_SLOT(09c)
	BFME_SLOT(0a0) BFME_SLOT(0a4) BFME_SLOT(0a8) BFME_SLOT(0ac)
	BFME_SLOT(0b0) BFME_SLOT(0b4) BFME_SLOT(0b8) BFME_SLOT(0bc)
	BFME_SLOT(0c0) BFME_SLOT(0c4) BFME_SLOT(0c8) BFME_SLOT(0cc)
	BFME_SLOT(0d0) BFME_SLOT(0d4) BFME_SLOT(0d8) BFME_SLOT(0dc)
	BFME_SLOT(0e0) BFME_SLOT(0e4) BFME_SLOT(0e8) BFME_SLOT(0ec)
	BFME_SLOT(0f0) BFME_SLOT(0f4) BFME_SLOT(0f8) BFME_SLOT(0fc)
	BFME_SLOT(100) BFME_SLOT(104) BFME_SLOT(108) BFME_SLOT(10c)
	BFME_SLOT(110) BFME_SLOT(114) BFME_SLOT(118) BFME_SLOT(11c)
	BFME_SLOT(120) BFME_SLOT(124) BFME_SLOT(128) BFME_SLOT(12c)
	BFME_SLOT(130) BFME_SLOT(134) BFME_SLOT(138) BFME_SLOT(13c)
	BFME_SLOT(140) BFME_SLOT(144) BFME_SLOT(148) BFME_SLOT(14c)
	BFME_SLOT(150) BFME_SLOT(154) BFME_SLOT(158) BFME_SLOT(15c)
	BFME_SLOT(160) BFME_SLOT(164) BFME_SLOT(168) BFME_SLOT(16c)
	BFME_SLOT(170) BFME_SLOT(174) BFME_SLOT(178) BFME_SLOT(17c)
	BFME_SLOT(180) BFME_SLOT(184) BFME_SLOT(188) BFME_SLOT(18c)
	BFME_SLOT(190) BFME_SLOT(194) BFME_SLOT(198) BFME_SLOT(19c)
	BFME_SLOT(1a0) BFME_SLOT(1a4) BFME_SLOT(1a8) BFME_SLOT(1ac)
	BFME_SLOT(1b0) BFME_SLOT(1b4) BFME_SLOT(1b8) BFME_SLOT(1bc)
	BFME_SLOT(1c0) BFME_SLOT(1c4) BFME_SLOT(1c8) BFME_SLOT(1cc)
	BFME_SLOT(1d0) BFME_SLOT(1d4) BFME_SLOT(1d8) BFME_SLOT(1dc)
	BFME_SLOT(1e0) BFME_SLOT(1e4)
	virtual void setLocomotorGoalNone() = 0;		// +0x1e8

	Object *checkForCrateToPickup();			// ILT 0x000265A8
	Object *getNextMoodTarget(Bool calm, Bool alwaysAttack);	// ILT 0x00003F58

	unsigned char m_pad04[0x335 - 4];
	Bool m_bfmeFlag335;					// +0x335
};

class Object
{
public:
	void notifyModelConditionChanged();			// ILT 0x0002191D

	unsigned char m_pad00[0x114];
	UnsignedInt m_bfmeFlags114;				// +0x114
	unsigned char m_pad118[0x120 - 0x118];
	UnsignedInt m_bfmeFlags120;				// +0x120
	unsigned char m_pad124[0x204 - 0x124];
	AIUpdateInterface *m_ai;				// +0x204
};

class State
{
public:
	BFME_SLOT(000) BFME_SLOT(004) BFME_SLOT(008) BFME_SLOT(00c)
	BFME_SLOT(010) BFME_SLOT(014)
	virtual StateReturnType update() = 0;			// +0x18
	BFME_SLOT(01c) BFME_SLOT(020) BFME_SLOT(024) BFME_SLOT(028)
	BFME_SLOT(02c) BFME_SLOT(030) BFME_SLOT(034) BFME_SLOT(038)
	BFME_SLOT(03c) BFME_SLOT(040)
	virtual void computePath() = 0;				// +0x44

	unsigned char m_pad04[0x1c - 4];
	BfmeStateMachine *m_machine;				// +0x1c
};

class AIFollowWaypointPathState : public State
{
public:
	StateReturnType bfmeUpdate1888B0();			// ILT 0x00047EEC
	void computeGoal(Bool useGroupOffsets);			// ILT 0x00019DC1

	unsigned char m_pad20[0x69 - 0x20];
	Bool m_moveAsGroup;					// +0x69
};

class AIAttackFollowWaypointPathState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType update();

	BfmeStateMachine *m_attackFollowMachine;		// +0x6c
};

#undef BFME_SLOT

StateReturnType AIAttackFollowWaypointPathState::update()
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;

	Bool forceRetarget = false;
	Bool shouldRepath = false;

	if (!m_attackFollowMachine->isInIdleState())
	{
		ai->setLocomotorGoalNone();

		if (owner->m_bfmeFlags114 & 0x10000000)
		{
			owner->m_bfmeFlags114 &= ~0x10000000;
			owner->notifyModelConditionChanged();
		}

		if (owner->m_bfmeFlags120 & 0x00040000)
		{
			owner->m_bfmeFlags120 &= ~0x00040000;
			owner->notifyModelConditionChanged();
		}

		m_attackFollowMachine->updateStateMachine();

		if (m_attackFollowMachine == 0 || !m_attackFollowMachine->isInIdleState())
			return STATE_CONTINUE;

		forceRetarget = true;
		shouldRepath = true;
	}

	if (m_attackFollowMachine->isInIdleState())
	{
		Object *crate = ai->checkForCrateToPickup();
		if (crate != 0)
		{
			m_attackFollowMachine->setGoalObject(crate);
			m_attackFollowMachine->setState(0x27);
			return STATE_CONTINUE;
		}

		Object *victim = ai->getNextMoodTarget(!forceRetarget, false);
		if (victim != 0)
		{
			m_attackFollowMachine->setGoalObject(victim);
			m_attackFollowMachine->setState(0x0a);
			ai->m_bfmeFlag335 = true;
			return STATE_CONTINUE;
		}
	}

	if (shouldRepath)
	{
		computeGoal(m_moveAsGroup);

		if (Glo012F0239 && TheCRCParameterCheck != 0)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"CritterDesync: ComputePath38");

		computePath();
	}

	return AIFollowWaypointPathState::bfmeUpdate1888B0();
}
