// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: BFME's PeerRequest has a four-byte tail after the vendored type.

#define Matrix4x4 Matrix4
class INI;
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/PeerThread.h"

struct BFMERetailPeerRequest
{
	PeerRequest request;
	unsigned char m_tailPad[4];
};

// ?joinGroupRoom@GameSpyInfo@@UAEXH@Z
void GameSpyInfo::joinGroupRoom(Int groupID)
{
	if (groupID > 0)
	{
		BFMERetailPeerRequest retailRequest;
		PeerRequest &request = retailRequest.request;
		request.peerRequestType = PeerRequest::PEERREQUEST_JOINGROUPROOM;
		request.groupRoom.id = groupID;
		TheGameSpyPeerMessageQueue->addRequest(request);
		reinterpret_cast<PlayerInfoMap *>(reinterpret_cast<char *>(this) + 0x4c)->clear();
	}
}
