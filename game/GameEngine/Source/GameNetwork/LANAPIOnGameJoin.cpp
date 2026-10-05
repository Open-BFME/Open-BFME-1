// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LANAPI::OnGameJoin, retail 0x006894B0, 891 bytes.
//
// Identity: LANAPI vtable VA 0x0111AF50 (installed by the matched ??0LANAPI
// at 0x006854F0) slot 29 (+0x74) is ILT 0x000346C6 -> 0x006894B0. That slot
// sits between the matched OnPlayerList (slot 28) and OnPlayerLeave
// (slot 32) in Zero Hour's LANAPIInterface order (OnGameList, OnPlayerList,
// OnGameJoin, OnPlayerJoin, OnHostLeave, OnPlayerLeave), and the matched
// JoinDeny handler (LANAPIMessageHandlers.cpp) calls slot 29 as
// OnGameJoin(reason, LookupGame(name), msg). The body is Zero Hour's
// LANAPICallbacks.cpp OnGameJoin with its literals (LAN:JoinFailed,
// PlayerTemplate=%d ... NAT=%d, Menus/LanGameOptionsMenu.wnd).
//
// BFME changes, all read from the retail body:
//  * the method takes a third argument, the join message (ret 0Ch);
//  * success opens with the OnGameCreate helper-or-shell-push branch on the
//    global at VA 0x012F4998 (matched LANAPIOnGameCreate.cpp);
//  * RequestGameOptions (slot 20) and RequestGameJoin (slot 11) take a
//    zeroing TransportAddress temporary by reference as their last argument;
//  * with _EA_RTS_HEADLESS set, a timed-out join of a known game is retried
//    through RequestGameJoin instead of the message box;
//  * the failure path calls the second helper of that global before
//    MessageBoxOk.
// The string, preference and address models are the matched
// LANAPIOnGameStart.cpp sibling's. The failure strings sit in their own
// block, which lets VC7.1 put body in the dead theGame argument slot.

#include <stdlib.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

#define NULL 0

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class First, class Second> struct pair {};

template <class Key, class Value, class Compare = less<Key>,
    class Allocator = allocator<pair<const Key, Value> > >
class map
{
private:
    void *m_header;
    UnsignedInt m_size;
    UnsignedInt m_allocator;
};
}

template <typename T>
struct StringBaseData
{
    UnsignedShort m_refCount;
    UnsignedShort m_numCharsAllocated;
    UnsignedInt m_length;
    T m_text[1];
};

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

public:
    void set(const StringBase<T> &other);

private:
    StringBase(void) : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase(void) { releaseBuffer(); }

    void releaseBuffer(void);

    StringBaseData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}

    const char *str(void) const { return m_data ? m_data->m_text : ""; }
    void format(AsciiString format, ...);
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString(void) : StringBase<WideChar>() {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString(void) {}

    UnicodeString &operator=(const UnicodeString &other)
    {
        set(other);
        return *this;
    }
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

    Int getPreferredFaction(void);
    Int getPreferredColor(void);
};

// BFME transport address: 32-bit IP and 16-bit port in an 8-byte record.
struct TransportAddress
{
	TransportAddress(void) : m_ip(0), m_port(0) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANGameInfo;
struct LANMessage;

class Shell
{
public:
	void push(AsciiString filename, Bool shutdownImmediate = false);
};
extern Shell *TheShell;
extern Bool LANbuttonPushed;

// Retail global at VA 0x012F4998; its two helpers keep address-derived
// owners (0x0051A640 on success, 0x00516A80 before the failure box).
struct BfmeObj935C;
class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

class BfmeC1013
{
public:
	void bfmeGo1013C(void);
};

class BfmeQ1063
{
public:
	void bfmeGo1063Q(void);
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

enum FirewallType
{
	FIREWALL_TYPE_SIMPLE = 1
};

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY,
		RET_UNKNOWN,
		RET_MAX
	};

	UnicodeString getErrorStringFromReturnType(ReturnType ret);

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
	virtual void RequestGameJoin(LANGameInfo *game,
		const TransportAddress &address = TransportAddress()) = 0;	// slot 11
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void RequestGameOptions(AsciiString gameOptions, Bool isPublic,
		const TransportAddress &address = TransportAddress()) = 0;	// slot 20
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *msg) = 0;	// slot 29
};

class LANAPI : public LANAPIInterface
{
public:
	virtual void OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *msg);

protected:
	UnsignedByte m_bfmeHeadA[0x10 - 0x04];
	UnicodeString m_name;								// +0x10
	AsciiString m_userName;								// +0x14
	AsciiString m_hostName;								// +0x18
};

// ?OnGameJoin@LANAPI@@UAEXW4ReturnType@LANAPIInterface@@PAVLANGameInfo@@PAULANMessage@@@Z
void LANAPI::OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *msg)
{
	if (ret == RET_OK)
	{
		if (reinterpret_cast<BfmeObj935C * &>(g_rva012F4998LanLobby))
		{
			reinterpret_cast<BfmeC1013 *>(reinterpret_cast<BfmeObj935C * &>(g_rva012F4998LanLobby))->bfmeGo1013C();
		}
		else
		{
			LANbuttonPushed = true;
			TheShell->push(AsciiString("Menus/LanGameOptionsMenu.wnd"), false);
		}

		LANPreferences pref;
		AsciiString options;
		options.format("PlayerTemplate=%d", pref.getPreferredFaction());
		RequestGameOptions(options, true);
		options.format("Color=%d", pref.getPreferredColor());
		RequestGameOptions(options, true);
		options.format("User=%s", m_userName.str());
		RequestGameOptions(options, true);
		options.format("Host=%s", m_hostName.str());
		RequestGameOptions(options, true);
		options.format("NAT=%d", FIREWALL_TYPE_SIMPLE);
		RequestGameOptions(options, true);
	}
	else if (ret != RET_BUSY)
	{
		if (getenv("_EA_RTS_HEADLESS") && ret == RET_TIMEOUT && theGame)
		{
			RequestGameJoin(theGame);
			return;
		}

		// Own block: retail keeps body in the dead theGame argument slot.
		{
			UnicodeString title, body;
			title = TheGameText->fetch("LAN:JoinFailed");
			body = getErrorStringFromReturnType(ret);
			if (reinterpret_cast<BfmeObj935C * &>(g_rva012F4998LanLobby))
				reinterpret_cast<BfmeQ1063 *>(reinterpret_cast<BfmeObj935C * &>(g_rva012F4998LanLobby))->bfmeGo1063Q();
			MessageBoxOk(title, body, NULL);
		}
	}
}
