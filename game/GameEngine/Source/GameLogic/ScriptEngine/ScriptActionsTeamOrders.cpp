// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ?doAttack@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamAttackArea@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamExitAll@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamHunt@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamHarvest@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The six one-order team actions:
//
//   0x002F2840  doAttack          arm 33, TEAM_ATTACK_TEAM  groupAttackTeam
//   0x002F2A50  doTeamAttackArea                            groupAttackArea
//   0x002F2AE0  doTeamEnterNamed                            groupEnter
//   0x002F2B70  doTeamExitAll                               groupEvacuate
//   0x002F3600  doTeamHunt                                  groupHunt
//   0x002F3670  doTeamHarvest     arm 468, TEAM_HARVEST     groupHarvest
//
// Every one of them is the same three steps: getTeamNamed at slot 17, an
// AIGroup from TheAI->createGroup filled by Team::getTeamAsAIGroup, and one
// group order with CMD_FROM_SCRIPT. Only the order differs, and only three of
// them look anything else up first.

#include "StringInline.h"

class Object;
class PolygonTrigger;
class Team;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

const int NO_MAX_SHOTS_LIMIT = 0x7fffffff;

struct Coord3D
{
	float x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
	unsigned char m_pad[0xC];
	Coord3D m_location;
public:
	const Coord3D *getLocation() const { return &m_location; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupAttackTeam(const Team *team, int maxShotsToFire,
		CommandSourceType cmd);
	void groupAttackArea(PolygonTrigger *area, CommandSourceType cmd);
	void groupEnter(Object *transport, CommandSourceType cmd);
	void groupEvacuate(CommandSourceType cmd);
	void groupHunt(CommandSourceType cmd);
	void groupHarvest(const Coord3D *pos, CommandSourceType cmd);
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
	virtual Team *getTeamNamed(AsciiString name, bool unused) = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
	virtual void slot23() = 0; virtual void slot24() = 0;
	virtual void slot25() = 0; virtual void slot26() = 0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doAttack(const AsciiString &attackerName, const AsciiString &victimName);
	void doTeamAttackArea(const AsciiString &teamName, const AsciiString &areaName);
	void doTeamEnterNamed(const AsciiString &teamName, const AsciiString &unitDestName);
	void doTeamExitAll(const AsciiString &teamName);
	void doTeamHunt(const AsciiString &teamName);
	void doTeamHarvest(const AsciiString &teamName, const AsciiString &waypointName);
};

void ScriptActions::doAttack(const AsciiString &attackerName,
	const AsciiString &victimName)
{
	Team *attackingTeam = TheScriptEngine->getTeamNamed(attackerName, false);
	const Team *victimTeam = TheScriptEngine->getTeamNamed(victimName, false);
	if (attackingTeam)
	{
		if (victimTeam)
		{
			AIGroup *aiGroup = TheAI->createGroup();
			if (aiGroup)
			{
				attackingTeam->getTeamAsAIGroup(aiGroup);
				aiGroup->groupAttackTeam(victimTeam, NO_MAX_SHOTS_LIMIT,
					CMD_FROM_SCRIPT);
			}
		}
	}
}

void ScriptActions::doTeamAttackArea(const AsciiString &teamName,
	const AsciiString &areaName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		AIGroup *theGroup = TheAI->createGroup();
		if (theGroup)
		{
			theTeam->getTeamAsAIGroup(theGroup);
			PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
			if (pTrig)
				theGroup->groupAttackArea(pTrig, CMD_FROM_SCRIPT);
		}
	}
}

void ScriptActions::doTeamEnterNamed(const AsciiString &teamName,
	const AsciiString &unitDestName)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theSrcTeam)
	{
		Object *theTransport = TheScriptEngine->getUnitNamedByValue(unitDestName);
		if (theTransport)
		{
			AIGroup *theGroup = TheAI->createGroup();
			theSrcTeam->getTeamAsAIGroup(theGroup);
			theGroup->groupEnter(theTransport, CMD_FROM_SCRIPT);
		}
	}
}

void ScriptActions::doTeamExitAll(const AsciiString &teamName)
{
	Team *theTeamOfTransports = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeamOfTransports)
	{
		AIGroup *theGroup = TheAI->createGroup();
		theTeamOfTransports->getTeamAsAIGroup(theGroup);
		theGroup->groupEvacuate(CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamHunt(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		AIGroup *theGroup = TheAI->createGroup();
		if (theGroup)
		{
			theTeam->getTeamAsAIGroup(theGroup);
			theGroup->groupHunt(CMD_FROM_SCRIPT);
		}
	}
}

void ScriptActions::doTeamHarvest(const AsciiString &teamName,
	const AsciiString &waypointName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
		if (way)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupHarvest(way->getLocation(), CMD_FROM_SCRIPT);
			}
		}
	}
}
