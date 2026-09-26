// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
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
