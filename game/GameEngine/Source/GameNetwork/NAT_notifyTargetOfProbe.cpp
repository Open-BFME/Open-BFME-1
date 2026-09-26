// cl: /DNDEBUG /MD /EHsc
// NAT::notifyTargetOfProbe, RVA 0x00671100, 374 bytes through RET 4.
// Callers use ILT 0x00028D1C. The PROBED%d request names this NAT operation;
// 0x006718BC, formerly attributed to it, lies inside a different routine.
//
// These TU-local views retain the retail string and request ABI. In particular,
// the inline AsciiString constructor forwards to StringBase<char>'s constructor
// at 0x00888BC0. Declaring the wrapper constructor out of line creates the two
// lifetime/scheduling differences that blocked the earlier reconstruction.

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
    const char *str() const { return data ? (char *)data + 8 : ""; }
};

class GameSlot {
public:
    UnicodeString getName() const;
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

class NAT {
protected:
    void notifyTargetOfProbe(GameSlot *);
    char pad[0x10];
    int localNodeNumber;
};

void NAT::notifyTargetOfProbe(GameSlot *targetSlot)
{
    PeerRequest req;
    AsciiString options;
    options.format(AsciiString("PROBED%d"), localNodeNumber);

    // BFME's UTMPLAYER request ordinal is 13. The other NAT notifications
    // share it; the reference ordinal 12 is different.
    req.peerRequestType = 13;
    req.isStagingRoom = true;
    req.id = "NAT/";

    AsciiString hostName;
    hostName.translate(targetSlot->getName());
    req.nick = hostName.str();
    req.options = options.str();
    TheGameSpyPeerMessageQueue->addRequest(req);
}
