// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Retail 0x00646AA0: updateBuddyStatus from GameNetwork/GameSpy/Thread/PeerThread.cpp.
// BuddyRequest is 0x2b8 bytes: retail _Construct at 0x0063AD00 copies 174
// dwords and deque allocation at 0x0063CD80 requests 696 bytes. The unknown
// tail is storage only; queue vtable 0x01118E70 slot 6 routes to addRequest.

#include <stdio.h>
#include <string.h>
#include <string>

typedef int Int;
typedef bool Bool;
typedef int GPProfile;
typedef int GPEnum;

enum GameSpyBuddyStatus
{
	BUDDY_OFFLINE,
	BUDDY_ONLINE,
	BUDDY_LOBBY,
	BUDDY_STAGING,
	BUDDY_LOADING,
	BUDDY_PLAYING,
	BUDDY_MATCHING,
	BUDDY_MAX
};

enum GPStatus
{
	GP_OFFLINE = 0,
	GP_ONLINE = 1,
	GP_PLAYING = 2,
	GP_STAGING = 3,
	GP_CHATTING = 4
};

class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_SETSTATUS = 9
	};

	int buddyRequestType;
	union
	{
		struct
		{
			GPEnum status;
			char statusString[256];
			char locationString[256];
		} status;
		char body[0x204];
	} arg;
	char _bfme_pad_tail[0xB0];
};

typedef char BuddyRequestSizeCheck[sizeof(BuddyRequest) == 0x2B8 ? 1 : -1];

class BuddyResponse;

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual Bool isThreadRunning(void) = 0;
	virtual Bool isConnected(void) = 0;
	virtual Bool isConnecting(void) = 0;
	virtual void addRequest(const BuddyRequest& req) = 0;
	virtual Bool getRequest(BuddyRequest& req) = 0;
	virtual void addResponse(const BuddyResponse& resp) = 0;
	virtual Bool getResponse(BuddyResponse& resp) = 0;
	virtual GPProfile getLocalProfileID(void) = 0;
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

void updateBuddyStatus(volatile GameSpyBuddyStatus status, Int groupRoom,
	std::string gameName)
{
	BuddyRequest req;
	if (!TheGameSpyBuddyMessageQueue)
		return;

	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	switch (status)
	{
	case BUDDY_OFFLINE:
		req.arg.status.status = GP_OFFLINE;
		strcpy(req.arg.status.statusString, "Offline");
		strcpy(req.arg.status.locationString, "");
		break;
	case BUDDY_ONLINE:
		req.arg.status.status = GP_ONLINE;
		strcpy(req.arg.status.statusString, "Online");
		strcpy(req.arg.status.locationString, "");
		break;
	case BUDDY_LOBBY:
		req.arg.status.status = GP_CHATTING;
		strcpy(req.arg.status.statusString, "Chatting");
		sprintf(req.arg.status.locationString, "%d", groupRoom);
		break;
	case BUDDY_STAGING:
		req.arg.status.status = GP_STAGING;
		strcpy(req.arg.status.statusString, "Staging");
		sprintf(req.arg.status.locationString, "%s", gameName.c_str());
		break;
	case BUDDY_LOADING:
		req.arg.status.status = GP_PLAYING;
		strcpy(req.arg.status.statusString, "Loading");
		sprintf(req.arg.status.locationString, "%s", gameName.c_str());
		break;
	case BUDDY_PLAYING:
		req.arg.status.status = GP_PLAYING;
		strcpy(req.arg.status.statusString, "Playing");
		sprintf(req.arg.status.locationString, "%s", gameName.c_str());
		break;
	case BUDDY_MATCHING:
		req.arg.status.status = GP_ONLINE;
		strcpy(req.arg.status.statusString, "Matching");
		strcpy(req.arg.status.locationString, "");
		break;
	}

	TheGameSpyBuddyMessageQueue->addRequest(req);
}

