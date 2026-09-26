// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The four actions that change a team's own record:
//
//   0x002F23F0  doSetTeamState                    m_state at +0x18
//   0x002F2440  doTeamCall2440                    a two-argument call on the team
//   0x002F4310  doTeamSetFlagPair                 the byte pair at +0xE4
//   0x002F4D10  doTeamRemoveAllOverrideRelations  both override tables
//
// All four are the same two lines: getTeamNamed at slot 17 with the name passed
// by value through the string wrapper, then one write or call on the team. They
// touch four different parts of Team, which is why merging them is worth doing --
// the four fields were only ever described one file at a time.

#include "ascii_string.h"

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

// Slot 17 takes the team name by value through this wrapper in all four bodies.
class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void setState(const AsciiString &state) { m_state.set(state); }
	void bfmeCall2440(void *a, void *b);
	bool removeOverrideTeamRelationship(unsigned int teamID);
	bool removeOverridePlayerRelationship(int playerIndex);

	unsigned char m_beforeState[0x18];
	AsciiString m_state;
	unsigned char m_beforeFlags[0xE4 - 0x1C];
	unsigned char m_byteE4;
	unsigned char m_byteE5;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetTeamState(const AsciiString &team, const AsciiString &state);
	void doTeamCall2440(const AsciiString &name, void *a, void *b);
	void doTeamSetFlagPair(const AsciiString &name, char value);
	void doTeamRemoveAllOverrideRelations(const AsciiString &teamName);
};

void ScriptActions::doSetTeamState(const AsciiString &team, const AsciiString &state)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (theTeam)
		theTeam->setState(state);
}

void ScriptActions::doTeamCall2440(const AsciiString &name, void *a, void *b)
{
	Team *team = TheScriptEngine->getTeamNamed(name, false);
	if (team)
		team->bfmeCall2440(a, b);
}

void ScriptActions::doTeamSetFlagPair(const AsciiString &name, char value)
{
	Team *team = TheScriptEngine->getTeamNamed(name, false);
	if (team)
	{
		team->m_byteE4 = 1;
		team->m_byteE5 = value;
	}
}

void ScriptActions::doTeamRemoveAllOverrideRelations(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		theTeam->removeOverrideTeamRelationship(0);
		theTeam->removeOverridePlayerRelationship(0);
	}
}
