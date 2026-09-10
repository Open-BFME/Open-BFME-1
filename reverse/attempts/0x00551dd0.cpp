// ?_bfme_onInitGadget@BfmeAptScreenOnlineLogin@@QAEXPBDPAXPAVGameWindow@@@Z
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BfmeAptScreenOnlineLogin::_bfme_onInitGadget, retail 0x00551DD0 (642 bytes).
// Registered as the OnlineLogin.apt InitGadgets callback: the constructor
// (0x005538A0) wraps a pointer to this body in an
// OnlineLoginInitGadgetsFunctorWrapper (vtable 0x011080BC) whose member
// function pointer resolves through ILT 0x0003FA71 straight to 0x00551DD0.
// Same (name, unused, window) ABI as the LanLobby sibling
// (BfmeAptScreenLanLobby_onInitGadget.cpp).  Once all four login fields are
// present it builds a GameWindowManager tab list (registerTabList is vtable
// slot 0x9C, clearTabList slot 0xA0 -- adjacent slots, called clear-then-
// register, matching the real ZH GameWindowManager.h order) exactly like
// GeneralsMD WOLLoginMenu.cpp's push_front(email)/push_back(...) sequence.

#include <list>

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow;

void GadgetListBoxReset(GameWindow *window);
void GadgetComboBoxReset(GameWindow *window);
void GadgetComboBoxSetMaxChars(GameWindow *window, int maxChars);
void bfmeGoLC(class BfmeKeyLC *key, unsigned int mask);

class BfmeKeyLC;
void bfmeGo924D(BfmeKeyLC *key, unsigned int mask);

struct GadgetUserData
{
	unsigned char m_unmodelled[0x10];
	unsigned short m_field10;
	unsigned char m_field12;
};

class GameWindow
{
public:
	void *winGetUserData();
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
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	static const UnicodeString TheEmptyString;
};

typedef std::list<GameWindow *> GameWindowList;

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
	virtual void registerTabList(GameWindowList tabList);
	virtual void clearTabList();
};

extern GameWindowManager *TheWindowManager;

// Retail [this+0x34]; +0x250 is the window handle the scripted-UI
// WindowManager operates on (matched by OnlineLoginRva005536F0.cpp).
struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[0x250];
	void *m_window;
};

class WindowManager
{
public:
	void add(void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3);
};

extern WindowManager *g_theWindowManager;

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_onInitGadget(const char *name, void *, GameWindow *window);
	bool bfmeSetTextAt7C(const UnicodeString &text, bool updateEnabled);
	void _bfme_populateCountryList();

private:
	unsigned char m_unmodelled00[0x34];
	BfmeOnlineLoginContext *m_context;
	unsigned char m_unmodelled38[0x3c];
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_dependentControl;
	unsigned char m_unmodelled84[4];
	GameWindow *m_countryList;
	int m_pendingButtonState;
	int m_fieldMask;
	unsigned char m_unmodelled94[8];
	bool m_ready;
};

extern BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;

// ?_bfme_onInitGadget@BfmeAptScreenOnlineLogin@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenOnlineLogin::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window)
{
	if (TheBfmeOnlineLogin && window)
	{
		GadgetListBoxReset(window);

		if (strcmp(name, "OnlineLogin::Password") == 0)
		{
			m_control7C = window;
			((GadgetUserData *)window->winGetUserData())->m_field12 = 1;
			GadgetUserData *userData = (GadgetUserData *)window->winGetUserData();
			if (userData)
				userData->m_field10 = 0x10;
			bfmeGo924D((BfmeKeyLC *)window, 0x40);
			bfmeSetTextAt7C(UnicodeString::TheEmptyString, true);
			m_fieldMask |= 4;
		}
		else if (strcmp(name, "OnlineLogin::Nickname") == 0)
		{
			GadgetComboBoxReset(window);
			GadgetComboBoxSetMaxChars(window, 0xf);
			bfmeGoLC((BfmeKeyLC *)window, 4);
			m_control78 = window;
			m_fieldMask |= 2;
		}
		else if (strcmp(name, "OnlineLogin::Email") == 0)
		{
			GadgetComboBoxReset(window);
			GadgetComboBoxSetMaxChars(window, 0x10);
			m_control74 = window;
			m_fieldMask |= 1;
		}
		else if (strcmp(name, "OnlineLogin::RememberInfo") == 0)
		{
			m_dependentControl = window;
			m_fieldMask |= 8;
		}
		else if (strcmp(name, "OnlineLogin::CountryList") == 0)
		{
			m_countryList = window;
			_bfme_populateCountryList();
			m_fieldMask |= 0x100;
		}

		if (!m_ready && m_control74 && m_control78 && m_control7C && m_dependentControl)
		{
			GameWindowList tabList;
			m_ready = true;
			tabList.push_front(m_control74);
			tabList.push_back(m_control7C);
			tabList.push_back(m_control78);
			tabList.push_back(m_dependentControl);
			TheWindowManager->clearTabList();
			TheWindowManager->registerTabList(tabList);
		}

		if (m_pendingButtonState == 1 && m_fieldMask == 0x10f)
		{
			m_pendingButtonState = 0;
			void *window2 = m_context->m_window;
			g_theWindowManager->add(window2, "CallChild", 1,
				(void *)"EnableButtonDeleteNickname", 0, 0, 0, 0);
		}
	}
}
