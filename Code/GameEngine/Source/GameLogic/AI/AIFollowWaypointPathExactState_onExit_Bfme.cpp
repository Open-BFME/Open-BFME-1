// cl: /DNDEBUG /MD /EHsc
// readable body of ?onExit@AIFollowWaypointPathExactState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout view for the retail exact-waypoint exit body.

enum StateExitType { STATE_EXIT_UNKNOWN = 0 };
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

class BFMEWaypointLocomotor
{
public:
	void clearPreciseZPos()
	{
		*(UnsignedInt *)((UnsignedByte *)this + 0x40) &= ~0x8u;
	}
};

class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setCompletedWaypoint(const Waypoint *waypoint);

	BFMEWaypointLocomotor *getCurLocomotor() const
	{
		return *(BFMEWaypointLocomotor **)((UnsignedByte *)this + 0x1CC);
	}
};

class BFMEWaypointObject
{
public:
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((UnsignedByte *)this + 0x204);
	}
};

class BFMEWaypointMachine
{
public:
	BFMEWaypointObject *getOwner() const
	{
		return *(BFMEWaypointObject **)((UnsignedByte *)this + 0x10);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIFollowWaypointPathExactState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIFollowWaypointPathExactState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	BFMEWaypointMachine *machine =
		*(BFMEWaypointMachine **)((UnsignedByte *)this + 0x1C);
	AIUpdateInterface *ai = machine->getOwner()->getAI();
	if (ai)
	{
		*(UnsignedByte *)((UnsignedByte *)ai + 0x328) = 0;
		ai->setCompletedWaypoint(0);
		BFMEWaypointLocomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
			locomotor->clearPreciseZPos();
		*(UnsignedInt *)((UnsignedByte *)ai + 0x194) = 0xFFFFFFFF;
	}
}
