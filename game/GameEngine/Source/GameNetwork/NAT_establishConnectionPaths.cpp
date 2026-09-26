// cl: /DNDEBUG /MD /EHsc
// NAT::establishConnectionPaths, complete 822-byte RVA 0x00672A60..0x00672D95.
// Staging caller 0x0063A62C uses ILT 0x0000FF92 after allocating TheNAT and
// attaching its slots. BFME selects its connection menu by the current screen.
// The derived menus retain their existing address-derived constructor names:
// 0x006709F0 installs VA 0x0111A394 (OnlineCustomMatch callbacks), while
// 0x00670A10 installs VA 0x0111A3B0 (OnlineQuickMatch callbacks).
// Both call the base constructor at 0x004B2C80 through ILT 0x0000F529.
// Base vtable VA 0x010FD79C slots 4/5 resolve to the independently matched
// EstablishConnectionsMenu::setPlayerName / setPlayerStatus bodies.
// Retail leaves the null-slot behavior of the final menu loop unchanged.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Transport;
template <class T> class StringBase {
    friend class UnicodeString;
private:
    StringBase(const StringBase &);
    ~StringBase();
    void *data;
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString(const UnicodeString &s) : StringBase<unsigned short>(s) {}
    ~UnicodeString() {}
};
class GameSlot {
public:
    bool isHuman() const;
    UnicodeString getName() const;
    unsigned getNATBehavior() const { return behavior; }
    char pad[0x38];
    unsigned behavior;
};
enum NATConnectionState {
    NATCONNECTIONSTATE_IDLE = 0,
    NATCONNECTIONSTATE_WAITINGTOBEGIN = 1
};
struct ConnectionNodeType { int behavior; unsigned slotIndex; };
class EstablishConnectionsMenu {
public:
    EstablishConnectionsMenu();
    virtual ~EstablishConnectionsMenu();
    virtual void initMenu();
    virtual void endMenu();
    virtual void abortGame();
    virtual void setPlayerName(int, UnicodeString);
    virtual void setPlayerStatus(int, NATConnectionState);
    int menuState;
};
class Rva006709F0 : public EstablishConnectionsMenu {
public:
    Rva006709F0() {}
    virtual ~Rva006709F0();
    virtual void initMenu();
};
class Rva00670A10 : public EstablishConnectionsMenu {
public:
    Rva00670A10() {}
    virtual ~Rva00670A10();
    virtual void initMenu();
};
extern EstablishConnectionsMenu *TheEstablishConnectionsMenu;
class BfmeAptScreenOnlineCustomMatch;
extern BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;
// OnlineQuickMatch singleton, identified by its 0x005587F0 destructor.
extern void *g_obj12F4ABC;
class FirewallHelperClass;
extern FirewallHelperClass *TheFirewallHelper;
FirewallHelperClass *createFirewallHelper();
class GameSpyStagingRoom {
public:
    virtual ~GameSpyStagingRoom();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual int getLocalSlotNum() const;
};
extern GameSpyStagingRoom *TheGameSpyGame;
class NAT {
public:
    void establishConnectionPaths();
protected:
    void doThisConnectionRound();
    void *vptr;
    Transport *transport;
    GameSlot **slotList;
    int state;
    int localNodeNumber, targetNodeNumber; // +0x010 / +0x014
    unsigned localIP, numNodes, connectionRound;
    int numRetries, maxNumRetriesAllowed;
    unsigned short packetID, spareSocketPort;
    unsigned manglerRetryTime;
    int manglerRetries;
    unsigned short previousSourcePort;
    bool beenProbed;                      // +0x03a
    unsigned manglerAddress, timeTillNextSend;
    NATConnectionState connectionStates[8]; // +0x044
    ConnectionNodeType connectionNodes[8];  // +0x064
    bool myConnections[8];                 // +0x0a4
    unsigned nextKeepaliveTime;
    int connectionPairIndex;
    unsigned short startingPortNumber;
    unsigned nextPortSendTime, timeoutTime, roundTimeout;
    bool unknownC4;                        // cleared when a probe changes port
    static int m_connectionPairs[7][7][8];
    static long m_timeForRoundTimeout;
};
void NAT::establishConnectionPaths() {
    state = 1;
    if (!TheEstablishConnectionsMenu) {
        if (TheBfmeOnlineCustomMatch)
            TheEstablishConnectionsMenu = new Rva006709F0;
        else if (g_obj12F4ABC)
            TheEstablishConnectionsMenu = new Rva00670A10;
        else
            TheEstablishConnectionsMenu = new EstablishConnectionsMenu;
    }
    TheEstablishConnectionsMenu->initMenu();
    if (!TheFirewallHelper)
        TheFirewallHelper = createFirewallHelper();
    if (!slotList)
        return;

    numNodes = 0;
    for (int i = 0; i < 8; ++i)
        if (slotList[i] && slotList[i]->isHuman())
            ++numNodes;
    if (numNodes < 2) {
        state = 3;
        return;
    }
    connectionRound = 0;
    connectionPairIndex = numNodes - 2;
    bool connectionAssigned[8];
    for (i = 0; i < 8; ++i) {
        connectionNodes[i].slotIndex = -1;
        connectionAssigned[i] = false;
    }
    previousSourcePort = 0;

    // Pair peers with the Netgear NAT-table reset behavior first.
    unsigned otherNetgearNum = -1;
    for (i = 0; i < 8; ++i) {
        if (slotList && slotList[i] && (slotList[i]->getNATBehavior() & 8)) {
            if (otherNetgearNum == -1) {
                int nodeindex = 0;
                while (m_connectionPairs[connectionPairIndex][0][nodeindex] == -1 ||
                       connectionNodes[nodeindex].slotIndex != -1)
                    ++nodeindex;
                connectionNodes[nodeindex].slotIndex = i;
                connectionNodes[nodeindex].behavior = slotList[i]->getNATBehavior();
                connectionAssigned[i] = true;
                otherNetgearNum = nodeindex;
            } else {
                int nodeindex = 0;
                while (m_connectionPairs[connectionPairIndex][0][nodeindex] != otherNetgearNum)
                    ++nodeindex;
                connectionNodes[nodeindex].slotIndex = i;
                connectionNodes[nodeindex].behavior = slotList[i]->getNATBehavior();
                connectionAssigned[i] = true;
                otherNetgearNum = -1;
            }
        }
    }
    for (i = 0; i < 8; ++i) {
        if (connectionAssigned[i] == true)
            continue;
        if (!slotList[i])
            continue;
        if (!slotList[i]->isHuman())
            continue;
        int nodeindex = 0;
        while (connectionNodes[nodeindex].slotIndex != -1)
            ++nodeindex;
        connectionNodes[nodeindex].slotIndex = i;
        connectionNodes[nodeindex].behavior = slotList[i]->getNATBehavior();
        connectionAssigned[i] = true;
    }
    for (i = 0; i < numNodes; ++i) {
        if (connectionNodes[i].slotIndex == TheGameSpyGame->getLocalSlotNum()) {
            localNodeNumber = i;
            break;
        }
    }
    int playerNum = 0;
    for (i = 0; i < 8; ++i) {
        while (i < 8 && slotList[i] && !slotList[i]->isHuman())
            ++i;
        if (i >= 8)
            break;
        if (i != TheGameSpyGame->getLocalSlotNum()) {
            TheEstablishConnectionsMenu->setPlayerName(playerNum, slotList[i]->getName());
            TheEstablishConnectionsMenu->setPlayerStatus(playerNum, NATCONNECTIONSTATE_WAITINGTOBEGIN);
            ++playerNum;
        }
    }
    roundTimeout = timeGetTime() + m_timeForRoundTimeout;
    doThisConnectionRound();
}
