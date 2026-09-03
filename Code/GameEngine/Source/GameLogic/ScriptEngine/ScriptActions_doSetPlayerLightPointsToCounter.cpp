// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: SET_PLAYER_LIGHT_POINTS_TO_COUNTER at retail RVA 0x002F65E0.

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

class PlayerLightPoints
{
};

class Player
{
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

extern void j_00047d34();

static __forceinline int bfmeGetLightPoints(Player *player)
{
	typedef int (PlayerLightPoints::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00047d34;
	return (reinterpret_cast<PlayerLightPoints *>(player)->*fn.member)();
}

class ScriptActions
{
protected:
	void doSetPlayerLightPointsToCounter(Parameter *player, Parameter *counter);
};

void ScriptActions::doSetPlayerLightPointsToCounter(Parameter *player,
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
				value += bfmeGetLightPoints(thePlayer);
		} while (mask);
	}

	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}
