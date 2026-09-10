// ?d_0064d320@@YAXXZ
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x0064D320 is the complete PeerThreadClass destructor (646 bytes),
// ending at RET +0x285; INT3 padding starts at +0x286.  Its paired constructor
// at 0x0064CEF0 stores PeerThreadClass's vtable 0x011196BC after calling the
// ThreadClass base constructor.  The member order below is the authentic
// PeerThread.cpp order, with the BFME +0x208/+0x20C staging-map placement.

#include "PreRTS.h"
#include <string>

// These are opaque TU-local views of the already-proven retail objects.  Their
// sizes and destructor ILTs are the evidence, while their contents are not
// needed by this destructor body.
struct RvaThreadBase
{
	char bytes[0x54];
	~RvaThreadBase();
};

struct RvaPeerRequest
{
	char bytes[0x194];
	~RvaPeerRequest();
};

struct RvaStatsMap
{
	char bytes[12];
	~RvaStatsMap();
};

struct RvaStagingServerMap
{
	char bytes[12];
	~RvaStagingServerMap();
};

#pragma comment(linker, "/alternatename:??1RvaThreadBase@@QAE@XZ=??1ThreadClass@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1RvaPeerRequest@@QAE@XZ=?j_00016bd5@@YAXXZ")
#pragma comment(linker, "/alternatename:??1RvaStatsMap@@QAE@XZ=?j_0002fb2b@@YAXXZ")
#pragma comment(linker, "/alternatename:??1RvaStagingServerMap@@QAE@XZ=?j_000196af@@YAXXZ")

typedef char RvaPeerRequestSizeCheck[sizeof(RvaPeerRequest) == 0x194 ? 1 : -1];
typedef char RvaStatsMapSizeCheck[sizeof(RvaStatsMap) == 12 ? 1 : -1];
typedef char RvaStagingServerMapSizeCheck[sizeof(RvaStagingServerMap) == 12 ? 1 : -1];
typedef char RvaThreadBaseSizeCheck[sizeof(RvaThreadBase) == 0x54 ? 1 : -1];

class PeerThreadClass
{
public:
	~PeerThreadClass();

private:
	RvaThreadBase m_threadBase;                       // +0x00, ThreadClass view
	std::string m_loginName;                         // +0x54
	std::string m_originalName;                      // +0x60
	std::string m_password;                          // +0x6C
	std::string m_email;                              // +0x78
	char m_padding_84_94[0x10];
	RvaStatsMap m_groupRoomStats;                     // +0x94
	RvaStatsMap m_stagingRoomStats;                   // +0xA0
	char m_padding_AC_B0[4];
	std::string m_mapName;                            // +0xB0
	char m_padding_BC_CC[0x10];
	std::string m_playerNames[8];                     // +0xCC
	char m_padding_12C_140[0x14];
	std::string m_pingStr;                            // +0x140
	std::string m_ladderIP;                           // +0x14C
	char m_padding_158_20C[0xB4];
	RvaStagingServerMap m_stagingServers;             // +0x20C
	std::wstring m_localStagingServerName;            // +0x218
	Int m_localRoomID;                                // +0x224
	char m_padding_228_22C[4];
	RvaPeerRequest m_qmInfo;                          // +0x22C
	char m_padding_3C0_3CC[0xC];
	std::string m_matchbotName;                       // +0x3CC
};

PeerThreadClass::~PeerThreadClass()
{
}
