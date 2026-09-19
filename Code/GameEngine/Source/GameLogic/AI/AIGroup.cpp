// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;

struct BfmeListNodeBase
{
	BfmeListNodeBase *next;
	BfmeListNodeBase *prev;
};

struct BfmeObjectNode : public BfmeListNodeBase
{
	Object *value;
};

struct ContainedItemsList
{
	BfmeListNodeBase *head;
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C();
	virtual void orderSlavesToAttackPosition(const Coord3D *, Int, CommandSourceType);
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual Bool isPassengerAllowedToFire();
	virtual void slotA4(); virtual void slotA8(); virtual void slotAC(); virtual void slotB0();
	virtual void slotB4(); virtual void slotB8(); virtual void slotBC(); virtual void slotC0();
	virtual void slotC4(); virtual void slotC8(); virtual void slotCC(); virtual void slotD0();
	virtual void slotD4(); virtual void slotD8(); virtual void slotDC(); virtual void slotE0();
	virtual void slotE4(); virtual void slotE8(); virtual void slotEC(); virtual void slotF0();
	virtual void slotF4(); virtual void slotF8(); virtual void slotFC(); virtual void slot100();
	virtual const ContainedItemsList *getContainedItemsList();
};

class AICommandInterface
{
public:
	void aiAttackPosition(const Coord3D *, Int, CommandSourceType);
};

class BfmeAIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	virtual ~Object();
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,
		const Object *, CommandSourceType, WeaponSlotType) const;

	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_position; }

	char m_pad04[0x34];
	Coord3D m_position;
	char m_pad44[0x1B8];
	ContainModuleInterface *m_contain;
	char m_pad200[4];
	BfmeAIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupAttackPosition(const Coord3D *, Int, CommandSourceType);
	UnsignedInt getID( void );

	std::list<Object *> m_memberList;
	char m_layout[0x14 - sizeof(std::list<Object *>)];
	UnsignedInt m_id;
};

UnsignedInt AIGroup::getID( void )
{
	return m_id;
}

void AIGroup::groupAttackPosition(const Coord3D *pos, Int maxShotsToFire,
	CommandSourceType cmdSource)
{
	Coord3D attackPos;
	if (pos)
		attackPos = *pos;

	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		if (!pos)
			attackPos.set((*i)->getPosition());

		ContainModuleInterface *contain = (*i)->getContain();
		if (contain && contain->isPassengerAllowedToFire())
		{
			const ContainedItemsList *items = contain->getContainedItemsList();
			if (items)
			{
				for (BfmeListNodeBase *it = items->head->next;
					it != items->head; it = it->next)
				{
					Object *garrisonedMember = ((BfmeObjectNode *)it)->value;
					CanAttackResult result =
						garrisonedMember->getAbleToAttackSpecificObject(
							ATTACK_NEW_TARGET, 0,
							(CommandSourceType)(unsigned int)&attackPos,
							(WeaponSlotType)cmdSource);
					if (result == ATTACKRESULT_POSSIBLE
						|| result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
					{
						BfmeAIUpdateInterface *memberAI = garrisonedMember->m_ai;
						if (memberAI)
							memberAI->m_commands.aiAttackPosition(
								&attackPos, maxShotsToFire, cmdSource);
					}
				}
			}
		}

		SpawnBehaviorInterface *spawnInterface =
			(*i)->getSpawnBehaviorInterface();
		if (spawnInterface)
			spawnInterface->orderSlavesToAttackPosition(
				&attackPos, maxShotsToFire, cmdSource);

		BfmeAIUpdateInterface *ai = (*i)->m_ai;
		if (ai)
			ai->m_commands.aiAttackPosition(&attackPos, maxShotsToFire,
				cmdSource);
	}
}
