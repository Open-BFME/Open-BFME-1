// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenLanLobby name submission, retail 0x00516C50 (237 bytes).
// The +0x3A4 UnicodeString belongs to LanLobbyUserNamePrefs.  The +0x3C8
// GameWindow pointer belongs to the Gen_00479A60 name-entry helper.  Both
// offsets match BfmeAptScreenLanLobby::_bfme_onInitGadget.

typedef unsigned short wchar_t;
#include "string_base.h"

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}

	void trim()
	{
		StringBase<unsigned short>::trim();
	}

	bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}
};

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

class LanguageFilter
{
public:
	void filterLine(UnicodeString &text);
};

extern LanguageFilter *TheLanguageFilter;

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void slot##N();
	LANAPI_SLOT(00) LANAPI_SLOT(01) LANAPI_SLOT(02) LANAPI_SLOT(03)
	LANAPI_SLOT(04) LANAPI_SLOT(05) LANAPI_SLOT(06) LANAPI_SLOT(07)
	LANAPI_SLOT(08) LANAPI_SLOT(09) LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14) LANAPI_SLOT(15)
	LANAPI_SLOT(16) LANAPI_SLOT(17) LANAPI_SLOT(18) LANAPI_SLOT(19)
	LANAPI_SLOT(20) LANAPI_SLOT(21) LANAPI_SLOT(22) LANAPI_SLOT(23)
	virtual void RequestSetName(UnicodeString name);
#undef LANAPI_SLOT
};

extern LANAPI *TheLAN;

class LanLobbyUserNamePrefs
{
public:
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
};

class BfmeAptScreenLanLobby
{
public:
	void submitNameRva00516C50();

private:
	char m_unmodelled[0x390];
	LanLobbyUserNamePrefs m_userNamePrefs;
	int m_state;
	GameWindow *m_gameInfo;
	GameWindow *m_chat;
	GameWindow *m_customGamesList;
	GameWindow *m_customPlayerList;
	GameWindow *m_chatEntry;
	Gen_00479A60 m_nameEntry;
	GameWindow *m_startingResources;
};

// ?submitNameRva00516C50@BfmeAptScreenLanLobby@@QAEXXZ
void BfmeAptScreenLanLobby::submitNameRva00516C50()
{
	GameWindow *entry = m_nameEntry.m_owner;
	UnicodeString text = GadgetTextEntryGetText(entry);
	UnicodeString trimmed(text);
	trimmed.trim();
	if (trimmed.isEmpty())
		text.set(m_userNamePrefs.m_userName);
	if (TheLanguageFilter)
		TheLanguageFilter->filterLine(text);
	TheLAN->RequestSetName(text);
	m_userNamePrefs.setUserName(text);
}
