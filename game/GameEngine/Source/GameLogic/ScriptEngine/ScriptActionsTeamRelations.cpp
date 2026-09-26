// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ?updateTeamSetAttitude@ScriptActions@@IAEXABVAsciiString@@H@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamRemoveOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The three actions that change how a team regards other teams:
//
//   0x002F29E0  updateTeamSetAttitude               how hard it fights at all
//   0x002F4C20  doTeamSetOverrideRelationToTeam     ally/enemy toward one team
//   0x002F4CA0  doTeamRemoveOverrideRelationToTeam  drop that override again
//
// All three start with getTeamNamed at slot 17; the two relation actions look up
// a second team and pass its id, and the attitude action goes through an
// AIGroup because attitude is a property of the group, not of the team record.

#include "StringInline.h"

class AIGroup;

enum AttitudeType
{
	AI_SLEEP = -2,
	AI_PASSIVE = -1,
	AI_NORMAL = 0,
	AI_ALERT = 1,
	AI_AGGRESSIVE = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	unsigned int getID() const
	{
		return m_id;
	}

	void setOverrideTeamRelationship(unsigned int id, int relation);
	void removeOverrideTeamRelationship(unsigned int id);
	void getTeamAsAIGroup(AIGroup *group);

private:
	unsigned char m_beforeId[8];
	unsigned int m_id;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void setAttitude(AttitudeType attitude);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, bool unused) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void updateTeamSetAttitude(const AsciiString &teamName, int attitude);
	void doTeamSetOverrideRelationToTeam(const AsciiString &teamName,
		const AsciiString &otherTeam, int relation);
	void doTeamRemoveOverrideRelationToTeam(const AsciiString &teamName,
		const AsciiString &otherTeam);
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

void ScriptActions::doTeamSetOverrideRelationToTeam(const AsciiString &teamName,
	const AsciiString &otherTeam, int relation)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	Team *theOtherTeam = TheScriptEngine->getTeamNamed(otherTeam, false);
	if (theTeam && theOtherTeam)
		theTeam->setOverrideTeamRelationship(theOtherTeam->getID(), relation);
}

void ScriptActions::doTeamRemoveOverrideRelationToTeam(const AsciiString &teamName,
	const AsciiString &otherTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	Team *theOtherTeam = TheScriptEngine->getTeamNamed(otherTeam, false);
	if (theTeam && theOtherTeam)
		theTeam->removeOverrideTeamRelationship(theOtherTeam->getID());
}
