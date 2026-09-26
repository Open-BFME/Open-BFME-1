// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
// Room listing callback passed to peerListGroupRoomsA at RVA 0x006499D6.
#include <string>
#include <string.h>

class PeerResponse {
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
    union {
        struct {
            int id;
            int numWaiting;
            int maxWaiting;
            int numGames;
            int numPlaying;
            int roomType;
        } groupRoom;
        int words[143];
    };
};
typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class GameSpyPeerMessageQueueInterface {
public:
    virtual ~GameSpyPeerMessageQueueInterface() {}
    virtual void startThread() = 0;
    virtual void endThread() = 0;
    virtual bool isThreadRunning() = 0;
    virtual bool isConnected() = 0;
    virtual bool isConnecting() = 0;
    virtual void addRequest(const void *) = 0;
    virtual bool getRequest(void *) = 0;
    virtual void addResponse(const PeerResponse &) = 0;
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class PeerThreadClass {
    char prefix[0x3e4];
public:
    bool m_unknown3E4;
};
extern "C" int SBServerGetIntValueA(void *, const char *, int);

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

void listGroupRoomsCallback(void *peer, int success, int groupID, void *server,
                            const char *name, int numWaiting, int maxWaiting,
                            int numGames, int numPlaying, void *param)
{
    PeerThreadClass *thread = (PeerThreadClass *)param;
    if (!thread || !success)
        return;
    PeerResponse response;
    response.peerResponseType = 3;
    response.groupRoom.id = groupID;
    response.groupRoom.numWaiting = numWaiting;
    response.groupRoom.maxWaiting = maxWaiting;
    response.groupRoom.numGames = numGames;
    response.groupRoom.numPlaying = numPlaying;
    if (server)
        response.groupRoom.roomType = SBServerGetIntValueA(server, "roomType", 1);
    if (name)
        response.groupRoomName = name;
    TheGameSpyPeerMessageQueue->addResponse(response);
    if (!groupID)
        thread->m_unknown3E4 = true;
}
