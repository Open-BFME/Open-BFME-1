// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

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

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	void guardSupplyCenter(Team *, Int);
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

class ScriptActions
{
protected:
	void doGuardSupplyCenter(const AsciiString &, Int);
};

// ?doGuardSupplyCenter@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doGuardSupplyCenter(const AsciiString &teamName, Int supplies)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	Player *player = team->getControllingPlayer();
	if (!player) {
		return;
	}

	player->guardSupplyCenter(team, supplies);
}
