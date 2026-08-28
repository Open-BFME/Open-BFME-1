// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"
#include "Common/SubsystemInterface.h"

// Retail 0x00684CD0 and 0x00684C90 -- LANAPIInterface's constructor and
// destructor.
//
// Both write 0x0111AE50, a table whose slots 2/3/6/7/8 are the same defaults
// NetworkInterface's carries and whose rest is _purecall. ~LANAPI at 0x00688680
// restores exactly that pointer before tail-jumping to
// ??1SubsystemInterface@@UAE@XZ, and the bodies around it -- RequestLocations
// (0x00684E20), ResetGameStartTimer (0x00684F20), RequestLobbyLeave
// (0x006850F0), LookupGameByListOffset (0x00685150) -- are already ledgered as
// LANAPI, which is what names the base.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPIInterface : public SubsystemInterface
{
public:
	LANAPIInterface();
	virtual ~LANAPIInterface();
};

// ??0LANAPIInterface@@QAE@XZ
LANAPIInterface::LANAPIInterface()
{
}

// ??1LANAPIInterface@@UAE@XZ
LANAPIInterface::~LANAPIInterface()
{
}
