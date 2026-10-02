// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "GameNetwork/LANGameInfo.h"

struct BfmeSlotJV
{
	unsigned char m_bfmeRawJV[0x68];
};

class BfmeOwnerJV
{
public:
	BfmeSlotJV *bfmeAtJV(int index)
	{
		if (index < 0 || index >= 8)
			return 0;

		return &m_bfmeSlotsJV[index];
	}

	int bfmeFindJV(void);

	unsigned char m_bfmeHeadJV[0xc];
	char m_bfmeActiveJV;
	unsigned char m_bfmeGapJV[0x4b];
	BfmeSlotJV m_bfmeSlotsJV[8];
};

int BfmeOwnerJV::bfmeFindJV(void)
{
	int result = -1;
	int index;

	if (m_bfmeActiveJV)
	{
		for (index = 0; index < 8; index++)
		{
			if (reinterpret_cast<LANGameSlot *>(bfmeAtJV(index))->isLocalPlayer())
			{
				result = index;
				break;
			}
		}
	}

	return result;
}
