// cl: /DNDEBUG /MD /EHsc
// BFME Connection::doSend, RVA 0x00661F10, 581 bytes through RET 4.
// flushConnections (0x00663708) and update (0x0066ADB1) call this through
// ILT 0x00013633. Layout and callees are checked against those retail bodies.
// This TU keeps BFME's de-pooled command references and Connection layout.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
typedef unsigned char UnsignedByte;
typedef int Int;

class NetCommandMsg {
public:
    void *vptr;
    unsigned timestamp, frame, player;
    unsigned short id;
    int type, refs;
};

class NetFrameCommandMsg : public NetCommandMsg {
public:
    unsigned originalFrame;
};

class NetCommandRef {
public:
    ~NetCommandRef();
    NetCommandMsg *getCommand() { return msg; }

    NetCommandMsg *msg;
    NetCommandRef *next, *previous;
    unsigned char relay;
    unsigned timeLastSent;
};

class NetCommandList {
public:
    void reset();
    void removeMessage(NetCommandRef *);

    void *vptr;
    NetCommandRef *first, *last, *lastInserted;
};

struct NetPacketAddress {
    unsigned ip;
    unsigned short port;
};

class NetPacket {
public:
    NetPacket();
    virtual ~NetPacket();
    void init();
    bool addCommand(NetCommandRef *);
    int getLength() { return length; }
    unsigned char *getData() { return data; }
    NetPacketAddress *getAddress() { return &address; }

    unsigned char data[0x1dc];    // +0x004
    int length;                 // +0x1e0
    NetPacketAddress address;   // +0x1e4
    int numCommands;            // +0x1ec
    NetCommandRef *last;
    unsigned lastFrame;
    unsigned short lastID;
    unsigned char lastPlayer, lastType, lastRelay;
};

class Transport {
public:
    bool queueSend(NetPacketAddress *, const unsigned char *, int);
};

class GlobalData {
public:
    char pad[0xcb4];
    unsigned networkRunAheadSlack;
};

class GameLogic {
public:
    char pad[0x3c];
    unsigned frame;
};

extern GlobalData *TheGlobalData;
extern GameLogic *TheGameLogic;
Int CommandRequiresAck(NetCommandMsg *);

class Connection {
public:
    unsigned doSend(bool throttle);

protected:
    void doRetryMetrics();

    int quitFrame;                  // +0x000; -1 until setQuitting
    unsigned quitTime;
    Transport *transport;
    NetPacketAddress address;
    unsigned addrExtra;
    NetCommandList *commands;        // +0x018
    unsigned retryTime;
    float averageLatency;
    float latencies[200];
    unsigned frameGrouping;         // +0x344
    unsigned lastTimeSent;
    unsigned unknown34C;
    int numRetries;
    unsigned retryMetricsTime;      // +0x354
};

// The separately emitted body is already owned by Connection.cpp at 0x00661D90.
// Definition visibility is required here because retail inlines this call.
void Connection::doRetryMetrics()
{
    static int numSeconds = 0;
    unsigned curTime = timeGetTime();
    if (curTime - retryMetricsTime > 10000) {
        retryMetricsTime = curTime;
        ++numSeconds;
        numRetries = 0;
    }
}

unsigned Connection::doSend(bool throttle)
{
    int numPackets = 0;
    unsigned currentTime = timeGetTime();
    if (currentTime < lastTimeSent)
        lastTimeSent = currentTime;
    bool couldQueue = true;

    if (quitFrame != -1 && currentTime > quitTime + 30000) {
        commands->reset();
        return 0;
    }
    if (currentTime - lastTimeSent < frameGrouping)
        return 0;

    NetCommandRef *msg = commands->first;
    while (msg && couldQueue) {
        // Retail allocates 0x200 bytes with operator new and constructs NetPacket.
        // The old attempt's ObjectDefectionHelper allocation identity was false.
        NetPacket *packet = new NetPacket;
        packet->init();
        packet->address = address;
        bool notDone = true;

        while (msg && notDone) {
            NetCommandRef *next = msg->next;
            unsigned timeLastSent = msg->timeLastSent;
            if (currentTime - timeLastSent > retryTime || timeLastSent == -1) {
                notDone = packet->addCommand(msg);
                if (notDone) {
                    if ((UnsignedByte)CommandRequiresAck(msg->getCommand())) {
                        if (timeLastSent != -1)
                            ++numRetries;
                        doRetryMetrics();
                        msg->timeLastSent = currentTime;

                        unsigned frame;
                        if (msg->getCommand()->type == 3)
                            frame = ((NetFrameCommandMsg *)msg->getCommand())->originalFrame;
                        else
                            frame = msg->getCommand()->frame;

                        // The command has already entered this packet. Old acknowledged
                        // command retries are retired using the configured frame slack.
                        if (frame != -1 && frame + TheGlobalData->networkRunAheadSlack < TheGameLogic->frame) {
                            commands->removeMessage(msg);
                            delete msg;
                        }
                    } else {
                        commands->removeMessage(msg);
                        delete msg;
                    }
                }
            }
            msg = next;
        }

        ++numPackets;
        if (packet->numCommands > 0) {
            couldQueue = transport->queueSend(packet->getAddress(), packet->getData(), packet->getLength());
            // Retail tests count > 5 after queueing: the throttle allows six packets.
            if (numPackets > 5 && throttle)
                couldQueue = false;
            lastTimeSent = currentTime;
        }
        delete packet;
    }
    return numPackets;
}
