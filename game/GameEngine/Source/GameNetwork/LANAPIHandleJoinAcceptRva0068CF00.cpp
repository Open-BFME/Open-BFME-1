// cl: /DNDEBUG /MD /EHsc
// Join-accept packet handler at 0x0068CF00, 818 retail bytes.
// LANAPI::update calls its ILT with a packet and sender address.


typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

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
	friend class AsciiString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase(void) { releaseBuffer(); }
	void releaseBuffer(void);

public:
	void set(const StringBase<T> &other);
	void concat(const StringBase<T> &other);
	void concat(const T *text, Int length);
	void removeLastChar(void);

	UnsignedShort getLength(void) const
	{
		return m_data ? m_data->m_length : 0;
	}

private:
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

	Bool isEmpty(void) const
	{
		return !m_data || m_data->m_length == 0;
	}

	UnsignedShort getLength(void) const
	{
		return m_data ? m_data->m_length : 0;
	}

	const WideChar *str(void) const
	{
		static const WideChar empty[] = { 0 };
		return m_data ? m_data->m_text : empty;
	}

	void format(UnicodeString format, ...);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	const char *str(void) const { static const char empty = 0; return m_data ? m_data->m_text : &empty; }
	void format(AsciiString format, ...);
	AsciiString &operator=(const AsciiString &other) { StringBase<char>::set(other); return *this; }
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString(void) {}
};

typedef char BfmeUnicodeStringSizeCheck[sizeof(UnicodeString) == 4 ? 1 : -1];
typedef char BfmeAsciiStringSizeCheck[sizeof(AsciiString) == 4 ? 1 : -1];

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedInt m_port;
};

#pragma pack(push, 1)
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

#pragma pack(pop)
class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo);

	UnicodeString getName(void) const;
	void setIP(UnsignedInt ip) { m_address.m_ip = ip; }
	void setPort(UnsignedInt port) { m_address.m_port = port; }

private:
	void *m_vptr;
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	UnsignedByte m_bfmeBeforeAddress[0x30 - 0x0b];

protected:
	BfmeNetAddress m_address;
	UnsignedByte m_bfmeTail[0x44 - 0x38];
};

class LANPlayer
{
public:
	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedByte m_bfmeTail[0x1c - 0x0c];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot(void);
	LANGameSlot(const LANGameSlot &other);
	~LANGameSlot(void);

	void setLogin(AsciiString name);
	void setHost(AsciiString name);
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }
	UnicodeString getName(void) const;

private:
	LANPlayer m_user;
	StringBase<char> m_serial;
	UnsignedInt m_lastHeard;
};

typedef char BfmeGameSlotSizeCheck[sizeof(GameSlot) == 0x44 ? 1 : -1];
typedef char BfmeLANGameSlotSizeCheck[sizeof(LANGameSlot) == 0x68 ? 1 : -1];

class GameInfo
{
public:
	void enterGame(void);
	void setMapForwarder(AsciiString mapName);

protected:
	void *m_vptr;
	Int m_preorderMask;
	Int m_crcInterval;
	Bool m_inGame;
	Bool m_inProgress;
	Bool m_surrendered;
	Int m_gameID;
	GameSlot *m_slots[8];
	UnsignedInt m_localIP;
	Int m_extra38;
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
	Int m_mapMask;
	Int m_seed;
	Int m_useStats;
	Int m_tail;
};

class LANGameInfo : public GameInfo
{
public:
	LANGameInfo(void);
	~LANGameInfo(void);

	void setSlot(Int slot, LANGameSlot slotInfo);
	GameSlot *getSlot(Int slot);
	void setName(UnicodeString name);

	Int getSeed(void) const { return m_seed; }
	void setNext(LANGameInfo *next) { m_next = next; }
	void setIsDirectConnect(Bool direct) { m_isDirectConnect = direct; }
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }
	UnicodeString getName(void) const;

private:
	LANGameSlot m_LANSlot[8];
	LANGameInfo *m_next;
	UnsignedInt m_lastHeard;
	UnicodeString m_gameName;
	Bool m_isDirectConnect;
};

typedef char BfmeGameInfoSizeCheck[sizeof(GameInfo) == 0x58 ? 1 : -1];
typedef char BfmeLANGameInfoSizeCheck[sizeof(LANGameInfo) == 0x3a8 ? 1 : -1];

struct Rva0068D3E0Slot
{
	char m_body[0x68];
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(int index);
private:
	char m_pad[0x58];
	Rva0068D3E0Slot m_items[8];
};

class PreferenceMap
{
public:
	AsciiString &operator[](const AsciiString &key);
private:
	UnsignedByte m_data[12];
};

class UserPreferences
{
public:
	virtual ~UserPreferences(void);
	AsciiString &operator[](const AsciiString &key) { return m_preferences[key]; }
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	PreferenceMap m_preferences;
	AsciiString m_filename;
};

class LANPreferences : public UserPreferences
{
public:
	LANPreferences(void);
	virtual ~LANPreferences(void);
	AsciiString getPreferredMap(void);
};

typedef char BfmeLANPreferencesSizeCheck[sizeof(LANPreferences) == 0x14 ? 1 : -1];

#pragma comment(linker, "/alternatename:??0LANGameSlot@@QAE@XZ=?j_0001de8a@@YAXXZ")
#pragma comment(linker, "/alternatename:?setHost@LANGameSlot@@QAEXVAsciiString@@@Z=?j_000241bd@@YAXXZ")

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_BUSY = 9
	};
};

class LANAPI
{
public:
	virtual void bfmeRetailSlot00(void) = 0;
	virtual void bfmeRetailSlot01(void) = 0;
	virtual void bfmeRetailSlot02(void) = 0;
	virtual void bfmeRetailSlot03(void) = 0;
	virtual void bfmeRetailSlot04(void) = 0;
	virtual void bfmeRetailSlot05(void) = 0;
	virtual void bfmeRetailSlot06(void) = 0;
	virtual void bfmeRetailSlot07(void) = 0;
	virtual void bfmeRetailSlot08(void) = 0;
	virtual void bfmeRetailSlot09(void) = 0;
	virtual void bfmeRetailSlot10(void) = 0;
	virtual void bfmeRetailSlot11(void) = 0;
	virtual void bfmeRetailSlot12(void) = 0;
	virtual void bfmeRetailSlot13(void) = 0;
	virtual void bfmeRetailSlot14(void) = 0;
	virtual void bfmeRetailSlot15(void) = 0;
	virtual void bfmeRetailSlot16(void) = 0;
	virtual void bfmeRetailSlot17(void) = 0;
	virtual void bfmeRetailSlot18(void) = 0;
	virtual void bfmeRetailSlot19(void) = 0;
	virtual void RequestGameCreate(UnicodeString gameName, Bool isDirectConnect);
	virtual void bfmeRetailSlot21(void) = 0;
	virtual void bfmeRetailSlot22(void) = 0;
	virtual void bfmeRetailSlot23(void) = 0;
	virtual void bfmeRetailSlot24(void) = 0;
	virtual void bfmeRetailSlot25(void) = 0;
	virtual void bfmeRetailSlot26(void) = 0;
	virtual void bfmeRetailSlot27(void) = 0;
	virtual void bfmeRetailSlot28(void) = 0;
	virtual void OnGameJoin(Int reason, LANGameInfo *game, void *message) = 0;
	virtual void bfmeRetailSlot30(void) = 0;
	virtual void bfmeRetailSlot31(void) = 0;
	virtual void bfmeRetailSlot32(void) = 0;
	virtual void bfmeRetailSlot33(void) = 0;
	virtual void bfmeRetailSlot34(void) = 0;
	virtual void bfmeRetailSlot35(void) = 0;
	virtual void bfmeRetailSlot36(void) = 0;
	virtual void bfmeRetailSlot37(void) = 0;
	virtual void bfmeRetailSlot38(void) = 0;
	virtual void bfmeRetailSlot39(void) = 0;
	virtual void OnGameCreate(LANAPIInterface::ReturnType ret);
	virtual void bfmeRetailSlot41(void) = 0;
	virtual LANGameInfo *LookupGame(UnicodeString name) = 0;
	virtual void bfmeRetailSlot43(void) = 0;
	virtual void bfmeRetailSlot44(void) = 0;
	virtual void bfmeRetailSlot45(void) = 0;
	virtual void bfmeRetailSlot46(void) = 0;
	virtual void bfmeRetailSlot47(void) = 0;
	virtual void bfmeRetailSlot48(void) = 0;
	virtual void bfmeRetailSlot49(void) = 0;
	virtual void bfmeRetailSlot50(void) = 0;
	virtual void bfmeRetailSlot51(void) = 0;
	virtual void bfmeRetailSlot52(void) = 0;
	virtual void bfmeRetailSlot53(void) = 0;
	virtual void bfmeRetailSlot54(void) = 0;
	virtual BfmeNetAddress *getLocalAddress(void) = 0;

protected:
	void handleJoinAcceptRva0068CF00(struct LANMessage *message, BfmeNetAddress *sender);
	void addGame(LANGameInfo *game);

	UnsignedByte m_bfmeHeadA[0x08 - 4];
	void *m_lobbyPlayers;
	UnsignedByte m_bfmeHeadB[0x10 - 0x0c];
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
	UnsignedInt m_gameStartTime;
	Int m_gameStartSeconds;
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	BfmeNetAddress m_directConnectRemoteAddress;
	UnsignedInt m_lastResendTime;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;
	BfmeNetAddress m_localAddress;
	void *m_transport;
};

typedef char BfmeLANAPISizeCheck[sizeof(LANAPI) == 0x50 ? 1 : -1];


#pragma pack(push, 1)
struct LANMessage
{
    Int messageType;
    WideChar name[13];
    char userName[2];
    char hostName[2];
    struct {
        WideChar gameName[20];
        UnsignedInt playerIP;
        UnsignedShort playerPort;
        Int slotPosition;
    } GameJoined;
};
#pragma pack(pop)

AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);
Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool includeSlots);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString text);

void LANAPI::handleJoinAcceptRva0068CF00(LANMessage *msg, BfmeNetAddress *sender)
{
    BfmeNetAddress *local = getLocalAddress();
    if (msg->GameJoined.playerIP != local->m_ip ||
        msg->GameJoined.playerPort != (UnsignedShort)getLocalAddress()->m_port)
        return;
    if (m_pendingAction != 1)
        return;

    m_currentGame = LookupGame(UnicodeString(msg->GameJoined.gameName));
    if (!m_currentGame) {
        OnGameJoin(10, 0, 0);
    } else {
        m_inLobby = false;
        AsciiString options = GameInfoToAsciiString(m_currentGame, true);
        m_currentGame->enterGame();
        ParseAsciiStringToGameInfo(m_currentGame, options, true);

        Int pos = msg->GameJoined.slotPosition;
        LANGameSlot slot;
        {
            GameSlotConnectInfo connectInfo;
            connectInfo.m_nat = 0;
            connectInfo.m_port = 0;
            slot.setState(SLOT_PLAYER, m_name, &connectInfo);
        }
        BfmeNetAddress *address = getLocalAddress();
        slot.setIP(address->m_ip);
        slot.setPort(address->m_port);
        slot.setLastHeard(0);
        slot.setLogin(m_userName);
        slot.setHost(m_hostName);
        m_currentGame->setSlot(pos, slot);
        ((LANGameSlot *)((Rva0068D3E0Arr *)m_currentGame)->at(0))->setHost(AsciiString(msg->hostName));
        ((LANGameSlot *)((Rva0068D3E0Arr *)m_currentGame)->at(0))->setLogin(AsciiString(msg->userName));

        LANPreferences prefs;
        AsciiString entry;
        entry.format("%d.%d.%d.%d:%i:%s", sender->m_ip >> 24,
            (sender->m_ip & 0xff0000) >> 16, (sender->m_ip & 0xff00) >> 8,
            sender->m_ip & 0xff, (UnsignedShort)sender->m_port,
            UnicodeStringToQuotedPrintable(m_currentGame->getSlot(0)->getName()).str());
        prefs["RemoteIP0"] = entry;
        prefs.write();
        OnGameJoin(0, m_currentGame, 0);
    }
    m_pendingAction = 0;
    m_expiration = 0;
}
