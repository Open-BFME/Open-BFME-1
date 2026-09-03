// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_GUARD_TEAM at retail RVA 0x002F64B0.

#include "StringInline.h"

typedef bool Bool;

class Team;
class AIGroup;
class ScriptActions;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
};

class BfmeAIGroupGuardTeamCall
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern void j_0002a07c();

static __forceinline void bfmeGroupGuardTeam(AIGroup *group,
	const Team *team)
{
	typedef void (BfmeAIGroupGuardTeamCall::*Function)(const Team *, int, int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002a07c;
	(reinterpret_cast<BfmeAIGroupGuardTeamCall *>(group)->*fn.member)(
		team, 0, 1);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamGuardTeam(const AsciiString &sourceTeam,
		const AsciiString &teamToGuard);
};

void ScriptActions::doTeamGuardTeam(const AsciiString &sourceTeam,
	const AsciiString &teamToGuard)
{
	Team *theSourceTeam = TheScriptEngine->getTeamNamed(sourceTeam, false);
	Team *theTeamToGuard = TheScriptEngine->getTeamNamed(teamToGuard, false);
	if (theSourceTeam && theTeamToGuard)
	{
		AIGroup *group = TheAI->createGroup();
		if (group)
		{
			theSourceTeam->getTeamAsAIGroup(group);
			bfmeGroupGuardTeam(group, theTeamToGuard);
		}
	}
}
