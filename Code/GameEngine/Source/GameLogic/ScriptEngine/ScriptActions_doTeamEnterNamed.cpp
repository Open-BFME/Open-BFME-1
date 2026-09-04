// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Object;
class AIGroup
{
public:
	void groupEnter(Object *transport, CommandSourceType cmd);
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
	virtual void slot26();
	virtual Object *getUnitNamedByValue(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamEnterNamed(const AsciiString &teamName, const AsciiString &unitDestName);
};

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
