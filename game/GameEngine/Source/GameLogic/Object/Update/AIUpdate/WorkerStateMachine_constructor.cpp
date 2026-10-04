// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "../../../../../../../inputs/reference/shims/stringinline/StringInline.h"

class Object;
class State;

typedef unsigned int StateID;
typedef bool (*StateTransFuncPtr)(State *, void *);

struct StateConditionInfo
{
	StateTransFuncPtr test;
	StateID toStateID;
	void *userData;

	StateConditionInfo(StateTransFuncPtr t, StateID id, void *ud)
		: test(t), toStateID(id), userData(ud)
	{
	}
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase(void *machine, AsciiString name);
	virtual void stateAnchor();

private:
	unsigned char m_stateData[0x20];
};

class State;

class StateMachine
{
public:
	StateMachine(Object *owner, AsciiString name, bool flag);

protected:
	// retail declares the virtual destructor protected; that access level is
	// part of the mangled name the compiler-emitted cleanup path calls.
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions);
};

// Retail reaches the base constructor through the incremental-link thunk
// j_0000f123, but the call is emitted from a constructor initializer list, so
// the compiler must name StateMachine::StateMachine and there is no spelling
// of the base ctor call that names the thunk instead.  Kept deliberately.
#pragma comment(linker, "/alternatename:??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z=?j_0000f123@@YAXXZ")

// Retail calls defineState through the incremental-link thunk j_0003d1b3; the
// union in the constructor routes the member call straight to the thunk.
extern void j_0003d1b3();

// The state-condition callbacks are stored as function pointers whose retail
// addresses are the ILT thunks j_0000a27c and j_0002d998.
extern void j_0000a27c();
extern void j_0002d998();

class ActAsDozerState : public Rva000A19E0StateBase
{
public:
	ActAsDozerState(StateMachine *machine)
		: Rva000A19E0StateBase(machine, AsciiString("ActAsDozerState"))
	{
	}
};

class ActAsSupplyTruckState : public Rva000A19E0StateBase
{
public:
	ActAsSupplyTruckState(StateMachine *machine)
		: Rva000A19E0StateBase(machine, AsciiString("ActAsSupplyTruckState"))
	{
	}
};

class WorkerStateMachine : public StateMachine
{
public:
	WorkerStateMachine(Object *owner);
};

WorkerStateMachine::WorkerStateMachine(Object *owner)
	: StateMachine(owner, AsciiString("WorkerStateMachine"), false)
{
	typedef void (StateMachine::*Define)(StateID, State *, StateID, StateID,
		const StateConditionInfo *) const;
	union { void (*fn)(); Define call; } define = { j_0003d1b3 };

	static const StateConditionInfo asDozerConditions[] =
	{
		StateConditionInfo((StateTransFuncPtr)(void *)j_0000a27c, 1, 0),
		StateConditionInfo(0, 0, 0)
	};

	static const StateConditionInfo asTruckConditions[] =
	{
		StateConditionInfo((StateTransFuncPtr)(void *)j_0002d998, 0, 0),
		StateConditionInfo(0, 0, 0)
	};

	(this->*define.call)(0, (State *)new ActAsDozerState(this), 999999, 999999,
		asDozerConditions);
	(this->*define.call)(1, (State *)new ActAsSupplyTruckState(this), 999999, 999999,
		asTruckConditions);
}
