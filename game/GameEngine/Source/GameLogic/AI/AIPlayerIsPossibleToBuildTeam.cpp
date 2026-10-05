// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME retail RVA 0x001645B0, 326 bytes.
//
// The TeamPrototype unit loop and AIPlayer declaration identify the cost helper.
//
// BFME stores seven 12-byte unit records at TeamPrototype+0x130 and keeps the
// count at +0x184. The build-idea override also reads the name at +0x14 and
// maximum instance count at +0x1C4.

extern char Rva006A16B0Empty[];

template <typename T>
class StringBase
{
    friend class AsciiString;
    struct Data
    {
        int m_refCount;
        int m_length;
        T m_text[1];
    };
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase &other);
    ~StringBase();
    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void format(AsciiString fmt, ...);
    const char *str() const
    {
        return m_data != 0 ? m_data->m_text : Rva006A16B0Empty;
    }
};

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
	char m_prefix[0x3c];
	Int m_maxInstances;
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

	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const
	{
		return m_name;
	}

private:
	char m_prefix[0x14];
	AsciiString m_name;
	char m_pad[0x118];
	BfmeTeamTemplateInfo m_teamTemplate;
};

class ThingTemplate
{
public:
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

class Team;
class Gen_001604e0
{
public:
	Int m();
};

class TeamInQueue
{
public:
	TeamInQueue *getNext()
	{
		return (TeamInQueue *)((Gen_001604e0 *)this)->m();
	}
	char m_prefix[0x1c];
	Team *m_team;
};

class Team
{
public:
	TeamPrototype *getPrototype() const
	{
		return *(TeamPrototype **)((const char *)this + 4);
	}
};

extern void j_000077b1();

class AIPlayer
{
protected:
	virtual Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);
	Bool isPossibleToBuildTeam(TeamPrototype *proto,
		Bool requireIdleFactory, Bool &notEnoughMoney);
	Bool rva00164750Check(TeamPrototype *proto)
	{
		typedef Bool (AIPlayer::*Call)(TeamPrototype *);
		union { void (*raw)(); Call member; } call;
		call.raw = j_000077b1;
		return (this->*call.member)(proto);
	}

	Object *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);

private:
	TeamInQueue *m_teamBuildQueue;
	char m_prefix[4];
	Player *m_player;
};

extern const float g_rva0107533C;

extern AI *TheAI;
class ThingFactory;
extern ThingFactory *TheThingFactory;

extern void j_00028560();
extern void j_000237d1();
extern void j_0002b62f();
extern void j_0000da8a();

static const ThingTemplate *bfmeFindTemplate(const AsciiString *name)
{
	typedef const ThingTemplate *(BfmeThingFactory::*FindTemplateCall)(
		const AsciiString &);
	union { void (*raw)(void); FindTemplateCall member; } call;
	call.raw = j_00028560;
	return (((BfmeThingFactory *)TheThingFactory)->*call.member)(*name);
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
			{
				typedef Int (ThingTemplate::*CalcCostCall)(const Player *,
					Int) const;
				union { void (*raw)(void); CalcCostCall member; } call;
				call.raw = j_0000da8a;
				thingCost = (thing->*call.member)(m_player, -1);
			}
			else
				thingCost = ((BfmeBuildIndexSetter *)((char *)m_player + 0x684))->set(buildIndex);
			if ((*(const unsigned int *)((const char *)thing + 0xd8) & 0x10000000) != 0)
				thingCost = 0;
			cost = (Int)(cost + thingCost *
				((float)(unitInfo->maxUnits + unitInfo->minUnits()) *
					g_rva0107533C));
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

class GlobalData
{
public:
	char m_prefix[0xa88];
	Int m_debugAI;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;

// AIPlayer's vtable at 0x010968B0 routes slot 25 through ILT 0x000320EC to this body.
//
// This method shares a source file with isPossibleToBuildTeam, so MSVC sees the matched helper body when it allocates stack slots.
Bool AIPlayer::isAGoodIdeaToBuildTeam(TeamPrototype *proto)
{
	if (!proto->evaluateProductionCondition())
		return false;

	if (proto->countTeamInstances() >= proto->getTemplateInfo()->m_maxInstances)
	{
		if (TheWritableGlobalData->m_debugAI)
		{
			AsciiString str;
			str.format(AsciiString("Team %s not chosen - %d already exist."),
				proto->getName().str(), proto->countTeamInstances());
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;
	}

	for (TeamInQueue *team = m_teamBuildQueue; team; team = team->getNext())
		if (team->m_team->getPrototype() == proto)
			return false;

	if (rva00164750Check(proto))
		return true;

	Bool needMoney;
	if (!isPossibleToBuildTeam(proto, true, needMoney))
	{
		if (TheWritableGlobalData->m_debugAI)
		{
			AsciiString str;
			if (needMoney)
				str.format(AsciiString("Team %s not chosen - Not enough money."), proto->getName().str());
			else
				str.format(AsciiString("Team %s not chosen - Factory/tech missing or busy."), proto->getName().str());
			TheScriptEngine->AppendDebugMessage(str, false);
		}
		return false;
	}
	return true;
}
