// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Open-BFME1: lift the retail AIMoveAndDeleteState::onEnter body to C++.
//
// The vendored ZH StateMachine.h disagrees with this build's real layout:
// retail's StateMachine has ~0x10 bytes of extra fields between
// m_goalPosition and m_locked that the header doesn't declare, and
// AIInternalMoveToState's own m_machine/m_goalPosition sit 4 bytes earlier
// than the header would place them. This isolated thunk holds a local
// replica sized from the retail disassembly instead of editing the shared
// header (which other rows compile against).

enum StateReturnType
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition(void) const { return (const Coord3D *)((const unsigned char *)this + 0x38); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject(void);
	const Coord3D *getGoalPosition(void) const { return &m_goalPosition; }
	void lock(const char *msg) { m_locked = 1; }

private:
	unsigned char m_unreconstructed_00[0x24];
	Coord3D m_goalPosition;                    // offset 0x24
	unsigned char m_unreconstructed_30[0x10];  // offset 0x30, size 0x10 -> up to 0x40
	unsigned char m_locked;                    // offset 0x40
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	StateMachine *getMachine(void) const { return m_machine; }
	void setAdjustsDestination(bool b) { m_adjustDestinations = b; }

protected:
	unsigned char m_unreconstructed_04[0x18];  // offset 0x4, size 0x18 -> up to 0x1C
	StateMachine *m_machine;                   // offset 0x1C
	unsigned char m_unreconstructed_20[4];     // offset 0x20, size 4 -> up to 0x24
	Coord3D m_goalPosition;                    // offset 0x24
	unsigned char m_unreconstructed_30[0x1C];  // offset 0x30, size 0x1C -> up to 0x4C
	unsigned char m_adjustDestinations;        // offset 0x4C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	unsigned char m_appendGoalPosition;        // offset 0x50
};

// The retail function actually starts 0x20 bytes before the packet's stated
// RVA -- the leading bytes are the same CritterDesync debug guard seen at
// several other onEnter() sites in this build (string table confirms
// "CritterDesync: setAdjustDestination(FALSE) 60" at retail 0x0017EF50).
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndDeleteState::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 60");
	}

	setAdjustsDestination(false);
	getMachine()->lock("AIMoveAndDeleteState::onEnter");
	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	m_appendGoalPosition = 1; // We may be moving off the map.
	return AIInternalMoveToState::onEnter();
}
