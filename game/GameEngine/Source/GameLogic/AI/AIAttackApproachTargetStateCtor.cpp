// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class StateMachine;

extern const UnsignedInt g_0109A4C0[];

class State
{
public:
	State( StateMachine *, AsciiString );
	virtual ~State();

private:
	UnsignedByte m_head[0x20];
};

class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState( StateMachine *, AsciiString );
	virtual ~AIInternalMoveToState();

private:
	UnsignedByte m_body[0x2c];
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	AIAttackApproachTargetState(
		StateMachine *, Bool follow, Bool attackingObject, Bool forceAttacking );

private:
	volatile UnsignedInt m_unreconstructed0050[8];
	volatile Bool m_unreconstructed0070[6];
};

AIAttackApproachTargetState::AIAttackApproachTargetState(
	StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking )
	: AIInternalMoveToState(machine, AsciiString("AIAttackApproachTargetState"))
{
	*(volatile UnsignedInt *)this = (UnsignedInt)g_0109A4C0;
	m_unreconstructed0050[0] = 0;
	m_unreconstructed0050[1] = 0;
	m_unreconstructed0050[2] = 0;
	m_unreconstructed0050[3] = 0;
	m_unreconstructed0050[4] = 0;
	m_unreconstructed0050[5] = 0;
	m_unreconstructed0070[0] = follow;
	Bool force = *(volatile Bool *)&forceAttacking;
	m_unreconstructed0050[6] = 0;
	m_unreconstructed0050[7] = 0;
	m_unreconstructed0070[2] = 0;
	m_unreconstructed0070[5] = 0;
	m_unreconstructed0070[1] = attackingObject;
	m_unreconstructed0070[3] = 1;
	m_unreconstructed0070[4] = force;
}
