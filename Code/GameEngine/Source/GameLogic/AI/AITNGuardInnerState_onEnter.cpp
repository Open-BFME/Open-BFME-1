// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AITNGuardInnerState::onEnter (0x0018A470): slot 4 of AITNGuardInnerState's
// table 0x0109B560 (ILT 0x0002BE7C), next to the matched update in slot 6.
// Zero Hour's body from AITNGuard.cpp.

typedef int ObjectID;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1 };
enum StateExitType { EXIT_RESET = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// hash_map placement as Code/GameEngine/Source/GameLogic/System/GameLogicFindObjectByID.cpp.
// findObjectByID has its visible body, left out of line: MSVC then knows it
// writes no memory and keeps TheGameLogic in EDI across the call, as retail
// does (the lever AIGuardAttackAggressorState_onEnter_Bfme.cpp found). The
// call still binds to the pinned 0x0009A510 body.
class GameLogic
{
public:
	__declspec(noinline) Object *findObjectByID( ObjectID id )
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_fields[0x3c];
	UnsignedInt m_frame;
	unsigned char m_slice_pad[0x70];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class AIData
{
public:
	unsigned char m_fields[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
};

class AI
{
public:
	const AIData *getAiData() const { return m_aiData; }

private:
	unsigned char m_fields[0x14];
	AIData *m_aiData;										///< this+0x14
};

extern AI *TheAI;

class StateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject( const Object *object );
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit( const StateMachine *machine ) const = 0;
};

class ExitConditions : public AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit( const StateMachine *machine ) const;
	UnsignedInt m_attackGiveUpFrame;					///< this+0x04
	unsigned char m_center[4];
};

class State
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit( StateExitType status );
	virtual StateReturnType update();

	StateMachine *getMachine() { return m_machine; }

	unsigned char m_stateFields[0x18];
	StateMachine *m_machine;								///< this+0x1C
};

class AIAttackState : public State
{
public:
	AIAttackState( StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *attackParameters );
	unsigned char m_attackFields[0x54 - 0x20];
};

class AITNGuardMachine : public StateMachine
{
public:
	ObjectID getNemesisID() const { return m_nemesisToAttack; }
	unsigned char m_fields[0x50 - 0x04];
	ObjectID m_nemesisToAttack;							///< this+0x50
};

class AITNGuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();

	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }

	unsigned char m_at20[4];
	ExitConditions m_exitConditions;						///< this+0x24
	AIAttackState *m_attackState;							///< this+0x30
};

// ?onEnter@AITNGuardInnerState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardInnerState::onEnter( void )
{
	Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == 0) 
	{
		return STATE_SUCCESS;
	}
	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;

	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);

	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}
