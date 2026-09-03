// cl: /DNDEBUG /MD /EHsc
// readable body of ?doBuildTeam@ScriptActions@@IAEXABVAsciiString@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void buildSpecificTeam(TeamPrototype *);
};

// BUILD_TEAM resolves prototypes through ScriptEngine slot 16 in BFME; the
// neighboring runtime-team lookup occupies slot 17 and takes an extra Bool.
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
	virtual TeamPrototype *getTeamPrototypeNamed(BfmeAsciiStringArg) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
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
