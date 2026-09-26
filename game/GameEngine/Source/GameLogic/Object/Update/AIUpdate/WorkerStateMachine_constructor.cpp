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
	virtual ~StateMachine();

protected:
	void defineState(StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions);
};

#pragma comment(linker, "/alternatename:??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z=?j_0000f123@@YAXXZ")
#pragma comment(linker, "/alternatename:?defineState@StateMachine@@IAEXIPAVState@@IIPBUStateConditionInfo@@@Z=?j_0003d1b3@@YAXXZ")

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

	static bool supplyTruckSubMachineWantsToEnter(State *, void *);
	static bool supplyTruckSubMachineReadyToLeave(State *, void *);
};

#pragma comment(linker, "/alternatename:?supplyTruckSubMachineWantsToEnter@WorkerStateMachine@@SA_NPAVState@@PAX@Z=?j_0000a27c@@YAXXZ")
#pragma comment(linker, "/alternatename:?supplyTruckSubMachineReadyToLeave@WorkerStateMachine@@SA_NPAVState@@PAX@Z=?j_0002d998@@YAXXZ")

WorkerStateMachine::WorkerStateMachine(Object *owner)
	: StateMachine(owner, AsciiString("WorkerStateMachine"), false)
{
	static const StateConditionInfo asDozerConditions[] =
	{
		StateConditionInfo(supplyTruckSubMachineWantsToEnter, 1, 0),
		StateConditionInfo(0, 0, 0)
	};

	static const StateConditionInfo asTruckConditions[] =
	{
		StateConditionInfo(supplyTruckSubMachineReadyToLeave, 0, 0),
		StateConditionInfo(0, 0, 0)
	};

	defineState(0, (State *)new ActAsDozerState(this), 999999, 999999,
		asDozerConditions);
	defineState(1, (State *)new ActAsSupplyTruckState(this), 999999, 999999,
		asTruckConditions);
}
