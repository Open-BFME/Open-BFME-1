// cl: /DNDEBUG /MD /EHsc
// BFME's team-state conditions: the two retail bodies are adjacent and differ
// only in the sense of the AsciiString comparison.

typedef bool Bool;

#include "../../../../../reference/shims/stringinline/StringInline.h"

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const throw();
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Team
{
public:
	const AsciiStringCompareShim &getState(void) const
	{
		return *(const AsciiStringCompareShim *)((const char *)this + 0x18);
	}
};

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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamStateIs(Parameter *, Parameter *);
	Bool evaluateTeamStateIsNot(Parameter *, Parameter *);
};

// ?evaluateTeamStateIs@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamStateIs(
	Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return theTeam->getState().compare(stateName) == 0;
	}
	return false;
}

// ?evaluateTeamStateIsNot@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamStateIsNot(
	Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return theTeam->getState().compare(stateName) != 0;
	}
	return false;
}
