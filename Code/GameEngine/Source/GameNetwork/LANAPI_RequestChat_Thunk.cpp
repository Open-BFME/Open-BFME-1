// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LANAPI::RequestChat, retail 0x006865C0, 347 bytes.
//
// Identity is established by the LANAPI vtable at 0x0111AF50: slot 16
// (+0x40) is ILT 0x0003F03F, whose retail thunk targets this body.  The
// named callers in LanLobbyMenu and LanGameOptionsMenu call RequestChat on
// TheLAN.  The same vtable and field layout is independently used by the
// landed LANAPI message paths below: fillInLANMessage is slot 49 (+0xC4),
// OnChat is slot 35 (+0x8C), and _bfme_localAddress is slot 55 (+0xDC).
//
// BFME's UnicodeString is the data-bearing StringBase<unsigned short> view:
// its buffer header has WORD length/capacity fields and its text starts at
// header offset eight.  The visible inline forwarding copy constructor is
// material to the EH-store order at both OnChat argument copies; this is the
// same pattern proven by LANAPIOnGameStartTimer.cpp.  The layout stays local
// to this TU so the incompatible old lanapi.cpp shims are untouched.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef char Bool;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int );

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
	~StringBase() { releaseBuffer(); }
	void releaseBuffer(void);

	BfmeStringData<T> *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString(void) {}

	const WideChar *str(void) const
	{
		static const WideChar empty[] = { 0 };
		return m_data ? m_data->m_text : empty;
	}
};

class AsciiString
{
private:
	void *m_data;
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

template <typename T> class LANAPIStringSizeCheck;
typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];

#pragma pack(push, 1)
struct LANChatPayload
{
	WideChar gameName[17];
	Int chatType;
	WideChar message[101];
};

struct LANGameAnnouncePayload
{
	WideChar gameName[17];
	Bool inProgress;
	Bool isDirectConnect;
	char options[0x196];
};

struct LANMessage
{
	enum { MSG_CHAT = 11 };

	Int LANMessageType;
	unsigned char m_bfmeHeader[0x22 - 4];
	union
	{
		LANChatPayload Chat;
		LANGameAnnouncePayload GameAnnounce;
		char m_rawPayload[0x1BA];
	};
};
#pragma pack(pop)

typedef char BfmeMessageSizeCheck[sizeof(LANMessage) == 0x1DC ? 1 : -1];

class LANGameInfo
{
public:
	UnicodeString getName(void);
};

class LANAPIInterface
{
public:
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_EMOTE = 1,
		LANCHAT_SYSTEM = 2,
		LANCHAT_MAX = 3
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
	virtual void RequestChat(UnicodeString message,
		LANAPIInterface::ChatType format);
	virtual void bfmeRetailSlot17(void) = 0;
	virtual void bfmeRetailSlot18(void) = 0;
	virtual void bfmeRetailSlot19(void) = 0;
	virtual void bfmeRetailSlot20(void) = 0;
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
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, Int chatType) = 0;
	virtual void bfmeRetailSlot36(void) = 0;
	virtual void bfmeRetailSlot37(void) = 0;
	virtual void bfmeRetailSlot38(void) = 0;
	virtual void bfmeRetailSlot39(void) = 0;
	virtual void bfmeRetailSlot40(void) = 0;
	virtual void bfmeRetailSlot41(void) = 0;
	virtual void bfmeRetailSlot42(void) = 0;
	virtual void bfmeRetailSlot43(void) = 0;
	virtual void bfmeRetailSlot44(void) = 0;
	virtual void bfmeRetailSlot45(void) = 0;
	virtual void bfmeRetailSlot46(void) = 0;
	virtual void bfmeRetailSlot47(void) = 0;
	virtual void bfmeRetailSlot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;
	virtual void bfmeRetailSlot50(void) = 0;
	virtual void bfmeRetailSlot51(void) = 0;
	virtual void bfmeRetailSlot52(void) = 0;
	virtual void bfmeRetailSlot53(void) = 0;
	virtual void bfmeRetailSlot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip);

	unsigned char m_bfmeHeadA[0x08 - 4];
	void *m_lobbyPlayers;
	unsigned char m_bfmeHeadB[0x10 - 0x0C];
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
	unsigned char m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;
	BfmeNetAddress m_localAddress;
	void *m_transport;
};

// ?RequestChat@LANAPI@@UAEXVUnicodeString@@W4ChatType@LANAPIInterface@@@Z
void LANAPI::RequestChat(UnicodeString message,
	LANAPIInterface::ChatType format)
{
	LANMessage msg;
	fillInLANMessage(&msg);
	wcsncpy(msg.Chat.gameName,
		m_currentGame ? m_currentGame->getName().str()
			: L"",
		16);
	msg.Chat.gameName[16] = 0;
	msg.LANMessageType = LANMessage::MSG_CHAT;
	msg.Chat.chatType = format;
	wcsncpy(msg.Chat.message, message.str(), 100);
	msg.Chat.message[100] = 0;
	sendMessage(&msg, 0);
	OnChat(m_name, _bfme_localAddress(), message, format);
}
