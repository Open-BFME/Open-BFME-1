// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Open-BFME: SET_PLAYER_KILLS_OF_KINDOF_TO_COUNTER at retail RVA 0x002FCEA0.

#include "StringInline.h"
#include <bitset>

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
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

template <size_t BitCount>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
private:
	_STL::bitset<BitCount> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags()
	{
	}

	BitFlags(BogusInitType, int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

	void clear()
	{
		m_bits.reset();
	}

	void set(int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

};

typedef BitFlags<192> KindOfMaskType;

struct ScriptCounter
{
	int m_value;
};

class PlayerKills
{
	public:
	int getKillsOfKindOf(KindOfMaskType setMask,
		KindOfMaskType clearMask);
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

extern void j_00036d72();

static __forceinline int bfmeGetKillsOfKindOf(PlayerKills *kills,
	KindOfMaskType setMask, KindOfMaskType clearMask)
{
	typedef int (PlayerKills::*Function)(KindOfMaskType,
		KindOfMaskType);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_00036d72;
	return (kills->*function.member)(setMask, clearMask);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetPlayerKillsOfKindOfToCounter(Parameter *player,
		Parameter *kindOf, Parameter *counter);
};

// ?doSetPlayerKillsOfKindOfToCounter@ScriptActions@@IAEXPAVParameter@@00@Z
void ScriptActions::doSetPlayerKillsOfKindOfToCounter(Parameter *player,
	Parameter *kindOf, Parameter *counter)
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

	KindOfMaskType setMask;
	setMask.set(kindOf->m_int);
	KindOfMaskType clearMask;
	clearMask.clear();
	int value = bfmeGetKillsOfKindOf(kills, setMask, clearMask);
	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}
