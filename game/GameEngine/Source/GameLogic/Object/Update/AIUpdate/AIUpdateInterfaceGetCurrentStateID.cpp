// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x000C3D90, 20 bytes through the int3 run at +0x14: the Zero Hour
// inline AIUpdateInterface::getCurrentStateID, out of line in BFME and reached
// through ILT 0x0002FAEA from AIAttackApproachTargetState::updateInternal,
// which compares the result against state IDs.  The layout witness puts
// m_stateMachine at AIUpdateInterface+0x30 and m_currentState at
// StateMachine+0x1C; 999999 is ZH's INVALID_STATE_ID.

typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
enum { INVALID_STATE_ID = 999999 };

class State
{
public:
	StateID getID( void ) const { return m_ID; }
private:
	char m_unmodelled00[ 4 ];
	StateID m_ID;
};

class StateMachine
{
public:
	StateID getCurrentStateID( void ) const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
private:
	char m_unmodelled00[ 0x1C ];
	State *m_currentState;
};

class AIUpdateInterface
{
public:
	StateID getCurrentStateID( void ) const;
	StateMachine *getStateMachine( void ) const { return m_stateMachine; }
private:
	char m_unmodelled00[ 0x30 ];
	StateMachine *m_stateMachine;
};

StateID AIUpdateInterface::getCurrentStateID( void ) const
{
	return getStateMachine()->getCurrentStateID();
}
