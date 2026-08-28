// cl: /DNDEBUG /MD /EHsc
// readable body of ?setGoalPosition@StateMachine@@: Code/GameEngine/Source/Common/StateMachine.cpp

// StateMachine::setGoalPosition, retail 0x000A0880. No calls: a lock flag at
// +0x40 and a null argument both fall straight to the return, and otherwise the
// three floats are copied into the member at +0x24. Retail folds the member
// offset into the destination register once rather than into each store, which
// is a struct assignment and not three field writes.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	void setGoalPosition( const Coord3D *pos );

private:
	unsigned char m_unmodelled_00[ 0x24 ];
	Coord3D m_goalPosition;					// +0x24
	unsigned char m_unmodelled_30[ 0x40 - 0x30 ];
	bool m_locked;							// +0x40
};

// ?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z
void StateMachine::setGoalPosition( const Coord3D *pos )
{
	if( m_locked )
		return;

	if( pos == 0 )
		return;

	m_goalPosition = *pos;
}
