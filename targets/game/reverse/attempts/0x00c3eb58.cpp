// $L25751
// partial score=0.4872 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: a destructor at retail 0x00619BB0, 106 bytes.  Two bases: the
// array member goes first, then the second base restores its vftable, then the
// first base's string is released.  The null test before the vftable store is
// the this-adjustment to a base that does not sit at offset zero.

#include "Common/INI.h"
#include "GameNetwork/GameInfo.h"

extern "C" void *bfmeVftableCB[];

class StringBaseNarrowCB
{
protected:
	~StringBaseNarrowCB(void);

	char *m_bfmeNarrowCB;
};

class AsciiStringCB : public StringBaseNarrowCB
{
public:
	~AsciiStringCB(void)
	{
	}
};

class BfmeFirstCB
{
public:
	~BfmeFirstCB(void)
	{
	}

	char m_bfmePadACB[0x3c];
	AsciiStringCB m_bfmeNameCB;
	char m_bfmePadBCB[0x18];
};

class BfmeSecondCB
{
public:
	~BfmeSecondCB(void)
	{
		m_bfmeVfptrCB = bfmeVftableCB;
	}

	void *volatile m_bfmeVfptrCB;
};

class BfmeOwnerCB : public BfmeFirstCB, public BfmeSecondCB
{
public:
	~BfmeOwnerCB(void);

	GameSlot m_bfmeElemsCB[8];
};

BfmeOwnerCB::~BfmeOwnerCB(void)
{
}
