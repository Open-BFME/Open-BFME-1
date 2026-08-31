// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
public:
	Bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

private:
	struct Header
	{
		int refCount;
		unsigned short length;
	};
	Header *m_data;
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

class TeamPrototype
{
public:
	Player *getControllingPlayer() const;
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

class Player
{
public:
	void recruitSpecificTeam(TeamPrototype *, Real, const Coord3D *);
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
	virtual TeamPrototype *getTeamPrototypeNamed(BfmeAsciiStringArg) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doRecruitTeam(const AsciiString &, Real, const AsciiString &);
};

// ?doRecruitTeam@ScriptActions@@IAEXABVAsciiString@@M0@Z
void ScriptActions::doRecruitTeam(
	const AsciiString &teamName, Real recruitRadius, const AsciiString &recruitAtTeamName)
{
	TeamPrototype *teamPrototype = TheScriptEngine->getTeamPrototypeNamed(teamName);
	if (!teamPrototype) {
		return;
	}

	Player *player = teamPrototype->getControllingPlayer();
	if (!player) {
		return;
	}

	if (!recruitAtTeamName.isEmpty()) {
		Team *recruitAtTeam = TheScriptEngine->getTeamNamed(recruitAtTeamName, false);
		if (!recruitAtTeam) {
			return;
		}

		Coord3D position;
		recruitAtTeam->getEstimateTeamPosition(&position);
		player->recruitSpecificTeam(teamPrototype, recruitRadius, &position);
		return;
	}

	player->recruitSpecificTeam(teamPrototype, recruitRadius, 0);
}
