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

// Retail constructs and destroys the local PeerResponse through the ILT
// thunks at 0x00042069 and 0x00044733, not through a locally emitted
// constructor; the calls below name those thunks directly.
extern void j_00042069();
extern void j_00044733();

// Retail's local is a non-trivially destructible object of exactly 0x330
// bytes, so the frame carries its SEH scope and its destructor slot; only the
// constructor and destructor bodies come from the ILT thunks. Keeping that
// shape here is what makes the prologue, the dtor flag store and the frame
// size match retail byte for byte.
class PeerResponseSlot {
public:
    char at000[sizeof(PeerResponse)];
    __forceinline PeerResponseSlot()
    {
        typedef void (PeerResponse::*Fn)();
        union { void (*fn)(); Fn call; } u = { j_00042069 };
        (((PeerResponse *)at000)->*u.call)();
    }
    __forceinline ~PeerResponseSlot()
    {
        typedef void (PeerResponse::*Fn)();
        union { void (*fn)(); Fn call; } u = { j_00044733 };
        (((PeerResponse *)at000)->*u.call)();
    }
};

void listGroupRoomsCallback(void *peer, int success, int groupID, void *server,
                            const char *name, int numWaiting, int maxWaiting,
                            int numGames, int numPlaying, void *param)
{
    PeerThreadClass *thread = (PeerThreadClass *)param;
    if (!thread || !success)
        return;
    PeerResponseSlot slot;
    PeerResponse *response = (PeerResponse *)slot.at000;
    response->peerResponseType = 3;
    response->groupRoom.id = groupID;
    response->groupRoom.numWaiting = numWaiting;
    response->groupRoom.maxWaiting = maxWaiting;
    response->groupRoom.numGames = numGames;
    response->groupRoom.numPlaying = numPlaying;
    if (server)
        response->groupRoom.roomType = SBServerGetIntValueA(server, "roomType", 1);
    if (name)
        response->groupRoomName = name;
    TheGameSpyPeerMessageQueue->addResponse(*response);
    if (!groupID)
        thread->m_unknown3E4 = true;
}
