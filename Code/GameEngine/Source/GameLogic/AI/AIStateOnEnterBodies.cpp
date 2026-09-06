// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?onEnter@AIHuntState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?onEnter@AITunnelNetworkGuardState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?onEnter@AIGuardRetaliateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// The four AIStates.cpp state-entry overrides that read the owning machine and
// then build or seed a sub-machine. Each used to sit in its own file with its
// own copy of Object, StateMachine and AIUpdateInterface, and each copy was
// right about the one offset its body touched and silent -- or wrong -- about
// every other. Placed together they agree:
//
//   Object        m_position +0x38, m_id +0x74, kind flags +0x94, m_ai +0x204
//   StateMachine  m_owner +0x10, m_goalPosition +0x24, initDefaultState vslot
//                 +0x1C, setState +0x20, createHuntMachine +0x24
//   AIUpdate      m_stateMachine +0x30, getGuardLocation vslot +0x1A0,
//                 getGuardMode +0x1BC
//
// AIPickUpCrateState::onEnter  retail 0x0016C0A0 (96B), vtable 0x00C960D0 slot 4.
//   BFME wraps setAdjustsDestination(true) in the CritterDesync logger.
// AIHuntState::onEnter         retail 0x0016DCE0 (59B), vtable 0x00C98330 slot 4.
//   Creates the hunt sub-machine, then the ZH sleep spike
//   GetGameLogicRandomValue(0, ENEMY_SCAN_RATE) with ENEMY_SCAN_RATE == 15.
// AITunnelNetworkGuardState::onEnter  retail 0x0016DAC0 (201B).
//   new AITNGuardMachine, guard location into +0x44 and guard mode into +0x54,
//   initDefaultState, then setState(AI_TN_GUARD_RETURN).
// AIGuardRetaliateState::onEnter      retail 0x0017E1F0 (199B).
//   ZH's body plus BFME's kindFlags 0x20 melee-target resolve. The accessors
//   match the inlines in StateMachine.h / AIUpdate.h / AIGuardRetaliate.h, so
//   the goal-position copy stays `add`-based (src +0x24, dest +0x44) and the
//   second getMachineOwner reload can land in ecx.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	AI_TN_GUARD_RETURN = 0x138B
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class StateMachine;
class HuntSubMachine;

template <int N>
class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <>
class VirtualSlots<0>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);
	virtual HuntSubMachine *createHuntMachine();

	Object *getOwner() { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
	unsigned char m_machineFields14[0x10];
	Coord3D m_goalPosition;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public VirtualSlots<104>
{
public:
	virtual const Coord3D *getGuardLocation();
	virtual void pad_1a4();
	virtual void pad_1a8();
	virtual void pad_1ac();
	virtual void pad_1b0();
	virtual void pad_1b4();
	virtual void pad_1b8();
	virtual int getGuardMode();

	StateMachine *getStateMachine() { return m_stateMachine; }
	const StateMachine *getStateMachine() const { return m_stateMachine; }
	Object *getGoalObject() { return getStateMachine()->getGoalObject(); }
	const Coord3D *getGoalPosition() const { return getStateMachine()->getGoalPosition(); }

	unsigned char m_aiFields04[0x2c];
	StateMachine *m_stateMachine;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Object *bfmeResolveMeleeTarget(int index);
	AIUpdateInterface *getAI() { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	UnsignedInt getID() const { return m_id; }

	unsigned char m_objectFields00[0x38];
	Coord3D m_position;
	unsigned char m_objectFields44[0x30];
	UnsignedInt m_id;
	unsigned char m_objectFields78[0x1c];
	unsigned char m_kindFlags;
	unsigned char m_objectFields95[0x16f];
	AIUpdateInterface *m_ai;
};

#pragma comment(linker, "/alternatename:?bfmeResolveMeleeTarget@Object@@QAEPAV1@H@Z=?j_0000faa6@@YAXXZ")

// The sub-machine a hunt state runs; only its default-state entry is reached
// from here, at the same vslot StateMachine puts it.
class HuntSubMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
};

class AITNGuardMachine
{
public:
	AITNGuardMachine(Object *owner);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);

	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setGuardMode(int mode) { m_guardMode = mode; }

	unsigned char m_machineFields04[0x40];
	Coord3D m_positionToGuard;
	unsigned int m_nemesisToAttack;
	int m_guardMode;
};

class AIGuardRetaliateMachine
{
public:
	AIGuardRetaliateMachine(Object *owner);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();

	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setNemesisID(UnsignedInt id) { m_nemesisToAttack = id; }

	unsigned char m_machineFields04[0x40];
	Coord3D m_positionToGuard;
	unsigned int m_nemesisToAttack;
};

#pragma comment(linker, "/alternatename:??0AIGuardRetaliateMachine@@QAE@PAVObject@@@Z=?j_0003e8d3@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	char m_logicFields00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// The debug-report hook BFME wraps its state logging in: a global enable byte,
// a context pointer, and the report call reached through its ILT thunk.
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIPickUpCrateState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }
	void setAdjustsDestination(bool value) { m_adjustDestinations = value ? 1 : 0; }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	Coord3D m_goalPosition;
	unsigned char m_stateFields30[0x1C];
	unsigned char m_adjustDestinations;
	unsigned char m_stateFields4d[3];
	int m_delayCounter;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIHuntState
{
public:
	virtual StateReturnType onEnter();

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	int m_stateFields20;
	HuntSubMachine *m_huntMachine;
	UnsignedInt m_nextEnemyScanTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AITunnelNetworkGuardState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AITNGuardMachine *m_guardMachine;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIGuardRetaliateState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIGuardRetaliateMachine *m_guardRetaliateMachine;
};

// ?onEnter@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIPickUpCrateState::onEnter()
{
	Object *goalObj = getMachineGoalObject();
	if (!goalObj)
		return STATE_FAILURE;

	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(
			g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 38");
	}

	setAdjustsDestination(true);
	m_goalPosition = *goalObj->getPosition();
	m_delayCounter = 3;
	return STATE_CONTINUE;
}

// ?onEnter@AIHuntState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIHuntState::onEnter()
{
	m_huntMachine = m_machine->createHuntMachine();
	UnsignedInt sleepTime = GetGameLogicRandomValue(
		0,
		15,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
		0x3574);
	m_nextEnemyScanTime = TheGameLogic->getFrame() + sleepTime;
	return m_huntMachine->initDefaultState();
}

// ?onEnter@AITunnelNetworkGuardState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITunnelNetworkGuardState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardMachine = new AITNGuardMachine(getMachineOwner());
	m_guardMachine->setTargetPositionToGuard(ai->getGuardLocation());
	m_guardMachine->setGuardMode(ai->getGuardMode());

	if (m_guardMachine->initDefaultState() == STATE_FAILURE)
		return STATE_FAILURE;
	return m_guardMachine->setState(AI_TN_GUARD_RETURN);
}

// ?onEnter@AIGuardRetaliateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIGuardRetaliateState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardRetaliateMachine = new AIGuardRetaliateMachine(getMachineOwner());
	m_guardRetaliateMachine->setTargetPositionToGuard(ai->getGoalPosition());

	Object *goalObject = ai->getGoalObject();
	if (goalObject)
	{
		if ((goalObject->m_kindFlags & 0x20) != 0)
		{
			Object *resolved = goalObject->bfmeResolveMeleeTarget(0);
			if (resolved != 0)
				goalObject = goalObject->bfmeResolveMeleeTarget(0);
		}
		m_guardRetaliateMachine->setNemesisID(goalObject->getID());
	}

	return m_guardRetaliateMachine->initDefaultState();
}
