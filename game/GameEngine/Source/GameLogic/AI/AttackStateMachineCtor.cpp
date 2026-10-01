// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// AttackStateMachine constructor reconstruction for retail 0x00180810.

#include "StringInline.h"

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class Object;
class AIAttackState;
class State;
struct StateConditionInfo;

class StateMachine;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	UnsignedByte m_head[4];
	Overridable *m_nextOverride;
};

class Object
{
public:
	Bool isImmobile() const
	{
		return (*(const UnsignedByte *)((const char *)this + 0x94) & 0x20) != 0;
	}

	Bool isPortableStructure() const
	{
		const Overridable *tmpl = *(const Overridable **)((const char *)this + 4);
		const Overridable *resolved = tmpl;
		if (tmpl == 0)
			resolved = 0;
		else if (tmpl->m_nextOverride != 0)
			resolved = tmpl->m_nextOverride->getFinalOverride();
		return (*(const UnsignedByte *)((const char *)resolved + 0xc8) & 4) != 0;
	}

	Bool hasPortableStructureTemplateFlag() const
	{
		const Overridable *tmpl = *(const Overridable **)((const char *)this + 4);
		const Overridable *resolved = tmpl;
		if (tmpl == 0)
			resolved = 0;
		else if (tmpl->m_nextOverride != 0)
			resolved = tmpl->m_nextOverride->getFinalOverride();
		return (*(volatile const UnsignedInt *)((const char *)resolved + 0xcc) & 0x1000000) != 0;
	}
};

enum KindOfType
{
	KINDOF_CAN_ATTACK = 3
};

class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, Bool flag );

protected:
	// retail's StateMachine destructor is protected: ??1StateMachine@@MAE@XZ
	virtual ~StateMachine();

	void defineState( UnsignedInt id, State *state, UnsignedInt success,
		UnsignedInt failure, const StateConditionInfo *conditions );
};

#pragma comment(linker, "/alternatename:??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z=?j_0000f123@@YAXXZ")
#pragma comment(linker, "/alternatename:?defineState@StateMachine@@IAEXIPAVState@@IIPBUStateConditionInfo@@@Z=?j_0003d1b3@@YAXXZ")

class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual ~State();

private:
	UnsignedByte m_head[0x20];
};

#pragma comment(linker, "/alternatename:??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z=?j_000035b2@@YAXXZ")

typedef Bool (*StateConditionFunction)( State *, void * );

extern void j_0001745e();
extern void j_0000d7a1();
extern void j_00035a53();
extern void d_0016af70();
Bool inWeaponRangeObject( State *thisState, void *userData );

extern "C" void *bfmeVftAIAttackAimAtTargetState[];
extern "C" void *bfmeVftAIAttackFireWeaponState[];
extern "C" void *bfmeVftFailureState[];
extern "C" void *bfmeVftAIWaitUntilFinishedFiringState[];
extern "C" void *bfmeVftRva0016AB00TailDtor[];
#pragma comment(linker, "/alternatename:_bfmeVftAIAttackAimAtTargetState=??_7AIAttackAimAtTargetState@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftAIAttackFireWeaponState=??_7AIAttackFireWeaponState@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftFailureState=??_7FailureState@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftAIWaitUntilFinishedFiringState=??_7AIWaitUntilFinishedFiringState@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftRva0016AB00TailDtor=??_7Rva0016AB00TailDtor@@6B@")

struct StateConditionInfo
{
	StateConditionFunction test;
	UnsignedInt toState;
	void *userData;

	StateConditionInfo( StateConditionFunction fn, UnsignedInt id,
		void *data ) : test(fn), toState(id), userData(data) {}
};

class Rva00180810AimState : public State
{
public:
	Rva00180810AimState( StateMachine *machine, Bool attackingObject,
		Bool forceAttacking )
		: State(machine, AsciiString("AIAttackAimAtTargetState"))
	{
		*(void **)this = bfmeVftAIAttackAimAtTargetState;
		m_attackingObject = attackingObject;
		m_canTurnInPlace = false;
		m_setLocomotor = false;
		m_forceAttacking = forceAttacking;
	}

private:
	Bool m_attackingObject;
	Bool m_canTurnInPlace;
	Bool m_setLocomotor;
	Bool m_forceAttacking;
};
class Rva00180810FireState : public State
{
public:
	Rva00180810FireState( StateMachine *machine, void *notify )
		: State(machine, AsciiString("AIAttackFireWeaponState"))
	{
		*(void **)this = bfmeVftAIAttackFireWeaponState;
		m_notify = notify;
		m_finished = false;
	}

private:
	void *m_notify;
	Bool m_finished;
};
class Rva00180810FailureState : public State
{
public:
	Rva00180810FailureState( StateMachine *machine )
		: State(machine, AsciiString("FailureState"))
	{
		*(void **)this = bfmeVftFailureState;
	}

private:
};

class AIAttackPursueTargetState
{
public:
	AIAttackPursueTargetState( StateMachine *, Bool, Bool, Bool );
	virtual ~AIAttackPursueTargetState();

private:
	UnsignedByte m_body[0x64];
};

class AIAttackApproachTargetState
{
public:
	AIAttackApproachTargetState( StateMachine *, Bool, Bool, Bool );
	virtual ~AIAttackApproachTargetState();

private:
	UnsignedByte m_body[0x74];
};

class ContinueState
{
public:
	ContinueState( StateMachine * );
	virtual ~ContinueState();

private:
	UnsignedByte m_body[0x20];
};

class Rva00180810WaitState : public State
{
public:
	Rva00180810WaitState( StateMachine *machine )
		: State(machine, AsciiString("AIWaitUntilFinishedFiringState"))
	{
		*(void **)this = bfmeVftAIWaitUntilFinishedFiringState;
	}
};

struct AttackStateMachine : public StateMachine
{
	AttackStateMachine( Object *, AIAttackState *, AsciiString,
		Bool, Bool, Bool );
	virtual ~AttackStateMachine();
};

AttackStateMachine::AttackStateMachine(
	Object *obj, AIAttackState *att, AsciiString name,
	Bool follow, Bool attackingObject, Bool forceAttacking )
: StateMachine(obj, name, false)
{
	*(void **)this = bfmeVftRva0016AB00TailDtor;

	static const StateConditionInfo objectConditionsNormal[] =
	{
		StateConditionInfo((StateConditionFunction)j_0001745e, 0x64, 0),
		StateConditionInfo((StateConditionFunction)j_0000d7a1, 0x64, 0),
		StateConditionInfo((StateConditionFunction)d_0016af70, 0x270f, (void *)2),
		StateConditionInfo(0, 0, 0)
	};
	static const StateConditionInfo objectConditionsForced[] =
	{
		StateConditionInfo((StateConditionFunction)j_0001745e, 0x64, 0),
		StateConditionInfo((StateConditionFunction)d_0016af70, 0x270f, (void *)3),
		StateConditionInfo((StateConditionFunction)j_0000d7a1, 0x64, 0),
		StateConditionInfo(0, 0, 0)
	};
	const StateConditionInfo *objectConditions =
		forceAttacking ? objectConditionsForced : objectConditionsNormal;

	static const StateConditionInfo positionConditions[] =
	{
		StateConditionInfo((StateConditionFunction)j_00035a53, 0x64, 0),
		StateConditionInfo(0, 0, 0)
	};
	static const StateConditionInfo immobileConditions[] =
	{
		StateConditionInfo((StateConditionFunction)d_0016af70, 0x270f, (void *)2),
		StateConditionInfo(0, 0, 0)
	};
	if (((Object *)obj)->isImmobile())
		objectConditions = immobileConditions;

	defineState(0x66, (State *)new Rva00180810AimState((StateMachine *)this,
			attackingObject, forceAttacking), 0x67, 0x270f,
		attackingObject ? objectConditions : positionConditions);

	defineState(0x67, (State *)new Rva00180810FireState(
		(StateMachine *)this, att ? (char *)att + 0x24 : 0), 0x68, 0x64,
		attackingObject ? objectConditions : positionConditions);

	defineState(0x68, (State *)new Rva00180810WaitState(
		(StateMachine *)this), 0x66, 0x270f, 0);

	if (!((Object *)obj)->isPortableStructure())
	{
		if (((Object *)obj)->hasPortableStructureTemplateFlag() &&
			((Thing *)obj)->isKindOf(KINDOF_CAN_ATTACK))
		{
			static const StateConditionInfo portableStructureChaseConditions[] =
			{
				StateConditionInfo((StateConditionFunction)inWeaponRangeObject, 0x66, 0),
				StateConditionInfo(0, 0, 0)
			};

			defineState(0x64, (State *)new ContinueState((StateMachine *)this), 0x270f, 0x270f,
				portableStructureChaseConditions);
		}
		else if (attackingObject)
		{
			defineState(0x64, (State *)new AIAttackPursueTargetState((StateMachine *)this, follow,
					attackingObject, forceAttacking), 0x65, 0x65, 0);

			defineState(0x65, (State *)new AIAttackApproachTargetState((StateMachine *)this, follow,
					attackingObject, forceAttacking), 0x66, 0x270f, 0);
		}
		else
		{
			defineState(0x64, (State *)new AIAttackApproachTargetState((StateMachine *)this, follow,
					attackingObject, forceAttacking), 0x66, 0x270f, 0);

			defineState(0x65, (State *)new AIAttackApproachTargetState((StateMachine *)this, follow,
					attackingObject, forceAttacking), 0x66, 0x270f, 0);
		}
	}
	else
	{
		defineState(0x64, (State *)new Rva00180810FailureState((StateMachine *)this), 0x270f, 0x270f, 0);
	}
}

// ??0AttackStateMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@_N33@Z
