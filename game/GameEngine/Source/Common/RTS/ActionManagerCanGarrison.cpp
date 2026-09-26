// cl: /DNDEBUG /MD /EHsc
//
// BFME's ActionManager::canGarrison at retail RVA 0x000C5D00.  This local ABI
// slice keeps the BFME Object offsets and ContainModuleInterface slots rather
// than relying on the narrower Zero Hour header.

typedef bool Bool;
typedef int Int;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI, CMD_FROM_DOZER, CMD_DEFAULT_SWITCH_WEAPON };

// BFME KindOfType values proven by the three retail immediate operands.
enum KindOfType
{
	KINDOF_INFANTRY = 8,
	KINDOF_NO_GARRISON = 0x1B,
	KINDOF_STRUCTURE = 7
};

enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class Team;

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType type) const;
};

class Object;

class ContainModuleInterface
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual Bool isGarrisonable() const;
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual Bool isValidContainerFor(const Object *obj, Bool checkCapacity) const;
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void slot_0bc();
	virtual void slot_0c0();
	virtual void slot_0c4();
	virtual void slot_0c8();
	virtual void slot_0cc();
	virtual void slot_0d0();
	virtual void slot_0d4();
	virtual void slot_0d8();
	virtual void slot_0dc();
	virtual void slot_0e0();
	virtual void slot_0e4();
	virtual void slot_0e8();
	virtual void slot_0ec();
	virtual void slot_0f0();
	virtual void slot_0f4();
	virtual void slot_0f8();
	virtual void slot_0fc();
	virtual Int getContainCount(Int arg) const;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;

	ContainModuleInterface *getContain() const
	{
		return m_contain;
	}

	Team *getTeam() const
	{
		return m_team;
	}

private:
	char m_bfmeHead[0x1FC];
	ContainModuleInterface *m_contain;
	char m_bfmeMiddle[0x23C - 0x200];
	Team *m_team;
};

class ActionManager
{
public:
	Bool canGarrison(const Object *obj, const Object *target,
		CommandSourceType commandSource);
};

Bool ActionManager::canGarrison(const Object *obj, const Object *target,
	CommandSourceType commandSource)
{
	if (!(obj && target))
		return false;

	if (obj->isKindOf(KINDOF_INFANTRY) == false ||
		obj->isKindOf(KINDOF_NO_GARRISON))
		return false;

	if (target->isKindOf(KINDOF_STRUCTURE) == false)
		return false;

	ContainModuleInterface *objCMI = obj->getContain();
	if (!objCMI)
		return false;

	ContainModuleInterface *cmi = target->getContain();
	if (cmi == 0)
		return false;

	if (cmi->isGarrisonable() == false)
		return false;

	if (obj->getControllingPlayer() == target->getControllingPlayer())
	{
		return cmi->isValidContainerFor(obj, true);
	}

	if (obj->getControllingPlayer()->getRelationship(target->getTeam()) == NEUTRAL)
	{
		return (cmi->getContainCount(0) == 0 &&
			cmi->isValidContainerFor(obj, true));
	}

	return false;
}
