// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: SET_PLAYER_MONEY_TO_COUNTER at retail RVA 0x002F6550.

#include "StringInline.h"

typedef bool Bool;

class Player;
class ScriptActions;
struct ScriptCounter;

class ScriptEngine
{
protected:
	friend class ScriptActions;
	ScriptCounter *bfmeCounter(AsciiString name);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

struct ScriptCounter
{
	int m_value;
};

struct Money
{
	unsigned char m_beforeValue[4];
	int m_value;
};

class Player
{
};

struct BfmePlayerMoney
{
	unsigned char m_beforeMoney[0x48];
	Money m_money;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
	void doSetPlayerMoneyToCounter(Parameter *player, Parameter *counter);
};

void ScriptActions::doSetPlayerMoneyToCounter(Parameter *player,
	Parameter *counter)
{
	int value = 0;
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (mask)
	{
		do
		{
			Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
			if (thePlayer)
			{
				Money *money = &((BfmePlayerMoney *)thePlayer)->m_money;
				if (money)
					value += money->m_value;
			}
		} while (mask);
	}

	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}
