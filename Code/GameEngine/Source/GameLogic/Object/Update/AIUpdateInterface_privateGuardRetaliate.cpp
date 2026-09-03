// cl: /DNDEBUG /MD
// readable body of ?privateGuardRetaliate@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Retail 0x002795D0: AIUpdateInterface::privateGuardRetaliate. Null victim
// guard, clear, setGoalObject, setGoalPositionClipped, setState(0x3e), then
// the current weapon's max-shot count at +0x34.

typedef bool Bool;
typedef int Int;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_GUARD_RETALIATE = 0x3E
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	unsigned char m_unmodelled_00[0x34];
	Int m_maxShotCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);

protected:
	virtual void privateGuardRetaliate(Object *victim, const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::privateGuardRetaliate(Object *victim, const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if (!victim)
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	setGoalPositionClipped(pos, cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD_RETALIATE);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
		weapon->m_maxShotCount = maxShotsToFire;
}
