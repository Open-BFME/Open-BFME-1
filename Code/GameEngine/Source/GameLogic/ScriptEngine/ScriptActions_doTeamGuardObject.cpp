// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamGuardObject@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction jump-table arm 207 is TEAM_GUARD_OBJECT.
// getUnitNamed slot 26 by ref, getTeamNamed slot 17 by value, createGroup,
// getTeamAsAIGroup, groupGuardObject(unit, GUARDMODE_NORMAL, CMD_FROM_SCRIPT).

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

class Object;
class AIGroup
{
public:
	void groupGuardObject(Object *obj, GuardMode mode, CommandSourceType cmd);
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
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual Object *getUnitNamed(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamGuardObject(const AsciiString &teamName, const AsciiString &unitName);
};

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
