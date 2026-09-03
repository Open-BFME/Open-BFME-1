// cl: /DNDEBUG /MD /EHsc
// readable body of ?onExit@AIDockState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIDockState::onExit — retail 0x0016CEA0 (75B).
//
// Constructor-owned vtable 0x00C97F08 slot 5. Slot 2 is the literal name
// getter for "AIDockState". halt is StateMachine vslot +0x3C; deleteInstance
// is the scalar deleting dtor. setCanPathThroughUnits(false) is the byte at
// AIUpdateInterface+0x328; ignoreObstacle(NULL) is a tail call.

enum StateExitType
{
	EXIT_NORMAL = 0
};

class Object;

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
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_pad[0x10];
	Object *m_owner;
};

class DockMachine
{
public:
	virtual ~DockMachine();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void halt();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIDockState
{
public:
	virtual void onExit(StateExitType status);

private:
	unsigned char m_pad[0x18];
	StateMachine *m_machine;
	int m_unused20;
	DockMachine *m_dockMachine;
};

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
