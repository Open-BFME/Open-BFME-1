// ?recruitSpecificAITeam@AIPlayer@@UAEXPAVTeamPrototype@@M@Z
// partial score=0.34 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /ICode/Libraries/Source/WWVegas/WWLib
// BFME reconstruction of AIPlayer::recruitSpecificAITeam.

#include "string_base.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

extern const char Rva006A16B0Empty[];

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void concat(const char *text)
	{
		StringBase<char>::concat(text);
	}

	void concat(const AsciiString &text)
	{
		const char *data = *(const char *const *)&text;
		const unsigned short *length = data ? (const unsigned short *)(data + 4) : 0;
		data = data ? data + 8 : Rva006A16B0Empty;
		StringBase<char>::concat(data, length ? *length : 0);
	}
	};

class TeamPrototype;
class Team;
class TeamFactory;
class ThingFactory;
class ThingTemplate;
class Object;
class ScriptEngine;
class AIUpdateInterface;
class TeamInQueue;

struct BfmeUnitInfoRecord
{
	Int minUnits;
	Int maxUnits;
	AsciiString unitThingName;
};

struct BfmeTeamTemplateInfo
{
	BfmeUnitInfoRecord m_unitsInfo[7];
	Int m_numUnitsInfo;
	Coord3D m_homeLocation;
	Bool m_hasHomeLocation;
};

struct BfmeUnitInfoCursor
{
	Int maxUnits;
	AsciiString unitThingName;
	unsigned char suffix[4];
};

class TeamPrototype
{
public:
	const AsciiString &getOwnerName() const
	{
		return *(const AsciiString *)((const char *)this + 0x10);
	}

	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x14);
	}

	Bool getIsSingleton() const
	{
		return (*(const unsigned char *)((const char *)this + 0x18) & 1) != 0;
	}

	const BfmeTeamTemplateInfo *getTemplateInfo() const
	{
		return (const BfmeTeamTemplateInfo *)((const char *)this + 0x130);
	}

	const BfmeUnitInfoCursor *getUnitInfo() const
	{
		return (const BfmeUnitInfoCursor *)((const char *)this + 0x134);
	}
};

class Team
{
public:
	virtual ~Team();
	Bool hasAnyObjects(Bool flag);
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *home,
		Real radius);

	TeamPrototype *getPrototype() const
	{
		return *(TeamPrototype *const *)((const char *)this + 4);
	}
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name, const AsciiString &owner);
	Team *bfmeCreateInactiveTeam(const AsciiString &owner,
		const AsciiString &name);
};

class ThingTemplate
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
	void aiMoveToPosition(const Coord3D *position, Int commandSource);
};

class AIUpdateInterface
{
	unsigned char m_prefix[0x20];

public:
	AICommandInterface m_command;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void setTeam(Team *team);

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	Team *getTeam() const
	{
		return *(Team *const *)((const char *)this + 0x23c);
	}

private:
	unsigned char m_prefix[0x200];
	AIUpdateInterface *m_ai;
	unsigned char m_between[0x34];
	Team *m_team;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

class TeamInQueue
{
public:
	TeamInQueue() :
		m_buildPrevious(0),
		m_buildNext(0),
		m_readyPrevious(0),
		m_readyNext(0),
		m_workOrders(0),
		m_priorityBuild(false),
		m_team(0),
		m_nextTeamInQueue(0),
		m_frameStarted(0),
		m_sentToStartLocation(false),
		m_stopQueueing(false),
		m_reinforcement(false),
		m_pad2b(0),
		m_reinforcementID(0)
	{
	}

	virtual ~TeamInQueue();

	TeamInQueue *m_buildPrevious;
	TeamInQueue *m_buildNext;
	TeamInQueue *m_readyPrevious;
	TeamInQueue *m_readyNext;
	void *m_workOrders;
	Bool m_priorityBuild;
	Team *m_team;
	TeamInQueue *m_nextTeamInQueue;
	Int m_frameStarted;
	Bool m_sentToStartLocation;
	Bool m_stopQueueing;
	Bool m_reinforcement;
	unsigned char m_pad2b;
	Int m_reinforcementID;
};

typedef char TeamInQueueSizeCheck[sizeof(TeamInQueue) == 0x30 ? 1 : -1];

class GameLogic
{
};

class AISkirmishPlayer
{
public:
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto,
		Real recruitRadius, const Coord3D *position);

private:
	TeamInQueue *m_buildQueueHead;
	TeamInQueue *m_readyQueueHead;
};

extern void j_0000d15c();
extern void j_0001478b();
extern void j_0001a2b2();
extern void j_00022057();
extern void j_00028560();
extern void j_00028ce0();
extern void j_0003436a();
extern void j_000391ee();

#define TheTeamFactory (*(TeamFactory **)0x012ED810)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)
#define TheGameLogic (*(GameLogic **)0x012F0898)
#define g_bfmeDefaultBU (*(const Real *)0x01075334)

static Team *bfmeFindTeam(const AsciiString &name,
	const AsciiString &owner)
{
	typedef Team *(TeamFactory::*Call)(const AsciiString &,
		const AsciiString &);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_000391ee;
	return (TheTeamFactory->*target.member)(name, owner);
}

static Team *bfmeCreateInactiveTeam(const AsciiString &owner,
	const AsciiString &name)
{
	typedef Team *(TeamFactory::*Call)(const AsciiString &,
		const AsciiString &);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_0000d15c;
	return (TheTeamFactory->*target.member)(owner, name);
}

static Bool bfmeHasAnyObjects(Team *team, Bool flag)
{
	typedef Bool(Team::*Call)(Bool) const;
	union { void (*raw)(void); Call member; } target;
	target.raw = j_0001478b;
	return (team->*target.member)(flag);
}

static Object *bfmeTryToRecruit(Team *team, const ThingTemplate *thing,
	const Coord3D *home, Real radius)
{
	typedef Object *(Team::*Call)(const ThingTemplate *, const Coord3D *,
		Real);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_0001a2b2;
	return (team->*target.member)(thing, home, radius);
}

static const ThingTemplate *bfmeFindTemplate(const AsciiString &name)
{
	typedef const ThingTemplate *(ThingFactory::*Call)(const AsciiString &);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_00028560;
	return (TheThingFactory->*target.member)(name);
}

static void bfmeAppendDebugMessage(ScriptEngine *engine,
	const AsciiString &message, Bool forcePause)
{
	typedef void(ScriptEngine::*Call)(const AsciiString &, Bool);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_00028ce0;
	(engine->*target.member)(message, forcePause);
}

static void bfmeMoveToPosition(AICommandInterface *command,
	const Coord3D *position, Int commandSource)
{
	typedef void(AICommandInterface::*Call)(const Coord3D *, Int);
	union { void (*raw)(void); Call member; } target;
	target.raw = j_0003436a;
	(command->*target.member)(position, commandSource);
}

void AISkirmishPlayer::recruitSpecificAITeam(TeamPrototype *teamProto,
	Real recruitRadius, const Coord3D *position)
{
	if (recruitRadius < g_bfmeDefaultBU)
		recruitRadius = 99999.0f;

	if (teamProto)
	{
		if (teamProto->getIsSingleton())
		{
			Team *singletonTeam = TheTeamFactory->findTeam(
				teamProto->getOwnerName(), teamProto->getName());
			if (singletonTeam && singletonTeam->hasAnyObjects(false))
			{
				AsciiString teamStr = "Unable to recruit singleton team '";
				teamStr.concat("' because team already exists.");
				TheScriptEngine->AppendDebugMessage(teamStr, false);
				return;
			}
		}

		if (!teamProto->getTemplateInfo()->m_hasHomeLocation)
		{
			AsciiString teamStr = "Error : team '";
			teamStr.concat(teamProto->getName());
			teamStr.concat("' has no Home Position (or Origin).");
			TheScriptEngine->AppendDebugMessage(teamStr, false);
		}

		Team *theTeam = TheTeamFactory->bfmeCreateInactiveTeam(
			teamProto->getOwnerName(), teamProto->getName());
		AsciiString teamName = teamProto->getName();
		teamName.concat(" - Recruiting.");
		TheScriptEngine->AppendDebugMessage(teamName, false);

		const BfmeUnitInfoCursor *unitInfo = teamProto->getUnitInfo();
		Int i;
		Int unitsRecruited = 0;
		for (i = 0; i < teamProto->getTemplateInfo()->m_numUnitsInfo; i++)
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate(
				unitInfo[i].unitThingName);
			if (thing)
			{
				Int count = unitInfo[i].maxUnits;
				while (count > 0)
				{
					Object *unit = theTeam->tryToRecruit(thing,
						&teamProto->getTemplateInfo()->m_homeLocation,
						recruitRadius);
					if (unit)
					{
						++unitsRecruited;
						AsciiString teamStr = "Team '";
						teamStr.concat(theTeam->getPrototype()->getName());
						teamStr.concat("' recruits ");
						teamStr.concat(thing->getName());
						teamStr.concat(" from team '");
						teamStr.concat(unit->getTeam()->getPrototype()->getName());
						teamStr.concat("'");
						TheScriptEngine->AppendDebugMessage(teamStr, false);

						unit->setTeam(theTeam);
						AIUpdateInterface *ai = unit->getAIUpdateInterface();
						if (ai)
							ai->m_command.aiMoveToPosition(
								&teamProto->getTemplateInfo()->m_homeLocation, 2);
					}
					else
					{
						break;
					}
					count--;
				}
			}
		}

		if (unitsRecruited > 0)
		{
			TeamInQueue *team = new TeamInQueue;
			if (m_readyQueueHead)
			{
				team->m_readyNext = m_readyQueueHead;
				m_readyQueueHead->m_readyPrevious = team;
			}
			m_readyQueueHead = team;
			team->m_priorityBuild = false;
			team->m_workOrders = 0;
			team->m_frameStarted = *(Int *)((char *)TheGameLogic + 0x3c);
			team->m_team = theTeam;
			AsciiString teamName = teamProto->getName();
			teamName.concat(" - Finished recruiting.");
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
		else
		{
			if (!theTeam->getPrototype()->getIsSingleton())
				delete theTeam;
			AsciiString teamName = teamProto->getName();
			teamName.concat(" - Recruited 0 units, disbanding.");
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
	}
}
