// cl: /DNDEBUG /MD /EHsc
// NAT::connectionUpdate, RVA 0x006721D0, 989 bytes through both return paths.
// BFME's connection state machine uses packed transport entries and the compact
// NAT layout below. The reference's sourcePorts array is absent in this body.
// Calls/literals were verified independently against the retail image.

extern "C" unsigned __cdecl strlen(const char *);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
extern "C" int __cdecl memcmp(const void *, const void *, unsigned);
#pragma intrinsic(strlen, memcmp)

template <class T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringBase() : data(0) {}
    StringBase(const StringBase &);
    StringBase(const T *);
    ~StringBase();
    void *data;
};

class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString(const UnicodeString &s) : StringBase<unsigned short>(s) {}
    ~UnicodeString() {}
};

class AsciiString : private StringBase<char> {
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *s) : StringBase<char>(s) {}
    AsciiString(const AsciiString &s) : StringBase<char>(s) {}
    ~AsciiString() {}
    void format(AsciiString, ...);
    void translate(const UnicodeString &);
    const char *str() const { return data ? (char *)data + 8 : ""; }
};

struct NetPacketAddress {
    unsigned ip;
    unsigned short port;
};

class GameSlot {
public:
    UnicodeString getName() const;
    unsigned getIP() const { return address.ip; }
    unsigned short getPort() const { return address.port; }
    void setIP(unsigned ip) { address.ip = ip; }
    void setPort(unsigned short port) { address.port = port; }
    char pad[0x30];
    NetPacketAddress address;
};

#pragma pack(push, 1)
struct TransportMessage {
    unsigned crc;
    unsigned char data[0x400];
    unsigned length;
    unsigned addr;
    unsigned short port;
};
#pragma pack(pop)

class Transport {
public:
    bool update();
    bool queueSend(NetPacketAddress *, const unsigned char *, int);
    TransportMessage outgoing[128], incoming[128];
};
typedef char TransportMessageSizeCheck[sizeof(TransportMessage) == 0x40e ? 1 : -1];

class FirewallHelperClass {
public:
    unsigned short getManglerResponse(unsigned short, int);
    void closeSpareSocket(unsigned short);
    bool sendToManglerFromPort(unsigned, unsigned short, unsigned short, bool);
};
extern FirewallHelperClass *TheFirewallHelper;

enum NATConnectionState {
    NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE = 2,
    NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT = 3,
    NATCONNECTIONSTATE_WAITINGFORRESPONSE = 4,
    NATCONNECTIONSTATE_DONE = 5,
    NATCONNECTIONSTATE_FAILED = 6
};
struct ConnectionNodeType {
    int behavior;
    unsigned slotIndex;
};

class NAT {
protected:
    NATConnectionState connectionUpdate();
    void setConnectionState(int, NATConnectionState);
    void sendMangledPortNumberToTarget(unsigned short, GameSlot *);
    void notifyUsersOfConnectionDone(int);
    void notifyUsersOfConnectionFailed(int);
    void sendAProbe(unsigned, unsigned short, int);
    void notifyTargetOfProbe(GameSlot *);
    void processManglerResponse(unsigned short);
public:
    // Definition visible because retail inlines the separately matched body.
    int getSlotPort(int slot) { return slotList[slot] ? slotList[slot]->getPort() : 0; }
protected:
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
    static int m_timeBetweenRetries, m_maxAllowedManglerRetries;
    static long m_keepaliveInterval, m_manglerRetryTimeInterval;
};

NATConnectionState NAT::connectionUpdate() {
    GameSlot*targetSlot=0;
    if (targetNodeNumber>=0)targetSlot=slotList[connectionNodes[targetNodeNumber].slotIndex];
    else return connectionStates[localNodeNumber];
    if (!beenProbed) {
        if (timeGetTime()>=nextPortSendTime) {
            // Retail retains these format/translation lifetimes before the actual
            // notification call, even though neither local string is consumed here.
            AsciiString options;
            int port=getSlotPort(connectionNodes[localNodeNumber].slotIndex);
            options.format(AsciiString("PORT%d %d %08X"),localNodeNumber,(unsigned short)port,localIP);
            AsciiString hostName;
            hostName.translate(targetSlot->getName());
            sendMangledPortNumberToTarget(port,targetSlot);
            nextPortSendTime=timeGetTime()+m_timeBetweenRetries;
        }
    }
    if (timeGetTime()>=nextKeepaliveTime) {
        for (int node=0;node<numNodes;++node) {
            if (myConnections[node]==true) {
                int slotIndex=connectionNodes[node].slotIndex;
                GameSlot*slot=slotList[slotIndex];
                if (slot)transport->queueSend(&slot->address,(const unsigned char*)"KEEPALIVE",10);
            }
        }
        nextKeepaliveTime=timeGetTime()+m_keepaliveInterval;
    }
    transport->update();
    for (int i=0;i<128;++i) {
        if (transport->incoming[i].length>0) {
            unsigned char*data=transport->incoming[i].data;
            if (memcmp(data,"PROBE",5)==0) {
                int fromNode=atoi((char*)data+5);
                if (fromNode==targetNodeNumber) {
                    setConnectionState(targetNodeNumber,NATCONNECTIONSTATE_DONE);
                    if (transport->incoming[i].addr!=targetSlot->getIP()) {
                        unsigned fromIP=transport->incoming[i].addr;
                        targetSlot->setIP(fromIP);
                    }
                    if (transport->incoming[i].port!=targetSlot->getPort()) {
                        targetSlot->setPort(transport->incoming[i].port);
                        unknownC4=false;
                    }
                    notifyUsersOfConnectionDone(targetNodeNumber);
                    beenProbed=true;
                }
                transport->incoming[i].length=0;
            }
            if (memcmp(data,"KEEPALIVE",9)==0)transport->incoming[i].length=0;
        }
    }
    if (connectionStates[localNodeNumber]==NATCONNECTIONSTATE_WAITINGFORRESPONSE) {
        if (timeTillNextSend!=-1 && timeTillNextSend<=timeGetTime()) {
            if (numRetries>maxNumRetriesAllowed) {
                setConnectionState(localNodeNumber,NATCONNECTIONSTATE_FAILED);
                notifyUsersOfConnectionFailed(localNodeNumber);
            } else {
                sendAProbe(targetSlot->getIP(),targetSlot->getPort(),localNodeNumber);
                timeTillNextSend=timeGetTime()+m_timeBetweenRetries;
                notifyTargetOfProbe(targetSlot);
                ++numRetries;
            }
        }
    }
    if (connectionStates[localNodeNumber]==NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE) {
        unsigned short mangledPort=0;
        if (TheFirewallHelper)mangledPort=TheFirewallHelper->getManglerResponse(packetID,0);
        if (mangledPort!=0) {
            processManglerResponse(mangledPort);
            TheFirewallHelper->closeSpareSocket(spareSocketPort);
            spareSocketPort=0;
        } else {
            if (timeGetTime()>=manglerRetryTime) {
                ++manglerRetries;
                if (manglerRetries>m_maxAllowedManglerRetries) {
                    sendMangledPortNumberToTarget(getSlotPort(connectionNodes[localNodeNumber].slotIndex),targetSlot);
                    setConnectionState(localNodeNumber,NATCONNECTIONSTATE_WAITINGFORRESPONSE);
                } else {
                    if (TheFirewallHelper)TheFirewallHelper->sendToManglerFromPort(manglerAddress,spareSocketPort,packetID,false);
                    manglerRetryTime=m_manglerRetryTimeInterval+timeGetTime();
                }
            }
        }
    }
    if (connectionStates[localNodeNumber]==NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT) {
        if (timeGetTime()>timeoutTime) {
            setConnectionState(localNodeNumber,NATCONNECTIONSTATE_FAILED);
            notifyUsersOfConnectionFailed(localNodeNumber);
        }
    }
    return connectionStates[localNodeNumber];
}
