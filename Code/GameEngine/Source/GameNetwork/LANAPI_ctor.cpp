// cl: /DNDEBUG /MD /EHsc
// readable body of ??0LANAPI@@QAE@XZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// LANAPI::LANAPI, 0x006854F0, 242 bytes.
//
// Installs vtable 0x0111AF50 after SubsystemInterface's constructor. BFME
// keeps the Zero Hour initializer list and adds getenv("_EA_RTS_HEADLESS")
// to pick a 50000 ms action timeout when that variable is set else 5000.
// Transport is de-pooled at 0x410E4 bytes. Three string members need inline
// default constructors and destructors so unwind state walks 0 to 3 before
// the body; getenv in the m_actionTimeout initializer is what places that
// call between the +0x28 and +0x30 stores.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class BfmeStr
{
public:
	BfmeStr() : m_data(0) {}
	~BfmeStr() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class Transport
{
public:
	Transport();

private:
	unsigned char m_blob[0x410E4];
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
	TransportAddress() : m_ip(0), m_port(0) {}
};

class LANAPI : public SubsystemInterface
{
public:
	LANAPI();
	virtual ~LANAPI();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	void *m_lobbyPlayers;
	void *m_games;
	BfmeStr m_name;
	BfmeStr m_userName;
	BfmeStr m_hostName;
	UnsignedInt m_gameStartTime;
	Int m_gameStartSeconds;
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	TransportAddress m_directConnect;
	UnsignedInt m_lastResendTime;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	unsigned char m_pad3E[2];
	void *m_currentGame;
	TransportAddress m_localAddress;
	Transport *m_transport;
	UnsignedInt m_broadcastAddr;
	UnsignedInt m_lastUpdate;
	Bool m_isActive;
	Bool m_unknown59;
	unsigned char m_pad5A[2];
	UnsignedInt m_extra5C;
	UnsignedInt m_extra60;
	UnsignedInt m_extra64;
};

LANAPI::LANAPI()
	: m_lobbyPlayers(0)
	, m_games(0)
	, m_gameStartTime(0)
	, m_gameStartSeconds(0)
	, m_pendingAction(0)
	, m_expiration(0)
	, m_actionTimeout(getenv("_EA_RTS_HEADLESS") ? 50000 : 5000)
	, m_directConnect()
	, m_lastResendTime(0)
	, m_isInLANMenu(true)
	, m_inLobby(true)
	, m_currentGame(0)
	, m_localAddress()
	, m_transport(0)
	, m_broadcastAddr(0xFFFFFFFF)
	, m_lastUpdate(0)
	, m_isActive(true)
	, m_unknown59(false)
	, m_extra5C(0)
	, m_extra60(0)
	, m_extra64(0)
{
	m_transport = new Transport;
}
