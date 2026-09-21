// ?_bfme_update@BfmeAptScreenOnlineLogin@@UAEXXZ
// partial score=0.29 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <string>


typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);
	void set(const T *text);

protected:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text);
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const char *text);
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(*(const StringBase<char> *)&other);
		return *this;
	}
	const char *str(void) const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
	void format(AsciiString format, ...);
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(*(const StringBase<unsigned short> *)&other);
		return *this;
	}
	const unsigned short *str(void) const
	{
		return m_data ? m_data->m_text : (const unsigned short *)0x0107388B;
	}
};

class BFMERetailAsciiString : public AsciiString
{
public:
	BFMERetailAsciiString() : AsciiString() {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() {}
};

// The BFME record is the 0x20-byte form: the dword after m_name is present
// before the translated string.  The constructor/copy/dtor bodies are the
// already-proven retail callees printed by callees.py.
class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom();
	GameSpyGroupRoom(const GameSpyGroupRoom &other);
	~GameSpyGroupRoom();

	AsciiString m_name;
	Int m_bfmeHoleAfterName;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
};

class PSPlayerStats
{
public:
	PSPlayerStats();
	PSPlayerStats(const PSPlayerStats &other);
	~PSPlayerStats();

	Int id;
	char m_unmodelled04[0x144];
	Int locale;
	char m_unmodelled14c[0x78];
};
typedef char PSPlayerStatsSizeCheck[(sizeof(PSPlayerStats) == 0x1c4) ? 1 : -1];

class BfmeReqEUG
{
public:
	BfmeReqEUG();
	~BfmeReqEUG();

	Int requestType;
	PSPlayerStats player;
	std::string cdkey;
	std::string nick;
	std::string password;
	std::string email;
	Bool addDiscon;
	Bool addDesync;
	Int lastHouse;
	std::string results;
	char m_bfmeTail[4];
};
typedef char BfmeReqEUGSizeCheck[(sizeof(BfmeReqEUG) == 0x210) ? 1 : -1];

class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_GROUPROOM,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_LOGIN
	} peerResponseType;

	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct { Int reason; } discon;
		struct
		{
			Int id;
			Int numWaiting;
			Int maxWaiting;
			Int numGames;
			Int numPlaying;
		} groupRoom;
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			Int roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			Int internalIP;
			Int externalIP;
			char m_unmodelled2c[0x210];
		} player;
	};
};
typedef char PeerResponseSizeCheck[(sizeof(PeerResponse) == 0x330) ? 1 : -1];

class PingResponse
{
public:
	std::string hostname;
	Int avgPing;
	Int repetitions;
};

class BfmeGameSpyInfoSlots
{
public:
#define BFME_GSI_SLOT(n) virtual void slot##n(void) = 0;
	BFME_GSI_SLOT(00) BFME_GSI_SLOT(01) BFME_GSI_SLOT(02) BFME_GSI_SLOT(03)
	virtual void addGroupRoom(GameSpyGroupRoom room) = 0;
	BFME_GSI_SLOT(05) BFME_GSI_SLOT(06) BFME_GSI_SLOT(07) BFME_GSI_SLOT(08)
	BFME_GSI_SLOT(09) BFME_GSI_SLOT(10) BFME_GSI_SLOT(11) BFME_GSI_SLOT(12)
	BFME_GSI_SLOT(13) BFME_GSI_SLOT(14) BFME_GSI_SLOT(15) BFME_GSI_SLOT(16)
	BFME_GSI_SLOT(17) BFME_GSI_SLOT(18) BFME_GSI_SLOT(19) BFME_GSI_SLOT(20)
	BFME_GSI_SLOT(21) BFME_GSI_SLOT(22) BFME_GSI_SLOT(23) BFME_GSI_SLOT(24)
	virtual void setLocalName(AsciiString name) = 0;
	BFME_GSI_SLOT(26)
	virtual void setLocalProfileID(Int profileID) = 0;
	virtual Int getLocalProfileID(void) = 0;
	virtual AsciiString getLocalEmail(void) = 0;
	BFME_GSI_SLOT(30)
	virtual AsciiString getLocalPassword(void) = 0;
	BFME_GSI_SLOT(32) BFME_GSI_SLOT(33)
	virtual AsciiString getLocalBaseName(void) = 0;
	virtual void setCachedLocalPlayerStats(PSPlayerStats stats) = 0;
	BFME_GSI_SLOT(36) BFME_GSI_SLOT(37) BFME_GSI_SLOT(38) BFME_GSI_SLOT(39)
	BFME_GSI_SLOT(40) BFME_GSI_SLOT(41) BFME_GSI_SLOT(42) BFME_GSI_SLOT(43)
	BFME_GSI_SLOT(44) BFME_GSI_SLOT(45) BFME_GSI_SLOT(46) BFME_GSI_SLOT(47)
	BFME_GSI_SLOT(48) BFME_GSI_SLOT(49) BFME_GSI_SLOT(50) BFME_GSI_SLOT(51)
	BFME_GSI_SLOT(52) BFME_GSI_SLOT(53) BFME_GSI_SLOT(54) BFME_GSI_SLOT(55)
	BFME_GSI_SLOT(56) BFME_GSI_SLOT(57) BFME_GSI_SLOT(58) BFME_GSI_SLOT(59)
	BFME_GSI_SLOT(60) BFME_GSI_SLOT(61) BFME_GSI_SLOT(62) BFME_GSI_SLOT(63)
	BFME_GSI_SLOT(64)
	virtual const AsciiString &getMOTD(void) = 0;
	BFME_GSI_SLOT(66)
	virtual const AsciiString &getConfig(void) = 0;
	BFME_GSI_SLOT(68) BFME_GSI_SLOT(69) BFME_GSI_SLOT(70) BFME_GSI_SLOT(71)
	BFME_GSI_SLOT(72) BFME_GSI_SLOT(73) BFME_GSI_SLOT(74) BFME_GSI_SLOT(75)
	BFME_GSI_SLOT(76)
	virtual void loadSavedIgnoreList(void) = 0;
	BFME_GSI_SLOT(78) BFME_GSI_SLOT(79) BFME_GSI_SLOT(80) BFME_GSI_SLOT(81)
	virtual void setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP) = 0;
	BFME_GSI_SLOT(83) BFME_GSI_SLOT(84) BFME_GSI_SLOT(85) BFME_GSI_SLOT(86)
	BFME_GSI_SLOT(87) BFME_GSI_SLOT(88) BFME_GSI_SLOT(89)
	virtual void setMaxMessagesPerUpdate(Int value) = 0;
	BFME_GSI_SLOT(91) BFME_GSI_SLOT(92) BFME_GSI_SLOT(93)
	virtual void readAdditionalDisconnects(void) = 0;
#undef BFME_GSI_SLOT
};
class GameSpyInfo : public BfmeGameSpyInfoSlots
{
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual Bool getResponse(PeerResponse &response) = 0;
};

class PingerInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual Bool getResponse(PingResponse &response) = 0;
};

class GameTextInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual UnicodeString fetch(const char *label) = 0;
	virtual UnicodeString fetch(BFMERetailAsciiString label) = 0;
};

class BfmeQueueEUG
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void addRequest(BfmeReqEUG *request) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(PSPlayerStats stats) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(PSPlayerStats stats) = 0;
	virtual PSPlayerStats findPlayerStatsByID(Int profileID) = 0;
};

class GameSpyMiscPreferences
{
public:
	GameSpyMiscPreferences();
	~GameSpyMiscPreferences();
	Int getMaxMessagesPerUpdate(void);
	Int getLocale(void);
	void setLocale(Int value);
	Bool write(void);
	AsciiString getCachedStats(void);
	char m_unmodelled[0x18];
};

class BfmeSub1030
{
public:
	void bfmeInit1030(Int value, Int *out);
	char m_unmodelled[0x0c];
};

class Rva00579160Manager
{
public:
	void add(void *window, const char *format, Int type, void *value,
		Int unused0, Int unused1, Int unused2, Int unused3);
};

class Rva00548D30WindowGroup
{
public:
	void winEnable(Bool enabled);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern PingerInterface *ThePinger;
extern GameSpyInfo *TheGameSpyInfo;
extern GameTextInterface *TheGameText;
extern BfmeQueueEUG *g_bfmeQueueEUG;
extern Rva00579160Manager *g_theWindowManager;
extern char g_bfmeFmt1057[];

extern void j_00005f9c(...);
extern void j_00014e25(...);
extern void j_00026b39(...);
extern void j_00015235(...);
extern void j_0003aae9(...);
extern void j_000404b7(...);
extern void j_0002bbe8(...);
extern void j_0004557a(...);

extern void bfmeParsePlayerKVPairs(PSPlayerStats *stats);
extern void GSMessageBoxOk(UnicodeString title, UnicodeString body,
	void (*callback)(void) = 0);

#pragma comment(linker, "/alternatename:??0AsciiString@@QAE@PBD@Z=?j_00012c42@@YAXXZ")
#pragma comment(linker, "/alternatename:??4AsciiString@@QAEAAV0@PBD@Z=?j_00028bb9@@YAXXZ")
#pragma comment(linker, "/alternatename:??0GameSpyGroupRoom@@QAE@XZ=?j_0001dcc3@@YAXXZ")
#pragma comment(linker, "/alternatename:??1GameSpyGroupRoom@@QAE@XZ=?j_000099d0@@YAXXZ")
#pragma comment(linker, "/alternatename:??0PSPlayerStats@@QAE@XZ=?j_0003599a@@YAXXZ")
#pragma comment(linker, "/alternatename:??0PSPlayerStats@@QAE@ABV0@@Z=?j_00019371@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PSPlayerStats@@QAE@XZ=?j_00025c1b@@YAXXZ")
#pragma comment(linker, "/alternatename:??0BfmeReqEUG@@QAE@XZ=?j_0002e38e@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeReqEUG@@QAE@XZ=?j_0001658b@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeInit1030@BfmeSub1030@@QAEXHPAH@Z=?j_0003b318@@YAXXZ")
#pragma comment(linker, "/alternatename:?winEnable@Rva00548D30WindowGroup@@QAEX_N@Z=?j_0003e9b9@@YAXXZ")
#pragma comment(linker, "/alternatename:?add@Rva00579160Manager@@QAEXPAXPBDH0HHHH@Z=?j_00015235@@YAXXZ")
#pragma comment(linker, "/alternatename:??0GameSpyMiscPreferences@@QAE@XZ=?j_000267e2@@YAXXZ")
#pragma comment(linker, "/alternatename:??1GameSpyMiscPreferences@@QAE@XZ=?j_000141a0@@YAXXZ")
#pragma comment(linker, "/alternatename:?getMaxMessagesPerUpdate@GameSpyMiscPreferences@@QAEHXZ=?j_00014b69@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLocale@GameSpyMiscPreferences@@QAEHXZ=?j_00019ede@@YAXXZ")
#pragma comment(linker, "/alternatename:?setLocale@GameSpyMiscPreferences@@QAEXH@Z=?j_0002dafb@@YAXXZ")
#pragma comment(linker, "/alternatename:?write@GameSpyMiscPreferences@@QAE_NXZ=?j_00030495@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ=?j_0001c689@@YAXXZ")
#pragma comment(linker, "/alternatename:?GSMessageBoxOk@@YAXVUnicodeString@@0P6AXXZ@Z=?j_0002bbe8@@YAXXZ")

// The parser thunk has an address-derived ABI in this body: it fills the
// caller-provided 0x1c4-byte result after the BfmeSub1030 helper has prepared
// the cached string.  Keep that call opaque until its exact shared signature
// is recovered; the printed callee contract remains the j_000339ec thunk.
#pragma comment(linker, "/alternatename:?bfmeParsePlayerKVPairs@@YAXPAVPSPlayerStats@@@Z=?j_000339ec@@YAXXZ")

class BfmeAptScreenOnlineLogin
{
public:
	virtual void _bfme_update(void);
	void _bfme_checkLogin(void);
	void _bfme_applyLoginGadgets(void);

private:
	char m_unmodelled00[0x30];
	void *m_context;
	char m_unmodelled38[0x5c];
	Bool m_loggedInOK;
	Bool m_needsRefresh;
	char m_unmodelled96[2];
	Int m_z98;
	char m_z9c;
	Bool m_pad9d;
	char m_gadgetState9e;
	char m_pad9f;
	Bool m_padA0;
	char m_zA1;
	char m_unmodelledA2[2];
	Int m_locale;
	char m_name[4];
	Bool m_padAC;
};

void BfmeAptScreenOnlineLogin::_bfme_update(void)
{
	if (TheGameSpyPeerMessageQueue == 0)
		return;

	PingResponse ping;
	if (ThePinger != 0 && ThePinger->getResponse(ping))
	{
		_bfme_checkLogin();
		m_padA0 = 0;
		m_padAC = 0;
		j_00014e25();
		j_00026b39();
		if (m_padAC)
			j_00005f9c(this, 1);
		if (m_padA0)
		{
			Rva00548D30WindowGroup *windowGroup =
				reinterpret_cast<Rva00548D30WindowGroup *>(this);
			windowGroup->winEnable(1);
			g_theWindowManager->add(*reinterpret_cast<void **>(
				reinterpret_cast<char *>(m_context) + 0x250), g_bfmeFmt1057, 1,
				(void *)"EnableButtonDeleteNickname", 0, 0, 0, 0);
			g_theWindowManager->add(*reinterpret_cast<void **>(
				reinterpret_cast<char *>(m_context) + 0x250), g_bfmeFmt1057, 1,
				(void *)"EnableButtonCreate", 0, 0, 0, 0);
			g_theWindowManager->add(*reinterpret_cast<void **>(
				reinterpret_cast<char *>(m_context) + 0x250), g_bfmeFmt1057, 1,
				(void *)"EnableButtonLogin", 0, 0, 0, 0);
			g_theWindowManager->add(*reinterpret_cast<void **>(
				reinterpret_cast<char *>(m_context) + 0x250), g_bfmeFmt1057, 1,
				(void *)"EnableButtonServiceTerms", 0, 0, 0, 0);
		}
	}

	PeerResponse response;
	if (!m_loggedInOK && TheGameSpyPeerMessageQueue->getResponse(response))
	{
		switch (response.peerResponseType)
	{
		case PeerResponse::PEERRESPONSE_GROUPROOM:
			{
				GameSpyGroupRoom room;
				room.m_groupID = response.groupRoom.id;
				room.m_maxWaiting = response.groupRoom.maxWaiting;
				room.m_name = response.groupRoomName.c_str();
				room.m_translatedName = UnicodeString(L"TEST");
				room.m_numGames = response.groupRoom.numGames;
				room.m_numPlaying = response.groupRoom.numPlaying;
				room.m_numWaiting = response.groupRoom.numWaiting;
				TheGameSpyInfo->addGroupRoom(room);
			}
			break;

		case PeerResponse::PEERRESPONSE_DISCONNECT:
			{
				m_z98 = 0;
				BFMERetailAsciiString disconMunkee;
				disconMunkee.format(AsciiString("GUI:GSDisconReason%d"),
					response.discon.reason);
				UnicodeString title = TheGameText->fetch("GUI:GSErrorTitle");
				UnicodeString body = TheGameText->fetch(disconMunkee);
				GSMessageBoxOk(title, body);
				reinterpret_cast<Rva00548D30WindowGroup *>(this)->winEnable(1);
				AsciiString motd = TheGameSpyInfo->getMOTD();
				AsciiString config = TheGameSpyInfo->getConfig();
				j_0003aae9();
				j_000404b7(motd.str(), config.str());
				m_loggedInOK = 0;
				m_pad9d = 0;
				_bfme_applyLoginGadgets();
			}
			break;

		case PeerResponse::PEERRESPONSE_LOGIN:
			{
				m_loggedInOK = 1;
				TheGameSpyInfo->setLocalName(
					AsciiString(response.nick.c_str()));
				TheGameSpyInfo->setLocalProfileID(response.player.profileID);
				TheGameSpyInfo->loadSavedIgnoreList();
				TheGameSpyInfo->setLocalIPs(response.player.internalIP,
					response.player.externalIP);
				TheGameSpyInfo->readAdditionalDisconnects();

				GameSpyMiscPreferences miscPref;
				TheGameSpyInfo->setMaxMessagesPerUpdate(
					miscPref.getMaxMessagesPerUpdate());
				if (miscPref.getLocale() < 1 || miscPref.getLocale() > 0x25)
				{
					miscPref.setLocale(m_locale);
					miscPref.write();

					BfmeReqEUG request;
					request.requestType = 2;
					request.player.locale = m_locale;
					request.email = TheGameSpyInfo->getLocalEmail().str();
					request.nick = TheGameSpyInfo->getLocalBaseName().str();
					request.password = TheGameSpyInfo->getLocalPassword().str();
					request.player.id = TheGameSpyInfo->getLocalProfileID();
					if (g_bfmeQueueEUG != 0)
						g_bfmeQueueEUG->addRequest(&request);

					AsciiString cachedStats = miscPref.getCachedStats();
					BfmeSub1030 sub;
					Int parseState = 0;
					sub.bfmeInit1030((Int)cachedStats.str(), &parseState);
					PSPlayerStats parsedStats;
					bfmeParsePlayerKVPairs(&parsedStats);
					parsedStats.id = TheGameSpyInfo->getLocalProfileID();
					g_bfmeQueueEUG->slot08(parsedStats);
					TheGameSpyInfo->setCachedLocalPlayerStats(parsedStats);
				}
			}
			break;
		}
	}

	_bfme_checkLogin();
}
