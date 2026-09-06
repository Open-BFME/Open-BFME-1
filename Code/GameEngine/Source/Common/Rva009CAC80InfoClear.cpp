// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/win32localfilesystem_wide /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME7: 0x009CAC80 is a byte twin of DetailedArchivedDirectoryInfo::clear
// (ArchiveFile.cpp, 0x009D1040): an AsciiString name at +0 followed by two
// std::maps at +4 and +0x10, cleared in order. The maps here are keyed by int
// (12-byte payload, _M_erase at 0x009CAAD0 already pinned under the
// Gen_t_009cac00_p12cd tag) and by NameKeyType with a float payload (_M_erase
// through the ILT at 0x00049E13, pinned as map<NameKeyType, float>).
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "Common/GameMemory.h"
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"

// Retail clears the name with an out-of-line releaseBuffer call (ILT-free
// direct call to 0x00887940), the BFME AsciiString::clear shape this tree
// spells as BFMERetailAsciiString.
class BFMERetailAsciiString
{
public:
	void clear()
	{
		releaseBuffer();
	}
private:
	void releaseBuffer();
	char *m_data;
};

struct Gen_t_009cac00_p12cd
{
	Int m_a;
	Int m_b;
	Int m_c;
};

class Rva009CAC80Info
{
public:
	BFMERetailAsciiString m_name;
	std::map<Int, Gen_t_009cac00_p12cd> m_byIndex;
	std::map<NameKeyType, Real> m_byKey;

	void clear();
};

void Rva009CAC80Info::clear()
{
	m_name.clear();
	m_byIndex.clear();
	m_byKey.clear();
}
