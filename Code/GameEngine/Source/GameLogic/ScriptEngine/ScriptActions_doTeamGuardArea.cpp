// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamGuardArea@ScriptActions@@IAEXABVAsciiString@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction arms 208 (TEAM_GUARD_AREA) and 487
// (TEAM_GUARD_AREA_FROM_POSITION) share this 3-arg body. Area via ScriptEngine
// slot 22, team via slot 17, optional waypoint via TerrainLogic slot 31, then
// groupGuardArea or groupGuardAreaFromPosition (waypoint+0xC).

#include "StringInline.h"

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

class PolygonTrigger;
class AIGroup
{
public:
	void groupGuardAreaFromPosition(PolygonTrigger *area, GuardMode mode,
		CommandSourceType cmd, const Coord3D *pos);
	void groupGuardArea(PolygonTrigger *area, GuardMode mode,
		CommandSourceType cmd);
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class AI
{
public:
	AIGroup *createGroup();
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual Team *getTeamNamed(AsciiString name, bool unused);
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamGuardArea(const AsciiString &teamName, const AsciiString &areaName,
		const AsciiString &waypointName);
};

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
