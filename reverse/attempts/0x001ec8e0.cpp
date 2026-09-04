// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@@Z
// partial score=0.25 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::getAbleToAttackSpecificObject (4-arg), retail 0x001EC8E0 size 999.
// Matched Object 3-arg wrapper at 0x001C77B0 calls ILT 0x291D6 -> this body.
// Eligibility half then forwards through ILT 0x1A889 (UseWeapon-merge at 0x001EBEB0).
// Function-local static NameKey "StealthUpdate" is what buys the SEH frame.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class Player;
class Team;
class Module;
class WeaponSet;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
};

extern PlayerList *ThePlayerList;

class BfmeAIInner
{
public:
	unsigned char m_pad[0xB8];
	unsigned char m_flagB8;
};

class BfmeAIRoot
{
public:
	unsigned char m_pad[0x14];
	BfmeAIInner *m_inner;
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	Team *getDefaultTeam();
};

class Team
{
public:
	Relationship getRelationship(const Team *other) const;
};

class StealthUpdate
{
public:
	unsigned char m_pad[0x34];
	Int m_disguisedPlayerIndex;
	Int m_isDisguised;
};

class BfmeContainInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	Player *getApparentControllingPlayer(const Player *observer) const;
};

class BfmeScriptStatus
{
public:
	Bool testBit(Int bit) const;
};

class BfmeWeaponOrTemplate
{
public:
	Bool bfmeAllowsRelationship(Int kind, const void *entry) const;
};

class Object
{
public:
	Bool testStatus(Int status) const;
	Bool isKindOf(Int kind) const;
	Player *getControllingPlayer() const;
	Bool isStealthedAndUndetected(const Player *viewer) const;
	Module *findModule(NameKeyType key) const;
	Relationship getRelationship(const Object *other) const;
	void *getCurrentWeapon(Int unused);
	Team *getTeam() const { return m_team; }

	unsigned char m_pad_00[0x38];
	Coord3D m_position;
	unsigned char m_pad_44[0x90 - 0x44];
	UnsignedInt m_status90;
	unsigned char m_pad_94[0x110 - 0x94];
	BfmeScriptStatus m_scriptStatus;
	unsigned char m_pad_script[0x1FC - 0x110 - 1];
	BfmeContainInterface *m_contain;
	unsigned char m_pad_200[0x214 - 0x200];
	Object *m_containedBy;
	unsigned char m_pad_218[0x23C - 0x218];
	Team *m_team;
	unsigned char m_pad_240[0x343 - 0x240];
	unsigned char m_scriptTargetable;
	unsigned char m_effectivelyDead;
	unsigned char m_status345;
};

class WeaponSet
{
public:
	CanAttackResult getAbleToAttackSpecificObject(
		AbleToAttackType attackType, const Object *source, const Object *victim,
		CommandSourceType commandSource) const;

private:
	CanAttackResult getAbleToUseWeaponAgainstTarget(
		AbleToAttackType attackType, const Object *source, const Object *victim,
		const Coord3D *pos, CommandSourceType commandSource) const;
};

// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@@Z
CanAttackResult WeaponSet::getAbleToAttackSpecificObject(
	AbleToAttackType attackType, const Object *source, const Object *victim,
	CommandSourceType commandSource) const
{
	static NameKeyType stealthKey = TheNameKeyGenerator->nameToKey("StealthUpdate");

	if (source == 0)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim == 0)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (source->m_effectivelyDead & 1)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim->m_effectivelyDead & 1)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (source->m_status90 & 1)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim->m_status90 & 1)
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim == source)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus(0x32))
		return ATTACKRESULT_NOT_POSSIBLE;

	unsigned char sameOwnerForceAttack = 0;
	if (source->getControllingPlayer() == victim->getControllingPlayer())
	{
		sameOwnerForceAttack = 1;
		if (((Int)attackType & 1) == 0)
			sameOwnerForceAttack = 0;
	}

	Int ignoreStealth = 0;
	if (source->testStatus(0x24))
		ignoreStealth = 1;
	if ((~ignoreStealth) & victim->m_status345)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->isKindOf(0x35))
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim->testStatus(0x3B))
		return ATTACKRESULT_NOT_POSSIBLE;
	if (victim->testStatus(0x1A) && commandSource == CMD_FROM_AI)
		return ATTACKRESULT_NOT_POSSIBLE;

	unsigned char allowStealth = 1;
	if (source->testStatus(0x1B) || sameOwnerForceAttack)
		allowStealth = 0;

	if ((Int)attackType & 1)
	{
		if (victim->isKindOf(0x57))
		{
			StealthUpdate *disguise = (StealthUpdate *)victim->findModule(stealthKey);
			if (disguise != 0 && disguise->m_isDisguised)
				allowStealth = 0;
		}
	}

	if (allowStealth
		&& victim->isStealthedAndUndetected(source->getControllingPlayer()))
	{
		if (!victim->isKindOf(0x57))
			return ATTACKRESULT_NOT_POSSIBLE;

		StealthUpdate *update = (StealthUpdate *)victim->findModule(stealthKey);
		if (update != 0 && update->m_isDisguised)
		{
			Player *ourPlayer = source->getControllingPlayer();
			Player *otherPlayer = ThePlayerList->getNthPlayer(update->m_disguisedPlayerIndex);
			if (ourPlayer != 0 && otherPlayer != 0
				&& ourPlayer->getRelationship(otherPlayer->getDefaultTeam()) != ENEMIES)
				return ATTACKRESULT_NOT_POSSIBLE;
		}
	}

	unsigned char reject = 0;
	if (source->isKindOf(0x36) && source->isKindOf(2) && victim->isKindOf(0x8B)
		&& source->m_scriptStatus.testBit(0x10C))
		reject = 1;

	void *curWeapon = ((Object *)source)->getCurrentWeapon(0);
	if (curWeapon != 0)
	{
		BfmeWeaponOrTemplate *tmpl = *(BfmeWeaponOrTemplate **)((char *)curWeapon + 4);
		if (tmpl->bfmeAllowsRelationship(6, curWeapon))
			reject = 1;
	}

	Relationship r = ENEMIES;
	if (!reject)
		r = source->getRelationship(victim);

	if (source->isKindOf(0x36))
	{
		if (r == ALLIES)
			return ATTACKRESULT_NOT_POSSIBLE;
		if (victim->isKindOf(7))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (!(victim->isKindOf(0x5D) && TheAIParseDefinitionAI->m_inner->m_flagB8)
		&& r != ENEMIES
		&& ((Int)attackType & 1) == 0
		&& !reject
		&& commandSource == CMD_FROM_PLAYER
		&& (victim->m_scriptTargetable & 0x10) == 0)
		return ATTACKRESULT_NOT_POSSIBLE;

	Object *victimsContainer = victim->m_containedBy;
	BfmeContainInterface *containerContain = victimsContainer
		? victimsContainer->m_contain : 0;

	if (victim->testStatus(0x3B))
	{
		if (containerContain == 0)
			return ATTACKRESULT_NOT_POSSIBLE;
		if (source->m_containedBy != victimsContainer)
			return ATTACKRESULT_NOT_POSSIBLE;
		if (!victim->testStatus(0x24) || !source->testStatus(0x24))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (((Int)attackType & 1) == 0)
	{
		BfmeContainInterface *victimContain = victim->m_contain;
		if (victimContain != 0)
		{
			Player *apparent = victimContain->getApparentControllingPlayer(
				source->getControllingPlayer());
			if (apparent != 0
				&& source->getTeam()->getRelationship(apparent->getDefaultTeam()) != ENEMIES
				&& commandSource == CMD_FROM_PLAYER
				&& (victim->m_scriptTargetable & 0x10) == 0)
				return ATTACKRESULT_NOT_POSSIBLE;
		}
	}

	return getAbleToUseWeaponAgainstTarget(
		attackType, source, victim, &victim->m_position, commandSource);
}
