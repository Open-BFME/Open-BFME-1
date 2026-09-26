// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Near-twin of GameSpyInfo::leaveGroupRoom (GameSpyInfo_leaveGroupRoom_Thunk.cpp,
// retail 0x00634CE0): byte-identical shape, only the peerRequestType constant
// differs (6 here, not 5). ZH's PeerRequest enum
// (GameEngine/Include/GameNetwork/GameSpy/PeerThread.h) puts LOGIN=0,
// LOGOUT=1, MESSAGEPLAYER=2, MESSAGEROOM=3, JOINGROUPROOM=4,
// LEAVEGROUPROOM=5, STARTGAMELIST=6 in that order, so this issues
// PEERREQUEST_STARTGAMELIST; ZH itself builds that request inline in
// WOLLobbyMenu.cpp rather than through a GameSpyInfo method, so the method
// name is inferred from the request type, not from a matched ZH caller.

#define Matrix4x4 Matrix4
class INI;
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/PeerThread.h"

class BFMEGroupRoomInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void setCurrentGroupRoom(Int groupID);
	virtual Int getCurrentGroupRoom();
};

struct BFMERetailPeerRequest
{
	PeerRequest request;
	unsigned char m_tailPad[4];
};

// ?startGameList@GameSpyInfo@@QAEXXZ
void GameSpyInfo::startGameList(void)
{
	BFMERetailPeerRequest retailRequest;
	PeerRequest &request = retailRequest.request;
	request.peerRequestType = PeerRequest::PEERREQUEST_STARTGAMELIST;
	BFMEGroupRoomInterface *roomInterface = (BFMEGroupRoomInterface *)this;
	request.groupRoom.id = roomInterface->getCurrentGroupRoom();
	TheGameSpyPeerMessageQueue->addRequest(request);
	roomInterface->setCurrentGroupRoom(0);
	m_playerInfoMap.clear();
}
