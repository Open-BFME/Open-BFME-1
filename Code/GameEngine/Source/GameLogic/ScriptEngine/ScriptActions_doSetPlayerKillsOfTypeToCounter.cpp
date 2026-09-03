// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: SET_PLAYER_KILLS_OF_TYPE_TO_COUNTER at retail RVA 0x002F6920.

#include "StringInline.h"

typedef bool Bool;

class Player;
class ScriptActions;
struct ScriptCounter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getPlayerFromMask(unsigned short mask);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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

struct PlayerKills
{
	int getKillsOfType(const AsciiString &objectType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
private:
	unsigned char m_beforeKills[0x348];

public:
	PlayerKills m_kills;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

extern void j_00020dc9();

static __forceinline int bfmeGetKillsOfType(PlayerKills *kills,
	const AsciiString &objectType)
{
	typedef int (PlayerKills::*Function)(const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020dc9;
	return (kills->*fn.member)(objectType);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetPlayerKillsOfTypeToCounter(Parameter *player,
		Parameter *objectType, Parameter *counter);
};

void ScriptActions::doSetPlayerKillsOfTypeToCounter(Parameter *player,
	Parameter *objectType, Parameter *counter)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (!mask)
		return;

	Player *thePlayer = ThePlayerList->getPlayerFromMask(mask);
	if (!thePlayer)
		return;

	PlayerKills *kills = &thePlayer->m_kills;
	if (!kills)
		return;

	int value = bfmeGetKillsOfType(kills, objectType->m_string);
	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}
