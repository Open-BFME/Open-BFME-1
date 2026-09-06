// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateTeamCreated@ScriptConditions@@IAE_NPAVParameter@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateIsDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The two ScriptConditions conditions that ask about a team's own lifecycle
// rather than where it is: has it been created yet, and has it been destroyed.
// Both look the team up by name and read a flag, so they share every model
// here -- and each carried a private copy of all of it, with a Team that
// stopped at whichever flag its own body read.
//
// Declared once, the two flags sit in one layout: m_created at +0x32 and
// m_ready at +0xFC.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyObjects(Bool includeDead);

	Bool isCreated(void) { return m_created; }
	Bool isReady(void) { return m_ready; }

private:
	unsigned char m_pad[0x32];
	Bool m_created;						// this+0x32
	unsigned char m_pad33[0xFC - 0x33];
	Bool m_ready;						// this+0xFC
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;	// slot 17, vtable+0x44
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamCreated(Parameter *);
	Bool evaluateIsDestroyed(Parameter *);
};

// ?evaluateTeamCreated@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateTeamCreated(Parameter *pTeamParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (pTeam) {
		return pTeam->isCreated();
	}
	return ( false );
}

// ?evaluateIsDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateIsDestroyed(Parameter *pTeamParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (theTeam) {
		if (!theTeam->isReady()) {
			return false;
		}
		return (!theTeam->hasAnyObjects(false));
	}
	return false;
}
