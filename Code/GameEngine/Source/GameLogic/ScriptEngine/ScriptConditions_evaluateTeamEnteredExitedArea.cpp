// cl: /DNDEBUG /MD /EHsc
// The four Team entered/exited trigger-area conditions:
//
//   0x00324E40  evaluateTeamEnteredAreaEntirely   didAllEnter    0x000F5580
//   0x00324ED0  evaluateTeamEnteredAreaPartially  didPartialEnter 0x000F56D0
//   0x00324FF0  evaluateTeamExitedAreaPartially   didPartialExit  0x000F57C0
//   0x00324F60  evaluateTeamExitedAreaEntirely    didAllExit      0x000F58B0
//
// Callees are the Team.cpp cluster immediately before allInside (0x000F5A30),
// in that file's order.  Entered vs exited is the call; the two if-shapes are
// the ZH source forms (if (pTrig) return vs if (!pTrig) return 0) that each
// pair compiles to.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class PolygonTrigger;

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
	Int getInt(void) const { return m_int; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;
	unsigned char m_beforeString[0x10 - 0x0C];
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didPartialEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didPartialExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
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
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;	// slot 22, vtable+0x58
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamEnteredAreaEntirely(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamEnteredAreaPartially(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamExitedAreaEntirely(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamExitedAreaPartially(Parameter *, Parameter *, Parameter *);
};

// ?evaluateTeamEnteredAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamEnteredAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig) {
		return pTeam->didAllEnter(pTrig, (UnsignedInt)pTypeParm->getInt());
	}

	return false;
}

// ?evaluateTeamEnteredAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamEnteredAreaPartially(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig) {
		return pTeam->didPartialEnter(pTrig, (UnsignedInt)pTypeParm->getInt());
	}

	return false;
}

// ?evaluateTeamExitedAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamExitedAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (!pTrig) {
		return false;
	}

	return (pTeam->didAllExit(pTrig, (UnsignedInt)pTypeParm->getInt()));
}

// ?evaluateTeamExitedAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamExitedAreaPartially(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (!pTrig) {
		return false;
	}

	return (pTeam->didPartialExit(pTrig, (UnsignedInt)pTypeParm->getInt()));
}
