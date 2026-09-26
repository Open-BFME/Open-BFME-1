// cl: /DNDEBUG /MD /EHsc
// RVA 0x00661E00, 207 bytes through RET 12. bfmeConfigurePeer is descriptive;
// it does not claim the reference's no-argument Connection::init identity.
// attachPlayersFromGameInfo calls ILT 0x00034E9B at 0x0066675C/0x006667DA,
// passing the peer address, GameSlot::getName result and manager transport.
// The first caller has just constructed a 0x358-byte Connection. Its alternate
// relay-address path invokes this same method on that Connection again.

class Transport;

class NetCommandList {
public:
    NetCommandList();
    virtual ~NetCommandList();
    void reset();

    void *first, *last, *lastInserted;
};

template <class T> class StringBase {
    friend class Connection;
public:
    StringBase &operator=(const StringBase &other) { set(other); return *this; }
private:
    void set(const StringBase &);
    void *data;
};

typedef StringBase<unsigned short> UnicodeString;

struct NetPacketAddress {
    unsigned ip;
    unsigned short port;
};

class Connection {
public:
    void bfmeConfigurePeer(const NetPacketAddress &, const UnicodeString &, Transport *);

    int quitFrame;                  // +0x000
    unsigned quitTime;
    Transport *transport;
    NetPacketAddress address;       // +0x00c; retail copies all eight bytes
    UnicodeString playerName;       // +0x014
    NetCommandList *commands;
    unsigned retryTime;             // +0x01c; retained by this method
    float averageLatency;
    float latencies[200];
    unsigned frameGrouping;         // +0x344
    unsigned lastTimeSent;
    unsigned unknown34C;
    int numRetries;
    unsigned retryMetricsTime;
};

void Connection::bfmeConfigurePeer(const NetPacketAddress &peerAddress,
    const UnicodeString &name, Transport *peerTransport)
{
    transport = peerTransport;
    address = peerAddress;
    // Inline StringBase assignment calls the wide set body at 0x00888530.
    playerName = name;

    if (commands == 0) {
        commands = new NetCommandList;
        // Retail init and reset both route to 0x006731A0 through ILT 0x0000B9CE.
        commands->reset();
    }
    commands->reset();

    lastTimeSent = 0;
    unknown34C = 0;
    numRetries = 0;
    retryMetricsTime = 0;
    frameGrouping = 1;
    for (int i = 0; i < 200; ++i)
        latencies[i] = 0;
    averageLatency = 0;
    quitTime = 0;
    quitFrame = -1;
}
