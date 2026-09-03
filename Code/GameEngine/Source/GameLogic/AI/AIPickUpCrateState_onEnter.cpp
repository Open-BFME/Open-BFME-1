// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIPickUpCrateState::onEnter — retail 0x0016C0A0 (96B).
//
// Constructor-owned vtable 0x00C960D0 slot 4. Slot 2 is the literal name
// getter for "AIPickUpCrateState"; slot 6 is the already-matched update.
// BFME wraps setAdjustsDestination(true) in the CritterDesync logger.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad[0x38];
	Coord3D m_position;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIPickUpCrateState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }
	void setAdjustsDestination(bool value) { m_adjustDestinations = value ? 1 : 0; }

private:
	unsigned char m_pad[0x18];
	StateMachine *m_machine;
	unsigned char m_pad_020[4];
	Coord3D m_goalPosition;
	unsigned char m_pad_030[0x1C];
	unsigned char m_adjustDestinations;
	unsigned char m_pad_04d[3];
	int m_delayCounter;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

StateReturnType AIPickUpCrateState::onEnter()
{
	Object *goalObj = getMachineGoalObject();
	if (!goalObj)
		return STATE_FAILURE;

	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(
			g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 38");
	}

	setAdjustsDestination(true);
	m_goalPosition = *goalObj->getPosition();
	m_delayCounter = 3;
	return STATE_CONTINUE;
}
