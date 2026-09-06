// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: clean C++ recovery of the retail body at 0x002F4AB0.
// Identity follows the ZH ScriptActions source and the TEAM_USE_COMMANDBUTTON_ABILITY_ON_NAMED
// executeAction arm: team lookup, named-object lookup, command lookup, then group dispatch.

#include "StringInline.h"

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class AIGroup;
class Object;
class Team;
class CommandButton;

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual Object *getUnitNamed(AsciiString name) = 0;
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class AIGroup
{
public:
	void groupDoCommandButtonAtObject(const CommandButton *button, Object *object,
		CommandSourceType source);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamUseCommandButtonAbilityOnNamed(const AsciiString &team,
		const AsciiString &ability, const AsciiString &target);
};

void ScriptActions::doTeamUseCommandButtonAbilityOnNamed(
	const AsciiString &team, const AsciiString &ability, const AsciiString &target)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (!theTeam)
		return;

	Object *theObject = TheScriptEngine->getUnitNamed(target);
	if (!theObject)
		return;

	const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
	if (!commandButton)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	theGroup->groupDoCommandButtonAtObject(commandButton, theObject, CMD_FROM_SCRIPT);
}
