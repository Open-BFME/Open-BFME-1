// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LANAPI::RequestHasMap, retail 0x006861C0, 809 bytes.
//
// BFME keeps the Zero Hour request flow but moves the LANAPI state fields,
// routes the map-transfer test through the BFME GameInfo overload, and flushes
// the transport after sending the availability packet.  The ABI views stay in
// this TU because the neighboring LANAPI source files intentionally model
// other BFME subobjects.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int);

template <typename T> struct BfmeStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase(void) { releaseBuffer(); }
	void releaseBuffer(void);

	BfmeStringData<T> *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString(void) {}

	const WideChar *str(void) const
	{
		return m_data ? m_data->m_text
			: (const WideChar *)0x0107388C;
	}

	void format(UnicodeString format, ...);
};

// The BFME retail AsciiString release body is exposed under this local ABI
// name.  AsciiString below deliberately keeps the public return type used by
// GameInfo/GameState while forwarding destruction to that proven body.
class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	~AsciiString(void)
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	const char *str(void) const
	{
		return m_data ? (const char *)m_data + 8
			: (const char *)0x0107388B;
	}

	Int getLength(void) const
	{
		return m_data ? *(const UnsignedShort *)((const UnsignedByte *)m_data + 4)
			: 0;
	}

private:
	void *m_data;
};

class GameSlot
{
public:
	Bool hasMap(void) const { return m_hasMap; }

private:
	void *m_vtable;
	UnsignedByte m_bfmeBeforeHasMap[5];
	Bool m_hasMap;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
	AsciiString getMap(void) const;
};

class LANGameInfo
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual Int getLocalSlotNum(void) const = 0;
};

// 0x00041FC9 is an ILT pinned under LANGameInfo::getName.  The body behind
// that thunk is the staging-room getter, so the live identity is used here.
class GameSpyStagingRoom
{
public:
	UnicodeString getGameName(void) const;
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
	AsciiString getMapLeafName(const AsciiString &path) const;
};

class MapMetaData
{
public:
	UnicodeString m_displayName;
	UnsignedByte m_bfmeBeforeOfficial[0x26 - 4];
	Bool m_isOfficial;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class GameTextInterface
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

class Transport
{
public:
	void update(void);
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

#pragma pack(push, 1)
struct LANMapStatus
{
	WideChar gameName[17];
	UnsignedInt mapCRC;
	Bool hasMap;
};

struct LANMessage
{
	enum { MSG_MAP_AVAILABILITY = 10 };

	Int LANMessageType;
	UnsignedByte m_bfmeHeader[0x22 - 4];
	union
	{
		LANMapStatus MapStatus;
		UnsignedByte m_rawPayload[0x1DC - 0x22];
	};
};
#pragma pack(pop)

typedef char BfmeLANMessageSizeCheck[
	sizeof(LANMessage) == 0x1DC ? 1 : -1];

extern GameState *TheGameState;
extern MapCache *TheMapCache;
extern GameTextInterface *TheGameText;
extern UnsignedInt BFMEComputeCRC(const UnsignedByte *data,
	UnsignedInt length, UnsignedInt seed);

// The BFME callsite passes the GameInfo object, not an AsciiString map name.
Bool WouldMapTransfer(GameInfo *game);
#pragma comment(linker, "/alternatename:?WouldMapTransfer@@YA_NPAVGameInfo@@@Z=?j_000393fb@@YAXXZ")

class LANAPI
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void RequestHasMap(void);
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void bfmeSlot29(void) = 0;
	virtual void bfmeSlot30(void) = 0;
	virtual void bfmeSlot31(void) = 0;
	virtual void bfmeSlot32(void) = 0;
	virtual void bfmeSlot33(void) = 0;
	virtual void bfmeSlot34(void) = 0;
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, Int chatType) = 0;
	virtual void bfmeSlot36(void) = 0;
	virtual void bfmeSlot37(void) = 0;
	virtual void bfmeSlot38(void) = 0;
	virtual void bfmeSlot39(void) = 0;
	virtual void bfmeSlot40(void) = 0;
	virtual void bfmeSlot41(void) = 0;
	virtual void bfmeSlot42(void) = 0;
	virtual void bfmeSlot43(void) = 0;
	virtual void bfmeSlot44(void) = 0;
	virtual void bfmeSlot45(void) = 0;
	virtual void bfmeSlot46(void) = 0;
	virtual void bfmeSlot47(void) = 0;
	virtual void bfmeSlot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *message) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;

protected:
	void sendMessage(LANMessage *message, UnsignedInt address);

	UnsignedByte m_bfmeBeforeLobby[0x3D - 4];
	Bool m_inLobby;
	UnsignedByte m_bfmeBeforeCurrent[0x40 - 0x3E];
	LANGameInfo *m_currentGame;
	UnsignedByte m_bfmeBeforeTransport[0x4C - 0x44];
	Transport *m_transport;
};

// ?RequestHasMap@LANAPI@@UAEXXZ
void LANAPI::RequestHasMap(void)
{
	if (m_inLobby || !m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage(&msg);
	msg.LANMessageType = LANMessage::MSG_MAP_AVAILABILITY;
	msg.MapStatus.hasMap = reinterpret_cast<GameInfo *>(m_currentGame)->getSlot(
		m_currentGame->getLocalSlotNum())->hasMap();
	wcsncpy(msg.MapStatus.gameName,
		reinterpret_cast<const GameSpyStagingRoom *>(m_currentGame)
			->getGameName().str(), 16);
	msg.MapStatus.gameName[16] = 0;

	AsciiString portableMapName = TheGameState->realMapPathToPortableMapPath(
		reinterpret_cast<GameInfo *>(m_currentGame)->getMap());
	msg.MapStatus.mapCRC = BFMEComputeCRC(
		reinterpret_cast<const UnsignedByte *>(portableMapName.str()),
		portableMapName.getLength(), 0);
	sendMessage(&msg, 0);
	reinterpret_cast<Transport *>(m_transport)->update();

	if (!msg.MapStatus.hasMap)
	{
		UnicodeString text;
		UnicodeString mapDisplayName;
		const MapMetaData *mapData = TheMapCache->findMap(
			reinterpret_cast<GameInfo *>(m_currentGame)->getMap());
		Bool willTransfer = true;
		if (mapData)
		{
			mapDisplayName.format(L"%ls", mapData->m_displayName.str());
			if (mapData->m_isOfficial)
				willTransfer = false;
		}
		else
		{
			mapDisplayName.format(L"%hs",
				TheGameState->getMapLeafName(
					reinterpret_cast<GameInfo *>(m_currentGame)->getMap()).str());
			willTransfer = WouldMapTransfer(
				reinterpret_cast<GameInfo *>(m_currentGame));
		}
		if (willTransfer)
			text.format(TheGameText->fetch(
				"GUI:LocalPlayerNoMapWillTransfer"), mapDisplayName.str());
		else
			text.format(TheGameText->fetch(
				"GUI:LocalPlayerNoMap"), mapDisplayName.str());
		OnChat(UnicodeString(L"SYSTEM"), _bfme_localAddress(), text, 2);
	}
}
