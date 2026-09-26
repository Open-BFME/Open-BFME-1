// cl: /DNDEBUG /MD /EHsc
//
// AIFollowPathAsTeamState::isAttack, retail 0x0016C2B0.
//
// Identity is established by the dedicated vtable 0x01099C08 installed by
// the exact constructor at 0x00183990: retail slot 8 is the thunk to this
// body.  That constructor and the matched destructor both witness the owned
// attack-move machine at this+0x60.  The machine's current State is at +0x1c;
// BFME's State vtable puts isIdle at +0x1c, the same call used by the matched
// AIAttackMoveToState::isAttack sibling at 0x0016C410.

class Xfer;

class State
{
public:
	virtual ~State();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
	virtual int onEnter();
	virtual void onExit( int status );
	virtual int update();
	virtual bool isIdle() const;
};

class StateMachine
{
public:
	char m_slice[0x1C];
	State *m_currentState;

	bool isInIdleState() const { return m_currentState ? m_currentState->isIdle() : true; }
};

class AIFollowPathAsTeamState
{
public:
	virtual bool isAttack() const;

	char m_slice[0x5C];
	StateMachine *m_attackMoveMachine;
};

bool AIFollowPathAsTeamState::isAttack() const
{
	if (m_attackMoveMachine && !m_attackMoveMachine->isInIdleState())
		return true;
	return false;
}
