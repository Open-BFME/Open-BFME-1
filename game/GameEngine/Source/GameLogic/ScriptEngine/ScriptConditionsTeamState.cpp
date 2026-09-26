// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateIsDestroyed@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamCreated@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamHasNamed@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamStateIs@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamStateIsNot@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// Every ScriptConditions condition that asks a team about itself rather than
// about where it is:
//
//   0x003245A0  evaluateIsDestroyed     ready, and nothing left alive in it
//   0x00324D00  evaluateTeamCreated     has it spawned yet
//   0x00326960  evaluateTeamHasNamed    is this unit one of its members
//   0x0032AFD0  evaluateTeamStateIs     its state string equals this one
//   0x0032B0B0  evaluateTeamStateIsNot  ... and the same comparison negated
//
// All five look the team up through getTeamNamed and then read one thing off
// it, so they share every model here. They sat in three files that each
// carried a private copy of AsciiString, Parameter and the ScriptEngine
// vtable, and a Team that stopped at whichever field its own body reached.
//
// Declared once, that Team is a single layout instead of three overlapping
// guesses: the state string at +0x18, the created flag at +0x32, the ready
// flag at +0xFC. The state comparison keeps its own shim class because the
// callee it reaches is pinned under that name -- AsciiString::compare through
// the ILT thunk at 0x000220C5, not a member of the string model below.

typedef bool Bool;

class AsciiString;

// The string comparison the state conditions reach; retail 0x000220C5.
class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const throw();

private:
	char *m_text;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyObjects(Bool includeDead);
	char contains(const AsciiString &key);

	const AsciiStringCompareShim &getState(void) const { return m_state; }
	Bool isCreated(void) { return m_created; }
	Bool isReady(void) { return m_ready; }

private:
	unsigned char m_pad[0x18];
	AsciiStringCompareShim m_state;				// this+0x18
	unsigned char m_pad1C[0x32 - 0x1C];
	Bool m_created;						// this+0x32
	unsigned char m_pad33[0xFC - 0x33];
	Bool m_ready;						// this+0xFC
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;	// slot 17, vtable+0x44
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateIsDestroyed(Parameter *);
	Bool evaluateTeamCreated(Parameter *);
	Bool evaluateTeamHasNamed(Parameter *, Parameter *);
	Bool evaluateTeamStateIs(Parameter *, Parameter *);
	Bool evaluateTeamStateIsNot(Parameter *, Parameter *);
};

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

// ?evaluateTeamCreated@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateTeamCreated(Parameter *pTeamParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (pTeam) {
		return pTeam->isCreated();
	}
	return ( false );
}

// ?evaluateTeamHasNamed@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamHasNamed(Parameter *pTeamParm, Parameter *pNameParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam) {
		return false;
	}
	if (theTeam->contains(pNameParm->getString())) {
		return true;
	}
	return false;
}

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
