// cl: /DNDEBUG /MD /EHsc
// NAT::update, RVA 0x006727C0, 529 bytes through RET at 0x006729D0.
// The former 477-byte queue boundary truncated this state machine. Game-start
// callers at 0x004F6E80/0x00506975/0x00545087/0x0055A3E6 load TheNAT and
// call ILT 0x0003F3AF, which resolves here, then inspect NATSTATE_DONE (3).
// BFME runs FAILED cleanup after the state branches, including when the method
// was entered in the failed state. Its menu interface also owns virtual cleanup.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Transport {
public:
    ~Transport();
};
class FirewallHelperClass {
public:
    virtual ~FirewallHelperClass();
    void flagNeedToRefresh(bool);
};
extern FirewallHelperClass *TheFirewallHelper;

class EstablishConnectionsMenu {
public:
    virtual ~EstablishConnectionsMenu();
    virtual void initMenu();
    virtual void endMenu();
};
extern EstablishConnectionsMenu *TheEstablishConnectionsMenu;

class GameSlot {
public:
    bool isHuman() const;
};
class GameSpyGameSlot : public GameSlot {
public:
    int getProfileID() const { return profileID; }
    char gap[0x44];
    int profileID;
};
class GameSpyStagingRoom {
public:
    GameSpyGameSlot *getGameSpySlot(int);
};
extern GameSpyStagingRoom *TheGameSpyGame;

// The retail stats copy layout ends with a 12-byte string at +0x1B8. Only id
// is inspected here; construction and destruction remain with the real class.
class PSPlayerStats {
public:
    PSPlayerStats(const PSPlayerStats &);
    ~PSPlayerStats();
    int id;
    char tail[0x1c4 - 4];
};
typedef char PlayerStatsSizeCheck[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];
class PSRequest;
class PSResponse;
class GameSpyPSMessageQueueInterface {
public:
    virtual ~GameSpyPSMessageQueueInterface();
    virtual void startThread();
    virtual void endThread();
    virtual bool isThreadRunning();
    virtual void addRequest(const PSRequest &);
    virtual bool getRequest(PSRequest &);
    virtual void addResponse(const PSResponse &);
    virtual bool getResponse(PSResponse &);
    virtual void trackPlayerStats(PSPlayerStats);
    virtual PSPlayerStats findPlayerStatsByID(int);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

enum NATStateType {
    NATSTATE_IDLE = 0,
    NATSTATE_DOCONNECTIONPATHS = 1,
    NATSTATE_WAITFORSTATS = 2,
    NATSTATE_DONE = 3,
    NATSTATE_FAILED = 4
};
enum NATConnectionState { NATCONNECTIONSTATE_FAILED = 6 };

class NAT {
public:
    NATStateType update();
protected:
    bool allConnectionsDoneThisRound();
    bool allConnectionsDone();
    void doThisConnectionRound();
    NATConnectionState connectionUpdate();
    void setConnectionState(int, NATConnectionState);
    void notifyUsersOfConnectionFailed(int);

    void *vptr;
    Transport *transport;
    void *slots;
    NATStateType state;
    int localNodeNumber;
    char gap[0x20 - 0x14];
    unsigned connectionRound;
    char gap2[0xc0 - 0x24];
    unsigned roundTimeout;
    static long m_timeForRoundTimeout;
};

NATStateType NAT::update() {
    static unsigned s_startStatWaitTime=0;
    if (state==NATSTATE_DONE) {state=NATSTATE_IDLE;}
    else if (state==NATSTATE_WAITFORSTATS) {
        bool gotAllStats=true;
        bool timedOut=false;
        for (int i=0;i<8;++i) {
            const GameSpyGameSlot*slot=TheGameSpyGame->getGameSpySlot(i);
            if (slot&&slot->isHuman()) {
                PSPlayerStats stats=TheGameSpyPSMessageQueue->findPlayerStatsByID(slot->getProfileID());
                if (stats.id==0)gotAllStats=false;
            }
        }
        unsigned now=timeGetTime();
        if (now>s_startStatWaitTime+5000)timedOut=true;
        if (gotAllStats||timedOut) {
            state=NATSTATE_DONE;
            if (TheEstablishConnectionsMenu) {TheEstablishConnectionsMenu->endMenu();delete TheEstablishConnectionsMenu;TheEstablishConnectionsMenu=0;}
            if (TheFirewallHelper) {delete TheFirewallHelper;TheFirewallHelper=0;}
        }
    } else if (state==NATSTATE_DOCONNECTIONPATHS) {
        if (allConnectionsDoneThisRound()==true) {
            ++connectionRound;
            roundTimeout=timeGetTime()+m_timeForRoundTimeout;
            if (allConnectionsDone()==true) {
                state=NATSTATE_WAITFORSTATS;
                TheFirewallHelper->flagNeedToRefresh(false);
                s_startStatWaitTime=timeGetTime();
            } else doThisConnectionRound();
        }
        NATConnectionState connState=connectionUpdate();
        if (timeGetTime()>roundTimeout) {setConnectionState(localNodeNumber,NATCONNECTIONSTATE_FAILED);notifyUsersOfConnectionFailed(localNodeNumber);}
        if (connState==NATCONNECTIONSTATE_FAILED)state=NATSTATE_FAILED;
    }
    if (state==NATSTATE_FAILED) {
        if (TheEstablishConnectionsMenu) {TheEstablishConnectionsMenu->endMenu();delete TheEstablishConnectionsMenu;TheEstablishConnectionsMenu=0;}
        if (TheFirewallHelper) {TheFirewallHelper->flagNeedToRefresh(true);delete TheFirewallHelper;TheFirewallHelper=0;}
        if (transport) {delete transport;transport=0;}
    }
    return state;
}
