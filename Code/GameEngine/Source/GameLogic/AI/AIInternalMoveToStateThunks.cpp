// readable body of ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?update@AIMoveOutOfTheWayState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
enum StateReturnType
{
};

enum StateExitType
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
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

class AIMoveOutOfTheWayStateUpdateShim
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
	return ((AIMoveOutOfTheWayStateUpdateShim *)this)->update();
}
