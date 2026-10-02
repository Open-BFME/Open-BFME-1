// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring8 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/BitFlags.h"

class BfmeSubBMC
{
public:
	BitFlags<86> m_bfmeBits;
};

struct BfmeOwnerBMC
{
	unsigned char m_bfmeHead[0x90];
	BfmeSubBMC m_bfmeSub;
};

class BfmeThingBMC
{
public:
	void bfmeGoBMC(BfmeOwnerBMC *owner);
	unsigned char m_bfmeHead[8];
	BitFlags<86> m_bfmeA;
	BitFlags<86> m_bfmeB;
};

void BfmeThingBMC::bfmeGoBMC(BfmeOwnerBMC *owner)
{
	owner->m_bfmeSub.m_bfmeBits.testSetAndClear(m_bfmeA, m_bfmeB);
}
