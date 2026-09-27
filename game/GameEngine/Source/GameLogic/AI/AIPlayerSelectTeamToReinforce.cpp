// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?selectTeamToReinforce@AIPlayer@@MAE_NH@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::selectTeamToReinforce, 0x00167080, 1243 bytes.
// Identity: slot 23 (+0x5C) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x0003EE5A here, the slot Zero Hour's AIPlayer.h gives
// selectTeamToReinforce, and the matched selectTeamToBuild calls that slot
// with its best priority. The body is the Zero Hour twin: the build-queue
// busy test, the automatically-reinforce instance walk with
// countObjectsByThingTemplate and findFactory, the " - AutoReinforcing one "
// line, the recruit attempt and the "Team '" / "' recruits " /
// " from team '" / "'" line.
//
// BFME differences: findFactory takes the build-index out pointer (NULL here)
// and Object::setTeam is Object vtable slot 20 (ObjectSetTeam.cpp). The
// recruit call goes to the unnamed body 0x000F2A00 through ILT 0x0001A2B2
// with (thing, &origin, TAiData::m_maxRecruitDistance); the ledger's
// Team::tryToRecruit row sits elsewhere, so the call site keeps an
// address-derived view.
//
// Layout: AIPlayer build queue head +0x04, m_player +0x0C, m_teamDelay +0x24;
// Player team-prototype list +0x288; TeamPrototype name +0x14, template info
// +0x130 (units info, count +0x54, home +0x58, auto-reinforce +0x8F,
// priority +0x98), instance list +0x274; Team prototype +0x04, member head
// +0x0C; Object position +0x38, id +0x74, team +0x23C, AI +0x204 (its
// AICommandInterface at +0x20).

#define _STLP_NO_EXCEPTIONS 1
#include <list>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define FALSE 0

extern const AsciiString Rva01336E50EmptyString;

#include "../command_source_type.h"
enum { MAX_UNIT_TYPES = 7 };

struct Coord3D
{
	Real x, y, z;
};

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

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Object;
class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
private:
	char m_unmodelled000[0x20];
	AsciiString m_nameString;					// +0x20
};

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
	Coord3D m_homeLocation;						// +0x58
	char m_unmodelled064[0x8f - 0x64];
	Bool m_automaticallyReinforce;					// +0x8F
	char m_unmodelled090[0x98 - 0x90];
	Int m_productionPriority;					// +0x98
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }
	const TeamTemplateInfo *getTemplateInfo(void) const { return &m_teamTemplate; }
	DLINK_ITERATOR<Team> iterate_TeamInstanceList(void) const;

	char m_unmodelled000[0x14];
	AsciiString m_rva14Name;					// +0x14
	char m_unmodelled018[0x130 - 0x18];
	TeamTemplateInfo m_teamTemplate;				// +0x130
	char m_unmodelled1cc[0x274 - 0x1cc];
	Team *m_dlinkhead_TeamInstanceList;				// +0x274
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
		return m_proto->getName();
	}
	Object *getFirstItemIn_TeamMemberList(void) const { return m_dlinkhead_TeamMemberList; }
	Bool hasAnyUnits(void) const;
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate * const *things,
		Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction = true) const;
	Team *_bfme_nextInInstanceList(void) const;

private:
	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
	char m_unmodelled008[0x0c - 0x08];
	Object *m_dlinkhead_TeamMemberList;				// +0x0C
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList(void) const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::_bfme_nextInInstanceList);
}

// The recruit search at 0x000F2A00 (ILT 0x0001A2B2): Zero Hour's
// Team::tryToRecruit by call site; the body itself is still unnamed.
class Rva000F2A00Team
{
public:
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *teamHome, Real maxDist);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	BFME_VIRTUAL_SLOT(09) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19)
	virtual void setTeam(Team *team);				// slot 20

	const Coord3D *getPosition() const { return &m_pos; }
	Int getID() const { return m_id; }
	Team *getTeam() const { return m_team; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

private:
	char m_unmodelled004[0x38 - 0x04];
	Coord3D m_pos;							// +0x38
	char m_unmodelled044[0x74 - 0x44];
	Int m_id;							// +0x74
	char m_unmodelled078[0x204 - 0x78];
	AIUpdateInterface *m_ai;					// +0x204
	char m_unmodelled208[0x23c - 0x208];
	Team *m_team;							// +0x23C
};

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

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct TAiData
{
	char m_unmodelled000[0x5c];
	Real m_maxRecruitDistance;					// +0x5C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	char m_unmodelled000[0x14];
	TAiData *m_aiData;						// +0x14
};

extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	typedef _STL::list<TeamPrototype *> PlayerTeamList;
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
private:
	char m_unmodelled000[0x288];
	PlayerTeamList m_playerTeamPrototypes;				// +0x288
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	// Retail WorkOrder's installed table at 0x01096964, stored as
	// TeamInQueueXfer.cpp does; this TU emits no table.
	WorkOrder()
		: m_vptr((void *)0x01096964), m_thing(NULL), m_factoryID(0), m_next(NULL),
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

	TeamInQueue *dlink_next_TeamBuildQueue() const;
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
	BFME_VIRTUAL_SLOT(09) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19) BFME_VIRTUAL_SLOT(20)
	BFME_VIRTUAL_SLOT(21) BFME_VIRTUAL_SLOT(22)

protected:
	virtual Bool selectTeamToReinforce( Int minPriority );		// slot 23
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);	// slot 24

	Object *findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex);

	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}
	void prependTo_TeamBuildQueue(TeamInQueue *o)
	{
		if (!o->dlink_isInList_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue))
			o->dlink_prependTo_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
	Player *m_player;						// +0x0C
	char m_unmodelled010[0x24 - 0x10];
	Int m_teamDelay;						// +0x24
};

#undef BFME_VIRTUAL_SLOT

Bool AIPlayer::selectTeamToReinforce( Int minPriority )
{
	// Find a high production priority team that needs reinforcements.
	Player::PlayerTeamList::const_iterator t;
	Team *curTeam = NULL;
	Int curPriority = minPriority; // Don't reinforce a team unless it is above min priority.
	const ThingTemplate *curThing = NULL;
	for (t = m_player->getPlayerTeams()->begin(); t != m_player->getPlayerTeams()->end(); ++t)
	{
		TeamPrototype *proto = (*t);
		Bool busy = false;
		for ( DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team->getPrototype() == proto) {
				busy = true; // currently building one of these.
			}
		}
		if (busy) continue;
		if (proto->getTemplateInfo()->m_automaticallyReinforce && proto->getTemplateInfo()->m_productionPriority>curPriority) {
			// Check the team instances.
			for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
			{
				Team *team = iter.cur();
				if (team->hasAnyUnits() == false)
				{
					continue; // empty.
				}
				const TCreateUnitsInfo *unitInfo = &team->getPrototype()->getTemplateInfo()->m_unitsInfo[0];
				for( int i=0; i<team->getPrototype()->getTemplateInfo()->m_numUnitsInfo; i++ )
				{
					if (unitInfo[i].maxUnits < 1) continue;
					const ThingTemplate *thing = TheThingFactory->findTemplate( unitInfo[i].unitThingName );
					if (thing==NULL) continue;
					Int count=0;
					team->countObjectsByThingTemplate(1, &thing, false, &count);
					if (count < unitInfo[i].maxUnits)
					{
						// See if there is a factory available.
						if (NULL != findFactory(thing, false, NULL))
						{
							curTeam = team;
							curPriority = proto->getTemplateInfo()->m_productionPriority;
							curThing = thing;
						}
					}
				}
			}
		}
	}
	if (curTeam && curThing)
	{
		/* We have something to build. */
		TeamInQueue *teamQ = new TeamInQueue;
		// Put in front of queue.
		prependTo_TeamBuildQueue(teamQ);
		teamQ->m_priorityBuild = false;
		teamQ->m_reinforcement = true;

		WorkOrder *order = new WorkOrder;
		order->m_thing = curThing;
		order->m_factoryID = 0;
		order->m_numRequired = 1;
		order->m_required = true;
		// prepend to head of list
		order->m_next = NULL;
		teamQ->m_workOrders = order;
		teamQ->m_frameStarted = TheGameLogic->getFrame();
		teamQ->m_team = curTeam;

		AsciiString teamName = curTeam->getPrototype()->getName();
		((StringBase<char> *)&teamName)->concat(" - AutoReinforcing one ", 23);
		bfmeConcat(teamName, curThing->getName());
		TheScriptEngine->AppendDebugMessage(teamName, false);

		// start the creation of a new unit
		Coord3D origin;
		origin = curTeam->getPrototype()->getTemplateInfo()->m_homeLocation;
		if (curTeam->getFirstItemIn_TeamMemberList())
		{
			origin = *curTeam->getFirstItemIn_TeamMemberList()->getPosition();
		}
		Object *unit = ((Rva000F2A00Team *)curTeam)->tryToRecruit(curThing, &origin, TheAI->getAiData()->m_maxRecruitDistance);
		if (unit)
		{
			order->m_numCompleted = 1;

			AsciiString teamStr = "Team '";
			bfmeConcat(teamStr, curTeam->getPrototype()->getName());
			((StringBase<char> *)&teamStr)->concat("' recruits ", 11);
			bfmeConcat(teamStr, curThing->getName());
			((StringBase<char> *)&teamStr)->concat(" from team '", 12);
			bfmeConcat(teamStr, unit->getTeam()->getPrototype()->getName());
			((StringBase<char> *)&teamStr)->concat("'", 1);
			TheScriptEngine->AppendDebugMessage(teamStr, false);

			unit->setTeam(curTeam);

			teamQ->m_reinforcementID = unit->getID();

			AIUpdateInterface *ai = unit->getAIUpdateInterface();
			if (ai)
			{
				ai->getCommandInterface()->aiIdle(CMD_FROM_AI);
			}
		} else {
			startTraining( order, teamQ->m_priorityBuild, teamQ->m_team->getName());
		}
		m_teamDelay = 0;
		return true;
	}
	return false;
}
