// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

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

class UpgradeTemplate;

class Team
{
public:
	void giveUpgrade(const UpgradeTemplate *);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &) const;
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern UpgradeCenter *TheUpgradeCenter;

class ScriptActions
{
protected:
	void doTeamUpgrade(const AsciiString &, const AsciiString &);
};

// ?doTeamUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamUpgrade(
	const AsciiString &teamName, const AsciiString &upgradeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
	if (team && upgrade) {
		team->giveUpgrade(upgrade);
	}
}
