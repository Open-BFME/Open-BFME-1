// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCurrentVictimPos@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// AIUpdateInterface::getCurrentVictimPos, retail 0x00279640.  BFME places
// the owning Object at +0x08, the state machine at +0x30, and the current
// victim ID at +0x40.  The object status word and goal position are likewise
// modeled at the retail offsets so this ABI slice retains the source behavior
// without changing the shared Zero Hour AIUpdate layout.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum
{
	INVALID_OBJECT_ID = 0,
	OBJECT_STATUS_IS_ATTACKING = 0x00400000
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unmodelled_00[ 0x90 ];
	unsigned int m_status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
private:
	unsigned char m_unmodelled_00[ 0x24 ];
	Coord3D m_goalPosition;

public:
	const Coord3D *getGoalPosition( void ) const
	{
		return &m_goalPosition;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
private:
	unsigned char m_unmodelled_00[ 0x08 ];
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x24 ];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[ 0x0C ];
	int m_currentVictimID;

public:
	const Coord3D *getCurrentVictimPos( void ) const;
};

// ?getCurrentVictimPos@AIUpdateInterface@@QBEPBUCoord3D@@XZ
const Coord3D *AIUpdateInterface::getCurrentVictimPos( void ) const
{
	if( m_object->m_status & OBJECT_STATUS_IS_ATTACKING )
	{
		if( m_currentVictimID == INVALID_OBJECT_ID )
			return m_stateMachine->getGoalPosition();
	}

	return 0;
}
