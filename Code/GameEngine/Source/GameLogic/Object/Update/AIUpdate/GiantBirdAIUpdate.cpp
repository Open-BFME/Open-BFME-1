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

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// The Giant Bird AI's goal-routing subobject is shared with the neighbouring
// GiantBird state bodies.  These members are the retail offsets used by the
// update body below; route() is the independently matched 0x002BCB60 body.
class Rva002BCB60Owner
{
public:
	void route( void *mode, Coord3D *position, Int source );

	unsigned char m_unreconstructed000[0x424];
	unsigned char m_continue424;
	unsigned char m_unreconstructed425[0x47];
	unsigned char m_pending46c;
	char m_unreconstructed46d[3];
	float m_goalRange470;
	char m_unreconstructed474[4];
	void *m_goalMode478;
	Coord3D m_goalPosition47c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged();

	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0xd4];
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
	unsigned char m_unreconstructed_120[0xe4];
	Rva002BCB60Owner *m_aiUpdate;
	unsigned char m_unreconstructed_208[0x13c];
	unsigned char m_flags344;
};

class Thing
{
public:
	void setPosition( const Coord3D *position );
};

// BFME adds the source location to the retail updateGoal call.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
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
// Retail deliberately converts the byte at +0x46c to float before comparing.
extern const float BfmeZeroRange;

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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
	virtual StateReturnType update();
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

// ?update@GiantBirdNormalFlightState@@UAE?AW4StateReturnType@@XZ
StateReturnType GiantBirdNormalFlightState::update()
{
	Object *object = getMachineOwner();
	if ((object->m_flags344 & 1) != 0)
		return STATE_FAILURE;

	Rva002BCB60Owner *ai = object->m_aiUpdate;
	if (ai == 0)
		return STATE_FAILURE;

	ai->route( ai->m_goalMode478, 0, 1 );
	if (ai->m_continue424 == 0)
		return STATE_FAILURE;

	float height = ai->m_goalRange470;
	Coord3D goal;
	goal.x = ai->m_goalPosition47c.x;
	goal.y = ai->m_goalPosition47c.y;
	goal.z = ai->m_goalPosition47c.z;
	float dx = object->m_position.x - goal.x;
	float dy = object->m_position.y - goal.y;
	float dz = object->m_position.z - goal.z;
	unsigned char withinGoalRange = (unsigned char)(dx * dx + dy * dy + dz * dz < height * height);
	int pending = ai->m_pending46c;

	if (pending != BfmeZeroRange || withinGoalRange)
	{
		((Thing *)object)->setPosition( &goal );
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
