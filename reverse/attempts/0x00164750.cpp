// ?d_00164750@@YAXXZ
// partial score=0.78 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// BFME retail RVA 0x00164750, 476 bytes.
//
// The only named callers identify this as AIPlayer's one-argument
// TeamPrototype build check.  No surviving declaration proves the original
// method name, so the address remains in the member name.

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

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride();
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Int calcCostToBuild(const Player *player, Int buildIndex) const;


	void *m_vtable;
	ThingTemplate *m_nextOverride;
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
	unsigned char m_flagE5;
};

class ObjectState00164750
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

	Player *getControllingPlayer() const;
};

class GameLogic00164750
{
public:
	ObjectState00164750 *getFirstObject();
};

class ThingFactory00164750
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Money00164750
{
public:
	unsigned int m_money;
};

class BuildIndexSetter00164750
{
public:
	Int set(Int value);
};

class Player
{
public:
	char m_prefix00[0x4c];
	Money00164750 m_money;
	char m_prefix50[0x230 - 0x50];
	TeamState00164750 *m_defaultTeam;
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

extern void j_00028560();
extern void j_000358be();
extern void j_000022bb();
extern void j_0003e80b();
extern void j_00020824();
extern void j_0002b62f();
extern void j_0000da8a();
extern void j_000237d1();

static const ThingTemplate *bfmeFindTemplate00164750(
	ThingFactory00164750 *factory, const AsciiString &name)
{
	typedef const ThingTemplate *(ThingFactory00164750::*Call)(const AsciiString &);
	union { void (*raw)(); Call member; } target;
	target.raw = j_00028560;
	return (factory->*target.member)(name);
}

static ObjectState00164750 *bfmeFirstObject00164750(GameLogic00164750 *logic)
{
	typedef ObjectState00164750 *(GameLogic00164750::*Call)();
	union { void (*raw)(); Call member; } target;
	target.raw = j_000358be;
	return (logic->*target.member)();
}

static ThingTemplate *bfmeFinalOverride00164750(ThingTemplate *thing)
{
	typedef ThingTemplate *(ThingTemplate::*Call)();
	union { void (*raw)(); Call member; } target;
	target.raw = j_000022bb;
	return (thing->*target.member)();
}

static Bool bfmeEquivalent00164750(ThingTemplate *left,
	const ThingTemplate *right)
{
	typedef Bool (ThingTemplate::*Call)(const ThingTemplate *) const;
	union { void (*raw)(); Call member; } target;
	target.raw = j_0003e80b;
	return (left->*target.member)(right);
}

static Player *bfmeControllingPlayer00164750(
	const ObjectState00164750 *object)
{
	typedef Player *(ObjectState00164750::*Call)() const;
	union { void (*raw)(); Call member; } target;
	target.raw = j_00020824;
	return (object->*target.member)();
}

static ObjectState00164750 *bfmeFindFactory00164750(AIPlayer *player,
	const ThingTemplate *thing, Bool busyOK, Int *buildIndex)
{
	typedef ObjectState00164750 *(AIPlayer::*Call)(const ThingTemplate *, Bool,
		Int *);
	union { void (*raw)(); Call member; } target;
	target.raw = j_0002b62f;
	return (player->*target.member)(thing, busyOK, buildIndex);
}

static Int bfmeCost00164750(const ThingTemplate *thing, const Player *player,
	Int buildIndex)
{
	typedef Int (ThingTemplate::*Call)(const Player *, Int) const;
	union { void (*raw)(); Call member; } target;
	target.raw = j_0000da8a;
	return (thing->*target.member)(player, buildIndex);
}

static Int bfmeSetBuildIndex00164750(BuildIndexSetter00164750 *setter,
	Int buildIndex)
{
	typedef Int (BuildIndexSetter00164750::*Call)(Int);
	union { void (*raw)(); Call member; } target;
	target.raw = j_000237d1;
	return (setter->*target.member)(buildIndex);
}

Bool AIPlayer::rva00164750(TeamPrototype *proto)
{
	Bool result = true;
	float totalCost = 0.0f;
	Int i = 0;
	const TCreateUnitsInfo *firstUnit =
		&proto->getTemplateInfo()->m_unitsInfo[0];
	if (proto->getTemplateInfo()->m_numUnitsInfo <= i)
		return result;
	const TCreateUnitsInfo *unit = firstUnit;
	do
	{
		const ThingTemplate *thing =
			bfmeFindTemplate00164750(TheThingFactory, unit->unitThingName);
		if (unit->maxUnits <= 0)
			goto nextUnit;

		Int count = 0;
		for (ObjectState00164750 *object =
			bfmeFirstObject00164750(TheGameLogic); object; object = object->m_next)
		{
			ThingTemplate *objectThing = object->m_template;
			ThingTemplate *resolvedThing = 0;
			if (objectThing)
			{
				if (objectThing->m_nextOverride)
					resolvedThing = bfmeFinalOverride00164750(
						objectThing->m_nextOverride);
				else
					resolvedThing = objectThing;
			}
			if (!bfmeEquivalent00164750(resolvedThing, thing))
				continue;
			if (bfmeControllingPlayer00164750(object) != m_player)
				continue;

			TeamState00164750 *team = object->m_team;
			unsigned char eligible = false;
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

		if (count >= unit->minUnits)
			goto nextUnit;
		Int buildIndex;
		if (!bfmeFindFactory00164750(this, thing, false, &buildIndex))
			return false;
		Int thingCost;
		if (buildIndex == -1)
			thingCost = bfmeCost00164750(thing, m_player, -1);
		else
			thingCost = bfmeSetBuildIndex00164750(
				(BuildIndexSetter00164750 *)((char *)m_player + 0x684), buildIndex);
		totalCost += (float)((unit->minUnits - count) * thingCost);
		if ((float)m_player->m_money.m_money < totalCost)
			return false;
	nextUnit:
		++i;
		++unit;
	} while (i < proto->getTemplateInfo()->m_numUnitsInfo);
	return result;
}
