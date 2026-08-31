// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
private:
	char *m_text;
};
class Player;

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

class TeamPrototype
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	void buildSpecificTeam(TeamPrototype *);
};

// BUILD_TEAM resolves prototypes through ScriptEngine slot 16 in BFME; the
// neighboring runtime-team lookup occupies slot 17 and takes an extra Bool.
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
	virtual TeamPrototype *getTeamPrototypeNamed(BfmeAsciiStringArg) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doBuildTeam(const AsciiString &);
};

// ?doBuildTeam@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doBuildTeam(const AsciiString &teamName)
{
	TeamPrototype *teamPrototype = TheScriptEngine->getTeamPrototypeNamed(teamName);
	if (teamPrototype) {
		Player *player = teamPrototype->getControllingPlayer();
		if (player) {
			player->buildSpecificTeam(teamPrototype);
		}
	}
}
