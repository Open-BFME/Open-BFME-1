// cl: /DNDEBUG /MD /EHsc

// LANAPI::RequestGameCreate, retail 0x00687E90, 722 bytes.
//
// The callers in NetworkDirectConnect and LanLobbyMenu establish the
// UnicodeString-by-value/bool ABI.  The body is the BFME LAN create path: the
// BFME address pair from vtable slot 55 supplies both the game slot address
// and the seed-name prefix, and the GameInfo/LANGameInfo layout below is the
// one independently used by the matched LANGameInfo bodies.  All declarations
// stay in this TU because the older lanapi.cpp shims model different virtual
// and string layouts.

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

// The inline forwarding constructors are material to the EH temporary order
// in the format and setName calls.  This is the same data-bearing model landed
// for RequestChat and OnGameStartTimer, including the distinct empty fallback.
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
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString(void) {}
};

typedef char BfmeUnicodeStringSizeCheck[sizeof(UnicodeString) == 4 ? 1 : -1];
typedef char BfmeAsciiStringSizeCheck[sizeof(AsciiString) == 4 ? 1 : -1];

// RequestGameCreate copies the two DWORDs returned by the BFME LANAPI slot-55
// accessor into the slot's +0x30/+0x34 pair.  Other LAN readers use a narrow
// WORD view of the same retail eight-byte storage; this body specifically
// proves the DWORD load/store at the second field.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedInt m_port;
};

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

class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo);

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
	void setName(UnicodeString name);

	Int getSeed(void) const { return m_seed; }
	void setNext(LANGameInfo *next) { m_next = next; }
	void setIsDirectConnect(Bool direct) { m_isDirectConnect = direct; }
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }

private:
	LANGameSlot m_LANSlot[8];
	LANGameInfo *m_next;
	UnsignedInt m_lastHeard;
	UnicodeString m_gameName;
	Bool m_isDirectConnect;
};

typedef char BfmeGameInfoSizeCheck[sizeof(GameInfo) == 0x58 ? 1 : -1];
typedef char BfmeLANGameInfoSizeCheck[sizeof(LANGameInfo) == 0x3a8 ? 1 : -1];

// LANPreferences derives from the real UserPreferences virtual base.  The
// body only uses the already-matched constructor, getter, and destructor.
class UserPreferences
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	UnsignedByte m_bfmeBody[0x10];
};

class LANPreferences : public UserPreferences
{
public:
	LANPreferences(void);
	virtual ~LANPreferences(void);
	AsciiString getPreferredMap(void);
};

typedef char BfmeLANPreferencesSizeCheck[sizeof(LANPreferences) == 0x14 ? 1 : -1];

// These are ILT routes already used by the target's retail callsites.  The
// target bodies prove the generic thunk semantics: j_0001de8a is the
// LANGameSlot default constructor, and j_000241bd writes the LANPlayer host
// string at this+0x4c.
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

// BFME's LANAPI table places RequestChat at slot 16, RequestGameCreate at
// slot 20, OnGameCreate at slot 40, and the address accessor at slot 55.  The
// intervening declarations are only slot-preserving ABI declarations.
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
	virtual void bfmeRetailSlot29(void) = 0;
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
	virtual void bfmeRetailSlot42(void) = 0;
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
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;

protected:
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

// ?RequestGameCreate@LANAPI@@UAEXVUnicodeString@@_N@Z
void LANAPI::RequestGameCreate(UnicodeString gameName, Bool isDirectConnect)
{
	if ((!m_inLobby || m_currentGame) && !isDirectConnect)
	{
		OnGameCreate(LANAPIInterface::RET_BUSY);
		return;
	}

	if (m_pendingAction != 0)
	{
		OnGameCreate(LANAPIInterface::RET_BUSY);
		return;
	}

	m_inLobby = false;
	LANGameInfo *myGame = new LANGameInfo;
	myGame->enterGame();

	UnicodeString name;
	name.format(L"%8.8X%8.8X", _bfme_localAddress()->m_ip,
		myGame->getSeed());
	if (gameName.isEmpty())
		name.concat(m_name);
	else
		name.concat(gameName.str(), gameName.getLength());

	while (name.getLength() > 16)
		name.removeLastChar();

	myGame->setName(name);

	GameSlotConnectInfo connectInfo;
	LANGameSlot newSlot;
	connectInfo.m_nat = 0;
	connectInfo.m_port = 0;
	newSlot.setState(SLOT_PLAYER, m_name, &connectInfo);
	BfmeNetAddress *localAddress = _bfme_localAddress();
	newSlot.setIP(localAddress->m_ip);
	newSlot.setPort(localAddress->m_port);
	newSlot.setLastHeard(0);
	newSlot.setLogin(m_userName);
	newSlot.setHost(m_hostName);

	myGame->setSlot(0, newSlot);
	myGame->setNext(0);

	LANPreferences pref;
	AsciiString mapName = pref.getPreferredMap();
	myGame->setMapForwarder(mapName);
	myGame->setIsDirectConnect(isDirectConnect);
	myGame->setLastHeard(timeGetTime());
	m_currentGame = myGame;

	addGame(myGame);
	OnGameCreate(LANAPIInterface::RET_OK);
}
