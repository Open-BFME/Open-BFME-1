// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIDockState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIDockState::onEnter — retail 0x0016CDB0 (183B).
//
// ZH onEnter: require a goal object with a dock interface, ignoreObstacle it,
// new AIDockMachine, setGoalObject, initDefaultState. Isolated sibling of
// AIDockState_onExit.cpp.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class DockUpdateInterface;

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obj);
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	DockUpdateInterface *getDockUpdateInterface();

	unsigned char m_objectFields00[0x204];
	AIUpdateInterface *m_ai;
};

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

class AIDockMachine
{
public:
	AIDockMachine(Object *owner);

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

	unsigned char m_machineFields04[0x44];
};

class AIDockState
{
public:
	virtual StateReturnType onEnter();

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
