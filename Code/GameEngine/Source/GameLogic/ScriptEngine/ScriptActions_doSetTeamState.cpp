// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?doSetTeamState@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME: ScriptActions::doSetTeamState, retail 0x002F23F0, 52 bytes.
//
// ZH twin. BFME getTeamNamed is slot 17 with a by-value name and an extra Bool
// (false). Team::setState inlines to AsciiString::set of m_state at +0x18,
// already pinned at 0x00887C90.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const AsciiString &that);

private:
	char *m_text;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void setState(const AsciiString &state) { m_state.set(state); }

private:
	unsigned char m_pad[0x18];
	AsciiString m_state;
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetTeamState(const AsciiString &team, const AsciiString &state);
};

void ScriptActions::doSetTeamState(const AsciiString &team, const AsciiString &state)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (theTeam)
		theTeam->setState(state);
}
