// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source /Igame/Libraries/Source/WWVegas/WWLib
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
