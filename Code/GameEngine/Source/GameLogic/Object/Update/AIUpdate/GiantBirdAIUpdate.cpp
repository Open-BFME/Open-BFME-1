// cl: /DNDEBUG /MD /EHsc
//
// GiantBirdNormalFlightState::onExit.  The BFME state clears its two
// flight-related model-condition bits before rebuilding the ground goal.

typedef int Int;
typedef unsigned int UnsignedInt;

enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

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
	void notifyModelConditionChanged();

	unsigned char m_unreconstructed_00[0x118];
	union
	{
		unsigned char m_conditionFlags118Byte;
		UnsignedInt m_conditionFlags118;
	};
	union
	{
		unsigned char m_conditionFlags11cByte;
		UnsignedInt m_conditionFlags11c;
	};
};

// BFME adds the source location to the retail updateGoal call.
class Pathfinder
{
public:
	void removeGoal(Object *obj);
	void updateGoal(Object *obj, const Coord3D *newGoalPos,
		PathfindLayerEnum layer, const char *file, Int line);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

private:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
};

// The BFME State keeps its machine pointer at +0x1c.
class State
{
public:
	virtual void unused00() = 0;
	Object *getMachineOwner() { return m_machine->getOwner(); }

private:
	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class GiantBirdNormalFlightState : public State
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@GiantBirdNormalFlightState@@UAEXW4StateExitType@@@Z
void GiantBirdNormalFlightState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	if (obj->m_conditionFlags11cByte & 0x40)
	{
		obj->m_conditionFlags11c &= ~0x40u;
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags118Byte & 0x80)
	{
		obj->m_conditionFlags118 &= ~0x80u;
		obj->notifyModelConditionChanged();
	}
	TheAI->pathfinder()->removeGoal(obj);
#line 381 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal(obj, (const Coord3D *)((const char *)obj + 0x38), LAYER_GROUND, __FILE__, __LINE__);
}
