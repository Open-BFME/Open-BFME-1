// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

class HotKeyAsciiStringLess
{
public:
	bool operator()(const AsciiString& lhs, const AsciiString& rhs) const
	{
		return lhs.compare(rhs) < 0;
	}
};

namespace _STL
{
	template <>
	struct less<AsciiString> : public HotKeyAsciiStringLess
	{
	};
}

#include "GameClient/HotKey.h"

// Address-derived owner: two AsciiString->HotKey maps back to back, preceded
// by an 8-byte header, both destroyed the same way as HotKeyManager::m_hotKeyMap
// (same pinned ?_M_erase@?$_Rb_tree@VAsciiString@@... callee, RVA 0x00020E37).
class Rva005B3850Owner
{
public:
	void clear(void);

private:
	char m_head[8];
	std::map<AsciiString, HotKey> m_first;
	std::map<AsciiString, HotKey> m_second;
};

void Rva005B3850Owner::clear(void)
{
	m_first.clear();
	m_second.clear();
}
