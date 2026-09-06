// cl: /DNDEBUG /MD

typedef int Int;
typedef bool Bool;

enum StateReturnType
{
	STATE_FAILURE = 0,
	STATE_SUCCESS = 1
};

class StateMachine;
class GiantBirdState;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void unused014() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void unused020() = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void unused038() = 0;
	virtual void unused03c() = 0;
	virtual void unused040() = 0;
	virtual void unused044() = 0;
	virtual void unused048() = 0;
	virtual void unused04c() = 0;
	virtual void unused050() = 0;
	virtual void unused054() = 0;
	virtual void unused058() = 0;
	virtual void unused05c() = 0;
	virtual void unused060() = 0;
	virtual void unused064() = 0;
	virtual void unused068() = 0;
	virtual void unused06c() = 0;
	virtual void unused070() = 0;
	virtual void unused074() = 0;
	virtual void unused078() = 0;
	virtual void unused07c() = 0;
	virtual void unused080() = 0;
	virtual void unused084() = 0;
	virtual void unused088() = 0;
	virtual void unused08c() = 0;
	virtual void unused090() = 0;
	virtual void unused094() = 0;
	virtual void unused098() = 0;
	virtual void unused09c() = 0;
	virtual void unused0a0() = 0;
	virtual void unused0a4() = 0;
	virtual void unused0a8() = 0;
	virtual void unused0ac() = 0;
	virtual void unused0b0() = 0;
	virtual void unused0b4() = 0;
	virtual void unused0b8() = 0;
	virtual void unused0bc() = 0;
	virtual void unused0c0() = 0;
	virtual void unused0c4() = 0;
	virtual void unused0c8() = 0;
	virtual void unused0cc() = 0;
	virtual void unused0d0() = 0;
	virtual void unused0d4() = 0;
	virtual void unused0d8() = 0;
	virtual void unused0dc() = 0;
	virtual void unused0e0() = 0;
	virtual void unused0e4() = 0;
	virtual void unused0e8() = 0;
	virtual void unused0ec() = 0;
	virtual void unused0f0() = 0;
	virtual void unused0f4() = 0;
	virtual void unused0f8() = 0;
	virtual void unused0fc() = 0;
	virtual void unused100() = 0;
	virtual void unused104() = 0;
	virtual void unused108() = 0;
	virtual void unused10c() = 0;
	virtual void unused110() = 0;
	virtual void unused114() = 0;
	virtual void unused118() = 0;
	virtual void unused11c() = 0;
	virtual void unused120() = 0;
	virtual void unused124() = 0;
	virtual void unused128() = 0;
	virtual void unused12c() = 0;
	virtual void unused130() = 0;
	virtual void unused134() = 0;
	virtual void unused138() = 0;
	virtual void unused13c() = 0;
	virtual void unused140() = 0;
	virtual void unused144() = 0;
	virtual void unused148() = 0;
	virtual void unused14c() = 0;
	virtual void unused150() = 0;
	virtual void unused154() = 0;
	virtual void unused158() = 0;
	virtual void unused15c() = 0;
	virtual void unused160() = 0;
	virtual void unused164() = 0;
	virtual void unused168() = 0;
	virtual void unused16c() = 0;
	virtual void unused170() = 0;
	virtual void unused174() = 0;
	virtual void unused178() = 0;
	virtual void unused17c() = 0;
	virtual void unused180() = 0;
	virtual void unused184() = 0;
	virtual void unused188() = 0;
	virtual void unused18c() = 0;
	virtual void unused190() = 0;
	virtual void unused194() = 0;
	virtual void unused198() = 0;
	virtual void unused19c() = 0;
	virtual void unused1a0() = 0;
	virtual void unused1a4() = 0;
	virtual void unused1a8() = 0;
	virtual void unused1ac() = 0;
	virtual void unused1b0() = 0;
	virtual void unused1b4() = 0;
	virtual void unused1b8() = 0;
	virtual void unused1bc() = 0;
	virtual void unused1c0() = 0;
	virtual void unused1c4() = 0;
	virtual void unused1c8() = 0;
	virtual void unused1cc() = 0;
	virtual void unused1d0() = 0;
	virtual void unused1d4() = 0;
	virtual void unused1d8() = 0;
	virtual void unused1dc() = 0;
	virtual void unused1e0() = 0;
	virtual void unused1e4() = 0;
	virtual void setLocomotorGoalNone() = 0;
	virtual void unused1ec() = 0;
	virtual void unused1f0() = 0;
	virtual void unused1f4() = 0;
	virtual void unused1f8() = 0;
	virtual void unused1fc() = 0;
	virtual Int makeAttackMoveGoal() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed00[0x114];
	unsigned int m_conditionFlags114;
	unsigned int m_conditionFlags118;
	unsigned int m_conditionFlags11c;
	unsigned int m_conditionFlags120;
	unsigned char m_unreconstructed124[0xe0];
	AIUpdateInterface *m_aiUpdate;
};

class GiantBirdState
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual Bool isIdle() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Bool isInIdleState() const
	{
		return m_currentState ? m_currentState->isIdle() : true;
	}

	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void updateStateMachine() = 0;
	virtual void start() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void setState(Int id) = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void setGoalObject(Object *object) = 0;

	unsigned char m_unreconstructed04[0x0c];
	Object *m_owner;
	unsigned char m_unreconstructed14[0x08];
	GiantBirdState *m_currentState;
};

class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();

	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class GiantBirdAttackMoveToState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();

private:
	Int m_unreconstructed20;
	Int m_unreconstructed24;
	Int m_goalHandle;
	StateMachine *m_attackMachine;
	Int m_retryCount;
};

StateReturnType GiantBirdAttackMoveToState::onEnter()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_aiUpdate;
	m_attackMachine->start();
	m_attackMachine->setState(0);
	m_goalHandle = ai->makeAttackMoveGoal();
	m_retryCount = 5;
	return GiantBirdNormalFlightState::onEnter();
}

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	unsigned char m_unreconstructed00[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern void j_00003f58();
extern void j_00006ece();
extern void j_00012486();
extern void j_0002191d();
extern void j_000265a8();
extern void j_0003d609();

StateReturnType GiantBirdAttackMoveToState::update()
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->m_aiUpdate;
	Bool forceRetargetThisFrame = false;
	Bool shouldRepathThisFrame = false;

	if (!m_attackMachine->isInIdleState())
	{
		ai->setLocomotorGoalNone();
		if (owner->m_conditionFlags114 & 0x10000000)
		{
			owner->m_conditionFlags114 &= 0xEFFFFFFF;
			typedef void (Object::*NotifyCall)();
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			((Object *)owner->*notifyCast.asMember)();
		}
		if (owner->m_conditionFlags120 & 0x00040000)
		{
			owner->m_conditionFlags120 &= 0xFFFBFFFF;
			typedef void (Object::*NotifyCall)();
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			((Object *)owner->*notifyCast.asMember)();
		}
		m_attackMachine->updateStateMachine();
		if (!m_attackMachine)
			return STATE_FAILURE;
		if (!m_attackMachine->isInIdleState())
			return STATE_FAILURE;
		forceRetargetThisFrame = true;
		shouldRepathThisFrame = true;
		*(Int *)((char *)ai + 0x48) = m_goalHandle;
	}

	if (m_attackMachine->isInIdleState())
	{
		typedef Object *(AIUpdateInterface::*FindCrateCall)();
		union { void *asVoid; FindCrateCall asMember; } findCrateCast;
		findCrateCast.asVoid = (void *)j_000265a8;
		Object *crate = (ai->*findCrateCast.asMember)();
		if (crate)
		{
			m_attackMachine->setGoalObject(crate);
			m_attackMachine->setState(0x27);
			return STATE_FAILURE;
		}

		unsigned int frame = TheGameLogic->getFrame();
		typedef void (AIUpdateInterface::*SetMoodFrameCall)(unsigned int);
		union { void *asVoid; SetMoodFrameCall asMember; } setMoodFrameCast;
		setMoodFrameCast.asVoid = (void *)j_00006ece;
		(ai->*setMoodFrameCast.asMember)(frame);

		typedef Object *(AIUpdateInterface::*GetMoodTargetCall)(Bool, Bool);
		union { void *asVoid; GetMoodTargetCall asMember; } getMoodTargetCast;
		getMoodTargetCast.asVoid = (void *)j_00003f58;
		Object *target = (ai->*getMoodTargetCast.asMember)(!forceRetargetThisFrame, false);
		if (target)
		{
			typedef void (AIUpdateInterface::*EndMoveCall)();
			union { void *asVoid; EndMoveCall asMember; } endMoveCast;
			endMoveCast.asVoid = (void *)j_00012486;
			(ai->*endMoveCast.asMember)();
			m_attackMachine->setGoalObject(target);
			m_attackMachine->setState(0x0a);
			*(Int *)((char *)ai + 0x48) = 2;
			*((Bool *)((char *)ai + 0x335)) = true;
			return STATE_FAILURE;
		}
	}

	if (shouldRepathThisFrame)
		GiantBirdNormalFlightState::onEnter();

	typedef StateReturnType (GiantBirdNormalFlightState::*BaseUpdateCall)();
	union { void *asVoid; BaseUpdateCall asMember; } baseUpdateCast;
	baseUpdateCast.asVoid = (void *)j_0003d609;
	return (this->*baseUpdateCast.asMember)();
}
