// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamGuardPosition@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction jump-table arm 206 is TEAM_GUARD_POSITION.
// TerrainLogic getWaypointByName slot 31 first, getTeamNamed slot 17, createGroup,
// getTeamAsAIGroup, copy waypoint+0xC onto the stack, groupGuardPosition NORMAL/SCRIPT.

#include "StringInline.h"

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

class AIGroup
{
public:
	enum GuardMode
	{
		GUARDMODE_NORMAL = 0
	};
	enum CommandSourceType
	{
		CMD_FROM_PLAYER = 0,
		CMD_FROM_SCRIPT = 1
	};
	void groupGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType cmd);
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
	void doTeamGuardPosition(const AsciiString &teamName,
		const AsciiString &waypointName);
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
