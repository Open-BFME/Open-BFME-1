// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ?doTeamGuardPosition@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamGuardObject@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamGuardArea@ScriptActions@@IAEXABVAsciiString@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Every ScriptActions action that puts something on guard:
//
//   0x002F33D0  doTeamGuardPosition  arm 206  waypoint copied onto the stack
//   0x002F3490  doTeamGuardObject    arm 207  a named unit
//   0x002F3520  doTeamGuardArea      arms 208 and 487, with or without a waypoint
//   0x002F64B0  doTeamGuardTeam               another team
//   0x00301DD0  doUnitGuardArea               UNIT_GUARD_AREA(_FROM_POSITION)
//
// The four team actions all resolve the team through ScriptEngine slot 17,
// allocate an AIGroup with TheAI->createGroup, fill it with
// Team::getTeamAsAIGroup and then issue one group order; doUnitGuardArea issues
// the same order to a single object's AICommandInterface instead. So they share
// every model here.

#include "StringInline.h"

typedef bool Bool;

class Object;
class PolygonTrigger;
class ScriptActions;
class Team;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

struct Coord3D
{
	float x, y, z;
};

class Waypoint
{
public:
	unsigned char m_pad[0xC];
	Coord3D m_location;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	// groupGuardPosition's pin at 0x0004115F mangles its mode arguments as
	// W4GuardMode@1@ / W4CommandSourceType@1@ -- enums nested in AIGroup --
	// while the pins for the other three guard orders mangle theirs as
	// W4GuardMode@@, at file scope. The two spellings are not interchangeable:
	// they are different symbols and the ledger resolves them to different
	// addresses. So the nested pair below shadows the file-scope pair, and the
	// three file-scope orders qualify with :: to say which they mean.
	enum GuardMode
	{
		GUARDMODE_NORMAL = 0
	};
	enum CommandSourceType
	{
		CMD_FROM_PLAYER = 0,
		CMD_FROM_SCRIPT = 1
	};

	void groupGuardPosition(const Coord3D *pos, GuardMode mode,
		CommandSourceType cmd);
	void groupGuardObject(Object *obj, ::GuardMode mode,
		::CommandSourceType cmd);
	void groupGuardArea(PolygonTrigger *area, ::GuardMode mode,
		::CommandSourceType cmd);
	void groupGuardAreaFromPosition(PolygonTrigger *area, ::GuardMode mode,
		::CommandSourceType cmd, const Coord3D *pos);
};

// Guarding a team has no pinned AIGroup entry; it is reached through the ILT
// at j_0002a07c on the same group pointer.
class BfmeAIGroupGuardTeamCall
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

class AICommandInterface
{
public:
	void aiGuardArea(const PolygonTrigger *area, GuardMode mode,
		CommandSourceType source);
	void aiBfmeCommand44(const PolygonTrigger *area, int mode,
		CommandSourceType source, const Coord3D *position);
};

class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_commands;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_pad[0x204];

public:
	AIUpdateInterface *m_ai;
	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return m_ai;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
	virtual void slot23() = 0; virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

extern void j_0002a07c();
extern void j_000171c0();
extern void j_0004ad9a();

static __forceinline void bfmeGroupGuardTeam(AIGroup *group,
	const Team *team)
{
	typedef void (BfmeAIGroupGuardTeamCall::*Function)(const Team *, int, int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002a07c;
	(reinterpret_cast<BfmeAIGroupGuardTeamCall *>(group)->*fn.member)(
		team, 0, 1);
}

static __forceinline void bfmeGuardArea(AICommandInterface *commands,
	const PolygonTrigger *area)
{
	typedef void (AICommandInterface::*GuardAreaCall)(const PolygonTrigger *,
		GuardMode, CommandSourceType);
	union { void (*raw)(void); GuardAreaCall member; } call;
	call.raw = j_000171c0;
	(reinterpret_cast<AICommandInterface *>(commands)->*call.member)(area,
		GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}

static __forceinline void bfmeGuardAreaFromPosition(
	AICommandInterface *commands, const PolygonTrigger *area,
	const Coord3D *position)
{
	typedef void (AICommandInterface::*GuardAreaFromPositionCall)(
		const PolygonTrigger *, int, CommandSourceType, const Coord3D *);
	union { void (*raw)(void); GuardAreaFromPositionCall member; } call;
	call.raw = j_0004ad9a;
	(reinterpret_cast<AICommandInterface *>(commands)->*call.member)(area, 0,
		CMD_FROM_SCRIPT, position);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamGuardPosition(const AsciiString &teamName,
		const AsciiString &waypointName);
	void doTeamGuardObject(const AsciiString &teamName,
		const AsciiString &unitName);
	void doTeamGuardArea(const AsciiString &teamName, const AsciiString &areaName,
		const AsciiString &waypointName);
	void doTeamGuardTeam(const AsciiString &sourceTeam,
		const AsciiString &teamToGuard);
	void doUnitGuardArea(const AsciiString &unitName,
		const AsciiString &areaName, const AsciiString &waypointName);
};

void ScriptActions::doTeamGuardPosition(const AsciiString &teamName,
	const AsciiString &waypointName)
{
	Coord3D position;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		if (way)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				position.x = way->m_location.x;
				position.y = way->m_location.y;
				position.z = way->m_location.z;
				theGroup->groupGuardPosition(&position, AIGroup::GUARDMODE_NORMAL,
					AIGroup::CMD_FROM_SCRIPT);
			}
		}
	}
}

void ScriptActions::doTeamGuardObject(const AsciiString &teamName,
	const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		if (theUnit)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupGuardObject(theUnit, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
			}
		}
	}
}

void ScriptActions::doTeamGuardArea(const AsciiString &teamName,
	const AsciiString &areaName, const AsciiString &waypointName)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		if (pTrig)
		{
			Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				if (way)
					theGroup->groupGuardAreaFromPosition(pTrig, GUARDMODE_NORMAL,
						CMD_FROM_SCRIPT, &way->m_location);
				else
					theGroup->groupGuardArea(pTrig, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
			}
		}
	}
}

void ScriptActions::doTeamGuardTeam(const AsciiString &sourceTeam,
	const AsciiString &teamToGuard)
{
	Team *theSourceTeam = TheScriptEngine->getTeamNamed(sourceTeam, false);
	Team *theTeamToGuard = TheScriptEngine->getTeamNamed(teamToGuard, false);
	if (theSourceTeam && theTeamToGuard)
	{
		AIGroup *group = TheAI->createGroup();
		if (group)
		{
			theSourceTeam->getTeamAsAIGroup(group);
			bfmeGroupGuardTeam(group, theTeamToGuard);
		}
	}
}

void ScriptActions::doUnitGuardArea(const AsciiString &unitName,
	const AsciiString &areaName, const AsciiString &waypointName)
{
	PolygonTrigger *area = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (unit)
	{
		if (unit->getAIUpdateInterface())
		{
			if (area)
			{
				Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
				AICommandInterface *commands = &unit->getAIUpdateInterface()->m_commands;
				if (way)
					bfmeGuardAreaFromPosition(commands, area, &way->m_location);
				else
					bfmeGuardArea(commands, area);
			}
		}
	}
}
