// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// ScriptConditions::evaluatePlayerHasKilledKindOfUnits, retail 0x003297F0.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef unsigned short UnsignedShort;

class Player;
class Parameter;

class ScriptEngine
{
public:
	UnsignedShort unidentified_0034DB40(Parameter *playerParm);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

template <size_t BitCount>
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

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class PlayerKills
{
public:
	int getKillsOfKindOf(KindOfMaskType setMask, KindOfMaskType clearMask);
};

class Player
{
private:
	unsigned char m_beforeKills[0x348];

public:
	PlayerKills m_kills;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasKilledKindOfUnits(Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerHasKilledKindOfUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasKilledKindOfUnits(
	Parameter *pPlayerParm, Parameter *pCountParm, Parameter *pKindOfParm)
{
	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
	if (thePlayer) {
		PlayerKills *kills = &thePlayer->m_kills;
		if (kills) {
			KindOfMaskType setMask;
			setMask.set(pKindOfParm->m_int);
			KindOfMaskType clearMask;
			clearMask.clear();
			int value = kills->getKillsOfKindOf(setMask, clearMask);
			return value >= pCountParm->m_int;
		}
	}

	return false;
}
