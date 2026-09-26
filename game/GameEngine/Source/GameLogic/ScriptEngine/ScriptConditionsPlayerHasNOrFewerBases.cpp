// ?evaluatePlayerHasNOrFewerBases@ScriptConditions@@IAE_NPAVParameter@@0@Z
// BFME PLAYER_HAS_N_OR_FEWER_BASES script condition, retail 0x00328680, 281 B.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

template <size_t NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(void) {}
	BitFlags(BogusInitType, int idx) { m_bits._Unchecked_set((size_t)idx); }
	BitFlags(BogusInitType, int idx1, int idx2)
	{
		m_bits._Unchecked_set(idx1);
		m_bits._Unchecked_set(idx2);
	}

	void clear(void) { m_bits.reset(); }
	void set(int idx) { m_bits._Unchecked_set((size_t)idx); }
};

typedef BitFlags<192> KindOfMaskType;

class Parameter
{
public:
	int getInt(void) const { return m_int; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	PlayerMaskType unidentified_0034DB40(Parameter *playerParm);
	PlayerMaskType unidentified_0034DB40(const AsciiString &name);
};

class Player;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class Player
{
public:
	int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
};

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasNOrFewerBases(Parameter *baseCountParm,
		Parameter *playerParm);
};

class Rva006C9270GlobalData
{
public:
	unsigned char m_beforeSecondsBeforeBaseCheckActive[0x11f8];
	Real m_secondsBeforeBaseCheckActive;
};

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x3c];
	UnsignedInt m_frame;
};

#define TheWritableGlobalData (*(Rva006C9270GlobalData **)0x012ED5C8)
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)
#define ThePlayerList (*(PlayerList **)0x012ED748)
#define g_bfmeK1266C (*(const Real *)0x01075344)

extern const KindOfMaskType KINDOFMASK_NONE;

Bool ScriptConditions::evaluatePlayerHasNOrFewerBases(
	Parameter *baseCountParm, Parameter *playerParm)
{
	int baseCheckFrame;
	if (TheWritableGlobalData)
		baseCheckFrame = (int)(TheWritableGlobalData->m_secondsBeforeBaseCheckActive
			* g_bfmeK1266C);
	else
		baseCheckFrame = (int)(*(const Real *)0x010E1F40);

	if (TheBfmeGameLogic->m_frame < (UnsignedInt)baseCheckFrame)
		return false;

	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	KindOfMaskType setMask(KindOfMaskType::kInit, 175);
	int count = 0;
	while (mask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			count += player->countObjects(setMask, KINDOFMASK_NONE);
	}

	int limit = baseCountParm->getInt();
	Bool result = limit >= count;
	return result;
}
