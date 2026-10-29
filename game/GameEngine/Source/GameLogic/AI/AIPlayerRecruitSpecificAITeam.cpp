// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?recruitSpecificAITeam@AIPlayer@@UAEXPAVTeamPrototype@@MPBVCoord3D@@@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::recruitSpecificAITeam, 0x00167930, 1077 bytes (ret 0xC at +0x432).
// Identity: slot 10 (+0x28) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x0001177A here. BFME dropped Zero Hour's three base-building virtuals,
// so slot 9 is buildSpecificAITeam (AIPlayerBuildSpecificAITeam.cpp), slots
// 11-13 are the isSkirmishAI/getAiEnemy/checkBridges stubs and slot 14 is
// repairStructure (AIPlayerRepairStructure.cpp). The body is the Zero Hour
// twin, with all of its debug lines ("Unable to recruit singleton team '",
// " - Recruiting.", "Team '" / "' recruits " / " from team '" / "'",
// " - Finished recruiting.", " - Recruited 0 units, disbanding.").
//
// BFME differences: a third argument, an optional recruit position, replaces
// the team's home location both as the recruit search origin and as the move
// target; without it the recruits move to the home location when the team
// has one and otherwise to the team's estimated position (0x000F2420). The
// "has no Home Position" check is gone; TeamFactory's findTeam and
// createInactiveTeam take the prototype's two names (+0x10 and +0x14); the
// recruit search is the unnamed 0x000F2A00 (ILT 0x0001A2B2), as in
// AIPlayerSelectTeamToReinforce.cpp; and one teamName serves all three
// progress lines.
//
// Layout: AIPlayer ready queue head +0x08; TeamPrototype names +0x10/+0x14,
// singleton flag bit 0 of +0x18, template info +0x130 (units info, count
// +0x54, home +0x58, has-home +0x64); Team prototype +0x04; Object team
// +0x23C, AI +0x204 (its AICommandInterface at +0x20); TeamInQueue as in
// AIPlayerBuildSpecificAITeam.cpp.

// This unit's local TeamPrototype view defines getTemplateInfo inline at its own offset
// (not +0x68) and emits that COMDAT copy; rename it so only retail's 0x003BCD70
// (lea eax,[ecx+0x68]) carries the name. Inlined calls are unchanged.
#define getTemplateInfo getTemplateInfo_LocalView
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
enum { TEAM_SINGLETON = 0x01 };

// BFME declares Coord3D as a class: retail's ILT order confirms this method's
// PBVCoord3D decoration, as for AISkirmishPlayer's slot-10 override.
// class-gate: allow Coord3D retail's ILT slot for this body spells the third parameter PBVCoord3D@@ (class key); the canonical header's struct spelling mangles PBUCoord3D@@, which tools/ilt_oracle.py contradicts.
class Coord3D
{
public:
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
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ThingFactory;
extern ThingFactory *TheThingFactory;
#define TheThingFactory ((BfmeThingFactory *)TheThingFactory)

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
	Bool m_hasHomeLocation;						// +0x64
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
	virtual ~Team();

	void deleteInstance(void) { delete this; }
	const TeamPrototype *getPrototype(void) const { return m_proto; }
	Bool hasAnyObjects(Bool ignoreBuildings = false) const;

private:
	TeamPrototype *m_proto;						// +0x04
};

// Team::getEstimateTeamPosition (0x000F2420) is defined with the struct-key
// Coord3D, and retail's ILT order rejects a class-key spelling of it, so this
// class-key TU reaches it through its retail ILT thunk (0x0002990B), as
// AISkirmishPlayerRecruitSpecificAITeam.cpp does for its callees.
extern void j_0002990b();

static Coord3D *bfmeGetEstimateTeamPosition(const Team *team, Coord3D *pos)
{
	typedef Coord3D *(Team::*Call)(Coord3D *) const;
	union { void (*raw)(void); Call member; } target;
	target.raw = j_0002990b;
	return (team->*target.member)(pos);
}

// The recruit search at 0x000F2A00 (ILT 0x0001A2B2): Zero Hour's
// Team::tryToRecruit by call site; the body itself is still unnamed.
class Rva000F2A00Team
{
public:
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *teamHome, Real maxDist);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name, const AsciiString &name2);
	Team *createInactiveTeam(const AsciiString &name, const AsciiString &name2);
};

extern TeamFactory *TheTeamFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
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

	Team *getTeam() const { return m_team; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

private:
	char m_unmodelled004[0x204 - 0x04];
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

class WorkOrder;

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

	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamReadyQueue_prev || m_dlink_TeamReadyQueue_next;
	}
	void dlink_prependTo_TeamReadyQueue(TeamInQueue **pListHead)
	{
		m_dlink_TeamReadyQueue_next = *pListHead;
		if (*pListHead)
			(*pListHead)->m_dlink_TeamReadyQueue_prev = this;
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
	BFME_VIRTUAL_SLOT(09)
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius,
		const Coord3D *recruitPos);				// slot 10

protected:
	void prependTo_TeamReadyQueue(TeamInQueue *o)
	{
		if (!o->dlink_isInList_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue))
			o->dlink_prependTo_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue);
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
};

#undef BFME_VIRTUAL_SLOT

void AIPlayer::recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius,
	const Coord3D *recruitPos)
{
	if (recruitRadius < 1) recruitRadius = 99999.0f;
	//
	// Create "Team in queue" based on team population
	//
	if (teamProto)
	{
		if (teamProto->getIsSingleton()) {
			Team *singletonTeam = TheTeamFactory->findTeam( teamProto->m_name, teamProto->getName() );
			if (singletonTeam && singletonTeam->hasAnyObjects()) {
				AsciiString teamStr = "Unable to recruit singleton team '";
				teamStr.concat("' because team already exists.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
				return;
			}
		}
		// create inactive team to place members into as they are built
		// when team is complete, the team is activated
		Team *theTeam = TheTeamFactory->createInactiveTeam( teamProto->m_name, teamProto->getName() );
		AsciiString teamName = teamProto->getName();
		((StringBase<char> *)&teamName)->concat(" - Recruiting.", 14);
		TheScriptEngine->AppendDebugMessage(teamName, false);
		const TCreateUnitsInfo *unitInfo = &teamProto->getTemplateInfo()->m_unitsInfo[0];
		Int i;
		Int unitsRecruited = 0;
		// Recruit.
		for( i=0; i<teamProto->getTemplateInfo()->m_numUnitsInfo; i++ )
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate( unitInfo[i].unitThingName );
			if (thing)
			{
				int count = unitInfo[i].maxUnits;
				while (count>0) {
					Object *unit;
					if (recruitPos)
						unit = ((Rva000F2A00Team *)theTeam)->tryToRecruit(thing, recruitPos, recruitRadius);
					else
						unit = ((Rva000F2A00Team *)theTeam)->tryToRecruit(thing, &teamProto->getTemplateInfo()->m_homeLocation, recruitRadius);
					if (unit)
					{
						unitsRecruited++;

						AsciiString teamStr = "Team '";
						bfmeConcat(teamStr, theTeam->getPrototype()->getName());
						((StringBase<char> *)&teamStr)->concat("' recruits ", 11);
						bfmeConcat(teamStr, thing->getName());
						((StringBase<char> *)&teamStr)->concat(" from team '", 12);
						bfmeConcat(teamStr, unit->getTeam()->getPrototype()->getName());
						((StringBase<char> *)&teamStr)->concat("'", 1);
						TheScriptEngine->AppendDebugMessage(teamStr, false);

						unit->setTeam(theTeam);

						AIUpdateInterface *ai = unit->getAIUpdateInterface();
						if (ai)
						{
							const Coord3D *to = recruitPos;
							Coord3D pos;
							bfmeGetEstimateTeamPosition(theTeam, &pos);
							if (to == NULL)
							{
								if (teamProto->getTemplateInfo()->m_hasHomeLocation)
									pos = teamProto->getTemplateInfo()->m_homeLocation;
								to = &pos;
							}
							ai->getCommandInterface()->aiMoveToPosition( to, CMD_FROM_AI);
						}
					} else {
						break;
					}
					count--;
				}
			}
		}
		if (unitsRecruited>0)
		{
			/* We have something to build. */
			TeamInQueue *team = new TeamInQueue;
			// Put in front of queue.
			prependTo_TeamReadyQueue(team);
			team->m_priorityBuild = false;
			team->m_workOrders = NULL;
			team->m_frameStarted = TheGameLogic->getFrame();
			team->m_team = theTeam;
			teamName = teamProto->getName();
			((StringBase<char> *)&teamName)->concat(" - Finished recruiting.", 23);
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}	else {
			//disband.
			if (!theTeam->getPrototype()->getIsSingleton()) {
				theTeam->deleteInstance();
				theTeam = NULL;
			}
			teamName = teamProto->getName();
			((StringBase<char> *)&teamName)->concat(" - Recruited 0 units, disbanding.", 33);
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
	}
}
