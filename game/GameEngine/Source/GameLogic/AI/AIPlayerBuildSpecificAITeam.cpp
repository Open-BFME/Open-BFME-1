// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?buildSpecificAITeam@AIPlayer@@UAEXPAVTeamPrototype@@_N@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::buildSpecificAITeam, 0x001650F0, 1341 bytes (the lift stopped at
// 1335; ret 8 at +0x53A, int3 pad after).
// Identity: slot 9 (+0x24) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x0003C79F here, and the matched selectTeamToBuild calls that slot with
// (teamProto, false), as Zero Hour's does. The body is the Zero Hour twin
// with all of its debug lines ("Can't build team '", "Unable to build
// singleton team '", "Note - queueing team '", "Unable to build team '",
// " - starting team build.", " - contains 0 buildable units.").
//
// BFME differences: the one-argument check at 0x00164750 (landed as
// AIPlayer::rva00164750) is asked before isPossibleToBuildTeam and a true
// answer skips it; TeamFactory's findTeam and createInactiveTeam take the
// prototype's two names (+0x10 and +0x14); the new team gets the +0xE7/+0xE6
// flag setter at 0x000EC960 with true; and findScriptByName is ScriptEngine
// slot 53 with an out name that slot 25 (friend_executeAction) then takes.
// That out name is released through StringBase<char>::releaseBuffer
// (0x00887940), as TeamPrototypeScripts.cpp found, so it is a narrow string.
//
// Layout: AIPlayer build queue head +0x04, m_player +0x0C, m_teamDelay +0x24;
// Player can-build-units flag +0x294; TeamPrototype names +0x10/+0x14,
// singleton flag bit 0 of +0x18, template info +0x130 (units info, count
// +0x54), production condition +0x1E8, execute-actions flag +0x1EC; Script
// action +0x20; WorkOrder and TeamInQueue as in
// AIPlayerSelectTeamToReinforce.cpp.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0
#define FALSE 0

extern const AsciiString Rva01336E50EmptyString;

enum { MAX_UNIT_TYPES = 7 };
enum { TEAM_SINGLETON = 0x01 };

// StringBase<char>'s buffer header: refcount, length, capacity, data.
struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

// Retail inlines AsciiString::concat(const AsciiString &) as
// concat(str(), getLength()), each accessor with its own null test.
class BfmeAsciiView
{
public:
	int getLength() const { return m_data ? m_data->m_length : 0; }
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	const BfmeAsciiHeader *m_data;
};

static inline void bfmeConcat(AsciiString &dst, const AsciiString &src)
{
	const BfmeAsciiView &s = *(const BfmeAsciiView *)&src;
	((StringBase<char> *)&dst)->concat(s.str(), s.getLength());
}

class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
struct TCreateUnitsInfo
{
	Int minUnits;
	Int maxUnits;
	AsciiString unitThingName;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamTemplateInfo
{
public:
	TCreateUnitsInfo m_unitsInfo[MAX_UNIT_TYPES];			// +0x00
	Int m_numUnitsInfo;						// +0x54
	char m_unmodelled058[0xb8 - 0x58];
	AsciiString m_productionCondition;				// +0xB8
	Bool m_executeActions;						// +0xBC
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }
	Bool getIsSingleton(void) const { return (m_flags & TEAM_SINGLETON) != 0; }
	const TeamTemplateInfo *getTemplateInfo(void) const { return &m_teamTemplate; }

	char m_unmodelled000[0x10];
	AsciiString m_name;						// +0x10
	AsciiString m_rva14Name;					// +0x14
	Int m_flags;							// +0x18
	char m_unmodelled01c[0x130 - 0x1c];
	TeamTemplateInfo m_teamTemplate;				// +0x130
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	const TeamPrototype *getPrototype(void) const { return m_proto; }
	const AsciiString &getName(void) const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->m_name;
	}
	Bool hasAnyObjects(Bool ignoreBuildings = false) const;
private:
	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
};

class Rva000EC960FlagUpdate
{
public:
	void update(unsigned char set);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name, const AsciiString &name2);
	Team *createInactiveTeam(const AsciiString &name, const AsciiString &name2);
};

extern TeamFactory *TheTeamFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }
private:
	char m_unmodelled000[0x3c];
	UnsignedInt m_frame;						// +0x3C
};

extern GameLogic *TheGameLogic;

// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. Only the field this body reads is described on a
// TU-local view; the real class is never redeclared.
class GlobalData;
struct Rva012ED5C8GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;							// +0xA88
};

extern GlobalData *TheWritableGlobalData;

class ScriptAction;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class Script
{
public:
	ScriptAction *getAction(void) const { return m_action; }
private:
	char m_unmodelled000[0x20];
	ScriptAction *m_action;						// +0x20
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();
#define BFME_VIRTUAL_SLOT10(n) BFME_VIRTUAL_SLOT(n##0) BFME_VIRTUAL_SLOT(n##1) \
	BFME_VIRTUAL_SLOT(n##2) BFME_VIRTUAL_SLOT(n##3) BFME_VIRTUAL_SLOT(n##4) \
	BFME_VIRTUAL_SLOT(n##5) BFME_VIRTUAL_SLOT(n##6) BFME_VIRTUAL_SLOT(n##7) \
	BFME_VIRTUAL_SLOT(n##8) BFME_VIRTUAL_SLOT(n##9)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	BFME_VIRTUAL_SLOT10(0) BFME_VIRTUAL_SLOT10(1)
	BFME_VIRTUAL_SLOT(20) BFME_VIRTUAL_SLOT(21) BFME_VIRTUAL_SLOT(22)
	BFME_VIRTUAL_SLOT(23) BFME_VIRTUAL_SLOT(24)
	virtual void friend_executeAction(AsciiString *scriptName, ScriptAction *pActionHead,
		Team *pThisTeam);					// slot 25, +0x64
	BFME_VIRTUAL_SLOT(26) BFME_VIRTUAL_SLOT(27) BFME_VIRTUAL_SLOT(28)
	BFME_VIRTUAL_SLOT(29) BFME_VIRTUAL_SLOT10(3) BFME_VIRTUAL_SLOT10(4)
	BFME_VIRTUAL_SLOT(50) BFME_VIRTUAL_SLOT(51) BFME_VIRTUAL_SLOT(52)
	virtual Script *findScriptByName(const AsciiString *teamName,
		const AsciiString *scriptName, AsciiString *outName);	// slot 53, +0xD4

	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool getCanBuildUnits(void) { return m_canBuildUnits; }
private:
	char m_unmodelled000[0x294];
	Bool m_canBuildUnits;						// +0x294
};

extern int Gen01096964;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	// Retail WorkOrder's installed table at 0x01096964, stored as
	// TeamInQueueXfer.cpp does; this TU emits no table.
	WorkOrder()
		: m_vptr((void *)&Gen01096964), m_thing(NULL), m_factoryID(0), m_next(NULL),
		  m_numCompleted(0), m_numRequired(1), m_isResourceGatherer(false)
	{
	}

	void *m_vptr;
	const ThingTemplate *m_thing;					// +0x04
	Int m_factoryID;						// +0x08
	WorkOrder *m_next;						// +0x0C
	Int m_numCompleted;						// +0x10
	Int m_numRequired;						// +0x14
	Bool m_required;						// +0x18
	Bool m_isResourceGatherer;					// +0x19
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	TeamInQueue()
		: m_dlink_TeamBuildQueue_prev(NULL), m_dlink_TeamBuildQueue_next(NULL),
		  m_dlink_TeamReadyQueue_prev(NULL), m_dlink_TeamReadyQueue_next(NULL),
		  m_workOrders(NULL), m_priorityBuild(false), m_team(NULL),
		  m_nextTeamInQueue(NULL), m_frameStarted(0), m_sentToStartLocation(false),
		  m_stopQueueing(false), m_reinforcement(false), m_reinforcementID(0)
	{
	}
	virtual ~TeamInQueue();

	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_dlink_TeamBuildQueue_next; }
	void dlink_swapLinks_TeamBuildQueue()
	{
		TeamInQueue *originalNext = m_dlink_TeamBuildQueue_next;
		m_dlink_TeamBuildQueue_next = m_dlink_TeamBuildQueue_prev;
		m_dlink_TeamBuildQueue_prev = originalNext;
	}
	Bool dlink_isInList_TeamBuildQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamBuildQueue_prev || m_dlink_TeamBuildQueue_next;
	}
	void dlink_prependTo_TeamBuildQueue(TeamInQueue **pListHead)
	{
		m_dlink_TeamBuildQueue_next = *pListHead;
		if (*pListHead)
			(*pListHead)->m_dlink_TeamBuildQueue_prev = this;
		*pListHead = this;
	}

	TeamInQueue *m_dlink_TeamBuildQueue_prev;			// +0x04
	TeamInQueue *m_dlink_TeamBuildQueue_next;			// +0x08
	TeamInQueue *m_dlink_TeamReadyQueue_prev;			// +0x0C
	TeamInQueue *m_dlink_TeamReadyQueue_next;			// +0x10
	WorkOrder *m_workOrders;					// +0x14
	Bool m_priorityBuild;						// +0x18
	Team *m_team;							// +0x1C
	TeamInQueue *m_nextTeamInQueue;					// +0x20
	Int m_frameStarted;						// +0x24
	Bool m_sentToStartLocation;					// +0x28
	Bool m_stopQueueing;						// +0x29
	Bool m_reinforcement;						// +0x2A
	Int m_reinforcementID;						// +0x2C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// slot 9

protected:
	Bool rva00164750(TeamPrototype *proto);
	Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney);

	Bool isInList_TeamBuildQueue(TeamInQueue *o) const
	{
		return o->dlink_isInList_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
	}
	void prependTo_TeamBuildQueue(TeamInQueue *o)
	{
		if (!isInList_TeamBuildQueue(o))
			o->dlink_prependTo_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
	}
	void reverse_TeamBuildQueue()
	{
		TeamInQueue *cur = m_dlinkhead_TeamBuildQueue;
		TeamInQueue *prev = NULL;
		while (cur)
		{
			TeamInQueue *originalNext = cur->dlink_next_TeamBuildQueue();
			cur->dlink_swapLinks_TeamBuildQueue();
			prev = cur;
			cur = originalNext;
		}
		m_dlinkhead_TeamBuildQueue = prev;
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
	Player *m_player;						// +0x0C
	char m_unmodelled010[0x24 - 0x10];
	Int m_teamDelay;						// +0x24
};

#undef BFME_VIRTUAL_SLOT10
#undef BFME_VIRTUAL_SLOT

void AIPlayer::buildSpecificAITeam( TeamPrototype *teamProto, Bool priorityBuild)
{
	//
	// Create "Team in queue" based on team population
	//
	if (teamProto)
	{
		if (!m_player->getCanBuildUnits()) {
			AsciiString teamStr = "Can't build team '";
			bfmeConcat(teamStr, teamProto->getName());
			((StringBase<char> *)&teamStr)->concat("' because build units is disabled.", 34);
			TheScriptEngine->AppendDebugMessage(teamStr, false);
			return;
		}
		if (priorityBuild && teamProto->getIsSingleton()) {
			Team *singletonTeam = TheTeamFactory->findTeam( teamProto->m_name, teamProto->getName() );
			if (singletonTeam && singletonTeam->hasAnyObjects()) {
				AsciiString teamStr = "Unable to build singleton team '";
				teamStr.concat("' because team already exists.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
				return;
			}
		}
		// Check & make sure we have factories.
		Bool needMoney;
		if (!rva00164750(teamProto) && !isPossibleToBuildTeam(teamProto, false, needMoney)) {
			if (needMoney) {
				// Queue it up anyway.
				AsciiString teamStr = "Note - queueing team '";
				teamStr.concat(teamProto->getName());
				teamStr.concat("' but there is enough money.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			} else {
				// Tech tree doesn't work.
				AsciiString teamStr = "Unable to build team '";
				teamStr.concat(teamProto->getName());
				teamStr.concat("' because required factories/tech don't exist.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
				return;
			}
		}
		const TCreateUnitsInfo *unitInfo = &teamProto->getTemplateInfo()->m_unitsInfo[0];
		WorkOrder *orders = NULL;
		Int i;
		// Queue up optional units.
		for( i=0; i<teamProto->getTemplateInfo()->m_numUnitsInfo; i++ )
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate( unitInfo[i].unitThingName );
			if (thing)
			{
				int count = unitInfo[i].maxUnits-unitInfo[i].minUnits;
				if (count>0) {
					WorkOrder *order = new WorkOrder;
					order->m_thing = thing;
					order->m_factoryID = 0;
					order->m_numRequired = count;
					// prepend to head of list
					order->m_next = orders;
					orders = order;
				}
			}
		}
		// Queue up required units.
		for( i=0; i<teamProto->getTemplateInfo()->m_numUnitsInfo; i++ )
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate( unitInfo[i].unitThingName );
			if (thing)
			{
				int count = unitInfo[i].minUnits;
				WorkOrder *order = new WorkOrder;
				order->m_thing = thing;
				order->m_factoryID = 0;
				order->m_numRequired = count;
				order->m_required = true;
				// prepend to head of list
				order->m_next = orders;
				orders = order;
			}
		}
		if (orders)
		{
			/* We have something to build. */
			TeamInQueue *team = new TeamInQueue;
			if (priorityBuild) {
				// Put in front of queue.
				prependTo_TeamBuildQueue(team);
				team->m_priorityBuild = true;
			}	else {
				// Put in back of queue.
				reverse_TeamBuildQueue();
				prependTo_TeamBuildQueue(team);
				reverse_TeamBuildQueue();
				team->m_priorityBuild = false;
			}
			team->m_workOrders = orders;
			team->m_frameStarted = TheGameLogic->getFrame();
			// create inactive team to place members into as they are built
			// when team is complete, the team is activated
			team->m_team = TheTeamFactory->createInactiveTeam( teamProto->m_name, teamProto->getName() );
			AsciiString teamName = teamProto->getName();
			((StringBase<char> *)&teamName)->concat(" - starting team build.", 23);
			TheScriptEngine->AppendDebugMessage(teamName, false);
			m_teamDelay = 0;
			((Rva000EC960FlagUpdate *)team->m_team)->update(true);
			if (team->m_team->getPrototype()->getTemplateInfo()->m_executeActions) {
				AsciiString scriptName;
				const Script *script = TheScriptEngine->findScriptByName(&team->m_team->getName(),
					&team->m_team->getPrototype()->getTemplateInfo()->m_productionCondition, &scriptName);
				if (script && script->getAction()) {
					TheScriptEngine->friend_executeAction(&scriptName, script->getAction(), team->m_team);
				}
			}
		} else {
			if (((const Rva012ED5C8GlobalData *)TheWritableGlobalData)->m_debugAI) {
				AsciiString teamName = teamProto->getName();
				((StringBase<char> *)&teamName)->concat(" - contains 0 buildable units.", 30);
				TheScriptEngine->AppendDebugMessage(teamName, false);
			}
		}

	}
}
