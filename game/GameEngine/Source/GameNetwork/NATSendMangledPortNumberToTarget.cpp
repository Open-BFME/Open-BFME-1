// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail body reached by the NAT public method's incremental-link thunk.
// The local declarations use the BFME request layout proven by the online
// custom-match request body.

#include "../../Include/Common/ScalarTypes.h"

typedef unsigned short WideChar;



extern "C" unsigned int strlen(const char *text);

template <typename T>
struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[1];
};

class UnicodeString;
class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	void translate(const UnicodeString &source);
	void __cdecl format(AsciiString format, ...);
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class GameSlot
{
public:
	UnicodeString getName() const;
};

namespace _STL
{
template <class T> class char_traits;
template <class T> class allocator;

// Declaration-only STLport string view: assign(first, last) is the
// specialization matched at 0x000A5810, reached through ILT 0x0002B297.
template <class C, class Traits, class Allocator> class basic_string
{
public:
	basic_string &assign(const C *first, const C *last);

private:
	char m_bytes[12];
};
typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();

	int peerRequestType;
	_STL::string nick;
	char m_mid[0x24];
	_STL::string id;
	_STL::string options;
	char m_pad4C[0xE4 - 0x4C];
	struct
	{
		unsigned char isStagingRoom;
	} UTM;
	char m_tail[0x194 - 0xE5];
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual Bool isThreadRunning() = 0;
	virtual Bool isConnected() = 0;
	virtual Bool isConnecting() = 0;
	virtual void addRequest(const PeerRequest &request) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class NAT
{
protected:
	virtual ~NAT();
	void *m_transport;
	GameSlot **m_slotList;
	Int m_NATState;
	Int m_localNodeNumber;
	Int m_targetNodeNumber;
	UnsignedInt m_localIP;
};

class NATSendMangledPortShim : public NAT
{
public:
	void send(UnsignedShort mangledPort, GameSlot *targetSlot);
};

// ?send@NATSendMangledPortShim@@QAEXGPAVGameSlot@@@Z
void NATSendMangledPortShim::send(UnsignedShort mangledPort, GameSlot *targetSlot)
{
	PeerRequest req;
	AsciiString options;
	options.format(AsciiString("PORT%d %d %08X"), m_localNodeNumber, mangledPort, m_localIP);

	req.peerRequestType = 0xD;
	req.UTM.isStagingRoom = 1;
	req.id.assign("NAT/", "NAT/" + 4);
	AsciiString hostName;
	hostName.translate(targetSlot->getName());
	const char *nick = hostName.str();
	req.nick.assign(nick, nick + strlen(nick));
	const char *requestOptions = options.str();
	req.options.assign(requestOptions, requestOptions + strlen(requestOptions));
	TheGameSpyPeerMessageQueue->addRequest(req);
}
