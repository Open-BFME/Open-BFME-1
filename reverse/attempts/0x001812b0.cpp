// ??0Rva001812B0AIHordeMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
// partial score=0.31 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef unsigned int StateID;

class Object;
class AIAttackState;
class State;

struct StateConditionInfo;

class StateMachine
{
public:
	StateMachine(Object *owner, AsciiString name, bool flag);
	virtual ~StateMachine();

protected:
	void defineState(StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions);

private:
	char m_stateMachineStorage[0x40];
};

class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
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
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	void *m_vftable;
	Overridable *m_template;
};

class AIAttackMeleeSquishState
{
public:
	AIAttackMeleeSquishState(StateMachine *machine);

private:
	char m_storage[0x6c];
};

class AIAttackMeleeHordeApproachTargetState
{
public:
	AIAttackMeleeHordeApproachTargetState(StateMachine *machine);

private:
	char m_storage[0x64];
};

class Rva0017F570State
{
public:
	Rva0017F570State(StateMachine *machine, bool first, bool second,
		bool third);

private:
	char m_storage[0x78];
};

class Rva001710C0State
{
public:
	Rva001710C0State(void *machine);

private:
	char m_storage[0x28];
};

class Rva00171120State
{
public:
	Rva00171120State(void *machine);

private:
	char m_storage[0x2c];
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase(void *machine, AsciiString name);
	virtual void stateAnchor() {}

private:
	char m_stateData[0x20];
};

class Rva001812B0FireWeaponState : public Rva000A19E0StateBase
{
public:
	Rva001812B0FireWeaponState(StateMachine *machine, AIAttackState *attack);

private:
	void *m_attackField;
	unsigned char m_field28;
};

Rva001812B0FireWeaponState::Rva001812B0FireWeaponState(
	StateMachine *machine, AIAttackState *attack)
	: Rva000A19E0StateBase(machine, AsciiString("AIAttackFireWeaponState")),
	  m_attackField(attack ? (char *)attack + 0x24 : 0),
	  m_field28(0)
{
}

class Rva001812B0WaitUntilFiringState : public Rva000A19E0StateBase
{
public:
	Rva001812B0WaitUntilFiringState(StateMachine *machine)
		: Rva000A19E0StateBase(machine,
			AsciiString("AIWaitUntilFinishedFiringState"))
	{
	}
};

#pragma comment(linker, "/alternatename:??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z=?j_0000f123@@YAXXZ")
#pragma comment(linker, "/alternatename:?defineState@StateMachine@@IAEXIPAVState@@IIPBUStateConditionInfo@@@Z=?j_0003d1b3@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentWeapon@Object@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?get@Rva001E1770ByteField@@QBEEXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:??0AIAttackMeleeSquishState@@QAE@PAVStateMachine@@@Z=?j_0002e9b5@@YAXXZ")
#pragma comment(linker, "/alternatename:??0AIAttackMeleeHordeApproachTargetState@@QAE@PAVStateMachine@@@Z=?j_00013999@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0017F570State@@QAE@PAVStateMachine@@_N11@Z=?j_00037b05@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva001710C0State@@QAE@PAX@Z=?j_0001f3e8@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00171120State@@QAE@PAX@Z=?j_00041902@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva000A19E0StateBase@@QAE@PAXVAsciiString@@@Z=?j_000035b2@@YAXXZ")

class Rva001812B0AIHordeMachine : public StateMachine
{
public:
	Rva001812B0AIHordeMachine(Object *owner, AIAttackState *attack,
		AsciiString name);
};

Rva001812B0AIHordeMachine::Rva001812B0AIHordeMachine(
	Object *owner, AIAttackState *attack, AsciiString name)
	: StateMachine(owner, name, false)
{
	const Overridable *thingTemplate = owner->m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
		thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();

	Weapon *weapon;
	if (((*(const unsigned int *)((const char *)thingTemplate + 0xd4)) &
		0x400000) != 0 &&
		((weapon = owner->getCurrentWeapon(0)) != 0) &&
		(weapon->m_template->get() != 0))
	{
		defineState(0xc8,
			(State *)new AIAttackMeleeSquishState(this),
			0xc9, 0x270f, 0);
		defineState(0xc9,
			(State *)new AIAttackMeleeHordeApproachTargetState(this),
			0xcb, 0x270f, 0);
		defineState(0xcb, (State *)new Rva001710C0State(this),
			0x270e, 0xcc, 0);
		defineState(0xcc, (State *)new Rva00171120State(this),
			0x270e, 0xc9, 0);
	}
	else
	{
		defineState(0xc8,
			(State *)new AIAttackMeleeSquishState(this),
			0xc9, 0x270f, 0);
		defineState(0xc9,
			(State *)new Rva0017F570State(this, false, true, false),
			0xca, 0x270f, 0);
		defineState(0xca,
			(State *)new Rva001812B0FireWeaponState(this, attack),
			0xcb, 0xc9, 0);
		defineState(0xcb,
			(State *)new Rva001812B0WaitUntilFiringState(this),
			0xc9, 0xc9, 0);
	}
}
