// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction for AIWaitUntilFinishedFiringState::onEnter.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponLockType
{
	LOCKED_TEMPORARILY = 1
};

enum DisabledType
{
	DISABLED_RELOADING = 8
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	char m_templateFields[ 0x68 ];
	int m_maxShotCount;
	int m_clipReloadTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	virtual ~Weapon();

	WeaponTemplate *m_template;
	char m_weaponFields[ 0x04 ];
	WeaponSlotType m_wslot;

	WeaponStatus getStatus() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );
	void setWeaponLock( int slot, int lockType );
	void setDisabledUntil( DisabledType type, unsigned int frame );

	char m_objectFields[ 0x94 ];
	unsigned char m_status94;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	char m_machineFields[ 0x10 ];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	virtual ~State();

	char m_stateFields[ 0x18 ];
	StateMachine *m_machine;

	Object *getMachineOwner()
	{
		return m_machine->m_owner;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_logicFields[ 0x3C ];
	unsigned int m_frame;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

class AIWaitUntilFinishedFiringState : public State
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIWaitUntilFinishedFiringState::onEnter()
{
	Weapon *weapon = getMachineOwner()->getCurrentWeapon( 0 );
	Object *object = getMachineOwner();
	if ( !weapon )
		return STATE_FAILURE;

	if ( weapon->getStatus() == READY_TO_FIRE )
	{
		if ( (object->m_status94 & 0x20) != 0 && (TheGameLogic->m_frame & 1) != 0 )
			return STATE_CONTINUE;
		return STATE_SUCCESS;
	}

	if ( weapon->m_template->m_maxShotCount >= 0 )
		object->setWeaponLock( weapon->m_wslot, LOCKED_TEMPORARILY );
	if ( weapon->m_template->m_clipReloadTime > 0 )
		object->setDisabledUntil( DISABLED_RELOADING,
			TheGameLogic->m_frame + weapon->m_template->m_clipReloadTime );
	return STATE_CONTINUE;
}
