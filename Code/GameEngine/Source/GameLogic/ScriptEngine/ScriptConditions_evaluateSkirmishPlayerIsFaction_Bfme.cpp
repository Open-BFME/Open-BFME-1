// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_beforeString[0x10];
	AsciiString m_string;
};

class Player
{
public:
	const AsciiString &getSide() const { return m_side; }

private:
	char m_beforeSide[0x28];
	AsciiString m_side;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluateSkirmishPlayerIsFaction(Parameter *, Parameter *);
};

// ?evaluateSkirmishPlayerIsFaction@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateSkirmishPlayerIsFaction(
	Parameter *pSkirmishPlayerParm, Parameter *pFactionParm)
{
	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(pSkirmishPlayerParm);
	while (mask != 0)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player && player->getSide().compare(pFactionParm->getString()) == 0)
			return true;
	}

	return false;
}
