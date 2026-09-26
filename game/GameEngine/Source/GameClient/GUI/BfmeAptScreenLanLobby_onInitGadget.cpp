// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BfmeAptScreenLanLobby::_bfme_onInitGadget, retail 0x005187F0 (632 bytes).
// The callback is bound by the LanLobby.apt screen and receives the gadget
// name, an unused argument, and the GameWindow being initialized.  The names
// below are the retail LanLobby:: strings, rather than names inferred from
// adjacency in the generated family.

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow;
class WinInstanceData;

typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *,
	unsigned int);

class GameWindow
{
public:
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);
};

// The focus dispatch is the already-owned GameWindowManager slot 44
// (+0xb0), not a new target identity.  Its one-argument ABI is established by
// the existing GameWindowManager::winSetFocus body and its current ledger row.
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual int winSetFocus(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

void GadgetListBoxReset(GameWindow *window);
void BfmeGadgetListBoxSetAudioFeedback(GameWindow *window, bool enabled);

class BfmeKeyLC;
void bfmeGo924D(BfmeKeyLC *key, unsigned int mask);
void bfmeGo924F(BfmeKeyLC *key, unsigned short value);

class BfmeQ1073
{
public:
	void bfmeGo1073A(char value);
};

class BfmeOwnerEJ;

// Gen_00479A60 is the 0x0c-byte helper at BfmeAptScreenLanLobby+0x3c0.
// Its owner is the +0x08 word, which is the +0x3c8 readiness test below.
class Gen_00479A60
{
public:
	void bfmeAttach(BfmeOwnerEJ *owner);

	int *m_table;
	int m_value;
	GameWindow *m_owner;
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static const UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);

// The tooltip callback starts at RVA 0x00518150 after 0xCC padding and
// ends at 0x005182E1. Its cdecl ABI reads the window and packed coordinates
// from stack arguments 1 and 3 and returns without stack cleanup.
static GameWinTooltipFunc const kLanLobbyGamesTooltip =
	reinterpret_cast<GameWinTooltipFunc>(0x00918150u);

class LanLobbyUserNamePrefs
{
private:
	char m_bytes[0x18];
};

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument,
		GameWindow *window);

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
	char m_unmodelled3d0[4];
	int m_bfmeFlags;
	unsigned char m_initComplete;
	char m_unmodelled3d9[3];
};

// ?_bfme_onInitGadget@BfmeAptScreenLanLobby@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenLanLobby::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window)
{
	if (window != 0)
	{
		if (strcmp(name, "LanLobby::CustomGamesList") == 0)
		{
			GadgetListBoxReset(window);
			m_customGamesList = window;
			window->winSetTooltipFunc(kLanLobbyGamesTooltip);
		}
		else if (strcmp(name, "LanLobby::CustomPlayerList") == 0)
		{
			GadgetListBoxReset(window);
			m_customPlayerList = window;
			BfmeGadgetListBoxSetAudioFeedback(window, true);
		}
		else if (strcmp(name, "LanLobby::Chat") == 0)
		{
			GadgetListBoxReset(window);
			m_chat = window;
		}
		else if (strcmp(name, "LanLobby::GameInfo") == 0)
		{
			GadgetListBoxReset(window);
			m_gameInfo = window;
		}
		else if (strcmp(name, "LanLobby::ChatEntry") == 0)
		{
			GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
			bfmeGo924F((BfmeKeyLC *)window, 0x6e);
			TheWindowManager->winSetFocus(window);
			m_chatEntry = window;
		}
		else if (strcmp(name, "LanLobby::NameEntry") == 0)
		{
			bfmeGo924F((BfmeKeyLC *)window, 0x0c);
			GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
			bfmeGo924D((BfmeKeyLC *)window, 0x80);
			m_nameEntry.bfmeAttach((BfmeOwnerEJ *)window);
		}
		else if (strcmp(name, "LanLobby::StartingResources") == 0)
		{
			m_startingResources = window;
			GadgetComboBoxAddEntry(m_startingResources,
				TheGameText->fetch("APT:VeryLowResourcesNum", 0), -1);
			GadgetComboBoxAddEntry(m_startingResources,
				TheGameText->fetch("APT:LowResourcesNum", 0), -1);
			GadgetComboBoxAddEntry(m_startingResources,
				TheGameText->fetch("APT:MediumResourcesNum", 0), -1);
			GadgetComboBoxAddEntry(m_startingResources,
				TheGameText->fetch("APT:HighResourcesNum", 0), -1);
			GadgetComboBoxAddEntry(m_startingResources,
				TheGameText->fetch("APT:VeryHighResourcesNum", 0), -1);
			return;
		}

		if (m_nameEntry.m_owner != 0 && m_chatEntry != 0)
		{
			((BfmeQ1073 *)this)->bfmeGo1073A(2);
			m_initComplete = 0;
		}
	}
}
