// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamHunt@ScriptActions@@IAEXABVAsciiString@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class AIGroup
{
public:
	void groupHunt(CommandSourceType cmd);
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

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamHunt(const AsciiString &teamName);
};

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
