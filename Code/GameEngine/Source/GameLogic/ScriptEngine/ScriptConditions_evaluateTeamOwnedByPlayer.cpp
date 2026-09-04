// cl: /DNDEBUG /MD /EHsc
// Clean BFME reconstruction of ScriptConditions::evaluateTeamOwnedByPlayer.

typedef bool Bool;
typedef unsigned short UnsignedShort;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

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

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Player;

class Team
{
public:
	Player *getControllingPlayer(void) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	UnsignedShort unidentified_0034DB40(Parameter *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluateTeamOwnedByPlayer(Parameter *, Parameter *);
};

// ?evaluateTeamOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamOwnedByPlayer(
	Parameter *teamParm, Parameter *playerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!theTeam) {
		return false;
	}

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (theTeam->getControllingPlayer() == player) {
			return true;
		}
	}

	return false;
}
