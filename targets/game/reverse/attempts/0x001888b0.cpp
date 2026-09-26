// ?update@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.21 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME layout shim for the complete AIFollowWaypointPathState::update body.
// Retail starts at 0x001888B0 and ends at 0x00188BF2 inclusive (835 bytes).

#include <math.h>

typedef unsigned char Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum MoodMatrixAction
{
	MM_Action_Move = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum
{
	MAA_Action_To_AttackMove = 4,
	NO_MAX_SHOTS_LIMIT = 0x7fffffff
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	__forceinline Real length() const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

struct Coord2D
{
	Real x;
	Real y;
};

class Object;
class StateMachine;
class Team;
class Player;
class AIGroup;
class AIData;
class AI;
class Pathfinder;
class Path;
class LocomotorSet;
class Waypoint;

extern void j_0000314d();
extern void j_00009c2d();
extern void j_0000ab1e();
extern void j_00010109();
extern void j_00011b26();
extern void j_0001246d();
extern void j_00015460();
extern void j_00019dc1();
extern void j_00020824();
extern void j_00022ec1();
extern void j_00027ffc();
extern void j_000294e2();
extern void j_0002b30f();
extern void j_0002c61a();
extern void j_0002c73c();
extern void j_0002d24f();
extern void j_0003a17a();
extern void j_0003b570();
extern void j_00043833();

class Waypoint
{
public:
	const Coord3D *getLocation() const
	{
		return (const Coord3D *)((const UnsignedByte *)this + 0x0c);
	}

	UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const UnsignedByte *)this + 4);
	}
};

class StateMachine
{
public:
	Object *getOwner() const
	{
		return *(Object **)((const UnsignedByte *)this + 0x10);
	}

	void setGoalPosition(const Coord3D *position)
	{
		typedef void (StateMachine::*SetGoalPositionCall)(const Coord3D *);
		union { void *asVoid; SetGoalPositionCall asMember; } cast;
		cast.asVoid = (void *)j_0000314d;
		(this->*cast.asMember)(position);
	}
};

class AICommandInterface
{
public:
	void aiAttackFollowWaypointPathAsTeam(const Waypoint *waypoint, Int shots,
		CommandSourceType source)
	{
		typedef void (AICommandInterface::*Call)(const Waypoint *, Int,
			CommandSourceType);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0002c73c;
		(this->*cast.asMember)(waypoint, shots, source);
	}

	void aiAttackFollowWaypointPath(const Waypoint *waypoint, Int shots,
		CommandSourceType source)
	{
		typedef void (AICommandInterface::*Call)(const Waypoint *, Int,
			CommandSourceType);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00011b26;
		(this->*cast.asMember)(waypoint, shots, source);
	}
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;

	AICommandInterface *getCommandInterface() const
	{
		return (AICommandInterface *)((UnsignedByte *)this + 0x20);
	}

	void aiAttackFollowWaypointPathAsTeam(const Waypoint *waypoint, Int shots,
		CommandSourceType source)
	{
		typedef void (AICommandInterface::*Call)(const Waypoint *, Int,
			CommandSourceType);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0002c73c;
		AICommandInterface *command =
			(AICommandInterface *)((UnsignedByte *)this + 0x20);
		(command->*cast.asMember)(waypoint, shots, source);
	}

	void aiAttackFollowWaypointPath(const Waypoint *waypoint, Int shots,
		CommandSourceType source)
	{
		typedef void (AICommandInterface::*Call)(const Waypoint *, Int,
			CommandSourceType);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00011b26;
		AICommandInterface *command =
			(AICommandInterface *)((UnsignedByte *)this + 0x20);
		(command->*cast.asMember)(waypoint, shots, source);
	}

	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const
	{
		typedef UnsignedInt (AIUpdateInterface::*Call)(MoodMatrixAction) const;
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0002b30f;
		return (this->*cast.asMember)(action);
	}

	Path *getPath() const
	{
		return *(Path **)((const UnsignedByte *)this + 0x140);
	}

	Bool isWaitingForPath() const
	{
		return *(const Bool *)((const UnsignedByte *)this + 0x31e);
	}

	const LocomotorSet &getLocomotorSet() const
	{
		return *(const LocomotorSet *)((const UnsignedByte *)this + 0x1a8);
	}

	void friend_startingMove()
	{
		typedef void (AIUpdateInterface::*Call)();
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0001246d;
		(this->*cast.asMember)();
	}

	void setPriorWaypointID(UnsignedInt id)
	{
		*(UnsignedInt *)((UnsignedByte *)this + 0x28) = id;
	}

	void setCurrentWaypointID(UnsignedInt id)
	{
		*(UnsignedInt *)((UnsignedByte *)this + 0x2c) = id;
	}

	void setCompletedWaypoint(const Waypoint *waypoint)
	{
		typedef void (AIUpdateInterface::*Call)(const Waypoint *);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0002d24f;
		(this->*cast.asMember)(waypoint);
	}
};

class Team
{
public:
	const Waypoint *getCurrentWaypoint() const
	{
		return *(const Waypoint * const *)((const UnsignedByte *)this + 0x40);
	}

	void setCurrentWaypoint(const Waypoint *waypoint)
	{
		*(const Waypoint **)((UnsignedByte *)this + 0x40) = waypoint;
	}

	void getTeamAsAIGroup(AIGroup *group)
	{
		typedef void (Team::*Call)(AIGroup *);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00022ec1;
		(this->*cast.asMember)(group);
	}
};

class Player
{
public:
	Bool isSkirmishAIPlayer() const
	{
		typedef Bool (Player::*Call)() const;
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00015460;
		return (this->*cast.asMember)();
	}
};

class Object
{
public:
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((const UnsignedByte *)this + 0x204);
	}

	Team *getTeam() const
	{
		return *(Team **)((const UnsignedByte *)this + 0x23c);
	}

	Player *getControllingPlayer() const
	{
		typedef Player *(Object::*Call)() const;
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00020824;
		return (this->*cast.asMember)();
	}
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *object, const LocomotorSet &locomotorSet,
		Coord3D *destination, const Coord3D *groupDestination = 0)
	{
		typedef Bool (Pathfinder::*Call)(Object *, const LocomotorSet &,
			Coord3D *, const Coord3D *);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00027ffc;
		return (this->*cast.asMember)(object, locomotorSet, destination,
			groupDestination);
	}

	void updateGoal(Object *object, const Coord3D *destination,
		PathfindLayerEnum layer, const char *file, Int line)
	{
		typedef void (Pathfinder::*Call)(Object *, const Coord3D *,
			PathfindLayerEnum, const char *, Int);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_000294e2;
		(this->*cast.asMember)(object, destination, layer, file, line);
	}
};

class Path
{
public:
	void appendNode(const Coord3D *position, PathfindLayerEnum layer)
	{
		typedef void (Path::*Call)(const Coord3D *, PathfindLayerEnum);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00043833;
		(this->*cast.asMember)(position, layer);
	}
};

class AIData
{
public:
	Real getSkirmishGroupFudgeValue() const
	{
		return *(const Real *)((const UnsignedByte *)this + 0x58);
	}
};

class AIGroup
{
public:
	Bool getCenter(Coord3D *position)
	{
		typedef Bool (AIGroup::*Call)(Coord3D *);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00009c2d;
		return (this->*cast.asMember)(position);
	}

	Int getCount()
	{
		typedef Int (AIGroup::*Call)();
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0002c61a;
		return (this->*cast.asMember)();
	}
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return *(Pathfinder **)((const UnsignedByte *)this + 0x0c);
	}

	AIGroup *createGroup()
	{
		typedef AIGroup *(AI::*Call)();
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0003b570;
		return (this->*cast.asMember)();
	}

	AIData *getAiData() const
	{
		return *(AIData * const *)((const UnsignedByte *)this + 0x14);
	}
};

class AIInternalMoveToState
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual StateReturnType update();
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Bool computePath() = 0;

	StateMachine *getMachine() const
	{
		return m_machine;
	}

	Object *getMachineOwner() const
	{
		return m_machine->getOwner();
	}

	Bool getAdjustsDestination() const
	{
		typedef Bool (AIInternalMoveToState::*Call)() const;
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00010109;
		return (this->*cast.asMember)();
	}

protected:
	unsigned char m_prefix[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	PathfindLayerEnum m_goalLayer;
	unsigned char m_pad34[0x1c];
};

class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

protected:
	Coord2D m_groupOffset;
	Real m_angle;
	Int m_framesSleeping;
	const Waypoint *m_currentWaypoint;
	const Waypoint *m_priorWaypoint;
	Bool m_appendGoalPosition;
	Bool m_isFollowWaypointPathState;
	Bool m_moveAsGroup;

	void computeGoal(Bool useGroupOffsets)
	{
		typedef void (AIFollowWaypointPathState::*Call)(Bool);
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_00019dc1;
		(this->*cast.asMember)(useGroupOffsets);
	}

	const Waypoint *getNextWaypoint()
	{
		typedef const Waypoint *(AIFollowWaypointPathState::*Call)();
		union { void *asVoid; Call asMember; } cast;
		cast.asVoid = (void *)j_0000ab1e;
		return (this->*cast.asMember)();
	}
};

#define TheAI (*(AI **)0x012EF214)
#define CritterDesyncFlag (*(volatile UnsignedByte *)0x012F0239)
#define CritterDesyncSink (*(void **)0x012ED4FC)
#define BfmeAiStatesFile ((const char *)0x0109769C)

typedef void (__cdecl *DebugLogFunction)(void *, const char *, ...);

StateReturnType AIFollowWaypointPathState::update()
{
	if (m_framesSleeping > 0) {
		m_framesSleeping--;
		return STATE_CONTINUE;
	}
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	getMachine()->setGoalPosition(m_currentWaypoint->getLocation());

	UnsignedInt adjustment = ai->getMoodMatrixActionAdjustment(MM_Action_Move);
	if (m_isFollowWaypointPathState && (adjustment & MAA_Action_To_AttackMove)) {
		if (m_moveAsGroup) {
			ai->aiAttackFollowWaypointPathAsTeam(
				m_currentWaypoint, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
		} else {
			ai->aiAttackFollowWaypointPath(
				m_currentWaypoint, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);
		}
	}

	if (m_appendGoalPosition) {
		Path *thePath = ai->getPath();
		if (!ai->isWaitingForPath() && ai->getPath()) {
			thePath->appendNode(&m_goalPosition, LAYER_GROUND);
			m_appendGoalPosition = false;
		}
	}
	if (m_moveAsGroup && m_currentWaypoint != obj->getTeam()->getCurrentWaypoint()) {
		m_priorWaypoint = m_currentWaypoint;
		m_currentWaypoint = obj->getTeam()->getCurrentWaypoint();
		if (m_currentWaypoint == 0) {
			return STATE_SUCCESS;
		}
		computeGoal(false);
		if (getAdjustsDestination() && ai->isDoingGroundMovement()) {
			if (!TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(),
				&m_goalPosition)) {
				if (CritterDesyncFlag && CritterDesyncSink)
					((DebugLogFunction)j_0003a17a)(CritterDesyncSink,
						"CritterDesync: ComputePath36");
				return STATE_FAILURE;
			}
		}
		ai->friend_startingMove();
		computePath();
		if (getAdjustsDestination()) {
			TheAI->pathfinder()->updateGoal(obj, &m_goalPosition, m_goalLayer,
				BfmeAiStatesFile, 0x2405);
		}
	}

	StateReturnType status = AIInternalMoveToState::update();

	if (m_moveAsGroup) {
		if (obj->getControllingPlayer()->isSkirmishAIPlayer()) {
			Team *team = obj->getTeam();
			AIGroup *group = TheAI->createGroup();
			team->getTeamAsAIGroup(group);

			Coord3D pos;
			group->getCenter(&pos);

			pos.x -= m_goalPosition.x;
			pos.y -= m_goalPosition.y;
			pos.z = 0;

			Int numInGroup = group->getCount();
			if (pos.length() <= (numInGroup * TheAI->getAiData()->getSkirmishGroupFudgeValue())) {
				status = STATE_SUCCESS;
			}
		}
	}

	if (status != STATE_CONTINUE) {
		m_currentWaypoint = getNextWaypoint();

		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		if (m_priorWaypoint)
			ai->setPriorWaypointID(m_priorWaypoint->getID());
		if (m_currentWaypoint)
			ai->setCurrentWaypointID(m_currentWaypoint->getID());

		if (m_currentWaypoint == 0) {
			ai->setCompletedWaypoint(m_priorWaypoint);
			return STATE_SUCCESS;
		}
		if (m_moveAsGroup)
			obj->getTeam()->setCurrentWaypoint(m_currentWaypoint);

		computeGoal(false);
		if (getAdjustsDestination() && ai->isDoingGroundMovement()) {
			if (!TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(),
				&m_goalPosition)) {
				if (CritterDesyncFlag && CritterDesyncSink)
					((DebugLogFunction)j_0003a17a)(CritterDesyncSink,
						"CritterDesync: ComputePath36");
				return STATE_FAILURE;
			}
		}
		ai->friend_startingMove();
		computePath();
		if (getAdjustsDestination()) {
			TheAI->pathfinder()->updateGoal(obj, &m_goalPosition, m_goalLayer,
				BfmeAiStatesFile, 0x244d);
		}

		return STATE_CONTINUE;
	}
	if (status != STATE_CONTINUE) {
		if (CritterDesyncFlag && CritterDesyncSink)
			((DebugLogFunction)j_0003a17a)(CritterDesyncSink,
				"CritterDesync: ComputePath37");
	}
	return status;
}
