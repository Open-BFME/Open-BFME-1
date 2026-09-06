// cl: /DNDEBUG /MD /EHsc
// readable body of ?getNextWaypoint@AIFollowWaypointPathState@@IAEPBVWaypoint@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?onExit@AIFollowWaypointPathExactState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// The two AIStates.cpp waypoint-path bodies. They used to sit one to a file,
// and the exact-path one reached everything it touched through raw casts on
// `this` because it had no model of the classes the other file already
// declared. Together they name the same three: a StateMachine whose owner is
// at +0x10, an Object whose AI is at +0x204, and the AIUpdateInterface that
// owns the current locomotor at +0x1CC.
//
// AIFollowWaypointPathState::getNextWaypoint  retail 0x0016C480 (75B). Named
//   callers: AIFollowWaypointPathState::update and AIPanicState::update. The
//   ALLOW_BACKTRACK shape: a random link in [0, 8), prior = current, and the
//   goal position set to the current waypoint's own location. Waypoint links
//   sit at +0x20, the link count at +0x4C and the location at +0x0C.
// AIFollowWaypointPathExactState::onExit      the exact-path exit: chain to the
//   base exit, then clear the AI's waypoint-exact byte at +0x328, drop the
//   completed waypoint, take the precise-Z bit off the current locomotor and
//   reset the waypoint index at +0x194 to -1.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

enum StateExitType { STATE_EXIT_UNKNOWN = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	int getNumLinks() const { return m_numLinks; }
	const Waypoint *getLink(int ndx) const
	{
		if (ndx < 0 || ndx >= 8)
			return 0;
		return m_links[ndx];
	}
	const Coord3D *getLocation() const { return &m_location; }

private:
	void *m_vptr;
	int m_id;
	void *m_name;
	Coord3D m_location;
	unsigned char m_pad_018[8];
	const Waypoint *m_links[8];
	unsigned char m_pad_040[0xC];
	int m_numLinks;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	void clearPreciseZPos()
	{
		*(UnsignedInt *)((UnsignedByte *)this + 0x40) &= ~0x8u;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setCompletedWaypoint(const Waypoint *waypoint);

	Locomotor *getCurLocomotor() const
	{
		return *(Locomotor **)((UnsignedByte *)this + 0x1CC);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((UnsignedByte *)this + 0x204);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);

	Object *getOwner() const
	{
		return *(Object **)((UnsignedByte *)this + 0x10);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIFollowWaypointPathState
{
protected:
	const Waypoint *getNextWaypoint();
	StateMachine *getMachine() { return m_machine; }

private:
	void *m_vptr;
	unsigned char m_pad[0x18];
	StateMachine *m_machine;
	unsigned char m_pad_020[0x40];
	const Waypoint *m_currentWaypoint;
	const Waypoint *m_priorWaypoint;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIFollowWaypointPathExactState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// ?getNextWaypoint@AIFollowWaypointPathState@@IAEPBVWaypoint@@XZ
const Waypoint *AIFollowWaypointPathState::getNextWaypoint()
{
	int linkCount = m_currentWaypoint->getNumLinks();
	int which = GetGameLogicRandomValue(
		0,
		linkCount - 1,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
		0x22A6);
	const Waypoint *nextWay = m_currentWaypoint->getLink(which);
	m_priorWaypoint = m_currentWaypoint;
	getMachine()->setGoalPosition(m_currentWaypoint->getLocation());
	return nextWay;
}

// ?onExit@AIFollowWaypointPathExactState@@UAEXW4StateExitType@@@Z
void AIFollowWaypointPathExactState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	StateMachine *machine =
		*(StateMachine **)((UnsignedByte *)this + 0x1C);
	AIUpdateInterface *ai = machine->getOwner()->getAI();
	if (ai)
	{
		*(UnsignedByte *)((UnsignedByte *)ai + 0x328) = 0;
		ai->setCompletedWaypoint(0);
		Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
			locomotor->clearPreciseZPos();
		*(UnsignedInt *)((UnsignedByte *)ai + 0x194) = 0xFFFFFFFF;
	}
}
