// cl: /DNDEBUG /MD /GX
// readable body of ?init@LANAPI@@UAEXXZ: game/GameEngine/Source/GameNetwork/lanapi.cpp

// The six LANAPI bodies that turn on our own address on the LAN.
//
// init (0x00685690, slot 1) is where the pair comes from: 8086 plus the
// headless-instance offset, the first port under 8094 Transport::init accepts.
// Every other body here asks vtable slot 55 (+0xDC) for that pair and compares
// something to it -- isLoopbackAddress (0x00685640, slot 51) against
// 127.0.0.1, AmIHost (0x006852E0, slot 46) against the current game's host,
// _bfme_requestSerializedGameInfo (0x00685000, slot 21) against each of the
// game's eight slots to find our own -- or matches a peer by pair:
// lookupPlayerByAddress (0x00685240, slot 54) over the lobby list and
// requestGameJoinDirectConnectAddress (0x00685E90, slot 12) into the message
// it sends.
//
// The pair has two names and both are frozen: the ledger rows for
// lookupPlayerByAddress and requestGameJoinDirectConnectAddress mangle
// BfmeNetAddress into their parameter lists, the row for
// _bfme_requestSerializedGameInfo mangles TransportAddress into its own, and
// Transport::init (0x00684200, already matched) takes a const TransportAddress *.
// They are the same eight bytes; renaming either would rename a matched row, so
// both stay and this comment is the reconciliation.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);
extern "C" __declspec(dllimport) Int __cdecl atoi(const char *text);
extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" char *__cdecl strcpy(char *dest, const char *source);
extern "C" __declspec(dllimport) Int __stdcall GetUserNameA(char *buffer, UnsignedInt *size);
extern "C" __declspec(dllimport) Int __stdcall GetComputerNameA(char *buffer, UnsignedInt *size);
extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar *dest, const WideChar *src, UnsignedInt count);
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

enum
{
	LAN_BASE_PORT = 8086,
	LAN_LAST_PORT = 8094,
	USER_NAME_BUFFER = 257,
	COMPUTER_NAME_BUFFER = 16
};

enum
{
	RET_GAME_GONE = 8,
	RET_BUSY = 9,
	ACT_NONE = 0,
	ACT_JOINDIRECTCONNECT = 2,
	LANMSG_REQUEST_GAME_INFO = 0x11,
	LANMSG_SERIALIZED_GAME_INFO = 0x12,
	LAN_PLAYER_NAME_LENGTH = 12,
	LAN_SERIALIZED_GAME_INFO_LENGTH = 0x196,
	LAN_MAX_SLOTS = 8
};

// The pair vtable slot 55 hands back. See the note at the top for why the same
// eight bytes carry two names.
struct BfmeNetAddress
{
	Bool operator==(const BfmeNetAddress &that) const
	{
		return m_ip == that.m_ip && m_port == that.m_port;
	}

	UnsignedInt m_ip;
	UnsignedShort m_port;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
struct BfmeUnicodeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class BfmeUnicodeString
{
public:
	const WideChar *str(void) const
	{
		return m_data ? (const WideChar *)(m_data + 1) : (const WideChar *)L"";
	}

private:
	BfmeUnicodeStringData *m_data;
};

// The join request's address and name fields sit at +0x22, which is not
// four-aligned, so they are packed on their own rather than packing the whole
// message and changing how a LANMessage local is laid out.
#pragma pack(push, 1)
struct LANMessageJoinRequest
{
	UnsignedInt m_addressIP;				// message +0x22
	unsigned short m_addressPort;				// message +0x26
	WideChar m_playerName[LAN_PLAYER_NAME_LENGTH + 1];	// message +0x28
};
#pragma pack(pop)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	Int m_type;						// +0x00
	unsigned char m_bfmeHeader[0x22 - 4];			// filled in by fillInLANMessage

	union
	{
		LANMessageJoinRequest m_joinRequest;					// +0x22
		char m_serializedGameInfo[LAN_SERIALIZED_GAME_INFO_LENGTH];		// +0x22
	};

	unsigned char m_bfmeTail[0x1DC - 0x22 - LAN_SERIALIZED_GAME_INFO_LENGTH];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	unsigned char m_bfmeHead[0x10];
	LANPlayer *m_next;					// +0x10
	BfmeNetAddress m_address;				// +0x14
};

struct BfmeLANSlot
{
	BfmeNetAddress m_address;
	unsigned char m_bfmeRest[0x68 - 8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
// Two bodies read +0x88 and spell it differently: AmIHost as the game's host
// address pair, the serialized-info walk as slot[0] of the eight 0x68-byte
// participant records. They alias, and the union says so instead of leaving one
// file's half to contradict the other's.
class LANGameInfo
{
public:
	unsigned char m_bfmeHead[0x88];

	union
	{
		struct
		{
			UnsignedInt m_hostIP;			// +0x88
			UnsignedShort m_hostPort;		// +0x8C
		};

		BfmeLANSlot m_slot[LAN_MAX_SLOTS];		// +0x88
	};
};

void __cdecl fillCurrentLANGameInfo(char *buffer, UnsignedInt size);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void init(void);					// slot 1
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void requestGameJoinDirectConnectAddress(BfmeNetAddress *address);	// slot 12
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_requestSerializedGameInfo(Bool unused, TransportAddress *destination);	// slot 21
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void OnGameJoin(Int reason, void *game, void *extra) = 0;		// slot 29, vtable+0x74
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_onSerializedGameInfo(BfmeNetAddress *from, Int playerSlot,
		char *buffer, UnsignedInt size) = 0;					// slot 39, vtable+0x9C
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual Int AmIHost(void);						// slot 46, and it really does return 32 bits
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;			// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual Bool isLoopbackAddress(void);					// slot 51
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *lookupPlayerByAddress(BfmeNetAddress *address);	// slot 54
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;			// slot 55, vtable+0xDC

protected:
	void sendMessage(LANMessage *msg, UnsignedInt address);			// ILT 0x0002B599

	unsigned char m_bfmeHeadA[0x08 - 4];
	LANPlayer *m_lobbyPlayers;			// +0x08
	unsigned char m_bfmeHeadB[0x10 - 0x0C];
	BfmeUnicodeString m_name;			// +0x10
	AsciiString m_userName;				// +0x14
	AsciiString m_hostName;				// +0x18
	UnsignedInt m_gameStartTime;			// +0x1C
	Int m_gameStartSeconds;				// +0x20
	Int m_pendingAction;				// +0x24
	UnsignedInt m_expiration;			// +0x28
	UnsignedInt m_actionTimeout;			// +0x2C
	BfmeNetAddress m_directConnectRemoteAddress;	// +0x30
	UnsignedInt m_lastResendTime;			// +0x38
	Bool m_isInLANMenu;				// +0x3C
	Bool m_inLobby;					// +0x3D
	unsigned char m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;			// +0x40
	TransportAddress m_localAddress;		// +0x44
	Transport *m_transport;				// +0x4C
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
	BfmeNetAddress noAddress = { 0, 0 };
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

// ?requestGameJoinDirectConnectAddress@LANAPI@@UAEXPAUBfmeNetAddress@@@Z
void LANAPI::requestGameJoinDirectConnectAddress(BfmeNetAddress *address)
{
	if (m_pendingAction != ACT_NONE)
	{
		OnGameJoin(RET_BUSY, 0, 0);
		return;
	}

	if (address->m_ip == 0 && address->m_port == 0)
	{
		OnGameJoin(RET_GAME_GONE, 0, 0);
		return;
	}

	m_directConnectRemoteAddress = *address;

	LANMessage msg;
	msg.m_type = LANMSG_REQUEST_GAME_INFO;
	fillInLANMessage(&msg);
	msg.m_joinRequest.m_addressIP = _bfme_localAddress()->m_ip;
	msg.m_joinRequest.m_addressPort = _bfme_localAddress()->m_port;
	wcsncpy(msg.m_joinRequest.m_playerName, m_name.str(), LAN_PLAYER_NAME_LENGTH);
	msg.m_joinRequest.m_playerName[LAN_PLAYER_NAME_LENGTH] = 0;

	sendMessage(&msg, (UnsignedInt)address);

	m_pendingAction = ACT_JOINDIRECTCONNECT;
	m_expiration = timeGetTime() + m_actionTimeout;
}

// ?_bfme_requestSerializedGameInfo@LANAPI@@UAEX_NPAUTransportAddress@@@Z
//
// BFME-only, between Zero Hour's RequestGameOptions and RequestGameCreate
// slots, so no retail name is available and the _bfme_ marker stays. It SENDS
// the block rather than asking for one -- type 0x11, sent by slot 12 above, is
// the request this answers -- but "request" is the family name every
// caller-side LANAPI slot carries.
void LANAPI::_bfme_requestSerializedGameInfo(Bool unused, TransportAddress *destination)
{
	if (!m_currentGame)
		return;

	LANMessage message;
	fillInLANMessage(&message);
	message.m_type = LANMSG_SERIALIZED_GAME_INFO;
	fillCurrentLANGameInfo(message.m_serializedGameInfo,
		LAN_SERIALIZED_GAME_INFO_LENGTH);
	sendMessage(&message, (UnsignedInt)destination);

	Int playerSlot;
	for (playerSlot = 0; playerSlot < LAN_MAX_SLOTS; ++playerSlot)
	{
		BfmeNetAddress *slotAddress = &m_currentGame->m_slot[playerSlot].m_address;
		BfmeNetAddress *localAddress = _bfme_localAddress();
		if (slotAddress->m_ip == localAddress->m_ip &&
			slotAddress->m_port == localAddress->m_port)
		{
			_bfme_onSerializedGameInfo(_bfme_localAddress(), playerSlot,
				message.m_serializedGameInfo, LAN_SERIALIZED_GAME_INFO_LENGTH);
			break;
		}
	}
}

// ?AmIHost@LANAPI@@UAEHXZ
//
// Zero Hour returns Bool here, and BFME's Bool is bool -- ?RequestLobbyLeave@LANAPI@@UAEX_N@Z
// is a matched row taking one. This body is not: it sets the whole of eax
// (b8 01 00 00 00 / 33 c0) where a bool return gives mov al,1 / xor al,al, so
// the declared type is 32 bits wide. Hence the H in the symbol, not _N.
Int LANAPI::AmIHost(void)
{
	LANGameInfo *game = m_currentGame;
	if (game != 0)
	{
		BfmeNetAddress *me = _bfme_localAddress();
		if (game->m_hostIP == me->m_ip && game->m_hostPort == me->m_port)
			return 1;
	}

	return 0;
}

// ?isLoopbackAddress@LANAPI@@UAE_NXZ
//
// The slot-51 thunk at 0x0043DCE9 is present in the retail table itself.
Bool LANAPI::isLoopbackAddress(void)
{
	return _bfme_localAddress()->m_ip == 0x7F000001u;
}

// ?lookupPlayerByAddress@LANAPI@@UAEPAVLANPlayer@@PAUBfmeNetAddress@@@Z
//
// The slot-54 thunk at 0x0041B9DC targets this body. A zero requested port is
// an IP-only match. The METHOD name stays descriptive: this slot sits at the
// end of BFME's vtable and takes an address pair, not Zero Hour's
// LookupPlayer(UnsignedInt) slot, so no retail name is claimed for it.
LANPlayer *LANAPI::lookupPlayerByAddress(BfmeNetAddress *address)
{
	LANPlayer *player = m_lobbyPlayers;
	while (player && !(player->m_address == *address
		|| (address->m_port == 0 && address->m_ip == player->m_address.m_ip)))
	{
		player = player->m_next;
	}

	return player;
}
