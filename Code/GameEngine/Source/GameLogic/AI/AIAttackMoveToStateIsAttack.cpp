// cl: /DNDEBUG /MD /EHsc
//
// AIAttackMoveToState::isAttack -- BFME rewrote the Zero Hour body.
//
// ZH declares this inline in GameLogic/AIStateMachine.h as
//     return m_attackMoveMachine ? m_attackMoveMachine->isInAttackState() : FALSE;
// but retail BFME dereferences m_attackMoveMachine WITHOUT a null test and
// calls State vtable slot 7 (isIdle) rather than slot 8 (isAttack), inverting
// the result.  That is StateMachine::isInAttackState's sibling
// StateMachine::isInIdleState, which Common/StateMachine.h still carries.
//
// The vendored header defines isAttack inline, so this body cannot be written
// against it without editing a shared header.  The classes below are a
// TU-scoped ABI slice at the retail offsets only -- m_attackMoveMachine at
// this+0x58, StateMachine::m_currentState at +0x1C, State::isIdle at vtable
// slot 7 -- and declare nothing beyond what this one body touches.

class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	// Slots 0..3 are the MemoryPoolObject destructor and the three Snapshot
	// hooks; only their count matters here, so isIdle lands on slot 7.
	virtual ~State();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
	virtual int onEnter();
	virtual void onExit( int status );
	virtual int update();
	virtual bool isIdle() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	char m_slice[0x1C];
	State *m_currentState;

	bool isInIdleState() const { return m_currentState ? m_currentState->isIdle() : true; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackMoveToState
{
public:
	virtual bool isAttack() const;

	char m_slice[0x54];					// vptr occupies offset 0
	StateMachine *m_attackMoveMachine;	// this+0x58
};

bool AIAttackMoveToState::isAttack() const
{
	if (!m_attackMoveMachine->isInIdleState())
		return true;
	return false;
}
