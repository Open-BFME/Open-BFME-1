// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doTeamSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

class Team
{
public:
	unsigned int getID() const
	{
		return m_id;
	}

	void setOverrideTeamRelationship(unsigned int id, int relation);

private:
	unsigned char m_beforeId[8];
	unsigned int m_id;
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

class ScriptActions
{
protected:
	void doTeamSetOverrideRelationToTeam(const AsciiString &teamName,
		const AsciiString &otherTeam, int relation);
};

void ScriptActions::doTeamSetOverrideRelationToTeam(const AsciiString &teamName,
	const AsciiString &otherTeam, int relation)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	Team *theOtherTeam = TheScriptEngine->getTeamNamed(otherTeam, false);
	if (theTeam && theOtherTeam)
		theTeam->setOverrideTeamRelationship(theOtherTeam->getID(), relation);
}
