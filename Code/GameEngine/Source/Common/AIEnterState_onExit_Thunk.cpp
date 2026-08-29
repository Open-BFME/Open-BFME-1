// cl: /DNDEBUG /MD /EHs-c-
// Lift the AIEnterState::onExit __emit thunk to clean C++.
//
// Verbatim Zero Hour AIStates.cpp: chain to the base onExit, stop the pathfinder
// ignoring this object, and tell whatever the goal was that it no longer wants
// to enter or exit.
//
// Retail pins what ZH leaves symbolic: the state machine is at this+0x1C with
// its owner at machine+0x10, the AI at Object+0x204, the current locomotor at
// AIUpdateInterface+0x1CC, the pending entry id at this+0x50, and the contain
// module at Object+0x1FC with onObjectWantsToEnterOrExit on its vtable at +0x34.
//
// setAllowInvalidPosition(false) is inlined to a single `and [esi+0x40], ~2`,
// so the flag is bit 1 of the word at Locomotor+0x40 rather than a call.

typedef int Int;

enum StateExitType { EXIT_NORMAL = 0 };
enum ObjectEnterExitType { WANTS_NEITHER = 0, WANTS_TO_ENTER = 1, WANTS_TO_EXIT = 2 };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	void setAllowInvalidPosition(bool allow)
	{
		if (!allow)
			m_flags &= ~ALLOW_INVALID_POSITION;
	}

private:
	enum { ALLOW_INVALID_POSITION = 0x00000002 };

	unsigned char m_unreconstructed_00[0x40];
	unsigned int m_flags;							///< retail this+0x40
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obj);					///< ILT thunk at 0x0000315C

	Locomotor *getCurLocomotor(void) const { return m_curLocomotor; }

private:
	unsigned char m_unreconstructed_00[0x1CC];
	Locomotor *m_curLocomotor;						///< retail this+0x1CC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants);	///< vtable +0x34
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI(void) const { return m_ai; }
	ContainModuleInterface *getContain(void) const { return m_contain; }

private:
	unsigned char m_unreconstructed_00[0x1FC];
	ContainModuleInterface *m_contain;				///< retail this+0x1FC
	unsigned char m_unreconstructed_200[4];
	AIUpdateInterface *m_ai;						///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);					///< ILT thunk at 0x0001F253
};

extern GameLogic *TheGameLogic;						///< retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;								///< retail this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);				///< ILT thunk at 0x00029311

	Object *getMachineOwner(void) const { return m_machine->m_owner; }

protected:
	unsigned char m_unreconstructed_04[0x1C - 4];
	StateMachine *m_machine;						///< retail this+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIEnterState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

private:
	unsigned char m_unreconstructed_20[0x50 - 0x20];
	Int m_entryToClear;								///< retail this+0x50
};

// ?onExit@AIEnterState@@UAEXW4StateExitType@@@Z
void AIEnterState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	AIInternalMoveToState::onExit(status);

	// tell the pathfinder to stop ignoring the object
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
	{
		ai->ignoreObstacle(0);
		if (ai->getCurLocomotor())
		{
			ai->getCurLocomotor()->setAllowInvalidPosition(false);
		}
	}

	// use this, rather than getMachineGoalObject, in case the goal
	// is killed while we were waiting...
	if (m_entryToClear != 0)
	{
		Object *goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
			{
				contain->onObjectWantsToEnterOrExit(obj, WANTS_TO_EXIT);
			}
		}
	}
}
