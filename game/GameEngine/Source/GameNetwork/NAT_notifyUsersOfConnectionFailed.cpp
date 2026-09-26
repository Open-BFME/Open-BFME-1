// cl: /DNDEBUG /MD /EHsc
// NAT::notifyUsersOfConnectionFailed, RVA 0x006715C0, 581 bytes through RET 4.
// The matched connectionUpdate body calls ILT 0x000208C4 at 0x0067244C and
// 0x00672574, and update calls it at 0x00672944 after a round timeout.
// That thunk resolves here. CONNFAILED%d names the corresponding notification.
// String/request ABI views are shared in shape with NAT_notifyTargetOfProbe.

extern "C" unsigned __cdecl strlen(const char *);
#pragma intrinsic(strlen)

namespace _STL {
template <class T> class char_traits;
template <class T> class allocator;

// Declaration-only STLport string view: assign(begin,end) is the established
// specialization reached through ILT 0x0002B297 -> 0x000A5810.
template <class C, class Traits, class Allocator> class basic_string {
public:
    basic_string &assign(const C *, const C *);
    basic_string &operator=(const C *s) { return assign(s, s + strlen(s)); }

    C *begin, *end, *capacity;
};
typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

class PeerRequest {
public:
    PeerRequest();       // ILT 0x000171FC -> 0x004D51B0
    ~PeerRequest();      // ILT 0x00016BD5 -> 0x004D52D0

    int peerRequestType;
    _STL::string nick;           // +0x004
    char textPasswordEmail[36];
    _STL::string id;             // +0x034
    _STL::string options;        // +0x040
    char intermediate[0xe4 - 0x4c];
    bool isStagingRoom;          // +0x0e4; UTM payload
    char tail[0x194 - 0xe5];
};
typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

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
    int getLength() const { return data ? *((unsigned short *)data + 2) : 0; }
    bool isNotEmpty() const { return data && *((unsigned short *)data + 2) != 0; }
    void concat(const char *, int);
    void concat(char c) { concat(&c, 1); }
    void concat(const AsciiString &s) { concat(s.str(), s.getLength()); }
    const char *str() const { return data ? (char *)data + 8 : ""; }
};

class GameSlot {
public:
    UnicodeString getName() const;
    bool isHuman() const;
};

class GameSpyPeerMessageQueueInterface {
public:
    virtual ~GameSpyPeerMessageQueueInterface();
    virtual void startThread();
    virtual void endThread();
    virtual bool isThreadRunning();
    virtual bool isConnected();
    virtual bool isConnecting();
    virtual void addRequest(const PeerRequest &);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

enum NATConnectionState { NATCONNECTIONSTATE_FAILED = 6 };
struct ConnectionNodeType {
    int behavior;
    unsigned slotIndex;
};

class NAT {
protected:
    void notifyUsersOfConnectionFailed(int);
    void setConnectionState(int, NATConnectionState);

    void *vptr;
    void *transport;
    GameSlot **slotList;             // +0x008
    int state;
    int localNodeNumber;             // +0x010
    char gap[0x64 - 0x14];
    ConnectionNodeType connectionNodes[8]; // slotIndex at +0x068 + node * 8
};

void NAT::notifyUsersOfConnectionFailed(int nodeIndex)
{
    GameSlot *localSlot = slotList[connectionNodes[localNodeNumber].slotIndex];
    if (localSlot == 0) {
        setConnectionState(localNodeNumber, NATCONNECTIONSTATE_FAILED);
        return;
    }

    PeerRequest req;
    AsciiString options;
    options.format(AsciiString("CONNFAILED%d"), nodeIndex);
    req.peerRequestType = 13;
    req.isStagingRoom = true;
    req.id = "NAT";

    AsciiString names;
    for (int i = 0; i < 8; ++i) {
        if (connectionNodes[localNodeNumber].slotIndex == i)
            continue;
        if (slotList[i] == 0 || !slotList[i]->isHuman())
            continue;
        AsciiString name;
        name.translate(slotList[i]->getName());
        if (names.isNotEmpty())
            names.concat(',');
        names.concat(name);
    }
    req.nick = names.str();
    req.options = options.str();
    TheGameSpyPeerMessageQueue->addRequest(req);
}
