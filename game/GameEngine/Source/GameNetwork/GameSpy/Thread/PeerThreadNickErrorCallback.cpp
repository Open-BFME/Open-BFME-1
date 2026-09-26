// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
// BFME retail PeerThreadClass::nickErrorCallback at 0x00649AE0.
// The callback thunk at 0x00018A9D supplies this body with PEER, error type,
// and nickname. The class member m_loginName starts at offset 0x54.

#include <ctype.h>
#include <string>
#include <string.h>

typedef void *PEER;
typedef int Int;

enum
{
	PEER_IN_USE = 0,
	DISCONNECT_NICKTAKEN = 1,
	DISCONNECT_BADNICK = 2,
	PEER_RESPONSE_DISCONNECT = 1
};

class PeerThreadClass
{
	char m_prefix[0x54];

public:
	std::string m_loginName;

	void nickErrorCallback(PEER peer, Int type, const char *nick);
};

class Gen006449B0Str
{
public:
	Gen006449B0Str *erase(unsigned int pos, unsigned int n);
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
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			int reason;
		} discon;
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
extern "C" void peerRetryWithNickA(PEER peer, const char *nick);

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void PeerThreadClass::nickErrorCallback(PEER peer, Int type, const char *nick)
{
	if (type == PEER_IN_USE)
	{
		Int len = strlen(nick);
		std::string nickStr = nick;
		Int newVal = 0;
		if (nick[len - 1] == '}' && nick[len - 3] == '{' && isdigit(nick[len - 2]))
		{
			newVal = nick[len - 2] - '0' + 1;
			((Gen006449B0Str *)&nickStr)->erase(len - 3, 3);
		}

		if (newVal < 10)
		{
			nickStr.append("{");
			char tmp[2];
			tmp[0] = '0' + newVal;
			tmp[1] = '\0';
			nickStr.append(tmp);
			nickStr.append("}");
			m_loginName = nickStr;
			peerRetryWithNickA(peer, nickStr.c_str());
		}
		else
		{
			PeerResponse resp;
			resp.peerResponseType = PEER_RESPONSE_DISCONNECT;
			resp.discon.reason = DISCONNECT_NICKTAKEN;
			TheGameSpyPeerMessageQueue->addResponse(resp);
			peerRetryWithNickA(peer, NULL);
		}
	}
	else
	{
		PeerResponse resp;
		resp.peerResponseType = PEER_RESPONSE_DISCONNECT;
		resp.discon.reason = DISCONNECT_BADNICK;
		TheGameSpyPeerMessageQueue->addResponse(resp);
		peerRetryWithNickA(peer, NULL);
	}
}
#pragma optimize("y", off)
