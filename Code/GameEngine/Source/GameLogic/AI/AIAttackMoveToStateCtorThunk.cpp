// cl: /DNDEBUG /MD /EHsc
// Retail 0x00183990 is the three-argument constructor for
// AIFollowPathAsTeamState.  The caller passes the state machine, a Bool, and
// the name "AIFollowPathAsTeamState"; vtable 0x01099C08 confirms the class.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

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

// This is the BFME AIInternalMoveToState prefix.  The complete virtual shape
// preserves the retail vtable slot used by the constructor's derived class.
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

// The constructor at 0x00581F60 is reached through the nested machine's
// constructor call.  Seven slots after the destructor put initDefaultState
// at the retail indirect-call slot +0x1c.
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

typedef Rva00581F60SubMachine AIAttackMoveStateMachine;

class BfmeStateMachineLayout
{
private:
	char m_gap00[0x10];

public:
	Object *m_owner;

	Object *getOwner() { return m_owner; }
};

extern int g_AIFollowPathAsTeamStateVTable;

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	AIFollowPathAsTeamState(StateMachine *machine, bool asTeam, AsciiString name);

private:
	int m_field50;
	int m_retryCount;
	bool m_field58;
	bool m_field59;
	bool m_field5A;
	bool m_field5B;
	int m_field5C;
	AIAttackMoveStateMachine *m_attackMoveMachine;
	int m_field64;
	bool m_field68;
};

// ??0AIFollowPathAsTeamState@@QAE@PAVStateMachine@@_NVAsciiString@@@Z
AIFollowPathAsTeamState::AIFollowPathAsTeamState(
	StateMachine *machine, bool asTeam, AsciiString name) :
	AIInternalMoveToState(machine, name)
{
	*(int **)this = &g_AIFollowPathAsTeamStateVTable;
	m_field50 = 0;
	m_retryCount = 5;
	m_field58 = true;
	m_field59 = false;
	m_field5A = false;
	m_field5B = false;
	m_field5C = 0;
	m_attackMoveMachine = 0;
	m_field64 = 0;
	m_field68 = false;
	if (asTeam)
	{
		m_attackMoveMachine = new AIAttackMoveStateMachine(
			((BfmeStateMachineLayout *)m_machine)->getOwner(),
			AsciiString("AIAttackMoveMachine"));
		m_attackMoveMachine->initDefaultState();
	}
}
