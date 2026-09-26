// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME retail RVA 0x001645B0, 326 bytes.
//
// The declared AIPlayer method and the TeamPrototype loop identify this body.
// BFME stores seven 12-byte unit records at TeamPrototype+0x130 and keeps the
// record count at +0x184, so this TU models only the fields that the body reads.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Object;
class Player;

struct TCreateUnitsInfo
{
	Int minUnits;
	Int maxUnits;
	AsciiString unitThingName;
};

struct BfmeTeamTemplateInfo
{
	TCreateUnitsInfo m_unitsInfo[7];
	Int m_numUnitsInfo;
};

struct BfmeUnitInfoCursor
{
	Int maxUnits;
	AsciiString unitThingName;
	char m_suffix[4];

	Int minUnits() const
	{
		return *((const Int *)this - 1);
	}
};

class TeamPrototype
{
public:
	const BfmeTeamTemplateInfo *getTemplateInfo() const
	{
		return &m_teamTemplate;
	}

	const BfmeUnitInfoCursor *getUnitInfo() const
	{
		return (const BfmeUnitInfoCursor *)((const char *)this + 0x134);
	}

private:
	char m_prefix[0x130];
	BfmeTeamTemplateInfo m_teamTemplate;
};

class ThingTemplate
{
public:
	Int calcCostToBuild(const Player *player, Int buildIndex) const;

	private:
		char m_prefix[0xd8];
		unsigned int m_flags;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Money
{
public:
	unsigned int countMoney() const
	{
		return m_money;
	}

private:
	unsigned int m_money;
};

class Player
{
public:
	Money *getMoney()
	{
		return &m_money;
	}

private:
	char m_prefix[0x4c];
	Money m_money;
};

class BfmeBuildIndexSetter
{
public:
	Int set(Int value);

private:
	char m_prefix[0x42c];
	Int m_value;
};

class AI
{
public:
	class Data
	{
	public:
		char m_prefix[0x28];
		float m_teamResourcesToBuild;
	};

	Data *getAiData()
	{
		return m_aiData;
	}

private:
	char m_prefix[0x14];
	Data *m_aiData;
};

class AIPlayer
{
protected:
	Bool isPossibleToBuildTeam(TeamPrototype *proto,
		Bool requireIdleFactory, Bool &notEnoughMoney);

	Object *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);

private:
	char m_prefix[0x0c];
	Player *m_player;
};

extern const float g_bfmeK1253;

#define TheAI (*(AI **)0x012EF214)
#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)

#pragma comment(linker, "/alternatename:?calcCostToBuild@ThingTemplate@@QBEHPBVPlayer@@H@Z=?j_0000da8a@@YAXXZ")

extern void j_00028560();
extern void j_000237d1();
extern void j_0002b62f();

static const ThingTemplate *bfmeFindTemplate(const AsciiString *name)
{
	typedef const ThingTemplate *(BfmeThingFactory::*FindTemplateCall)(
		const AsciiString &);
	union { void (*raw)(void); FindTemplateCall member; } call;
	call.raw = j_00028560;
	return (TheThingFactory->*call.member)(*name);
}

static Object *bfmeFindFactory(AIPlayer *player, const ThingTemplate *thing,
	Bool busyOK, Int *buildIndex)
{
	typedef Object *(AIPlayer::*FindFactoryCall)(const ThingTemplate *,
		Bool, Int *);
	union { void (*raw)(void); FindFactoryCall member; } call;
	call.raw = j_0002b62f;
	return (player->*call.member)(thing, busyOK, buildIndex);
}

// ?isPossibleToBuildTeam@AIPlayer@@IAE_NPAVTeamPrototype@@_NAA_N@Z
Bool AIPlayer::isPossibleToBuildTeam(TeamPrototype *proto,
	Bool requireIdleFactory, Bool &notEnoughMoney)
{
	Bool anyIdle = false;
	Int cost = 0;
	notEnoughMoney = false;
	Int i = 0;
	if (proto->getTemplateInfo()->m_numUnitsInfo <= i)
		goto afterUnits;
	const BfmeUnitInfoCursor *unitInfo = proto->getUnitInfo();
	do
	{
		const ThingTemplate *thing = bfmeFindTemplate(&unitInfo->unitThingName);
		if (thing)
		{
			Int thingCost;
			Int buildIndex;
			if (bfmeFindFactory(this, thing, true, 0) == 0)
				return false;
			if (bfmeFindFactory(this, thing, false, &buildIndex) != 0)
				anyIdle = true;
			if (buildIndex == -1)
				thingCost = thing->calcCostToBuild(m_player, -1);
			else
				thingCost = ((BfmeBuildIndexSetter *)((char *)m_player + 0x684))->set(buildIndex);
			if ((*(const unsigned int *)((const char *)thing + 0xd8) & 0x10000000) != 0)
				thingCost = 0;
			cost = (Int)(cost + thingCost *
				((float)(unitInfo->maxUnits + unitInfo->minUnits()) *
					g_bfmeK1253));
		}
		++i;
		++unitInfo;
	} while (i < proto->getTemplateInfo()->m_numUnitsInfo);

afterUnits:
	cost = (Int)((float)cost * TheAI->getAiData()->m_teamResourcesToBuild);
	if (m_player->getMoney()->countMoney() < (unsigned int)cost)
	{
		notEnoughMoney = true;
		return false;
	}
	if (anyIdle)
		return true;
	if (!requireIdleFactory)
		return true;
	return false;
}
