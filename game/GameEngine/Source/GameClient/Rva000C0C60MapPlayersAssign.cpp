// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Retail 0x000C0C60 assigns the eight 20-byte player records embedded at
// MapMetaData +0x54.  The surrounding MapMetaData copy/assignment bodies prove
// the count, stride, and member location; the last twelve bytes are the
// String-keyed STLport set whose assignment is reached through ILT 0x0001D10B.

#include <stl/_config.h>
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <set>

typedef unsigned char Rva000C0C60Bool;

struct Rva000C0C60PlayerRecord
{
	Rva000C0C60Bool m_human;
	Rva000C0C60Bool m_computer;
	Rva000C0C60Bool m_loadAIScripts;
	int m_forcePlayerTeam;
	std::set<AsciiString> m_factionSet;
};

class Rva000C0C60MapPlayers
{
public:
	Rva000C0C60MapPlayers &operator=(const Rva000C0C60MapPlayers &other);

private:
	Rva000C0C60PlayerRecord m_items[8];
};

Rva000C0C60MapPlayers &Rva000C0C60MapPlayers::operator=(
	const Rva000C0C60MapPlayers &other)
{
	for (int i = 0; i < 8; ++i)
	{
		m_items[i] = other.m_items[i];
	}
	return *this;
}
