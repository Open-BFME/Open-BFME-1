// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: a destructor at retail 0x00099000, 87 bytes.  The eight-element
// array is torn down through the vector destructor iterator before the string,
// which is reverse declaration order.

#include "Common/INI.h"
#include "GameNetwork/GameInfo.h"

class StringBaseNarrowBU
{
protected:
	~StringBaseNarrowBU(void);

	char *m_bfmeNarrowBU;
};

class AsciiStringBU : public StringBaseNarrowBU
{
public:
	~AsciiStringBU(void)
	{
	}
};

class BfmeOwnerBU
{
public:
	~BfmeOwnerBU(void);

	char m_bfmePadABU[0x3c];
	AsciiStringBU m_bfmeNameBU;
	char m_bfmePadBBU[0x18];
	GameSlot m_bfmeElemsBU[8];
};

BfmeOwnerBU::~BfmeOwnerBU(void)
{
}
