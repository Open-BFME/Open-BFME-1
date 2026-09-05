// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// LivingWorldPlayerArmy::findArmy - iterate m_armies (vector at +0x30, elem 0xB4),
// compare LivingWorldArmy::getName against the query, optionally write the index.
#include "Common/AsciiString.h"
#include <vector>

class LivingWorldArmy
{
public:
	AsciiString getName() const;

private:
	unsigned char m_bytes[0xB4];
};

class LivingWorldPlayerArmy
{
public:
	LivingWorldArmy *findArmy(const AsciiString &name, int *outIndex);

private:
	unsigned char m_prefix[0x30];
	std::vector<LivingWorldArmy> m_armies;
};

LivingWorldArmy *LivingWorldPlayerArmy::findArmy(const AsciiString &name, int *outIndex)
{
	for (unsigned i = 0; i < m_armies.size(); ++i)
	{
		AsciiString current = m_armies[i].getName();
		if (current.compare(name) == 0)
		{
			if (outIndex)
				*outIndex = (int)i;
			return &m_armies[i];
		}
	}
	return 0;
}
