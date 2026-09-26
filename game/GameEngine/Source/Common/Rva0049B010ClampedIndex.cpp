// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Non-empty UnicodeString at +0x68 wins; otherwise the same clamped indexed
// read as 0x0049B060 over the 4-byte vector at +0x44.

#include "PreRTS.h"
#include "Common/STLTypedefs.h"

struct Rva0049B010Data
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	wchar_t m_buffer[ 1 ];
};

struct Rva0049B010String
{
	Rva0049B010Data *m_data;

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_buffer[ 0 ] == 0;
	}
};

extern Rva0049B010String g_rva0049B010Fallback;

class Rva0049B010Owner
{
public:
	const Rva0049B010String &Rva0049B010();

private:
	unsigned char m_lead[ 0x44 ];
	std::vector<Rva0049B010String> m_items;
	unsigned char m_mid[ 0x68 - 0x50 ];
	Rva0049B010String m_override;
	unsigned char m_gap[ 0x148 - 0x6C ];
	unsigned int m_index;
};

const Rva0049B010String &Rva0049B010Owner::Rva0049B010()
{
	if ( !m_override.isEmpty() )
		return m_override;
	if ( !m_items.empty() )
	{
		if ( m_index >= m_items.size() )
			return m_items.back();
		return m_items[ m_index ];
	}
	return g_rva0049B010Fallback;
}
