// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail AIMoveAndTightenState::onEnter body to C++.

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

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void requestApproachPath(Coord3D *destination);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI(void) { return m_ai; }

private:
	unsigned char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_14[0x10];
	Coord3D m_goalPosition;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner(void) const { return m_machine->m_owner; }
	const Coord3D *getMachineGoalPosition(void) const { return &m_machine->m_goalPosition; }

	protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_20[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x1C];
	unsigned char m_adjustDestinations;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAndTightenState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	int m_okToRepathTimes;
	unsigned char m_checkForPath;
};

// These are the retail globals read by the debug guard and the pathfinder call.
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern AI *TheAI;

// Existing incremental-link thunks.  Their generated declarations are no-arg
// identities; the casts below supply the retail call signatures at each site.
extern void j_0003a17a(void);

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

// ?onEnter@AIMoveAndTightenState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndTightenState::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 7");
	}

	StateMachine *machine = m_machine;
	m_adjustDestinations = 0;
	Object *obj = machine->m_owner;
	AIUpdateInterface *ai = obj->getAI();
	m_okToRepathTimes = 1;
	m_checkForPath = 1;
	TheAI->pathfinder()->removeGoal(obj);
	m_goalPosition = *getMachineGoalPosition();
	ai->requestApproachPath(&m_goalPosition);
	return AIInternalMoveToState::onEnter();
}
