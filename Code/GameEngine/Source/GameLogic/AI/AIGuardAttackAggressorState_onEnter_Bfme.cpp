// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AIGuardAttackAggressorState::onEnter at retail RVA 0x0015CB70 (284 bytes).
// The dedicated AIGuardAttackAggressorState vtable 0x010963A0 slot 4 routes
// through ILT 0x0001CE81 to this body.  Port of the Zero Hour body in
// GameLogic/AI/AIGuard.cpp; BFME dropped the guard-radius exit condition and
// added the one-shot re-entry flag at +0x44.
//
// Retail keeps TheGameLogic in EDI across the findObjectByID call and reads
// the frame through it: BFME's findObjectByID was a header inline MSVC 7.1 left
// out of line, so its body was visible and proved it writes no memory.  The
// visible noinline body below reproduces that; the call still binds to the
// pinned 0x0009A510 body through ILT 0x0001F253.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

class Object;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

enum { INVALID_ID = 0 };

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1
};

class BodyModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual const struct DamageInfo *getLastDamageInfo() const;
};

struct DamageInfo
{
	unsigned char m_pad00[8];
	ObjectID m_sourceID;
};

class Object
{
public:
	BodyModule *getBodyModule() const
	{
		return *(BodyModule **)((const unsigned char *)this + 0x200);
	}
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);

	unsigned char m_pad04[0x0c];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// hash_map placement as Code/GameEngine/Source/GameLogic/System/GameLogicFindObjectByID.cpp
class GameLogic
{
public:
	__declspec(noinline) Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

	UnsignedInt getFrame()
	{
		return m_frame;
	}

private:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
	unsigned char m_slice_pad[0x70];
	ObjectPtrHash m_objHash;
};

class AIData
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	AIData *m_aiData;
	const AIData *getAiData() const
	{
		return m_aiData;
	}
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;

class BfmeGuardMachine : public StateMachine
{
public:
	unsigned char m_pad14[0x58];
	ObjectID m_nemesisID;

	void setNemesisID(ObjectID id) { m_nemesisID = id; }
	ObjectID getNemesisID() const { return m_nemesisID; }
};

class State
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(Int status);
	virtual StateReturnType update();

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];

	StateMachine *getMachine() const
	{
		return m_machine;
	}
	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const;
};

class ExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	float m_centerX;
	float m_centerY;
	float m_centerZ;
	float m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class AIAttackState
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject,
		Bool forceAttacking, AttackExitConditionsInterface *attackParameters);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void slot14();
	virtual StateReturnType update();

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_tail[0x34];
};

class AIGuardAttackAggressorState : public State
{
public:
	virtual StateReturnType onEnter();

	BfmeGuardMachine *getGuardMachine() const
	{
		return (BfmeGuardMachine *)getMachine();
	}

	ExitConditions m_exitConditions;
	AIAttackState *m_attackState;
	Bool m_unusedFlag;
};

StateReturnType AIGuardAttackAggressorState::onEnter()
{
	if (m_unusedFlag)
	{
		m_unusedFlag = false;
		return onEnter();
	}

	Object *obj = getMachineOwner();
	ObjectID nemID = INVALID_ID;

	if (obj->getBodyModule() && obj->getBodyModule()->getLastDamageInfo()->m_sourceID)
	{
		nemID = obj->getBodyModule()->getLastDamageInfo()->m_sourceID;
		getGuardMachine()->setNemesisID(nemID);
	}

	Object *nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID());
	if (nemesis == 0)
		return STATE_SUCCESS;

	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_exitConditions.m_conditionsToConsider = 6;

	m_attackState = new AIAttackState(getMachine(), true, true, false, &m_exitConditions);
	m_attackState->m_machine->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE)
		return STATE_CONTINUE;

	return STATE_SUCCESS;
}
