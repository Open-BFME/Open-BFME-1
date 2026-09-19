// cl: /O2
// readable body of ?supplyTruckSubMachineReadyToLeave@WorkerStateMachine@@SA_NPAVState@@PAX@Z: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp
// WorkerStateMachine::supplyTruckSubMachineReadyToLeave.  Zero Hour body:
// not wantsToEnter and isSupplyTruckBrainActiveAndBusy.  Layout matches
// WorkerStateMachineSupplyPredicate.cpp.

typedef bool Bool;
typedef int Int;

enum { INVALID_STATE_ID = 999999 };
enum { AS_SUPPLY_TRUCK = 1, ST_BUSY = 1 };

class BrainState
{
public:
	unsigned int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[4];
	unsigned int m_id;
};

class BrainStateMachine
{
public:
	unsigned int getCurrentStateID( void ) const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }

private:
	unsigned char m_unreconstructed_00[0x1c];
	BrainState *m_currentState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
struct Object
{
	char m_beforeAIUpdate[0x204];
	class WorkerAIUpdate *m_aiUpdate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
struct StateMachine
{
	char m_beforeOwner[0x10];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	char m_beforeMachine[0x1C];
	StateMachine *m_machine;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerAIUpdate
{
public:
	Int isSupplyTruckBrainActiveAndBusy();

private:
	unsigned char m_unreconstructed_00[0x41c];
	BrainStateMachine *m_workerMachine;
	BrainStateMachine *m_dozerMachine;
	BrainStateMachine *m_supplyTruckStateMachine;
};

Int WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy()
{
	return (m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK)
		&& (m_supplyTruckStateMachine->getCurrentStateID() == ST_BUSY);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerStateMachine
{
public:
	static Bool supplyTruckSubMachineWantsToEnter(State *thisState, void *userData);
	static Bool supplyTruckSubMachineReadyToLeave(State *thisState, void *userData);
};

Bool WorkerStateMachine::supplyTruckSubMachineReadyToLeave(State *thisState, void *)
{
	WorkerAIUpdate *update = thisState->m_machine->m_owner->m_aiUpdate;
	if (update == 0)
		return false;

	return !supplyTruckSubMachineWantsToEnter(thisState, 0)
		&& update->isSupplyTruckBrainActiveAndBusy();
}
