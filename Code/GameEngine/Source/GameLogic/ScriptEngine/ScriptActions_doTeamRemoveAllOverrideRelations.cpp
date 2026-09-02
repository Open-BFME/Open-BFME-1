// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: ScriptActions::doTeamRemoveAllOverrideRelations, retail 0x002F4D10, 61 bytes.
//
// ZH twin. BFME getTeamNamed is slot 17 with a by-value name and extra Bool.
// Both removeOverride* callees are already pinned at their ILTs.

class AsciiString
{
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

class Team
{
public:
	bool removeOverrideTeamRelationship(unsigned int teamID);
	bool removeOverridePlayerRelationship(int playerIndex);
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamRemoveAllOverrideRelations(const AsciiString &teamName);
};

void ScriptActions::doTeamRemoveAllOverrideRelations(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		theTeam->removeOverrideTeamRelationship(0);
		theTeam->removeOverridePlayerRelationship(0);
	}
}
