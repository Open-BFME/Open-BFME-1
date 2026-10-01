// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Rva001812B0AIHordeMachine constructor, retail 0x001812B0, 767 bytes.
// AIAttackState::createAttackMachine (0x00184110) builds it through ILT
// 0x000268DC with the debug name "AIHordeMachine"; its own vtable 0x01097238
// is not shared with a landed sibling, so the class keeps the address token.
// Shape follows the matched sibling AttackMeleeStateMachine constructor
// (AttackMeleeStateMachineCtor.cpp, 0x00180EE0): StateMachine base, then
// states newed and defined in order; the horde branch is taken when the
// owner's template carries kind bit 0x400000 and the current weapon's
// template byte is set. The fire and wait states construct inline with the
// same vtables (0x01097DC0, 0x01097D40) the sibling installs.

#include "StringInline.h"

class Object;
class AIAttackState;
class State;
struct StateConditionInfo;
class NotifyWeaponFiredInterface;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );

protected:
	// retail's StateMachine destructor is protected: ??1StateMachine@@MAE@XZ
	virtual ~StateMachine();

	void defineState( unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual ~State();

private:
	unsigned char m_head[ 0x20 ];
};

class AIAttackMeleeSquishState
{
public:
	AIAttackMeleeSquishState( StateMachine *machine );

private:
	unsigned char m_storage[ 0x6c ];
};

class AIAttackFireWeaponState : public State
{
public:
	AIAttackFireWeaponState( StateMachine *machine,
		NotifyWeaponFiredInterface *notify );

private:
	NotifyWeaponFiredInterface *m_notify;
	bool m_finished;
};

AIAttackFireWeaponState::AIAttackFireWeaponState(
	StateMachine *machine, NotifyWeaponFiredInterface *notify )
	: State( machine, AsciiString( "AIAttackFireWeaponState" ) ),
	  m_notify( notify ),
	  m_finished( false )
{
}

class AIWaitUntilFinishedFiringState : public State
{
public:
	AIWaitUntilFinishedFiringState( StateMachine *machine );
};

// ??0AIWaitUntilFinishedFiringState@@QAE@PAVStateMachine@@@Z absent-from-retail
AIWaitUntilFinishedFiringState::AIWaitUntilFinishedFiringState(
	StateMachine *machine )
	: State( machine, AsciiString( "AIWaitUntilFinishedFiringState" ) )
{
}


// Object template / weapon views the horde test reads.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vftable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if ( !m_overridable )
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	const T *m_overridable;
};

class ThingTemplate : public Overridable
{
public:
	char m_08[ 0xd4 - 8 ];
	unsigned int m_kindof;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	void *m_vftable;
	Rva001E1770ByteField *m_template;
};

class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );
	void *m_vftable;
	OVERRIDE<ThingTemplate> m_template;
	const ThingTemplate *getTemplate() const { return m_template.operator->(); }
};

class AIAttackMeleeHordeApproachTargetState
{
public:
	AIAttackMeleeHordeApproachTargetState( StateMachine *machine );

private:
	unsigned char m_storage[ 0x64 ];
};

class Rva001710C0State
{
public:
	Rva001710C0State( void *machine );

private:
	unsigned char m_storage[ 0x28 ];
};

class Rva00171120State
{
public:
	Rva00171120State( void *machine );

private:
	unsigned char m_storage[ 0x2c ];
};

class AIAttackApproachTargetState
{
public:
	AIAttackApproachTargetState( StateMachine *machine, bool a, bool b, bool c );

private:
	unsigned char m_storage[ 0x78 ];
};

class Rva001812B0AIHordeMachine : public StateMachine
{
public:
	Rva001812B0AIHordeMachine( Object *owner, AIAttackState *attack,
		AsciiString name );
};

// ??0Rva001812B0AIHordeMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
Rva001812B0AIHordeMachine::Rva001812B0AIHordeMachine(
	Object *owner, AIAttackState *attack, AsciiString name )
	: StateMachine( owner, name, false )
{
	Weapon *weapon;
	if ( ( owner->getTemplate()->m_kindof & 0x400000 ) &&
		( weapon = owner->getCurrentWeapon( 0 ) ) != 0 &&
		weapon->m_template->get() )
	{
		AIAttackMeleeSquishState *squish = new AIAttackMeleeSquishState( this );
		defineState( 0xc8, (State *)squish, 0xc9, 0x270f, 0 );
		AIAttackMeleeHordeApproachTargetState *approach =
			new AIAttackMeleeHordeApproachTargetState( this );
		defineState( 0xc9, (State *)approach, 0xcb, 0x270f, 0 );
		Rva001710C0State *first = new Rva001710C0State( this );
		defineState( 0xcb, (State *)first, 0x270e, 0xcc, 0 );
		Rva00171120State *second = new Rva00171120State( this );
		defineState( 0xcc, (State *)second, 0x270e, 0xc9, 0 );
	}
	else
	{
		AIAttackMeleeSquishState *squish = new AIAttackMeleeSquishState( this );
		defineState( 0xc8, (State *)squish, 0xc9, 0x270f, 0 );
		AIAttackApproachTargetState *approach =
			new AIAttackApproachTargetState( this, false, true, false );
		defineState( 0xc9, (State *)approach, 0xca, 0x270f, 0 );
		AIAttackFireWeaponState *fire =
			new AIAttackFireWeaponState(
				this, attack ? (NotifyWeaponFiredInterface *)((char *)attack + 0x24) : 0 );
		defineState( 0xca, (State *)fire, 0xcb, 0xc9, 0 );
		AIWaitUntilFinishedFiringState *wait =
			new AIWaitUntilFinishedFiringState( this );
		defineState( 0xcb, (State *)wait, 0xc9, 0xc9, 0 );
	}
}
