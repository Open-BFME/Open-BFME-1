// ?report@BFMEReportDamageSource@@QAEXPAVObject@@H@Z
// partial score=0.76 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc
//
// BFMEReportDamageSource::report, retail RVA 0x001C9490 (426 bytes).
//
// Identity is established by the existing report@BFMEReportDamageSource pin:
// AIMoveToPositionAndDieState, SpawnBehavior, LifetimeUpdate, BfmeUnitCN and
// RespawnBodyModuleData all call this exact body with an Object owner and a
// setting.  The retail body is the complete 426-byte range ending at ret 8;
// it is not a prefix of the adjacent 0x001C96B0 body.
//
// This TU keeps the BFME Object/Player/ScoreKeeper layouts local.  The typed
// callees are independently established bodies: Overridable::getFinalOverride
// (0x00087A80 via ILT 0x000022BB), Team::getControllingPlayer (0x000EC8F0 via
// ILT 0x0002369B), Player::getRelationship (0x000D19C0 via ILT 0x0003E77A),
// ScoreKeeper::addObjectBuilt/addObjectDestroyed (0x000EAB00/0x000EA910),
// Player::addSkillPointsForKill (retail body 0x000D9510),
// Player::doBountyForKill (0x000D5160), Object::getRelationship (ILT
// 0x0004A719), Thing::isKindOf (ILT 0x0003251F), and Object::rva001c9380
// (0x001C9380).  The Player skill-point callee's full retail body and the
// upstream Player declaration are the evidence for its direct-body pin.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum KindOfType
{
	KINDOF_REPORT_FILTER = 0x6c
};

class Object;
class Team;
class Player;
union Rva001C9380VictimArgument;
union Rva001C9380Argument;

// upstream layout: reference/.../Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

// The report arm tests bit 15 of the final override's word at +0xcc.
// Keeping the override chain as a real typed view gives the call at 0x22bb its
// proven ABI while preserving the BFME field offset.
class ThingTemplate : public Overridable
{
public:
	Bool hasReportFilterFlag(void) const
	{
		return (m_reportFlags & 0x8000U) != 0;
	}

	unsigned char m_pad08[0xcc - 0x08];
	UnsignedInt m_reportFlags;
};

class AsciiString
{
public:
	int compare(const char *text) const;
};

// upstream layout: reference/.../Include/GameLogic/ScoreKeeper.h
class ScoreKeeper
{
public:
	void addObjectBuilt(Object *object);
	void addObjectDestroyed(const Object *object);
};

// Team's controlling-player ILT and Player's relationship body are both
// existing named identities, not guessed virtual-slot labels.
class Team
{
public:
	Player *getControllingPlayer(void) const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	Bool addSkillPointsForKill(const Object *killer, const Object *victim);
	void doBountyForKill(const Object *killer, const Object *victim);

	const AsciiString &getSide(void) const
	{
		return m_side;
	}

	Team *getDefaultTeam(void) const
	{
		return m_defaultTeam;
	}

	ScoreKeeper *getScoreKeeper(void)
	{
		return &m_scoreKeeper;
	}

private:
	unsigned char m_pad00[0x28];
	AsciiString m_side;
	unsigned char m_pad2c[0x230 - 0x2c];
	Team *m_defaultTeam;
	unsigned char m_pad234[0x348 - 0x234];
	ScoreKeeper m_scoreKeeper;
};

class Thing
{
public:
	virtual ~Thing();

	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *templateObject = m_template;
		if (templateObject == 0)
			return 0;
		if (templateObject->m_nextOverride != 0)
			templateObject = (const ThingTemplate *)templateObject->m_nextOverride->getFinalOverride();
		return templateObject;
	}

	Bool isKindOf(KindOfType kind) const;

	Bool hasReportBeenCounted(void) const
	{
		return m_reported342 != 0;
	}

	void markReportCounted(void)
	{
		m_reported342 = 1;
	}

	ThingTemplate *m_template;
	unsigned char m_pad08[0x214 - 0x08];
	Object *m_containedBy;
	unsigned char m_pad218[0x23c - 0x218];
	Team *m_team;
	unsigned char m_pad240[0x342 - 0x240];
	unsigned char m_reported342;
	unsigned char m_pad343[0x378 - 0x343];
	UnsignedInt m_reportCount378;
	UnsignedInt m_reportCount37c;
};

class Object : public Thing
{
public:
	Team *getTeam(void) const
	{
		return m_team;
	}

	Relationship getRelationship(const Object *other) const;
	void rva001c9380(Rva001C9380VictimArgument victim, Rva001C9380Argument allow);
};

union Rva001C9380VictimArgument
{
	Object *object;
	int experience;
	float gain;
};

union Rva001C9380Argument
{
	Bool allow;
	float multiplier;
};

class StatsCollector
{
public:
	unsigned char m_pad00[0x24];
	UnsignedInt m_alliesKilled;
	UnsignedInt m_neutralsKilled;
	UnsignedInt m_enemiesKilled;
};

class PlayerList
{
public:
	unsigned char m_pad00[0x0c];
	Player *m_localPlayer;
};

extern StatsCollector *TheStatsCollector;
extern PlayerList *ThePlayerList;
extern const char g_bfmeSideNameC1294[];
extern const char g_bfmeSideNameD1294[];

class BFMEReportDamageSource : public Object
{
public:
	void report(Object *owner, int setting);
};

// ?report@BFMEReportDamageSource@@QAEXPAVObject@@H@Z
void BFMEReportDamageSource::report(Object *owner, int setting)
{
	if (*(const unsigned char *)((const unsigned char *)owner + 0x342) != 0)
		return;

	Object *source = (Object *)this;
	bool settingOne = setting == 1;
	*(unsigned char *)((unsigned char *)owner + 0x342) = 1;
	if (!settingOne && setting != 2)
		return;

	const ThingTemplate *templateObject = owner->getTemplate();
	if ((*(const UnsignedInt *)((const unsigned char *)templateObject + 0xcc) & 0x8000U) != 0)
		return;

	Player *ownerPlayer = 0;
	if (owner->getTeam() != 0)
		ownerPlayer = owner->getTeam()->getControllingPlayer();
	Player *sourcePlayer = 0;
	if (source->m_team != 0)
		sourcePlayer = source->m_team->getControllingPlayer();

	StatsCollector *stats = TheStatsCollector;
	if (stats != 0 && ThePlayerList != 0
		&& ThePlayerList->m_localPlayer == sourcePlayer
		&& sourcePlayer != 0)
	{
		if (ownerPlayer != 0)
		{
			Relationship relationship = sourcePlayer->getRelationship(ownerPlayer->getDefaultTeam());
			if (relationship == ENEMIES)
				++stats->m_enemiesKilled;
			else if (relationship == ALLIES)
				++stats->m_alliesKilled;
			else
				++stats->m_neutralsKilled;
		}
		else
		{
			++stats->m_neutralsKilled;
		}
	}

	if (ownerPlayer != 0)
		ownerPlayer->getScoreKeeper()->addObjectBuilt(owner);

	if (getRelationship(owner) != ENEMIES)
		goto finish;
	if (sourcePlayer == ownerPlayer)
		goto finish;

	if (sourcePlayer != 0)
	{
		++source->m_reportCount37c;
		++source->m_reportCount378;
		if (source->m_containedBy != 0 && source->m_containedBy->isKindOf(KINDOF_REPORT_FILTER))
		{
			++source->m_containedBy->m_reportCount37c;
			++source->m_containedBy->m_reportCount378;
		}

		sourcePlayer->getScoreKeeper()->addObjectDestroyed(owner);
		sourcePlayer->addSkillPointsForKill((const Object *)this, owner);
		sourcePlayer->doBountyForKill((const Object *)this, owner);
	}

	if (ownerPlayer != 0)
	{
		const AsciiString &side = ownerPlayer->getSide();
		if (side.compare(g_bfmeSideNameC1294) == 0
			|| side.compare(g_bfmeSideNameD1294) == 0)
			ownerPlayer->addSkillPointsForKill((const Object *)this, owner);
	}

finish:
	Rva001C9380VictimArgument victim;
	victim.object = owner;
	Rva001C9380Argument allow;
	allow.allow = 0;
	rva001c9380(victim, allow);
}
