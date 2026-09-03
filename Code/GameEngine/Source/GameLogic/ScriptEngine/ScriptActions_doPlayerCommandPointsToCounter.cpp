// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: command-point counter setters at retail RVAs 0x002F66E0,
// 0x002F6760, and 0x002F67E0.

#include "StringInline.h"

typedef bool Bool;

class Player;
class ScriptActions;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	friend class ScriptActions;
	struct ScriptCounter *bfmeCounter(AsciiString name);
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

struct ScriptCounter
{
	int m_value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

struct BfmeCommandPointsCall
{
	int call(int includeReserved);
};

struct BfmeTotalCommandPointsCall
{
	int call();
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

extern void j_0003deb0();
extern void j_0001af23();
extern void j_00004e3f();

class PlayerCommandPoints
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
private:
	unsigned char m_beforeCommandPoints[0x30];

public:
	PlayerCommandPoints m_commandPoints;
};

static __forceinline int bfmeCommandPointsUsed(PlayerCommandPoints *points)
{
	typedef int (BfmeCommandPointsCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003deb0;
	return (reinterpret_cast<BfmeCommandPointsCall *>(points)->*fn.member)(1);
}

static __forceinline int bfmeCommandPointsAvailable(PlayerCommandPoints *points)
{
	typedef int (BfmeCommandPointsCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001af23;
	return (reinterpret_cast<BfmeCommandPointsCall *>(points)->*fn.member)(1);
}

static __forceinline int bfmeCommandPointsTotal(PlayerCommandPoints *points)
{
	typedef int (BfmeTotalCommandPointsCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00004e3f;
	return (reinterpret_cast<BfmeTotalCommandPointsCall *>(points)->*fn.member)();
}

static __forceinline Player *bfmePlayerFromParameter(Parameter *player)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (!mask)
		return 0;
	return ThePlayerList->getPlayerFromMask(mask);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetPlayerCommandPointsUsedToCounter(Parameter *player,
		Parameter *counter);
	void doSetPlayerCommandPointsAvailableToCounter(Parameter *player,
		Parameter *counter);
	void doSetPlayerCommandPointsTotalToCounter(Parameter *player,
		Parameter *counter);
};

void ScriptActions::doSetPlayerCommandPointsUsedToCounter(Parameter *player,
	Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsUsed(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}

void ScriptActions::doSetPlayerCommandPointsAvailableToCounter(
	Parameter *player, Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsAvailable(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}

void ScriptActions::doSetPlayerCommandPointsTotalToCounter(Parameter *player,
	Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsTotal(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}
