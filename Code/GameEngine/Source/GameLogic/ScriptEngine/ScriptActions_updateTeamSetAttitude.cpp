// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?updateTeamSetAttitude@ScriptActions@@IAEXABVAsciiString@@H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

enum AttitudeType
{
	AI_SLEEP = -2,
	AI_PASSIVE = -1,
	AI_NORMAL = 0,
	AI_ALERT = 1,
	AI_AGGRESSIVE = 2
};

class AIGroup
{
public:
	void setAttitude(AttitudeType attitude);
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
	void updateTeamSetAttitude(const AsciiString &teamName, int attitude);
};

void ScriptActions::updateTeamSetAttitude(const AsciiString &teamName, int attitude)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theSrcTeam)
	{
		AIGroup *pAIGroup = TheAI->createGroup();
		if (pAIGroup)
		{
			theSrcTeam->getTeamAsAIGroup(pAIGroup);
			pAIGroup->setAttitude((AttitudeType)attitude);
		}
	}
}
