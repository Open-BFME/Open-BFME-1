// ?d_00689170@@YAXXZ
// partial score=0.99 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// The two BFME-only LANAPI receive handlers that answer a peer by slot.
//
// _bfme_handleHasMap_0068ACF0 (retail 0x0068ACF0) and
// _bfme_handleSerializedGameInfo_0068ADE0 (retail 0x0068ADE0) sit next to each
// other in the image and do the same three things: refuse the message unless we
// are past the lobby and in a game that has not started, walk the current
// game's eight slots for the one whose transport address pair equals the
// sender's, and forward the payload through a BFME-added vtable slot with that
// slot number or byte.  Neither exists in Zero Hour, which is why both names
// still carry the _bfme_ marker and their address.
//
// Zero Hour's own handlers take a bare sender IP; these take a pointer to the
// address PAIR, which is what makes the slot walk a two-field compare.

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase(void);

	void *m_data;
};

class AsciiString : private StringBase<char>
{
	public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
};

class UnicodeString
{
public:
	UnicodeString(void) { m_data = 0; }
	__forceinline UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString(void) {}

private:
	void *m_data;
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern Int g_bfmeCounter;

enum
{
	LAN_SERIALIZED_GAME_INFO_LENGTH = 0x196,
	LAN_MAX_SLOTS = 8
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
// The two payloads overlap: 0x0068ADE0 reads the serialized game-info block
// that starts at +0x22, and the map status byte 0x0068ACF0 reads at +0x44 falls
// inside it, so the same 0x1DC-byte message carries either one.
struct LANMessage
{
	Int m_type;						// +0x00
	UnsignedByte m_bfmeHeader[0x22 - 4];

	union
	{
		char m_serializedGameInfo[LAN_SERIALIZED_GAME_INFO_LENGTH];	// +0x22

		struct
		{
			UnsignedByte m_bfmeBeforeStatus[0x44 - 0x22];
			UnsignedByte m_status;				// +0x44
		};
	};

	UnsignedByte m_bfmeTail[0x1DC - 0x22 - LAN_SERIALIZED_GAME_INFO_LENGTH];
};

struct BfmeLANSlot
{
	TransportAddress m_address;
	UnsignedByte m_bfmeRest[0x68 - 8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnsignedByte m_bfmeHeadA[0x0d];
	Bool m_inProgress;					// +0x0d
	UnsignedByte m_bfmeHeadB[0x88 - 0x0e];
	BfmeLANSlot m_slot[LAN_MAX_SLOTS];			// +0x88
};

class GameInfo;

class BfmeSerializedInfoGuard
{
public:
	char check(void);
};
#pragma comment(linker, "/alternatename:?check@BfmeSerializedInfoGuard@@QAEDXZ=?j_000329b1@@YAXXZ")

class Gen_000970a0
{
public:
	int bfmeEquals(const Gen_000970a0 *other) const;
};
#pragma comment(linker, "/alternatename:?bfmeEquals@Gen_000970a0@@QBEHPBV1@@Z=?j_0002a72a@@YAXXZ")

extern AsciiString GameInfoToAsciiString(GameInfo *game, Bool includeSlots);
#pragma comment(linker, "/alternatename:?GameInfoToAsciiString@@YA?AVAsciiString@@PAVGameInfo@@_N@Z=?j_0000e70a@@YAXXZ")


extern Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options,
	char *buffer, UnsignedInt size);
#pragma comment(linker, "/alternatename:?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PADI@Z=?j_0003be85@@YAXXZ")

struct BfmeObj935C
{
	UnsignedByte m_bfmeBeforeFlag[0x26c];
	UnsignedByte m_bfmeFlag;
	void bfmeSerializedInfoGlobal(void);
};

extern BfmeObj935C *g_bfme935GlobC;

extern void bfmeSerializedInfoNoGlobal(void);
#pragma comment(linker, "/alternatename:?bfmeSerializedInfoNoGlobal@@YAXXZ=?j_00039202@@YAXXZ")

extern void bfmeSerializedInfoFallback(void);
#pragma comment(linker, "/alternatename:?bfmeSerializedInfoFallback@@YAXXZ=?j_0001c9d6@@YAXXZ")

#pragma comment(linker, "/alternatename:?bfmeSerializedInfoGlobal@BfmeObj935C@@QAEXXZ=?j_000467bd@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
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
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_afterAddress(UnicodeString name) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual Bool _bfme_onSerializedGameInfo_00689170(TransportAddress *from,
		Int playerSlot, char *buffer, UnsignedInt size) = 0;	// slot 39, vtable+0x9C
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;					// slot 46, vtable+0xB8
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_forwardMapStatus(UnsignedByte status) = 0;	// slot 52, vtable+0xD0
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual TransportAddress *_bfme_localAddress(void) = 0;		// slot 55, vtable+0xDC

protected:
	void _bfme_handleHasMap_0068ACF0(LANMessage *message,
		const TransportAddress *sender);
	void _bfme_handleSerializedGameInfo_0068ADE0(LANMessage *message,
		const TransportAddress *sender);

	UnsignedByte m_bfmeBeforeLobbyPlayers[0x08 - 4];
	void *m_lobbyPlayers;
	UnsignedByte m_bfmeBeforeName[0x10 - 0x0c];
	UnicodeString m_name;
	UnsignedByte m_bfmeBeforeLobby[0x3d - 0x14];
	Bool m_inLobby;						// +0x3d
	UnsignedByte m_bfmeBeforeCurrentGame[2];
	LANGameInfo *m_currentGame;				// +0x40
};

// ?_bfme_onSerializedGameInfo_00689170@LANAPI@@UAE_NPAUTransportAddress@@HPADI@Z
Bool LANAPI::_bfme_onSerializedGameInfo_00689170(
	TransportAddress *from, Int playerSlot, char *buffer, UnsignedInt size)
{
	if (!m_currentGame)
		return false;

	BfmeLANSlot *slot = (BfmeLANSlot *)((UnsignedByte *)m_currentGame +
		0x88 + playerSlot * 0x68);
	if (slot->m_address.m_ip != from->m_ip ||
		slot->m_address.m_port != from->m_port ||
		m_currentGame->m_inProgress || playerSlot != 0)
		return false;

	if (reinterpret_cast<BfmeSerializedInfoGuard *>(m_currentGame)->check())
		return false;

	*(UnsignedInt *)((UnsignedByte *)m_currentGame + 0x39c) =
		timeGetTime();
	GameInfo *info = (GameInfo *)(UnsignedInt)m_currentGame;
	char *bufferCopy = buffer;
	UnsignedInt sizeCopy = size;
	const AsciiString oldOptions(GameInfoToAsciiString(
		info, true));
	if (ParseGameOptionsString(m_currentGame,
		AsciiString((const char *)0x0107301c), bufferCopy, sizeCopy))
	{
		for (Int offset = 0x68; offset < 0x340; offset += 0x68)
		{
			const char *slot = (const char *)
				((UnsignedInt)m_currentGame + (UnsignedInt)offset + 0x88);
			if ((UnsignedByte)((Gen_000970a0 *)slot)->bfmeEquals(
				(const Gen_000970a0 *)_bfme_localAddress()))
				goto accepted;
		}
	}

	++g_bfmeCounter;
	ParseGameOptionsString(m_currentGame, oldOptions, 0, 0);
	if (g_bfmeCounter > 0x10)
	{
		_bfme_afterAddress(m_name);
		g_bfmeCounter = 0;
	}
	return false;

accepted:
	if (g_bfme935GlobC)
		g_bfme935GlobC->m_bfmeFlag = 1;
	else
		bfmeSerializedInfoNoGlobal();

	BfmeObj935C *global = g_bfme935GlobC;
	if (!global)
		bfmeSerializedInfoFallback();
	else
		global->bfmeSerializedInfoGlobal();
	g_bfmeCounter = 0;
	return true;
}

// ?_bfme_handleHasMap_0068ACF0@LANAPI@@IAEXPAULANMessage@@PBUTransportAddress@@@Z
void LANAPI::_bfme_handleHasMap_0068ACF0(
	LANMessage *message, const TransportAddress *sender)
{
	if (!m_currentGame)
		return;
	if (m_currentGame->m_inProgress)
		return;
	if (AmIHost())
		return;
	if (m_inLobby)
		return;

	Int player;
	for (player = 0; player < 8; ++player)
	{
		TransportAddress *slot = &m_currentGame->m_slot[player].m_address;
		if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
		{
			_bfme_forwardMapStatus(message->m_status);
			break;
		}
	}
}

// ?_bfme_handleSerializedGameInfo_0068ADE0@LANAPI@@IAEXPAULANMessage@@PBUTransportAddress@@@Z
void LANAPI::_bfme_handleSerializedGameInfo_0068ADE0(
	LANMessage *message, const TransportAddress *sender)
{
	if (m_inLobby || !m_currentGame || m_currentGame->m_inProgress)
		return;

	Int playerSlot;
	for (playerSlot = 0; playerSlot < LAN_MAX_SLOTS; ++playerSlot)
	{
		TransportAddress *slotAddress = &m_currentGame->m_slot[playerSlot].m_address;
		if (slotAddress->m_ip == sender->m_ip &&
			slotAddress->m_port == sender->m_port)
		{
			_bfme_onSerializedGameInfo_00689170((TransportAddress *)sender, playerSlot,
				message->m_serializedGameInfo, LAN_SERIALIZED_GAME_INFO_LENGTH);
			break;
		}
	}
}
