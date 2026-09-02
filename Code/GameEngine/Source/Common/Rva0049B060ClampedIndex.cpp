// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Clamped indexed read over a 4-byte vector at +0x50. Empty returns a shared
// fallback; an in-range index returns that slot; otherwise the last element.

#include "PreRTS.h"
#include "Common/STLTypedefs.h"

struct Rva0049B060Item
{
	int m_value;
};

extern Rva0049B060Item g_rva0049B060Fallback;

class Rva0049B060Owner
{
public:
	const Rva0049B060Item &Rva0049B060();

private:
	unsigned char m_lead[ 0x50 ];
	std::vector<Rva0049B060Item> m_items;
	unsigned char m_gap[ 0x148 - 0x5C ];
	unsigned int m_index;
};

const Rva0049B060Item &Rva0049B060Owner::Rva0049B060()
{
	if ( !m_items.empty() )
	{
		if ( m_index >= m_items.size() )
			return m_items.back();
		return m_items[ m_index ];
	}
	return g_rva0049B060Fallback;
}
