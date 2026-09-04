// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doAttack@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction jump-table arm 33 is TEAM_ATTACK_TEAM (ZH index 33,
// unshifted this low). Both parameter-count paths call this 123B body.
// Two getTeamNamed slot-17 lookups (by-value name plus false), createGroup,
// getTeamAsAIGroup, groupAttackTeam(victim, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT).

#include "StringInline.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

const int NO_MAX_SHOTS_LIMIT = 0x7fffffff;

class Team;
class AIGroup
{
public:
	void groupAttackTeam(const Team *team, int maxShotsToFire,
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
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doAttack(const AsciiString &attackerName, const AsciiString &victimName);
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
