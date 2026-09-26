// cl: /O2 /Ob0
//
// thiscall @ 0x0016C990, 86 bytes. Same State layout as chooseWeapon (machine
// at +0x1C, owner at machine+0x10). Object::getCurrentWeapon(0); null is
// STATE_FAILURE. If WeaponTemplate+0x68 is non-negative and Weapon+0x2C plus
// that exceeds TheGameLogic frame (unsigned), STATE_CONTINUE. If
// Weapon::getStatus is 5, STATE_CONTINUE. Else SUCCESS when +0x68 is
// negative, otherwise FAILURE.

enum WeaponSlotType
{
	PRIMARY_WEAPON
};

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	WEAPON_STATUS_COUNT
};

class Weapon
{
public:
	WeaponStatus getStatus() const;

	char m_lead[4];
	char *m_template;
	char m_mid[0x24];
	int m_2C;
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
};

class StateMachine
{
public:
	char m_lead[0x10];
	Object *m_owner;
};

class GameLogicFrameSlice
{
public:
	char m_lead[0x3C];
	int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

class Rva0016C990State
{
public:
	int checkReady();

private:
	char m_lead[0x1C];
	StateMachine *m_machine;
};

// ?checkReady@Rva0016C990State@@QAEHXZ
int Rva0016C990State::checkReady()
{
	Weapon *weapon = m_machine->m_owner->getCurrentWeapon(0);
	if (!weapon)
		return -2;

	int stamp = *(int *)(weapon->m_template + 0x68);
	if (stamp >= 0 && (unsigned)(weapon->m_2C + stamp) > (unsigned)TheGameLogic->m_frame)
		return 0;
	else
	{
		if (weapon->getStatus() == WEAPON_STATUS_COUNT)
			return 0;
		stamp = *(int *)(weapon->m_template + 0x68);
		return (stamp < 0) ? -1 : -2;
	}
}
