// ??0DozerPrimaryStateMachine@@QAE@PAVObject@@@Z
// partial score=0.4 date=2026-09-10
// Complete readable DozerPrimaryStateMachine constructor attempt used by
// DozerAIUpdate.cpp before the BFME ABI-focused reconstruction.
class Object;
class State;
class StateMachine;
struct StateConditionInfo;

class DozerPrimaryStateMachine {
public:
	DozerPrimaryStateMachine(Object *owner);
};

class DozerPrimaryIdleState {
public:
	DozerPrimaryIdleState(StateMachine *machine);
};

class DozerActionState {
public:
	DozerActionState(StateMachine *machine, int task);
};

class DozerPrimaryGoingHomeState {
public:
	DozerPrimaryGoingHomeState(StateMachine *machine);
};

extern bool DozerPrimaryStateMachine_isBuildMostImportant(State *, void *);
extern bool DozerPrimaryStateMachine_isRepairMostImportant(State *, void *);
extern bool DozerPrimaryStateMachine_isFortifyMostImportant(State *, void *);

// The complete source body from the readable DozerAIUpdate implementation.
DozerPrimaryStateMachine::DozerPrimaryStateMachine(Object *owner)
	: StateMachine(owner, "DozerPrimaryStateMachine")
{
	static const StateConditionInfo idleConditions[] = {
		StateConditionInfo(DozerPrimaryStateMachine_isBuildMostImportant, 2, 0),
		StateConditionInfo(DozerPrimaryStateMachine_isRepairMostImportant, 3, 0),
		StateConditionInfo(DozerPrimaryStateMachine_isFortifyMostImportant, 4, 0),
		StateConditionInfo(0, 0, 0)
	};

	defineState(0, new DozerPrimaryIdleState(this), 999999, 999999,
		idleConditions);
	defineState(1, new DozerActionState(this, 0), 0, 0, 0);
	defineState(2, new DozerActionState(this, 1), 0, 0, 0);
	defineState(3, new DozerActionState(this, 2), 0, 0, 0);
	defineState(4, new DozerPrimaryGoingHomeState(this), 0, 0, 0);
}
