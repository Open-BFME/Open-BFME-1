// BFME layout reconstruction for retail RVA 0x00178B40.

typedef bool Bool;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Rva00178B40AI
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad00[0x90];
	unsigned char m_status90;
	unsigned char m_pad91[3];
	unsigned char m_status94;
	unsigned char m_pad95[0x16f];
	Rva00178B40AI *m_ai;
	void unidentified_000F20F0(int, int);
};

struct Rva00178B40StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class Rva00178B40WeaponTarget
{
public:
	void setWeapon(float);
};

class Rva00178B40ObjectTarget
{
public:
	void apply(int, int);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

struct Rva00178B40Fields
{
	unsigned char m_pad00[0x1c];
	Rva00178B40StateMachine *m_machine;
};

extern void j_00048ca7();
extern void j_00019c54();
extern void j_00032dee();

class Rva00178B40State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

void Rva00178B40State::onExit(StateExitType status)
{
	Rva00178B40Fields *self = (Rva00178B40Fields *)this;
	Object *owner = self->m_machine->m_owner;
	if ((owner->m_status90 & 1) != 0)
		return;

	{
		Rva00178B40AI *ai = owner->m_ai;
		if (ai)
		{
			typedef void (Rva00178B40WeaponTarget::*WeaponCall)(float);
			union { void *asVoid; WeaponCall asMember; } weaponCast;
			weaponCast.asVoid = (void *)j_00048ca7;
			(reinterpret_cast<Rva00178B40WeaponTarget *>(ai)->*weaponCast.asMember)(999999.0f);
		}

		if ((owner->m_status94 & 0x20) == 0)
		{
			self->m_machine->m_owner->unidentified_000F20F0(0x4a, 0);

			typedef void (Rva00178B40ObjectTarget::*ObjectCall)(int, int);
			union { void *asVoid; ObjectCall asMember; } secondCast;
			secondCast.asVoid = (void *)j_00032dee;
			(reinterpret_cast<Rva00178B40ObjectTarget *>(self->m_machine->m_owner)->*secondCast.asMember)(0x4a, 0);
		}
	}

	AIInternalMoveToState::onExit(status);
}
