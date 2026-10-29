// ?recruitSpecificAITeam@AISkirmishPlayer@@UAEXPAVTeamPrototype@@MPBVCoord3D@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/GameLogic
//
// Retail 0x001699C0 (1130 bytes, RET 0xC at +0x467, then INT3) is
// AISkirmishPlayer's slot-10 override of AIPlayer::recruitSpecificAITeam.
// BFME added a third argument to the Zero Hour two-argument signature: the
// caller-supplied position replaces the template home location when it is
// non-null (+0x1E6 tests it). The body resolves the team factory, refuses a
// duplicate singleton, builds the ready-queue entry through the native
// readiness-list helpers, walks the seven unit records, recruits through
// Team::tryToRecruit and moves each new unit with the AI command interface.
//
// Identity: the matched constructor at 0x00168660 installs vtable 0x01096FB0
// whose slot 10 thunk (ILT RVA 0x0003499B) jumps here; the matched
// Player::recruitSpecificTeam at 0x000C9790 and its complete caller
// ScriptActions::doRecruitTeam at 0x002F37E0 pass the same three arguments in
// this order. ilt_oracle confirms the decorated name at 0x001699C0
// (p_false=6.52e-05, an exact 1-bucket window between the anchors
// ?winGetInstanceData@GameWindow@@ and ?WOLGameSetupMenuUpdate@@); the third
// parameter must be spelled with the class key, so the Coord3D view below
// carries `class`, not the canonical header's `struct`.
//
// Evidence: targets/game/reverse/identity_evidence/001699c2-recruit-specific-team.md
// and targets/game/reverse/identity_evidence/001699c0-recruit-specific-team.md
// This unit's TeamPrototype view defines getIsSingleton inline at another offset than
// retail's 0x000EC410 (+0x18) and emits that COMDAT copy; rename it so only
// retail-equal copies carry the name. Inlined calls are unchanged.
#define getIsSingleton getIsSingleton_LocalView
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

// Coord3D is spelled with the class key here: retail's ILT slot for this body
// names the third parameter PBVCoord3D@@, so the defining translation unit saw
// a class-key Coord3D. The layout is the canonical 12-byte {Real x, y, z}; the
// view is a layout view, not a claim about the shipped header's class key.
// class-gate: allow Coord3D retail's ILT slot for this body spells the third parameter PBVCoord3D@@ (class key). The canonical header's struct spelling mangles PBUCoord3D@@ and does not compile against this body (our=0 bytes).
class Coord3D
{
public:
	Real x, y, z;
};

#include "command_source_type.h"

extern const char g_bfmeEmptyAscii[];

static inline void bfmeConcat(AsciiString &dst, const AsciiString &text)
{
    dst.StringBase<char>::concat(text.str(), text.getLength());
}

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
	Bool hasAnyObjects(Bool flag) const;
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
	void aiMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
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
		m_reinforcementID(0)
	{
	}

protected:
	virtual ~TeamInQueue();

public:
    Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
    {
        return *pListHead == this || m_readyPrevious || m_readyNext;
    }
    void dlink_prependTo_TeamReadyQueue(TeamInQueue **pListHead)
    {
        m_readyNext = *pListHead;
        if (*pListHead)
            (*pListHead)->m_readyPrevious = this;
        *pListHead = this;
    }

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
public:
    unsigned int getFrame() const { return m_frame; }
private:
    unsigned char m_prefix[0x3c];
    unsigned int m_frame;
};

class AISkirmishPlayer
{
public:
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto,
		Real recruitRadius, const Coord3D *position);

    Bool isInList_TeamReadyQueue(TeamInQueue *o) const
    {
        return o->dlink_isInList_TeamReadyQueue(&m_readyQueueHead);
    }
    void prependTo_TeamReadyQueue(TeamInQueue *o)
    {
        if (!isInList_TeamReadyQueue(o))
            o->dlink_prependTo_TeamReadyQueue(&m_readyQueueHead);
    }

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

extern TeamFactory *TheTeamFactory;
extern ThingFactory *TheThingFactory;
extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern Real g_bfmeDefaultBU;

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
	const Coord3D *position, CommandSourceType commandSource)
{
	typedef void(AICommandInterface::*Call)(const Coord3D *, CommandSourceType);
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
			Team *singletonTeam = bfmeFindTeam(
				teamProto->getOwnerName(), teamProto->getName());
			if (singletonTeam && bfmeHasAnyObjects(singletonTeam, false))
			{
				AsciiString teamStr = "Unable to recruit singleton team '";
				teamStr.concat("' because team already exists.");
				bfmeAppendDebugMessage(TheScriptEngine, teamStr, false);
				return;
			}
		}

		if (!teamProto->getTemplateInfo()->m_hasHomeLocation)
		{
			AsciiString teamStr = "Error : team '";
			bfmeConcat(teamStr, teamProto->getName());
			teamStr.StringBase<char>::concat("' has no Home Position (or Origin).", 35);
			bfmeAppendDebugMessage(TheScriptEngine, teamStr, false);
		}

		Team *theTeam = bfmeCreateInactiveTeam(
			teamProto->getOwnerName(), teamProto->getName());
		AsciiString teamName = teamProto->getName();
		teamName.StringBase<char>::concat(" - Recruiting.", 14);
		bfmeAppendDebugMessage(TheScriptEngine, teamName, false);

		const BfmeUnitInfoRecord *unitInfo = &teamProto->getTemplateInfo()->m_unitsInfo[0];
		Int i;
		Int unitsRecruited = 0;
		for (i = 0; i < teamProto->getTemplateInfo()->m_numUnitsInfo; i++)
		{
			const ThingTemplate *thing = bfmeFindTemplate(
				unitInfo[i].unitThingName);
			if (thing)
			{
				Int count = unitInfo[i].maxUnits;
				while (count > 0)
				{
					Object *unit;
					if (position)
						unit = bfmeTryToRecruit(theTeam, thing, position, recruitRadius);
					else
						unit = bfmeTryToRecruit(theTeam, thing, &teamProto->getTemplateInfo()->m_homeLocation, recruitRadius);
					if (unit)
					{
						++unitsRecruited;
						AsciiString teamStr = "Team '";
						bfmeConcat(teamStr, theTeam->getPrototype()->getName());
						teamStr.StringBase<char>::concat("' recruits ", 11);
						bfmeConcat(teamStr, thing->getName());
						teamStr.StringBase<char>::concat(" from team '", 12);
						bfmeConcat(teamStr, unit->getTeam()->getPrototype()->getName());
						teamStr.StringBase<char>::concat("'", 1);
						bfmeAppendDebugMessage(TheScriptEngine, teamStr, false);

						unit->setTeam(theTeam);
						AIUpdateInterface *ai = unit->getAIUpdateInterface();
						if (ai)
							bfmeMoveToPosition(&ai->m_command, 
								&teamProto->getTemplateInfo()->m_homeLocation, CMD_FROM_AI);
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
			prependTo_TeamReadyQueue(team);
			team->m_priorityBuild = false;
			team->m_workOrders = 0;
			team->m_frameStarted = TheGameLogic->getFrame();
			team->m_team = theTeam;
			teamName = teamProto->getName();
			teamName.StringBase<char>::concat(" - Finished recruiting.", 23);
			bfmeAppendDebugMessage(TheScriptEngine, teamName, false);
		}
		else
		{
			if (!theTeam->getPrototype()->getIsSingleton())
				delete theTeam;
			teamName = teamProto->getName();
			teamName.StringBase<char>::concat(" - Recruited 0 units, disbanding.", 33);
			bfmeAppendDebugMessage(TheScriptEngine, teamName, false);
		}
	}
}
