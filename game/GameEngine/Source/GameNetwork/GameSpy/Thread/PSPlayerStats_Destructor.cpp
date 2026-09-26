// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: PSPlayerStats::~PSPlayerStats, retail 0x000A5150, 654 bytes --
// the compiler-generated destructor of the persistent-storage stats record
// (a run of std::map<Int,Int> members and strings).  Same include set and
// shims as PeerDefs.cpp; _STLP_NO_EXCEPTIONS makes the inlined _Rb_tree
// teardown take the shape retail has (no try/catch inside the STLport
// helpers, so MSVC 7.1 inlines them).  The anchor below is absent from
// retail: it only forces the destructor to be emitted in this TU.
#define _STLP_NO_EXCEPTIONS 1
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include "PreRTS.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"

// absent from retail
void Rva000A5150DestroyStats(PSPlayerStats *stats)
{
	stats->~PSPlayerStats();
}
