// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIMoveAndEvacuateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?update@AIMoveAndEvacuateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIMoveAndEvacuateState, both halves: onEnter locks the machine, records where
// the owner started and turns destination adjustment on; update (retail
// 0x00188520) runs the inherited move and, when it finishes, evacuates.
//
// They sat in two files that each described the same three objects only as far
// as its own body reached, and disagreed about the owner: the entry file read
// it straight out of the machine at +0x10 through a volatile slot, the update
// file through a getOwner() on a machine it modelled as ten bytes of padding.
// One layout here says both: the machine's owner at +0x10, its goal object id
// at +0x20, its goal position at +0x24 and its lock byte at +0x40; the state's
// own machine pointer at +0x1c, goal position at +0x24 and adjust-destination
// flag at +0x4c; and the Object's position at +0x38, AI module at +0x204, team
// at +0x23c and dead flags at +0x344.

typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

enum StateExitType
{
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiEvacuate(Bool exposeStealthUnits, CommandSourceType cmdSource);
};

class AIUpdateInterfacePrefix
{
	unsigned char m_unmodelled_000[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIUpdateInterfacePrefix, public AICommandInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
	unsigned char m_pad[0x31];

public:
	unsigned char m_b31; // +0x31
	unsigned char m_b32; // +0x32

	void setActive()
	{
		if (!m_b31)
		{
			m_b32 = 1;
			m_b31 = 1;
		}
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_unmodelled_044[0x204 - 0x44];
	AIUpdateInterface *m_ai; // +0x204
	unsigned char m_unmodelled_208[0x23c - 0x208];
	Team *m_team; // +0x23c
	unsigned char m_unmodelled_240[0x344 - 0x240];
	unsigned char m_deadFlags; // +0x344

public:
	const Coord3D *getPosition(void) const { return &m_position; }
	Bool isEffectivelyDead() const { return (m_deadFlags & 1) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }
};

// BFME's state-machine owner is at +0x10.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject(void);
	const Coord3D *getGoalPosition(void) const
	{
		return &m_goalPosition;
	}
	void lock(const char *)
	{
		m_locked = 1;
	}
	Object *getOwner() const { return m_owner; }
	// onEnter reads the owner across its lock() call and retail reloads it
	// there; a plain member read lets MSVC keep the pointer in the register it
	// already has, which costs the entry body its exact bytes. update() reads
	// it without the reload, so the volatile belongs to the access, not the
	// field.
	Object *getOwnerReloaded(void) const { return *(Object *const volatile *)&m_owner; }

	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_14[0x0c];
	int m_goalObjectId;
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x10];
	volatile unsigned char m_locked;
};

// BFME's State base has the machine pointer at +0x1c.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();

	StateMachine *getMachine(void) const
	{
		return m_machine;
	}
	void setAdjustsDestination(bool value)
	{
		m_adjustDestinations = value;
	}

protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }

	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_20[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x1c];
	unsigned char m_adjustDestinations;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();

private:
	Coord3D m_origin;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// ?onEnter@AIMoveAndEvacuateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndEvacuateState::onEnter()
{
	{
		Object *owner = getMachine()->getOwnerReloaded();
		getMachine()->lock("AIMoveAndEvacuateState::onEnter");
		m_origin = *owner->getPosition();
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 49");
	}

	setAdjustsDestination(true);
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	return AIInternalMoveToState::onEnter();
}

// ?update@AIMoveAndEvacuateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndEvacuateState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
	{
		return STATE_FAILURE;
	}

	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		if (obj->isEffectivelyDead())
		{
			return STATE_FAILURE;
		}

		AIUpdateInterface *ai = obj->getAI();
		ai->aiEvacuate(false, CMD_FROM_AI);
		obj->getTeam()->setActive();
	}

	return status;
}
