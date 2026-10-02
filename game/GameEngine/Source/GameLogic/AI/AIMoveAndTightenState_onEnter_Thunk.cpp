// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retain the matched AIInternalMoveToState getter body.

enum StateReturnType
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void requestApproachPath(Coord3D *destination);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI(void) { return m_ai; }

private:
	unsigned char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_14[0x10];
	Coord3D m_goalPosition;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner(void) const { return m_machine->m_owner; }
	const Coord3D *getMachineGoalPosition(void) const;

	protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_20[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x1C];
	unsigned char m_adjustDestinations;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAndTightenState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	int m_okToRepathTimes;
	unsigned char m_checkForPath;
};

const Coord3D *AIInternalMoveToState::getMachineGoalPosition(void) const
{
	return &m_machine->m_goalPosition;
}
