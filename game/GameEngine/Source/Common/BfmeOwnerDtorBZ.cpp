// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: a destructor at retail 0x00075D70, 106 bytes.  Two bases: the
// array member goes first, then the second base restores its vftable, then the
// first base's string is released.  The null test before the vftable store is
// the this-adjustment to a base that does not sit at offset zero.

#include "Common/INI.h"
#include "GameNetwork/GameInfo.h"

extern "C" void *bfmeVftableBZ[];

class StringBaseNarrowBZ
{
protected:
	~StringBaseNarrowBZ(void);

	char *m_bfmeNarrowBZ;
};

class AsciiStringBZ : public StringBaseNarrowBZ
{
public:
	~AsciiStringBZ(void)
	{
	}
};

class BfmeFirstBZ
{
public:
	~BfmeFirstBZ(void)
	{
	}

	char m_bfmePadABZ[0x3c];
	AsciiStringBZ m_bfmeNameBZ;
	char m_bfmePadBBZ[0x18];
};

class BfmeSecondBZ
{
public:
	~BfmeSecondBZ(void)
	{
		m_bfmeVfptrBZ = bfmeVftableBZ;
	}

	void *volatile m_bfmeVfptrBZ;
};

class BfmeOwnerBZ : public BfmeFirstBZ, public BfmeSecondBZ
{
public:
	~BfmeOwnerBZ(void);

	GameSlot m_bfmeElemsBZ[8];
};

BfmeOwnerBZ::~BfmeOwnerBZ(void)
{
}
