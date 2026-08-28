// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"
#include "Common/SubsystemInterface.h"

// Retail 0x00681840 and 0x00681860 -- NetworkInterface's own constructor and
// destructor, the pair that brackets Network's.
//
// Both write 0x0111A850. That is NetworkInterface's vtable: slots 2/3/6 hold
// SubsystemInterface's own defaults, slots 7/8 hold bodies Network inherits
// unchanged, and every other slot is _purecall -- and Network::~Network
// (0x006823B0) restores exactly this pointer before tail-jumping to
// ??1SubsystemInterface@@UAE@XZ at 0x009A1A40. Network's table follows it at
// 0x0111A968.
//
// Its own TU: Network.cpp opts into the languagefilter shim, which these two
// bodies do not need.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface : public SubsystemInterface
{
public:
	NetworkInterface();
	virtual ~NetworkInterface();
};

// ??0NetworkInterface@@QAE@XZ
NetworkInterface::NetworkInterface()
{
}

// ??1NetworkInterface@@UAE@XZ
NetworkInterface::~NetworkInterface()
{
}
