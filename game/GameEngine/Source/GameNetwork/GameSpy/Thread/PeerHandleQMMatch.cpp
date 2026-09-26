// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
// BFME retail PeerThreadClass::handleQMMatch, RVA 0x00649180, 653 bytes.
// playerMessageCallback (0x0064A2E0) passes PEER, map, seed and six token
// arrays through ILT 0x0003EA68; this body returns with ret 36.  The previous
// no-argument naked claim was an incorrect ABI identity.
//
// PeerThread.cpp supplies the algorithm. BFME adds a sixth numeric per-player
// value and a 16-bit port array to the quick-match response. The sixth field's
// original spelling is unknown, so it is called extra here. Present players
// receive port 8088+i; absent players receive extra=-1 and zero IP/side/color/NAT.
// The local PeerResponse view keeps the retail 0x330-byte STLport layout;
// words[] reserves unrelated response union members without guessing names.

#include <string>
#include <string.h>
#include <stdlib.h>

typedef void *PEER;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
static const Int MAX_SLOTS = 8;

enum MessageType
{
	NormalMessage,
	ActionMessage
};

enum QMStatus
{
	QM_IDLE,
	QM_JOININGQMCHANNEL,
	QM_LOOKINGFORBOT,
	QM_SENTINFO,
	QM_WORKING,
	QM_POOLSIZE,
	QM_WIDENINGSEARCH,
	QM_MATCHED,
	QM_INCHANNEL,
	QM_NEGOTIATINGFIREWALLS,
	QM_STARTINGGAME,
	QM_COULDNOTFINDBOT,
	QM_COULDNOTFINDCHANNEL,
	QM_COULDNOTNEGOTIATEFIREWALLS,
	QM_STOPPED
};

class PeerResponse
{
public:
	int peerResponseType;

	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[MAX_SLOTS];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			Bool isPrivate;
			Bool isAction;
			Int profileID;
		} message;
		struct
		{
			QMStatus status;
			Int poolSize;
			Int mapIdx;
			Int seed;
			UnsignedInt IP[MAX_SLOTS];
			unsigned short port[MAX_SLOTS];
			Int side[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int nat[MAX_SLOTS];
			Int extra[MAX_SLOTS];
		} qmStatus;
		int words[143];
	};
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual bool isThreadRunning(void) = 0;
	virtual bool isConnected(void) = 0;
	virtual bool isConnecting(void) = 0;
	virtual void addRequest(const void *) = 0;
	virtual bool getRequest(void *) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class PeerThreadClass
{
char prefix[0x54];
	std::string m_loginName;
	char gap[0x228-0x60];
	QMStatus m_qmStatus;
public:
	void handleQMMatch(PEER peer, Int mapIndex, Int seed,
		char *playerName[MAX_SLOTS], char *playerIP[MAX_SLOTS],
		char *playerSide[MAX_SLOTS], char *playerColor[MAX_SLOTS],
		char *playerNAT[MAX_SLOTS], char *playerExtra[MAX_SLOTS]);
};

extern "C" void peerLeaveRoomA(PEER,int,const char*);
extern "C" void peerMessagePlayerA(PEER,const char*,const char*,MessageType);
void PeerThreadClass::handleQMMatch(PEER peer,Int mapIndex,Int seed,
 char *playerName[MAX_SLOTS],char *playerIP[MAX_SLOTS],char *playerSide[MAX_SLOTS],
 char *playerColor[MAX_SLOTS],char *playerNAT[MAX_SLOTS],char *playerExtra[MAX_SLOTS])
{
 if(m_qmStatus==QM_WORKING) {
  m_qmStatus=QM_MATCHED;
  peerLeaveRoomA(peer,1,"");
  for(Int i=0;i<MAX_SLOTS;++i) {
   if(playerName[i] && stricmp(playerName[i],m_loginName.c_str()))
    peerMessagePlayerA(peer,playerName[i],"We're matched!",NormalMessage);
  }
  PeerResponse resp;
  resp.peerResponseType=17;
  resp.qmStatus.status=QM_MATCHED;
  for(Int i=0;i<MAX_SLOTS;++i) {
   if(playerName[i]) {
    resp.stagingRoomPlayerNames[i]=playerName[i];
    resp.qmStatus.IP[i]=atoi(playerIP[i]);
    resp.qmStatus.port[i]=8088+i;
    resp.qmStatus.side[i]=atoi(playerSide[i]);
    resp.qmStatus.color[i]=atoi(playerColor[i]);
    resp.qmStatus.nat[i]=atoi(playerNAT[i]);
    resp.qmStatus.extra[i]=atoi(playerExtra[i]);
   } else {
    resp.stagingRoomPlayerNames[i]="";
    resp.qmStatus.IP[i]=0;
    resp.qmStatus.side[i]=0;
    resp.qmStatus.color[i]=0;
    resp.qmStatus.nat[i]=0;
    resp.qmStatus.extra[i]=-1;
   }
  }
  resp.qmStatus.seed=seed;
  resp.qmStatus.mapIdx=mapIndex;
  TheGameSpyPeerMessageQueue->addResponse(resp);
 }
}
