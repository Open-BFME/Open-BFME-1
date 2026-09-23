// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?friend_getWaypointGoalPathSize@AIUpdateInterface@@: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Open-BFME: AIUpdateInterface::friend_getWaypointGoalPathSize, 0x00271AE0, 77 bytes.
//
// The Zero Hour body unchanged: a path size only while the AI is following a
// path (AI_FOLLOW_PATH, 6), else 0. W3DWaypointBuffer::drawWaypoints reaches it
// through ILT 0x0000BD84.
//
// getAIStateType is out of line at 0x0026F8F0 (AIUpdate.cpp) and inlined here.
// BFME's getCurrentStateID checks the state at +0x58 first and falls back to the
// one at +0x1C. Written as an early return of the first id, it gives both the
// 44-byte standalone copy and this inlined copy. The if-reassign spelling
// AIUpdate.cpp uses also matches the standalone copy, but here it moves the
// machine pointer into EAX and the id into ECX.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
enum { INVALID_STATE_ID = 999999 };
typedef UnsignedInt StateID;

// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
enum AIStateType
{
	AI_FOLLOW_PATH = 6
};

class Rva00271AE0Named
{
public:
	virtual void bfmeAnchor(void);

	StateID getID(void) const { return m_id; }

	StateID m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
// BFME offsets; the goal path is 12-byte points (see 0x0016F770).
class AIStateMachine
{
public:
	StateID getCurrentStateID(void) const
	{
		StateID id = m_primary ? m_primary->getID() : (StateID)INVALID_STATE_ID;
		if (id != INVALID_STATE_ID)
			return id;
		return m_fallback ? m_fallback->getID() : (StateID)INVALID_STATE_ID;
	}

	Int getGoalPathSize(void) const { return m_goalPath.size(); }

private:
	char m_pad00[0x1c];
	Rva00271AE0Named *m_fallback;
	char m_pad20[0x44 - 0x20];
	std::vector<Coord3D> m_goalPath;
	char m_pad50[0x58 - 0x50];
	Rva00271AE0Named *m_primary;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	const AIStateMachine *getStateMachine(void) const { return m_stateMachine; }

	AIStateType getAIStateType(void) const
	{
		return (AIStateType)getStateMachine()->getCurrentStateID();
	}

	Int friend_getWaypointGoalPathSize(void) const;

private:
	char m_pad00[0x30];
	AIStateMachine *m_stateMachine;
};

Int AIUpdateInterface::friend_getWaypointGoalPathSize(void) const
{
	if (getAIStateType() != AI_FOLLOW_PATH)
		return 0;

	return getStateMachine()->getGoalPathSize();
}
