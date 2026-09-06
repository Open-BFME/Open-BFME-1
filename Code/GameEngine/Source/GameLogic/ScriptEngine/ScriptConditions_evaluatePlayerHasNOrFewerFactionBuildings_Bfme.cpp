// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: ScriptConditions::evaluatePlayerHasNOrFewerFactionBuildings
// Retail BFME1 stores the faction-building mask in the first two dwords.

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, int idx1, int idx2)
	{
		m_bits._Unchecked_set(idx1);
		m_bits._Unchecked_set(idx2);
	}

	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

class Parameter
{
public:
	int getInt(void) const { return m_int; }

private:
	char m_unreconstructed00[0x8];
	int m_int;
};

class Player
{
public:
	int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
};

struct BfmeR1087;

class BfmeD1087
{
public:
	BfmeR1087 *bfmeLook1087(short *mask);
};

class BfmeP1087
{
public:
	int bfmeNext1087(int playerParm);
};

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasNOrFewerFactionBuildings(
		Parameter *buildingCountParm, Parameter *playerParm);
};

extern BfmeD1087 *g_bfmeD1087;
extern BfmeP1087 *g_bfmeP1087;
extern const KindOfMaskType KINDOFMASK_NONE;

// ?evaluatePlayerHasNOrFewerFactionBuildings@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluatePlayerHasNOrFewerFactionBuildings(
	Parameter *buildingCountParm, Parameter *playerParm)
{
	unsigned short mask = (unsigned short)g_bfmeP1087->bfmeNext1087((int)playerParm);
	KindOfMaskType setMask(KindOfMaskType::kInit, 37, 7);
	int count = 0;
	while (mask) {
		BfmeR1087 *record = g_bfmeD1087->bfmeLook1087((short *)&mask);
		if (record) {
			Player *player = (Player *)record;
			count += player->countObjects(setMask, KINDOFMASK_NONE);
		}
	}
	int limit = buildingCountParm->getInt();
	Bool result = limit >= count;
	return result;
}
