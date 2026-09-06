// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;

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

	Object *getOwner() { return m_owner; }
	Object *getGoalObject();

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

class BackAwayAndCowerStateMachine
{
public:
	BackAwayAndCowerStateMachine(Object *owner, Object *goal, AsciiString name);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();

	unsigned char m_machineFields04[0x40];
};

class AIBackAwayAndCowerState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	BackAwayAndCowerStateMachine *m_backAwayMachine;
};

StateReturnType AIBackAwayAndCowerState::onEnter()
{
	if (m_backAwayMachine)
		return STATE_FAILURE;

	m_backAwayMachine = new BackAwayAndCowerStateMachine(
		getMachineOwner(), getMachineGoalObject(),
		AsciiString("BackAwayAndCowerStateMachine"));
	if (m_backAwayMachine == 0)
		return STATE_FAILURE;
	return m_backAwayMachine->initDefaultState();
}
