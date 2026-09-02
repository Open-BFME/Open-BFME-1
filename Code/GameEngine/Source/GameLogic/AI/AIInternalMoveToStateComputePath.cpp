// cl: /DNDEBUG /MD
// Retail 0x001725B0: AIInternalMoveToState::computePath.  This is the BFME
// body corresponding to the Zero Hour implementation in AIStates.cpp; BFME
// records the AI interface's waiting-for-path byte after requesting the path.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AIUpdateInterface
{
public:
	void requestPath( Coord3D *goal, bool adjustsDestination );
	void friend_startingMove();

	char m_unknown[ 0x31E ];
	bool m_waitingForPath;
};

struct Object
{
	char m_unknown[ 0x204 ];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	char m_unknown[ 0x10 ];
	Object *m_owner;
};

class AIInternalMoveToState
{
protected:
	virtual bool computePath();
	bool getAdjustsDestination() const;

private:
	char m_state[ 0x18 ];
	StateMachine *m_machine;
	char m_gap20[ 4 ];
	Coord3D m_goalPosition;
	char m_gap30[ 0x1D ];
	bool m_waitingForPath;
};

bool AIInternalMoveToState::computePath()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	ai->requestPath( &m_goalPosition, getAdjustsDestination() );
	m_waitingForPath = ai->m_waitingForPath;
	ai->friend_startingMove();
	return true;
}
