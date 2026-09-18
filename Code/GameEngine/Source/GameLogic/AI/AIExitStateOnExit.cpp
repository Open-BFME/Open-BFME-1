// cl: /DNDEBUG /MD /EHsc
//
// AIExitState::onExit is a small BFME State leaf.  Keep the State/object
// layouts local to this TU: the checked retail body uses the BFME machine at
// this+0x1c and the entry id at this+0x24, while the broad AIStates.cpp model
// still carries the Zero Hour dual-base layout.

typedef int Int;

enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};

enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants); // vtable +0x34
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	unsigned char m_unreconstructed_00[0x1fc];
	ContainModuleInterface *m_contain; // retail this+0x1fc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id); // ILT thunk at 0x0001f253
};

extern GameLogic *TheGameLogic; // retail global [0x012f0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

private:
	virtual void unused00();
	void *m_stateMap[3];
	Object *m_owner; // retail this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	Object *getMachineOwner() { return m_machine->getOwner(); }

private:
	virtual void unused00();
	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine; // retail this+0x1c
	void *m_unreconstructed_tail; // keeps derived data at this+0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIExitState : public State
{
public:
	virtual void onExit(StateExitType status);

private:
	Int m_entryToClear; // retail this+0x24
};

// ?onExit@AIExitState@@UAEXW4StateExitType@@@Z
void AIExitState::onExit(StateExitType status)
{
	if (m_entryToClear != 0)
	{
		Object *goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
			{
				Object *obj = getMachineOwner();
				contain->onObjectWantsToEnterOrExit(obj, WANTS_NEITHER);
			}
		}
	}
}
