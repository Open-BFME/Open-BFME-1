// readable body of ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?update@AIMoveOutOfTheWayState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
enum StateReturnType
{
};

enum StateExitType
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	// AIMoveOutOfTheWayState jumps to this ILT, not directly to its target.
	__declspec(noinline) virtual StateReturnType update();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveOutOfTheWayState
{
public:
	virtual StateReturnType update();
};

class AIInternalMoveToStateOnEnterShim
{
public:
	StateReturnType onEnter();
};

class AIInternalMoveToStateUpdateShim
{
public:
	StateReturnType update();
};

StateReturnType AIInternalMoveToState::onEnter()
{
	return ((AIInternalMoveToStateOnEnterShim *)this)->onEnter();
}

StateReturnType AIInternalMoveToState::update()
{
	return ((AIInternalMoveToStateUpdateShim *)this)->update();
}

StateReturnType AIMoveOutOfTheWayState::update()
{
	return ((AIInternalMoveToState *)this)->AIInternalMoveToState::update();
}
