// cl: /DNDEBUG /MD /EHs-c-
// WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy. Zero Hour body unchanged:
// both brains report id 1 (AS_SUPPLY_TRUCK and ST_BUSY). BFME machines sit at
// +0x41c and +0x424; getCurrentStateID is the inline at StateMachine.h.

enum { INVALID_STATE_ID = 999999 };

enum
{
	AS_DOZER = 0,
	AS_SUPPLY_TRUCK = 1
};

enum
{
	ST_IDLE = 0,
	ST_BUSY = 1
};

typedef int Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	unsigned int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[4];
	unsigned int m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned int getCurrentStateID( void ) const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }

private:
	unsigned char m_unreconstructed_00[0x1c];
	State *m_currentState;
};

// upstream layout: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp
// BFME places the three machine pointers at +0x41c, +0x420 and +0x424.
class WorkerAIUpdate
{
public:
	Bool isSupplyTruckBrainActiveAndBusy();

private:
	unsigned char m_unreconstructed_00[0x41c];
	StateMachine *m_workerMachine;
	StateMachine *m_dozerMachine;
	StateMachine *m_supplyTruckStateMachine;
};

// ?isSupplyTruckBrainActiveAndBusy@WorkerAIUpdate@@QAEHXZ
Bool WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy()
{
	return (m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK)
		&& (m_supplyTruckStateMachine->getCurrentStateID() == ST_BUSY);
}
