// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIDockState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?onExit@AIDockState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIDockState::onEnter — retail 0x0016CDB0 (183B).
// AIDockState::onExit  — retail 0x0016CEA0 (75B).
//
// The state's whole life cycle: onEnter builds the AIDockMachine that onExit
// halts and deletes, so both bodies need the same state layout (the machine
// pointer at +0x24), the same machine vtable and the same reach from the
// state's own StateMachine to the owning Object's AI. They sat in two files
// that each described all of it, and disagreed: one called the machine
// AIDockMachine with fifteen slots, the other DockMachine with sixteen.
//
// ZH onEnter: require a goal object with a dock interface, ignoreObstacle it,
// new AIDockMachine, setGoalObject, initDefaultState.
//
// onExit is constructor-owned vtable 0x00C97F08 slot 5. Slot 2 is the literal
// name getter for "AIDockState". halt is machine vslot +0x3C; deleteInstance
// is the scalar deleting dtor. setCanPathThroughUnits(false) is the byte at
// AIUpdateInterface+0x328; ignoreObstacle(NULL) is a tail call.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

class Object;
class DockUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obj);

	unsigned char m_pad[0x328];
	unsigned char m_canPathThroughUnits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	DockUpdateInterface *getDockUpdateInterface();

	unsigned char m_objectFields00[0x204];
	AIUpdateInterface *m_ai;
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
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(Object *obj);

	Object *getOwner() { return m_owner; }
	Object *getGoalObject();

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

// Slot 0 is the scalar deleting destructor onExit's `delete` goes through, and
// halt sits one slot past setGoalObject, at +0x3C.
class AIDockMachine
{
public:
	AIDockMachine(Object *owner);

	virtual ~AIDockMachine();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(Object *obj);
	virtual void halt();

	unsigned char m_machineFields04[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIDockState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);

	Object *getMachineOwner() { return m_machine->getOwner(); }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIDockMachine *m_dockMachine;
};

StateReturnType AIDockState::onEnter()
{
	Object *dockWithMe = getMachineGoalObject();
	if (dockWithMe == 0)
		return STATE_FAILURE;
	if (dockWithMe->getDockUpdateInterface() == 0)
		return STATE_FAILURE;

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
		ai->ignoreObstacle(dockWithMe);

	m_dockMachine = new AIDockMachine(getMachineOwner());
	m_dockMachine->setGoalObject(dockWithMe);
	return m_dockMachine->initDefaultState();
}

void AIDockState::onExit(StateExitType status)
{
	if (m_dockMachine)
	{
		m_dockMachine->halt();
		if (m_dockMachine)
			delete m_dockMachine;
		m_dockMachine = 0;
	}

	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (ai)
	{
		ai->m_canPathThroughUnits = 0;
		ai->ignoreObstacle(0);
	}
}
