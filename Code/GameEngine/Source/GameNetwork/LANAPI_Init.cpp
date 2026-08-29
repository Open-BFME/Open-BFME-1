// cl: /DNDEBUG /MD /GX
// readable body of ?init@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// Retail 0x00685690, LANAPI vtable slot 1 (table at 0x0111AF50).  BFME keeps
// Zero Hour's initialization flow and adds a headless-instance port offset:
// start at 8086 + atoi(_EA_RTS_HEADLESS), then try ports below 8094 through
// Transport::init(const TransportAddress *).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);
extern "C" __declspec(dllimport) Int __cdecl atoi(const char *text);
extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" char *__cdecl strcpy(char *dest, const char *source);
extern "C" __declspec(dllimport) Int __stdcall GetUserNameA(char *buffer, UnsignedInt *size);
extern "C" __declspec(dllimport) Int __stdcall GetComputerNameA(char *buffer, UnsignedInt *size);

enum
{
	LAN_BASE_PORT = 8086,
	LAN_LAST_PORT = 8094,
	USER_NAME_BUFFER = 257,
	COMPUTER_NAME_BUFFER = 16
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class UDP
{
public:
	Int AllowBroadcasts(Bool value);
};

class Transport
{
public:
	void reset(void);
	Bool init(const TransportAddress *address);

	Bool allowBroadcasts(Bool value)
	{
		if (!m_udp)
			return false;
		return m_udp->AllowBroadcasts(value) ? true : false;
	}

private:
	unsigned char m_bfmeHead[0x40E04];
	UDP *m_udp;
};

class AsciiString
{
public:
	void set(const char *text, Int length);

	AsciiString &operator=(const char *text)
	{
		set(text, text ? (Int)strlen(text) : 0);
		return *this;
	}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void init(void);

protected:
	unsigned char m_bfmeHeadA[0x10 - 4];
	void *m_name;                            // +0x10
	AsciiString m_userName;                  // +0x14
	AsciiString m_hostName;                  // +0x18
	UnsignedInt m_gameStartTime;             // +0x1C
	Int m_gameStartSeconds;                  // +0x20
	Int m_pendingAction;                     // +0x24
	UnsignedInt m_expiration;                // +0x28
	UnsignedInt m_actionTimeout;             // +0x2C
	TransportAddress m_directConnectRemoteAddress; // +0x30
	UnsignedInt m_lastResendTime;            // +0x38
	Bool m_isInLANMenu;                      // +0x3C
	Bool m_inLobby;                          // +0x3D
	unsigned char m_bfmeHeadB[2];
	void *m_currentGame;                     // +0x40
	TransportAddress m_localAddress;         // +0x44
	Transport *m_transport;                  // +0x4C
};

// ?init@LANAPI@@UAEXXZ
void LANAPI::init(void)
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
	m_transport->reset();

	const char *headlessInstance = getenv("_EA_RTS_HEADLESS");
	Int port = LAN_BASE_PORT + atoi(headlessInstance ? headlessInstance : "0");
	while ((UnsignedShort)port < LAN_LAST_PORT)
	{
		m_localAddress.m_port = (UnsignedShort)port;
		if (m_transport->init(&m_localAddress))
			break;
		++port;
	}

	m_transport->allowBroadcasts(true);

	m_pendingAction = 0;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = true;
	m_currentGame = 0;
	TransportAddress noAddress = { 0, 0 };
	m_directConnectRemoteAddress = noAddress;

	UnsignedInt bufferSize = USER_NAME_BUFFER;
	char userName[USER_NAME_BUFFER];
	if (!GetUserNameA(userName, &bufferSize))
		strcpy(userName, "unknown");
	m_userName = userName;

	bufferSize = COMPUTER_NAME_BUFFER;
	char computerName[COMPUTER_NAME_BUFFER];
	if (!GetComputerNameA(computerName, &bufferSize))
		strcpy(computerName, "unknown");
	m_hostName = computerName;
}
