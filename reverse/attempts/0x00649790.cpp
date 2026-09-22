// ?connectCallback@PeerThreadClass@@QAEXPAXH@Z
// partial score=0.3913 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/stringbaseunicode /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/UserPreferences.h"
#include <string>

typedef void *PEER;
typedef int PEERBool;
class PeerResponse
{
public:
 PeerResponse();
 ~PeerResponse();
	int peerResponseType;

	std::string groupRoomName; // can't be in union

	std::string nick;   // can't be in a union
	std::string oldNick;   // can't be in a union
	std::wstring text;  // can't be in a union
	std::string locale; // can't be in a union

	std::string stagingServerGameOptions; // full string from UTMs

	// game opts sent with PEERRESPONSE_STAGINGROOM
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;

	// game opts sent with PEERRESPONSE_STAGINGROOMPLAYERINFO
	std::string stagingRoomPlayerNames[8];

	std::string command;
	std::string commandOptions;

    union {
        struct { int value; } payloadWord0;
        struct { int reason; } payloadWord1;
        struct { int words[8]; } payload32;
        struct { int id; bool ok; } payload8a;
        struct { int result; } payload4;
        struct { int id; bool ok; bool isHostPresent; int result; } payload12;
        struct { bool isPrivate; bool isAction; int profileID; } payload8b;
        struct {
 int profileID;
 char m_pad04[0x24-4];
 unsigned int internalIP, externalIP;
 char m_field2C[256], m_field12C[256];
 bool m_field22C;
 } player;
 int payload572[143];
        struct { int words[53]; } payload212;
        struct { int words[48]; } payload192;
    };
};
typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];


class PSPlayerStats {
public:
 PSPlayerStats(); ~PSPlayerStats();
 int id;
 char m_unmodelled[0x1c0];
};
class PSRequest {
public:
 PSRequest(); ~PSRequest();
 int m_requestType;
 PSPlayerStats m_player;
 std::string m_cdkey, m_nick, m_password, m_email;
 bool m_addDiscon, m_addDesync;
 int m_lastHouse, m_extra;
 std::string m_results;
};
typedef char PSSizeCheck[sizeof(PSRequest)==0x210?1:-1];
typedef char OptionSizeCheck[sizeof(OptionPreferences)==0x14?1:-1];
class GameSpyPeerMessageQueueInterface {
public:
 virtual ~GameSpyPeerMessageQueueInterface();
 virtual void startThread(); virtual void endThread();
 virtual bool isThreadRunning(); virtual bool isConnected(); virtual bool isConnecting();
 virtual void addRequest(const void *); virtual bool getRequest(void *);
 virtual void addResponse(const PeerResponse &);
};
class GameSpyPSMessageQueueInterface {
public:
 virtual ~GameSpyPSMessageQueueInterface();
 virtual void startThread(); virtual void endThread(); virtual bool isThreadRunning();
 virtual void addRequest(const PSRequest &);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
extern unsigned int Rva00649790LocalIP;
extern char Rva012F72D0[256], Rva012F71D0[256];
bool GetLocalChatConnectionAddress(AsciiString, unsigned short, unsigned int &);
class Rva0085A850 { public: static void store(int); };
extern "C" unsigned int peerGetLocalIP(PEER);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
typedef void (*GroupCallback)(PEER,int,int,void*,const char*,int,int,int,int,void*);
void listGroupRoomsCallback(PEER,int,int,void*,const char*,int,int,int,int,void*);
extern "C" void peerListGroupRoomsA(PEER,const char*,GroupCallback,void*,int);
class PeerThreadClass {
public:
 char m_pad00[0x50];
 bool m_isConnecting,m_isConnected;
 char m_pad52[2];
 std::string m_loginName,m_originalName,m_password,m_email;
 int m_profileID;
 void connectCallback(PEER,int);
};
void PeerThreadClass::connectCallback(PEER peer, int success)
{
 PeerResponse resp;
 if (!success) {
  resp.peerResponseType=1;
  resp.payloadWord1.reason=4;
  resp.player.m_field22C=false;
  TheGameSpyPeerMessageQueue->addResponse(resp);
  return;
 }
 m_isConnected=true;
 resp.peerResponseType=0;
 resp.player.profileID=m_profileID;
 resp.nick=m_loginName;
 bool found=GetLocalChatConnectionAddress("peerchat.gamespy.com",6667,Rva00649790LocalIP);
 Rva0085A850::store(Rva00649790LocalIP);
 if (!found) {
  OptionPreferences pref;
  Rva00649790LocalIP=htonl(pref.getOnlineIPAddress());
 }
 unsigned int externalIP=peerGetLocalIP(peer);
 resp.player.internalIP=htonl(Rva00649790LocalIP);
 resp.player.externalIP=htonl(externalIP);
 unsigned int i=0;
 do { resp.player.m_field2C[i]=Rva012F72D0[i]; } while (Rva012F72D0[i++]);
 i=0;
 do { resp.player.m_field12C[i]=Rva012F71D0[i]; } while (Rva012F71D0[i++]);
 resp.player.m_field22C=true;
 TheGameSpyPeerMessageQueue->addResponse(resp);
 PSRequest psReq;
 psReq.m_requestType=0;
 psReq.m_player.id=m_profileID;
 psReq.m_nick=m_originalName;
 psReq.m_email=m_email;
 psReq.m_password=m_password;
 TheGameSpyPSMessageQueue->addRequest(psReq);
 peerListGroupRoomsA(peer,"\\roomType",listGroupRoomsCallback,this,1);
}
