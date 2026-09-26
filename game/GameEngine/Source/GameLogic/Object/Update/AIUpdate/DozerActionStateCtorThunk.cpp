// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class Object;
typedef int StateReturnType;

enum DozerTask
{
	DOZER_TASK_DUMMY
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

private:
	unsigned char m_head[0x0c];
	Object *m_owner;
	unsigned char m_tail[0x30];

	public:
	virtual ~StateMachine();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual StateReturnType initDefaultState();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

	Object *getMachineOwner() { return m_machine->getOwner(); }

private:
	unsigned char m_head[0x18];
	StateMachine *m_machine;
	unsigned char m_tail[4];
};

class DozerActionStateMachine : public StateMachine
{
public:
	DozerActionStateMachine(Object *, DozerTask);

private:
	DozerTask m_task;
};

class DozerActionState : public State
{
public:
	DozerActionState(StateMachine *, DozerTask);

private:
	DozerTask m_task;
	DozerActionStateMachine *m_actionMachine;
};

// ??0DozerActionState@@QAE@PAVStateMachine@@W4DozerTask@@@Z
DozerActionState::DozerActionState(StateMachine *machine, DozerTask task) :
	State(machine, "DozerActionState"),
	m_task(task),
	m_actionMachine(new DozerActionStateMachine(getMachineOwner(), task))
{
	m_actionMachine->initDefaultState();
}
