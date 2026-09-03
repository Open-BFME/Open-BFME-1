// cl: /DNDEBUG /MD /EHsc
// stlport
// readable body of ?onExit@AIAttackFireWeaponState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout reconstruction for AIAttackFireWeaponState::onExit.

typedef bool Bool;

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponStatus
{
	PRE_ATTACK = 4
};

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags()
	{
	}

	BitFlags(_dummy_kInit, int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags(_dummy_kInit, int idx1, int idx2)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
	}

	void set(int idx)
	{
		m_bits.set(idx);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	WeaponStatus getStatus(void) const;
	void setPreAttackFinishedFrame(unsigned frame)
	{
		m_whenPreAttackFinished = frame;
		getStatus();
	}

private:
	unsigned char m_unreconstructed_00[0x1c];
	unsigned m_whenPreAttackFinished;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	virtual ~State();

protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;

	Object *getMachineOwner(void) const
	{
		return m_machine->m_owner;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackFireWeaponState : public State
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@AIAttackFireWeaponState@@UAEXW4StateExitType@@@Z
void AIAttackFireWeaponState::onExit(StateExitType status)
{
	register Object *obj = getMachineOwner();
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 13), false);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 27), false);

	volatile Weapon *weapon = obj->getCurrentWeapon((WeaponSlotType *)0);
	if (weapon && ((Weapon *)weapon)->getStatus() == PRE_ATTACK)
		((Weapon *)weapon)->setPreAttackFinishedFrame(0);

	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 81), false);
}
