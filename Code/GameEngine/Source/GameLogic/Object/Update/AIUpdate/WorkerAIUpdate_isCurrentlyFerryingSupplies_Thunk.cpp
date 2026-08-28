// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?isCurrentlyFerryingSupplies@WorkerAIUpdate@@UBE_NXZ: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp
// Open-BFME5: WorkerAIUpdate::isCurrentlyFerryingSupplies, retail 0x002C7E30,
// zh_sweep packet 002c7e30. The Zero Hour body unchanged.
//
// This is the worker's own copy, not the supply truck's at 0x002C5740's class:
// it reaches the state machine at [this+0xE0] rather than [this+0x04] off the
// second base, and its jump table has five entries where the truck's has six.
// Five is Zero Hour's case count exactly, so whatever sixth state BFME gave the
// truck, the worker's switch does not mention it.
//
// The table's arms agree with the truck's on the five shared states: 0, 1 and 3
// fall to false and 2 and 4 to true, which is ST_IDLE / ST_BUSY / ST_REGROUPING
// against ST_WANTING / ST_DOCKING -- see
// SupplyTruckAIUpdate_updateAndPrivateDock_Thunk.cpp, where the same numbering
// was established.
//
// Retail tests the current state for NULL before reading its id, and that arm
// lands on the switch's default rather than on a value of its own, which is
// what getCurrentStateID's INVALID_STATE_ID does once MSVC folds the constant
// through: it is outside the case range.

enum { INVALID_STATE_ID = 999999 };

// The five Zero Hour supply-truck states, keeping their Zero Hour values.
enum SupplyTruckStateTypes
{
	ST_IDLE = 0,
	ST_BUSY = 1,
	ST_WANTING = 2,
	ST_REGROUPING = 3,
	ST_DOCKING = 4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	unsigned int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[4];
	unsigned int m_id;								///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned int getCurrentStateID( void ) const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }

private:
	unsigned char m_unreconstructed_00[0x1c];
	State *m_currentState;							///< retail this+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerAIUpdate
{
public:
	virtual bool isCurrentlyFerryingSupplies( void ) const;

private:
	unsigned char m_unreconstructed_04[0xE0 - 4];
	StateMachine *m_supplyTruckStateMachine;		///< retail this+0xE0
};

// ?isCurrentlyFerryingSupplies@WorkerAIUpdate@@UBE_NXZ
bool WorkerAIUpdate::isCurrentlyFerryingSupplies() const
{
	if (m_supplyTruckStateMachine)
	{
		switch (m_supplyTruckStateMachine->getCurrentStateID())
		{
			case ST_IDLE:
			case ST_BUSY:
			case ST_REGROUPING:
				return false;
			case ST_WANTING:
			case ST_DOCKING:
				return true;
		}
	}
	return false;
}
