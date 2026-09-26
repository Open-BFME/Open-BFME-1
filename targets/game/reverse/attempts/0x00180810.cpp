// ?d_00180810@@YAXXZ
// partial score=0.44 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x00180810 constructor with address-derived local ABI views.

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

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class Object
{
public:
	Bool isKindOf( UnsignedInt kind ) const;

	Bool isImmobile() const
	{
		return (*(const UnsignedByte *)((const char *)this + 0x94) & 0x20) != 0;
	}

	Bool isPortableStructure() const
	{
		const Overridable *tmpl = *(const Overridable **)((const char *)this + 4);
		if (tmpl == 0)
			return false;
		if (tmpl->m_nextOverride != 0)
			tmpl = tmpl->m_nextOverride->getFinalOverride();
		return (*(const UnsignedByte *)((const char *)tmpl + 0xc8) & 4) != 0;
	}

	Bool hasPortableStructureTemplateFlag() const
	{
		const Overridable *tmpl = *(const Overridable **)((const char *)this + 4);
		if (tmpl == 0)
			return false;
		if (tmpl->m_nextOverride != 0)
			tmpl = tmpl->m_nextOverride->getFinalOverride();
		return (*(const UnsignedInt *)((const char *)tmpl + 0xcc) & 0x1000000) != 0;
	}
};

#pragma comment(linker, "/alternatename:?isKindOf@Object@@QBE_NI@Z=?j_0003251f@@YAXXZ")

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, Bool flag );
	virtual ~StateMachine();

protected:
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
		Bool forceAttacking );

private:
	Bool m_attackingObject;
	Bool m_canTurnInPlace;
	Bool m_setLocomotor;
	Bool m_forceAttacking;
};

Rva00180810AimState::Rva00180810AimState(
	StateMachine *machine, Bool attackingObject, Bool forceAttacking )
	: State(machine, AsciiString("AIAttackAimAtTargetState"))
{
	*(UnsignedInt *)this = 0x01097C60;
	m_attackingObject = attackingObject;
	m_canTurnInPlace = false;
	m_setLocomotor = false;
	m_forceAttacking = forceAttacking;
}

class Rva00180810FireState : public State
{
public:
	Rva00180810FireState( StateMachine *machine, void *notify );

private:
	void *m_notify;
	Bool m_finished;
};

Rva00180810FireState::Rva00180810FireState(
	StateMachine *machine, void *notify )
	: State(machine, AsciiString("AIAttackFireWeaponState"))
{
	*(UnsignedInt *)this = 0x01097DC0;
	m_notify = notify;
	m_finished = false;
}

class Rva00180810FailureState : public State
{
public:
	Rva00180810FailureState( StateMachine *machine );

private:
};

Rva00180810FailureState::Rva00180810FailureState(
	StateMachine *machine ) : State(machine, AsciiString("FailureState"))
{
	*(UnsignedInt *)this = 0x01097950;
}

class Rva00180810PursueState
{
public:
	Rva00180810PursueState( StateMachine *, Bool, Bool, Bool );
	virtual ~Rva00180810PursueState();

private:
	UnsignedByte m_body[0x64];
};

#pragma comment(linker, "/alternatename:??0Rva00180810PursueState@@QAE@PAVStateMachine@@_N11@Z=?j_00046ba@@YAXXZ")

class Rva00180810ApproachState
{
public:
	Rva00180810ApproachState( StateMachine *, Bool, Bool, Bool );
	virtual ~Rva00180810ApproachState();

private:
	UnsignedByte m_body[0x74];
};

#pragma comment(linker, "/alternatename:??0Rva00180810ApproachState@@QAE@PAVStateMachine@@_N11@Z=?j_00037b05@@YAXXZ")

class Rva00180810ContinueState
{
public:
	Rva00180810ContinueState( StateMachine * );
	virtual ~Rva00180810ContinueState();

private:
	UnsignedByte m_body[0x20];
};

#pragma comment(linker, "/alternatename:??0Rva00180810ContinueState@@QAE@PAVStateMachine@@@Z=?j_00046fbf@@YAXXZ")

struct Rva00180810Machine : public StateMachine
{
	Rva00180810Machine( Object *, AIAttackState *, AsciiString,
		Bool, Bool, Bool );
	virtual ~Rva00180810Machine();
};

Rva00180810Machine::Rva00180810Machine(
	Object *obj, AIAttackState *att, AsciiString name,
	Bool follow, Bool attackingObject, Bool forceAttacking )
: StateMachine(obj, name, false)
{
	*(UnsignedInt *)this = 0x01097168;

	static const StateConditionInfo objectConditionsNormal[] =
	{
		StateConditionInfo((StateConditionFunction)0x0041745E, 0x64, 0),
		StateConditionInfo((StateConditionFunction)0x0040D7A1, 0x64, 0),
		StateConditionInfo((StateConditionFunction)0x0056AF70, 0x270f, (void *)2),
		StateConditionInfo(0, 0, 0)
	};
	static const StateConditionInfo objectConditionsForced[] =
	{
		StateConditionInfo((StateConditionFunction)0x0041745E, 0x64, 0),
		StateConditionInfo((StateConditionFunction)0x0056AF70, 0x270f, (void *)3),
		StateConditionInfo((StateConditionFunction)0x0040D7A1, 0x64, 0),
		StateConditionInfo(0, 0, 0)
	};
	const StateConditionInfo *objectConditions =
		forceAttacking ? objectConditionsForced : objectConditionsNormal;

	static const StateConditionInfo positionConditions[] =
	{
		StateConditionInfo((StateConditionFunction)0x00435A53, 0x64, 0),
		StateConditionInfo(0, 0, 0)
	};
	static const StateConditionInfo immobileConditions[] =
	{
		StateConditionInfo((StateConditionFunction)0x0056AF70, 0x270f, (void *)2),
		StateConditionInfo(0, 0, 0)
	};
	if (obj->isImmobile())
		objectConditions = immobileConditions;

	Rva00180810AimState *aim =
		new Rva00180810AimState((StateMachine *)this,
			attackingObject, forceAttacking);
	defineState(0x66, (State *)aim, 0x67, 0x270f,
		attackingObject ? objectConditions : positionConditions);

	Rva00180810FireState *fire = new Rva00180810FireState(
		(StateMachine *)this, (char *)att + 0x24);
	defineState(0x67, (State *)fire, 0x68, 0x64,
		attackingObject ? objectConditions : positionConditions);

	if (!obj->isPortableStructure())
	{
		if (obj->hasPortableStructureTemplateFlag() && obj->isKindOf(3))
		{
			static const StateConditionInfo portableStructureChaseConditions[] =
			{
				StateConditionInfo((StateConditionFunction)0x00571FD0, 0x66, 0),
				StateConditionInfo(0, 0, 0)
			};

			Rva00180810ContinueState *chase =
				new Rva00180810ContinueState((StateMachine *)this);
			defineState(0x64, (State *)chase, 0x270f, 0x270f,
				portableStructureChaseConditions);
		}
		else if (attackingObject)
		{
			Rva00180810PursueState *pursue =
				new Rva00180810PursueState((StateMachine *)this, follow,
					attackingObject, forceAttacking);
			defineState(0x64, (State *)pursue, 0x65, 0x65, 0);

			Rva00180810ApproachState *approach =
				new Rva00180810ApproachState((StateMachine *)this, follow,
					attackingObject, forceAttacking);
			defineState(0x65, (State *)approach, 0x66, 0x270f, 0);
		}
		else
		{
			Rva00180810ApproachState *chase =
				new Rva00180810ApproachState((StateMachine *)this, follow,
					attackingObject, forceAttacking);
			defineState(0x64, (State *)chase, 0x66, 0x270f, 0);

			Rva00180810ApproachState *approach =
				new Rva00180810ApproachState((StateMachine *)this, follow,
					attackingObject, forceAttacking);
			defineState(0x65, (State *)approach, 0x66, 0x270f, 0);
		}
	}
	else
	{
		Rva00180810FailureState *chase =
			new Rva00180810FailureState((StateMachine *)this);
		defineState(0x64, (State *)chase, 0x270f, 0x270f, 0);
	}
}

// ??0Rva00180810Machine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@_N33@Z
