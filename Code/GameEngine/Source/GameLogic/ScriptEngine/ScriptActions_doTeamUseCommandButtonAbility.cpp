// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction arm 245 is ZH TEAM_USE_COMMANDBUTTON_ABILITY (241)
// after the +4 insert before TEAM_GUARD_POSITION. getTeamNamed slot 17,
// ControlBar::findCommandButton, createGroup, getTeamAsAIGroup,
// groupDoCommandButton(button, CMD_FROM_SCRIPT).

#include "StringInline.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class CommandButton;
class AIGroup
{
public:
	void groupDoCommandButton(const CommandButton *button, CommandSourceType cmd);
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

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
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
extern ControlBar *TheControlBar;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamUseCommandButtonAbility(const AsciiString &team,
		const AsciiString &ability);
};

void ScriptActions::doTeamUseCommandButtonAbility(const AsciiString &team,
	const AsciiString &ability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (theTeam)
	{
		const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
		if (commandButton)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupDoCommandButton(commandButton, CMD_FROM_SCRIPT);
			}
		}
	}
}
