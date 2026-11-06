// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/Libraries/Include/Lib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Collection transfer; layout and ABI evidence: identity_evidence/00366ca0-collection-xfer.md.

#include <vector>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

#include "ascii_string.h"

#include "xfer.h"
#include "Coord2D.h"

class LivingWorldPlayerArmy
{
public:
	LivingWorldPlayerArmy();
	LivingWorldPlayerArmy(const LivingWorldPlayerArmy &other);
	~LivingWorldPlayerArmy();
	virtual void *slot0(unsigned int flags);
	virtual void slot1();
	virtual void slot2();
	virtual void xfer(Xfer *xfer);
	// ?bfmeXfer@LivingWorldPlayerArmy@@QAEXPAVXfer@@@Z absent-from-retail
	__forceinline void bfmeXfer(Xfer *xferArg) { xfer(xferArg); }					// offset 0xc

private:
	char m_body[0x54];
};

namespace _STL
{
template <> LivingWorldPlayerArmy *vector<LivingWorldPlayerArmy>::erase(
	LivingWorldPlayerArmy *first, LivingWorldPlayerArmy *last);
}

class BfmeLivingWorldPlayerArmyCollection
{
public:
	void xfer(Xfer *xfer);

private:
	char m_pad00[4];
	AsciiString m_fieldA;					// +0x04, xfer slot 0x68
	Coord2D m_fieldB;				// +0x08, xfer slot 0x50 (8 bytes)
	Bool m_version;					// +0x10, xfer slot 0x8c
	Int m_fieldD;					// +0x14, xfer slot 0x78 (also used for the Int count/value fields)
	std::vector<LivingWorldPlayerArmy> m_armies;	// +0x18
	std::vector<Int> m_uniqueIds;			// +0x24
};

// ?xfer@BfmeLivingWorldPlayerArmyCollection@@QAEXPAVXfer@@@Z
void BfmeLivingWorldPlayerArmyCollection::xfer(Xfer *xferArg)
{
	*xferArg == m_fieldA;
	*xferArg == m_fieldB;
	*xferArg == m_version;
	*xferArg == m_fieldD;

	if (xferArg->IsLoading())
	{
		m_armies.clear();
		m_uniqueIds.clear();

		Int count;
		*xferArg == count;
		for (Int i = 0; i < count; ++i)
		{
			LivingWorldPlayerArmy army;
			army.xfer(xferArg);
			m_armies.push_back(army);
		}

		Int idCount;
		*xferArg == idCount;
		for (Int i = 0; i < idCount; ++i)
		{
			Int value;
			*xferArg == value;
			m_uniqueIds.push_back(value);
		}
	}
	else
	{
		Int count = (Int)m_armies.size();
		*xferArg == count;
		for (Int i = 0; i < count; ++i)
			m_armies[i].bfmeXfer(xferArg);

		Int idCount = (Int)m_uniqueIds.size();
		*xferArg == idCount;
		for (Int i = 0; i < idCount; ++i)
			*xferArg == m_uniqueIds[i];
	}
}
