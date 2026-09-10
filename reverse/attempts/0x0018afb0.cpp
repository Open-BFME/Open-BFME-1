// ??0AITNGuardMachine@@QAE@PAVObject@@@Z
// partial score=0.96 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// The retail constructor is identified by AITunnelNetworkGuardState::onEnter
// at 0x0016DAC0, which calls its one-argument ILT at VA 0x0040715D.  The
// constructor installs the AITNGuardMachine vtable at 0x0109B4B0 and the
// complete retail body is RVA 0x0018AFB0..0x0018B2A1 (753 bytes).  These
// TU-local ABI views keep that proven identity separate from the generated
// naked thunk while retaining the real C++ state construction and call order.

class Object;
class State
{
};

struct StateConditionInfo;
typedef bool (*StateTransFuncPtr)(State *, void *);

class StateMachine
{
public:
	StateMachine(Object *owner, AsciiString name, bool flag);
	virtual ~StateMachine();

protected:
	void defineState(unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions);

private:
	char m_layout[0x40];
};

struct StateConditionInfo
{
	StateTransFuncPtr test;
	unsigned int toStateID;
	void *userData;

	StateConditionInfo(StateTransFuncPtr t, unsigned int id, void *ud)
		: test(t), toStateID(id), userData(ud) { }
};

// The retail condition is a function-local static in AITNGuard.cpp.  Its
// address is used by the condition table; the constructor's identity comes
// from the named caller/vtable evidence above, not from this local callback.
static bool hasAttackedMeAndICanReturnFire(State *, void *)
{
	return false;
}

class Rva000A19E0StateBase : public State
{
public:
	Rva000A19E0StateBase(void *machine, AsciiString name);
};

class Rva0014F280StateBase : public State
{
public:
	Rva0014F280StateBase(void *machine, AsciiString name);
};

extern int g_AITNGuardMachineVTable;
extern int g_AITNGuardReturnStateVTable;
extern int g_AITNGuardIdleStateVTable;
extern int g_AITNGuardInnerStateVTable;
extern int g_AITNGuardOuterStateVTable;
extern int g_AITNGuardPickUpCrateStateVTable;
extern int g_AITNGuardAttackAggressorStateVTable;

class AITNGuardReturnState : public Rva0014F280StateBase
{
public:
	AITNGuardReturnState(void *machine)
		: Rva0014F280StateBase(machine, AsciiString("AITNGuardReturnState"))
	{
		m_field50 = 0;
		m_vftable = &g_AITNGuardReturnStateVTable;
		m_field54 = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x4c];
	volatile unsigned int m_field50;
	volatile unsigned int m_field54;
};

class AITNGuardIdleState : public Rva000A19E0StateBase
{
public:
	AITNGuardIdleState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardIdleState"))
	{
		m_vftable = &g_AITNGuardIdleStateVTable;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x30];
};

class AITNGuardInnerState : public Rva000A19E0StateBase
{
public:
	AITNGuardInnerState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardInner"))
	{
		m_vftable = &g_AITNGuardInnerStateVTable;
		m_field24 = &g_AITNGuardInnerStateVTable;
		m_field28 = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	char m_tail[0x8];
};

class AITNGuardOuterState : public Rva000A19E0StateBase
{
public:
	AITNGuardOuterState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardOuter"))
	{
		m_vftable = &g_AITNGuardOuterStateVTable;
		m_field24 = &g_AITNGuardInnerStateVTable;
		m_field28 = 0;
		m_field2c = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	volatile unsigned int m_field2c;
};

class AITNGuardPickUpCrateState : public Rva0014F280StateBase
{
public:
	AITNGuardPickUpCrateState(void *machine)
		: Rva0014F280StateBase(machine, AsciiString("AIAttackPickUpCrateState"))
	{
		m_field50 = 0;
		m_vftable = &g_AITNGuardPickUpCrateStateVTable;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x4c];
	volatile unsigned int m_field50;
};

class AITNGuardAttackAggressorState : public Rva000A19E0StateBase
{
public:
	AITNGuardAttackAggressorState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardAttackAggressorState"))
	{
		m_vftable = &g_AITNGuardAttackAggressorStateVTable;
		m_field24 = &g_AITNGuardInnerStateVTable;
		m_field28 = 0;
		m_field2c = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	volatile unsigned int m_field2c;
};

__declspec(novtable) class AITNGuardMachine : public StateMachine
{
public:
	AITNGuardMachine(Object *owner);

private:
	volatile int m_positionToGuard[3];
	volatile unsigned int m_nemesisToAttack;
	volatile unsigned int m_guardMode;
};

// ??0AITNGuardMachine@@QAE@PAVObject@@@Z
AITNGuardMachine::AITNGuardMachine(Object *owner)
	: StateMachine(owner, AsciiString("AITNGuardMachine"), false)
{
	*reinterpret_cast<volatile int *volatile *>(this) = &g_AITNGuardMachineVTable;
	m_nemesisToAttack = 0;
	m_guardMode = 0;

	m_positionToGuard[0] = 0;
	m_positionToGuard[1] = 0;
	m_positionToGuard[2] = 0;

	static const StateConditionInfo attackAggressors[] =
	{
		StateConditionInfo(hasAttackedMeAndICanReturnFire, 0x138d, 0),
		StateConditionInfo(0, 0, 0)
	};

	defineState(0x138b, new AITNGuardReturnState(this), 0x1389, 0x1388,
		attackAggressors);
	defineState(0x1389, new AITNGuardIdleState(this), 0x1388, 0x138b, 0);
	defineState(0x1388, new AITNGuardInnerState(this), 0x138a, 0x138a,
		attackAggressors);
	defineState(0x138a, new AITNGuardOuterState(this), 0x138c, 0x138c, 0);
	defineState(0x138c, new AITNGuardPickUpCrateState(this), 0x138b, 0x138b, 0);
	defineState(0x138d, new AITNGuardAttackAggressorState(this), 0x138b,
		0x138b, 0);
}
