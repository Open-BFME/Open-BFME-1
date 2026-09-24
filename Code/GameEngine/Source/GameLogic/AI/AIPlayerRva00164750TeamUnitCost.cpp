// ?rva00164750@AIPlayer@@IAE_NPAVTeamPrototype@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// BFME retail RVA 0x00164750, 476 bytes: AIPlayer one-argument TeamPrototype unit/cost check; method name unproven.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Player;

struct TCreateUnitsInfo
{
	Int minUnits;
	Int maxUnits;
	AsciiString unitThingName;
};

struct TeamTemplateInfo
{
	TCreateUnitsInfo m_unitsInfo[7];
	Int m_numUnitsInfo;
};

class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo() const
	{
		return &m_teamTemplate;
	}

private:
	char m_prefix00[0x130];
	TeamTemplateInfo m_teamTemplate;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeBuildIndexSetter
{
public:
	Int set(Int value);
};

class TeamState00164750
{
public:
	char m_prefix00[4];
	unsigned char *m_templateInfo;
	char m_prefix08[0x31 - 8];
	unsigned char m_active31;
	char m_prefix32[0xe4 - 0x32];
	unsigned char m_flagE4;
	Bool m_flagE5;
};

class ObjectState00164750 : public Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_prefix08[0x88 - 8];
	ObjectState00164750 *m_next;
	char m_prefix8c[0x1a4 - 0x8c];
	unsigned int m_status1A4;
	char m_prefix1a8[0x204 - 0x1a8];
	unsigned char *m_state204;
	char m_prefix208[0x23c - 0x208];
	TeamState00164750 *m_team;

	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
};

class GameLogic00164750 : public GameLogic
{
};

class ThingFactory00164750 : public BfmeThingFactory
{
};

class Money00164750
{
public:
	unsigned int m_money;
};

class BuildIndexSetter00164750 : public BfmeBuildIndexSetter
{
};

class Player
{
public:
	char m_prefix00[0x4c];
	Money00164750 m_money;
	char m_prefix50[0x230 - 0x50];
	TeamState00164750 *m_defaultTeam;
	char m_prefix234[0x684 - 0x234];
	BuildIndexSetter00164750 m_buildIndexSetter684;
};

class AIPlayer
{
protected:
	Bool rva00164750(TeamPrototype *proto);
	ObjectState00164750 *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);

private:
	char m_prefix00[0x0c];
	Player *m_player;
};

#define TheThingFactory (*(ThingFactory00164750 **)0x012EF1D8)
#define TheGameLogic (*(GameLogic00164750 **)0x012F0898)
#define BFME_UINT32_SCALE (*(const float *)0x01075358)

extern void j_0002b62f();

static ObjectState00164750 *bfmeFindFactory00164750(AIPlayer *player,
	const ThingTemplate *thing, Bool busyOK, Int *buildIndex)
{
	typedef ObjectState00164750 *(AIPlayer::*Call)(const ThingTemplate *, Bool,
		Int *);
	union { void (*raw)(); Call member; } target;
	target.raw = j_0002b62f;
	return (player->*target.member)(thing, busyOK, buildIndex);
}

Bool AIPlayer::rva00164750(TeamPrototype *proto)
{
	const TCreateUnitsInfo *unitInfo =
		&proto->getTemplateInfo()->m_unitsInfo[0];
	Bool result = true;
	float totalCost = 0.0f;
	for (Int i = 0; i < proto->getTemplateInfo()->m_numUnitsInfo; ++i)
	{
		const ThingTemplate *thing =
			TheThingFactory->findTemplate(unitInfo[i].unitThingName);
		if (unitInfo[i].maxUnits <= 0)
			continue;

		Int count = 0;
		for (ObjectState00164750 *object =
			static_cast<ObjectState00164750 *>(TheGameLogic->getFirstObject()); object; object = object->m_next)
		{
			if (!object->getTemplate()->isEquivalentTo(thing))
				continue;
			if (object->getControllingPlayer() != m_player)
				continue;

			TeamState00164750 *team = object->m_team;
			Bool eligible = false;
			if (team == m_player->m_defaultTeam)
				eligible = true;
			if (!team->m_active31)
				continue;
			if (team->m_templateInfo[0x1bc])
				eligible = true;
			if (team->m_flagE4 != 0)
				eligible = team->m_flagE5;
			if (!eligible)
				continue;
			if (object->m_state204 && !object->m_state204[0x32c])
				continue;
			if (object->m_status1A4 & 8)
				continue;
			++count;
		}

		if (count >= unitInfo[i].minUnits)
			continue;
		Int buildIndex;
		if (!bfmeFindFactory00164750(this, thing, false, &buildIndex))
		{
			result = false;
			break;
		}
		Int thingCost;
		if (buildIndex == -1)
			thingCost = thing->calcCostToBuild(m_player, buildIndex);
		else
			thingCost = m_player->m_buildIndexSetter684.set(buildIndex);
		totalCost += (float)((unitInfo[i].minUnits - count) * thingCost);
		if ((float)m_player->m_money.m_money < totalCost)
		{
			result = false;
			break;
		}
	}
	return result;
}
