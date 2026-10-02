// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib

// LANAPI::OnGameStart, retail 0x0068A3E0, 1041 bytes.
//
// Identity: LANAPI vtable 0x0111AF50 slot 36 (+0x90) via ILT 0x0003E8A6,
// immediately before OnGameStartTimer (+0x94, matched 0x00689050) as in
// Zero Hour LANAPI.h; the body follows ZH LANAPICallbacks.cpp OnGameStart
// with BFME changes: createTheNetwork() replaces the create/init pair, the
// local and per-slot transport addresses get their port bumped by 8, the
// logic clear is unconditional with two Bools, and the failure path deletes
// the game and raises a message box before the chat line.
//
// The preference block and the string model are the matched OnPlayerLeave
// sibling's (LANAPI_OnPlayerLeave.cpp); the LANAPI field layout (+0x10
// m_name, +0x3c m_isInLANMenu, +0x3d m_inLobby, +0x40 m_currentGame) is the
// one that sibling witnesses.
//
// Two spellings are load-bearing. OnChat takes the address by const
// reference and the failure path passes a zeroing TransportAddress()
// temporary: retail builds it during argument evaluation, so its two zero
// stores sink below the message fetch (a named local zeroed up front puts
// them before it). The local-address copy into the game goes through a
// local game pointer, which gives retail's eax base register.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class First, class Second> struct pair {};

template <class Key, class Value, class Compare = less<Key>,
    class Allocator = allocator<pair<const Key, Value> > >
class map
{
public:
    Value &operator[](const Key &key);

private:
    void *m_header;
    UnsignedInt m_size;
    UnsignedInt m_allocator;
};
}

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}

    void format(AsciiString format, ...);

    AsciiString &operator=(const AsciiString &other)
    {
        StringBase<char>::set(other);
        return *this;
    }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString(void) : StringBase<WideChar>() {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString(void) {}

    static UnicodeString TheEmptyString;
};

namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
    _STL::allocator<_STL::pair<const AsciiString, AsciiString> > >
    PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

class LANPreferences : public UserPreferences
{
public:
    LANPreferences(void);
    virtual ~LANPreferences(void);
};

// BFME transport address: 32-bit IP and 16-bit port in an 8-byte record.
struct TransportAddress
{
	TransportAddress(void) : m_ip(0), m_port(0) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class GameSlot
{
public:
	Bool isHuman(void) const;

	UnsignedByte m_beforeAddress[0x30];
	TransportAddress m_bfmeAddress30;
};

class GameInfo
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void startGame(Int gameID) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual Int getLocalSlotNum(void) const = 0;

	GameSlot *getSlot(Int slotNum);
	AsciiString getMap(void) const;

	UnsignedByte m_bfmeUnmodelled04[0x34 - 0x04];
	TransportAddress m_bfmeAddress34;
	UnsignedByte m_bfmeUnmodelled3C[0x4c - 0x3c];
	UnsignedInt m_bfmeSeed4C;
};

struct Rva0068D3E0Slot
{
	Int getColor(void) const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x0c);
	}

	Int getPlayerTemplate(void) const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x14);
	}
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

class BfmeThing935B
{
public:
	char bfmeGo935B(void);
};

class LANGameInfo : public GameInfo
{
public:
	~LANGameInfo(void);

	Rva0068D3E0Slot *getLANSlot(Int index)
	{
		return ((Rva0068D3E0Arr *)this)->at(index);
	}

	UnsignedInt getSeed(void) const
	{
		return m_bfmeSeed4C;
	}
};

class NetworkInterface
{
public:
	virtual ~NetworkInterface(void);
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
	virtual void parseUserList(const GameInfo *game) = 0;
	virtual void setLocalAddress(const TransportAddress *address) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void initTransport(void) = 0;
};

extern NetworkInterface *TheNetwork;
extern void createTheNetwork(void);

class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool unused);
};

class GameLogic;
extern GameLogic *TheGameLogic;

class MapMetaData;

class MapCache
{
public:
	void updateCache(void);
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class GlobalData
{
public:
	UnsignedByte m_beforePendingFile[0xB84];
	AsciiString m_pendingFile;
};

extern GlobalData *TheWritableGlobalData;

class GameMessage
{
public:
	void appendIntegerArgument(Int value);
};

class MessageStream
{
public:
#define MESSAGE_STREAM_SLOT(n) virtual void slot##n() = 0
	MESSAGE_STREAM_SLOT(00); MESSAGE_STREAM_SLOT(01); MESSAGE_STREAM_SLOT(02);
	MESSAGE_STREAM_SLOT(03); MESSAGE_STREAM_SLOT(04); MESSAGE_STREAM_SLOT(05);
	MESSAGE_STREAM_SLOT(06); MESSAGE_STREAM_SLOT(07); MESSAGE_STREAM_SLOT(08);
	MESSAGE_STREAM_SLOT(09); MESSAGE_STREAM_SLOT(10); MESSAGE_STREAM_SLOT(11);
	MESSAGE_STREAM_SLOT(12);
#undef MESSAGE_STREAM_SLOT
	virtual GameMessage *appendMessage(Int type) = 0;
};

extern MessageStream *TheMessageStream;

enum BfmeMessageType
{
	BFME_MSG_NEW_GAME = 0x1e
};

enum
{
	BFME_GAME_LAN = 1,
	BFME_LANCHAT_SYSTEM = 2
};

class GameTextInterface
{
public:
	virtual void vfn00(void);
	virtual void vfn01(void);
	virtual void vfn02(void);
	virtual void vfn03(void);
	virtual void vfn04(void);
	virtual void vfn05(void);
	virtual void vfn06(void);
	virtual void vfn07(void);
	virtual void vfn08(void);
	virtual void vfn09(void);
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class GameWindow;
extern GameWindow *MessageBoxOk(UnicodeString titleString,
	UnicodeString bodyString, void (*okCallback)(void));
extern Bool DoAnyMapTransfers(GameInfo *game);
extern AsciiString AsciiStringToQuotedPrintable(AsciiString original);
extern void InitGameLogicRandom(UnsignedInt seed);

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
	virtual void bfmeSlot15(void) = 0;
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
	virtual void OnPlayerLeave(UnicodeString player) = 0;
	virtual void bfmeSlot33(void) = 0;
	virtual void bfmeSlot34(void) = 0;
	virtual void OnChat(UnicodeString player, const TransportAddress &address,
		UnicodeString message, Int chatType) = 0;
	virtual void OnGameStart(void);
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
	virtual void bfmeSlot49(void) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual TransportAddress *getLocalAddress(void) = 0;

protected:
	void removeGame(LANGameInfo *game);

	UnsignedByte m_bfmeHeadA[0x10 - 0x04];
	UnicodeString m_name;
	UnsignedByte m_bfmeHeadB[0x3c - 0x14];
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;
};

// ?OnGameStart@LANAPI@@UAEXXZ
void LANAPI::OnGameStart(void)
{
	if (m_currentGame)
	{
		LANPreferences pref;
		AsciiString option;
		option.format("%d", m_currentGame->getLANSlot(
			m_currentGame->getLocalSlotNum())->getPlayerTemplate());
		pref["PlayerTemplate"] = option;
		option.format("%d", m_currentGame->getLANSlot(
			m_currentGame->getLocalSlotNum())->getColor());
		pref["Color"] = option;
		if (((BfmeThing935B *)m_currentGame)->bfmeGo935B() != 0)
			pref["Map"] = AsciiStringToQuotedPrintable(m_currentGame->getMap());
		pref.write();

		m_isInLANMenu = false;

		createTheNetwork();
		TransportAddress localAddress = *getLocalAddress();
		localAddress.m_port += 8;
		TheNetwork->setLocalAddress(&localAddress);
		TheNetwork->initTransport();
		LANGameInfo *game = m_currentGame;
		game->m_bfmeAddress34 = localAddress;

		for (Int i = 0; i < 8; ++i)
		{
			GameSlot *slot = m_currentGame->getSlot(i);
			if (m_currentGame->getSlot(i)->isHuman())
			{
				TransportAddress address = slot->m_bfmeAddress30;
				address.m_port += 8;
				slot->m_bfmeAddress30 = address;
			}
		}

		TheNetwork->parseUserList(m_currentGame);
		((BfmeGameLogicPause *)TheGameLogic)->clearGameData(false, false);

		Bool filesOk = DoAnyMapTransfers(m_currentGame);

		TheMapCache->updateCache();
		if (!filesOk || TheMapCache->findMap(m_currentGame->getMap()) == 0)
		{
			OnPlayerLeave(m_name);
			removeGame(m_currentGame);
			delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			if (TheNetwork != 0)
			{
				delete TheNetwork;
				TheNetwork = 0;
			}
			MessageBoxOk(TheGameText->fetch("GUI:ErrorStartingGame"),
				TheGameText->fetch("GUI:CouldNotTransferMap"), 0);
			OnChat(UnicodeString::TheEmptyString, TransportAddress(),
				TheGameText->fetch("GUI:CouldNotTransferMap"),
				BFME_LANCHAT_SYSTEM);
			return;
		}

		m_currentGame->startGame(0);
		TheWritableGlobalData->m_pendingFile = m_currentGame->getMap();

		GameMessage *msg = TheMessageStream->appendMessage(BFME_MSG_NEW_GAME);
		msg->appendIntegerArgument(BFME_GAME_LAN);

		InitGameLogicRandom(m_currentGame->getSeed());
	}
}
