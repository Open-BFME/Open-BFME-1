// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenLanLobby LAN start-up, retail 0x00517D00 (647 bytes).  This is
// the BFME counterpart of ZH LanLobbyMenuInit: create TheLAN, choose a local IP through
// IPEnumeration, publish the three list windows on the singleton, then clamp
// the preferences user name to twelve characters and announce it.  The window
// and preferences offsets are the ones BfmeAptScreenLanLobby_submitName.cpp
// established; sizeof(LANAPI) is fixed at 0x68 by the retail operator new.
// initLanRva00517D00 is an explicit reconstruction label, not a claim that
// the stripped executable preserves that original method spelling.
// Full COFF extent is 647 bytes: ret at RVA 0x00517F86, then INT3 padding.
// All 39 relocation sites follow existing pins; no new pin is introduced.

typedef unsigned short wchar_t;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

public:
	void set(const StringBase<T> &other);
	void removeLastChar();

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;

	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	void removeLastChar()
	{
		StringBase<unsigned short>::removeLastChar();
	}
};

static const int g_lanPlayerNameLength = 12;

class GameWindow;
void GadgetListBoxReset(GameWindow *listbox);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

class LanguageFilter
{
public:
	void filterLine(UnicodeString &text);
};

extern LanguageFilter *TheLanguageFilter;

class EnumeratedIP
{
public:
	UnsignedInt getIP() const { return m_ip; }

	void *m_unmodelled;
	UnsignedInt m_ip;
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses();

private:
	void *m_addresses;
	int m_isWinsockInitialized;
};

struct GlobalData
{
	char m_unmodelledA[0x1E];
	char m_useFpsLimit;
	char m_unmodelledB[0xB10 - 0x1F];
	UnsignedInt m_defaultIP;
};

extern GlobalData *TheWritableGlobalData;

class LANAPI
{
public:
	LANAPI();

	virtual void bfmeRetailSlot00();
	virtual void init();
	virtual void bfmeRetailSlot02();
	virtual void bfmeRetailSlot03();
	virtual void reset();
#define LANAPI_SLOT(N) virtual void bfmeRetailSlot##N();
	LANAPI_SLOT(05) LANAPI_SLOT(06) LANAPI_SLOT(07) LANAPI_SLOT(08)
	LANAPI_SLOT(09)
#undef LANAPI_SLOT
	virtual void RequestLocations();
#define LANAPI_SLOT(N) virtual void bfmeRetailSlot##N();
	LANAPI_SLOT(11) LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14)
	LANAPI_SLOT(15) LANAPI_SLOT(16) LANAPI_SLOT(17) LANAPI_SLOT(18)
	LANAPI_SLOT(19) LANAPI_SLOT(20) LANAPI_SLOT(21) LANAPI_SLOT(22)
	LANAPI_SLOT(23)
#undef LANAPI_SLOT
	virtual void RequestSetName(UnicodeString name);
#define LANAPI_SLOT(N) virtual void bfmeRetailSlot##N();
	LANAPI_SLOT(25) LANAPI_SLOT(26) LANAPI_SLOT(27) LANAPI_SLOT(28)
	LANAPI_SLOT(29) LANAPI_SLOT(30) LANAPI_SLOT(31) LANAPI_SLOT(32)
	LANAPI_SLOT(33) LANAPI_SLOT(34) LANAPI_SLOT(35) LANAPI_SLOT(36)
	LANAPI_SLOT(37) LANAPI_SLOT(38) LANAPI_SLOT(39) LANAPI_SLOT(40)
	LANAPI_SLOT(41) LANAPI_SLOT(42) LANAPI_SLOT(43) LANAPI_SLOT(44)
#undef LANAPI_SLOT
	virtual bool SetLocalIP(UnsignedInt ip);
#define LANAPI_SLOT(N) virtual void bfmeRetailSlot##N();
	LANAPI_SLOT(46) LANAPI_SLOT(47) LANAPI_SLOT(48) LANAPI_SLOT(49)
#undef LANAPI_SLOT
	virtual void bfmeRetailSlot50();

	char m_unmodelled[0x59 - 4];
	char m_isInLANMenu;
	char m_unmodelledTail[2];
	GameWindow *m_chatWindow;
	GameWindow *m_playerList;
	GameWindow *m_gameList;

	void setGameList(GameWindow *w) { m_gameList = w; }
	void setChatWindow(GameWindow *w) { m_chatWindow = w; }
	void setPlayerList(GameWindow *w) { m_playerList = w; }
};

typedef char LanLobbyLANSize[(sizeof(LANAPI) == 0x68) ? 1 : -1];
extern LANAPI *TheLAN;

class Rva005265F0
{
public:
	void go();
};

class LanLobbyUserNamePrefs
{
public:
	UnicodeString getUserName();
	void setUserName(UnicodeString name);

	char m_unmodelled[0x14];
	UnicodeString m_userName;
};

class Gen_00479A60
{
public:
	int *m_table;
	int m_value;
	GameWindow *m_owner;
// Keep this access as an inline accessor: MSVC reuses the retired screen
	// register for the window after constructing the by-value text argument.
	GameWindow *getOwner() { return m_owner; }
};

class BfmeAptScreenLanLobby
{
public:
	bool initLanRva00517D00();

private:
	char m_unmodelledA[0x25C];
	Rva005265F0 m_screenState;
	char m_unmodelledB[0x390 - 0x25D];
	LanLobbyUserNamePrefs m_userNamePrefs;
	int m_state;
	GameWindow *m_gameInfo;
	GameWindow *m_chat;
	GameWindow *m_customGamesList;
	GameWindow *m_customPlayerList;
	GameWindow *m_chatEntry;
	Gen_00479A60 m_nameEntry;
	GameWindow *m_startingResources;
	char m_unmodelledC[1];
	char m_useFpsLimit;
	char m_socketError;
};

// ?initLanRva00517D00@BfmeAptScreenLanLobby@@QAE_NXZ
bool BfmeAptScreenLanLobby::initLanRva00517D00()
{
	if (!m_customGamesList)
		return false;
	if (!m_customPlayerList)
		return false;
	if (!m_chat)
		return false;

	m_screenState.go();
	GadgetListBoxReset(m_customGamesList);

	if (!TheLAN)
	{
		TheLAN = new LANAPI();
		m_useFpsLimit = TheWritableGlobalData->m_useFpsLimit;
	}
	else
	{
		TheLAN->reset();
	}

	UnsignedInt ip = TheWritableGlobalData->m_defaultIP;
	IPEnumeration IPs;

	if (!ip)
	{
		EnumeratedIP *IPlist = IPs.getAddresses();
		if (!IPlist)
			return false;
		ip = IPlist->getIP();
	}

	TheLAN->init();
	TheLAN->m_isInLANMenu = 1;
	TheLAN->setGameList(m_customGamesList);
	TheLAN->setChatWindow(m_chat);
	TheLAN->setPlayerList(m_customPlayerList);
	if (TheLAN->SetLocalIP(ip) == false)
		m_socketError = 1;

	UnicodeString defaultName;
	defaultName.set(m_userNamePrefs.getUserName());
	while (defaultName.getLength() > g_lanPlayerNameLength)
		defaultName.removeLastChar();

	UnicodeString *slot = &m_userNamePrefs.m_userName;
	slot->set(defaultName);
	if (TheLanguageFilter)
		TheLanguageFilter->filterLine(defaultName);
	m_userNamePrefs.setUserName(defaultName);

	if (m_nameEntry.m_owner)
		GadgetTextEntrySetText(m_nameEntry.getOwner(), defaultName);

	TheLAN->RequestSetName(defaultName);
	TheLAN->RequestLocations();
	TheLAN->bfmeRetailSlot50();
	return true;
}
