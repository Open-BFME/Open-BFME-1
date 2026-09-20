// ??1Rva0064D320PeerThreadView@@QAE@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Oy /Ireference/shims/stlp_nodealloc /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include <map>
#include <string>

class ThreadClass
{
	public:
	virtual ~ThreadClass();

	char bytes[0x50];
};

class PeerRequest
{
	char bytes[0x194];

public:
	~PeerRequest();
};

struct Gen_t_00645480_p4pod
{
	int a[1];
};

typedef _STL::pair<const int, Gen_t_00645480_p4pod> TgPair_tree_int_p4pod_00645480;
typedef _STL::_Rb_tree<int, TgPair_tree_int_p4pod_00645480,
	_STL::_Select1st<TgPair_tree_int_p4pod_00645480>, _STL::less<int>,
	_STL::allocator<TgPair_tree_int_p4pod_00645480> > RvaStagingServerMap;

struct Rva0064C290Tree
{
	char bytes[12];
	~Rva0064C290Tree();
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];
typedef char StatsMapSizeCheck[sizeof(Rva0064C290Tree) == 12 ? 1 : -1];
typedef char StagingServerMapSizeCheck[sizeof(RvaStagingServerMap) == 12 ? 1 : -1];
typedef char ThreadBaseSizeCheck[sizeof(ThreadClass) == 0x54 ? 1 : -1];

class Rva0064D320PeerThreadView
{
public:
	~Rva0064D320PeerThreadView();

private:
	ThreadClass m_threadBase;
	std::string m_loginName;
	std::string m_originalName;
	std::string m_password;
	std::string m_email;
	char m_padding_84_94[0x10];
	Rva0064C290Tree m_groupRoomStats;
	Rva0064C290Tree m_stagingRoomStats;
	char m_padding_AC_B0[4];
	std::string m_mapName;
	char m_padding_BC_C0[4];
	std::string m_openStaging;
	std::string m_playerNames[8];
	char m_padding_12C_140[0x14];
	std::string m_pingStr;
	std::string m_ladderIP;
	char m_padding_158_20C[0xB4];
	RvaStagingServerMap m_stagingServers;
	std::wstring m_localStagingServerName;
	Int m_localRoomID;
	char m_padding_228_22C[4];
	PeerRequest m_qmInfo;
	char m_padding_3C0_3CC[0xC];
	std::string m_matchbotName;
};

typedef char RvaPeerThreadSizeCheck[sizeof(Rva0064D320PeerThreadView) == 0x3D8 ? 1 : -1];

Rva0064D320PeerThreadView::~Rva0064D320PeerThreadView()
{
}
