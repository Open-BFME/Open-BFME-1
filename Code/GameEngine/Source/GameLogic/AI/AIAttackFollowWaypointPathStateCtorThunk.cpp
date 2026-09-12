// cl: /DNDEBUG /MD /EHsc
// Identity evidence: AIStateMachine's constructor calls this 201-byte body;
// its two retail literals are "AIFollowWaypointPathState" and
// "AIAttackFollowMachine", matching the upstream constructor exactly.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// One byte, like EA's Bool field.  Its inline construction retains the source
// initializer boundary that VC6 used before setting up the following new-expression.
class BfmeOrderedBool
{
public:
	__forceinline BfmeOrderedBool(bool value)
	{
		m_value = value;
	}

private:
	volatile bool m_value;
};

class AsciiString
{
public:
	AsciiString(const char *text) : m_data(text) {}

	StringBase<char> m_data;
};

class StateMachine;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	AIInternalMoveToState(void *machine, AsciiString name);

	virtual ~AIInternalMoveToState();
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
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();

protected:
	char m_baseGap04[0x18];
	void *m_machine;
	char m_baseTail20[0x50 - 0x20];
};

// Seven slots after the destructor place initDefaultState at retail slot +0x1c.
class Rva00581F60SubMachine
{
public:
	Rva00581F60SubMachine(Object *owner, AsciiString name);
	virtual ~Rva00581F60SubMachine();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0C();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void initDefaultState();

private:
	char m_unreconstructed04[0x40];
};

// The existing neutral pin reaches the 0x00181F60 body.  The enclosing
// constructor and its "AIAttackFollowMachine" literal prove its role here.
typedef Rva00581F60SubMachine AIAttackMoveStateMachine;

class BfmeStateMachineLayout
{
private:
	char m_gap00[0x10];

public:
	Object *m_owner;

	Object *getOwner() { return m_owner; }
};

extern int g_AIAttackFollowWaypointPathStateVTable;

// upstream source: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
class AIAttackFollowWaypointPathState : public AIInternalMoveToState
{
public:
	AIAttackFollowWaypointPathState(StateMachine *machine, bool asGroup);

private:
	volatile int m_groupOffsetX;
	volatile int m_groupOffsetY;
	volatile float m_angle;
	volatile int m_framesSleeping;
	void *volatile m_currentWaypoint;
	void *volatile m_priorWaypoint;
	volatile bool m_appendGoalPosition;
	const volatile bool m_moveAsGroup;
	BfmeOrderedBool m_isFollowWaypointPathState;
	char m_pad6B;
	AIAttackMoveStateMachine *m_attackFollowMachine;
};

// ??0AIAttackFollowWaypointPathState@@QAE@PAVStateMachine@@_N@Z
AIAttackFollowWaypointPathState::AIAttackFollowWaypointPathState(
	StateMachine *machine,
	bool asGroup) :
	AIInternalMoveToState(machine, AsciiString("AIFollowWaypointPathState")),
	m_groupOffsetX(0),
	m_groupOffsetY(0),
	m_angle(0.0f),
	m_framesSleeping(0),
	m_currentWaypoint(0),
	m_priorWaypoint(0),
	m_appendGoalPosition(false),
	m_moveAsGroup(asGroup),
	m_isFollowWaypointPathState(false)
{
	*(int **)this = &g_AIAttackFollowWaypointPathStateVTable;
	m_attackFollowMachine = new AIAttackMoveStateMachine(
		((BfmeStateMachineLayout *)m_machine)->getOwner(),
		AsciiString("AIAttackFollowMachine"));
	m_attackFollowMachine->initDefaultState();
}
