// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
//
// AptOnlineLogin::InitGadgets callback, retail 0x00551DD0 (642 bytes).
// The five names and the member offsets below come from the retail callback
// itself; the surrounding APT state is intentionally left opaque.

#include <list>

class UnicodeString
{
public:
	static UnicodeString TheEmptyString;
};

class GameWindow
{
public:
	void *winGetUserData();
};

typedef std::list<GameWindow *> GameWindowList;

class GameWindowManager
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02();
	virtual void unused03(); virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07(); virtual void unused08();
	virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14();
	virtual void unused15(); virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19(); virtual void unused20();
	virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26();
	virtual void unused27(); virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31(); virtual void unused32();
	virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37(); virtual void unused38();
	virtual void unused39();
	virtual void clearTabList();
	virtual void registerTabList(GameWindowList tabList);
};

extern GameWindowManager *TheWindowManager;
extern void *TheBfmeOnlineLogin;

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern void prepareGadget(GameWindow *window);
extern void setWindowUserFlags(GameWindow *window, unsigned flags);
extern void resetComboBox(GameWindow *window);
extern void setComboBoxMaxChars(GameWindow *window, int maxChars);

#pragma comment(linker, "/alternatename:?prepareGadget@@YAXPAVGameWindow@@@Z=?j_0000a3df@@YAXXZ")
#pragma comment(linker, "/alternatename:?setWindowUserFlags@@YAXPAVGameWindow@@I@Z=?j_0003de88@@YAXXZ")
#pragma comment(linker, "/alternatename:?resetComboBox@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")
#pragma comment(linker, "/alternatename:?setComboBoxMaxChars@@YAXPAVGameWindow@@H@Z=?j_00020c4d@@YAXXZ")

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_beforeContext[0x34];
	void *m_context;
	unsigned char m_beforeGadgets[0x3C];
	GameWindow *m_email;
	GameWindow *m_nickname;
	GameWindow *m_password;
	GameWindow *m_rememberInfo;
	unsigned char m_betweenGadgets[0x04];
	GameWindow *m_controlList;
	unsigned int m_firstInit;
	unsigned int m_initFlags;
	unsigned char m_afterFlags[0x08];
	unsigned char m_tabListReady;

	void clearPasswordText(const UnicodeString &text, bool updateEnabled);
	void initializeControlList();
};

#pragma comment(linker, "/alternatename:?clearPasswordText@BfmeAptScreenOnlineLogin@@QAEXABVUnicodeString@@_N@Z=?j_000409e9@@YAXXZ")
#pragma comment(linker, "/alternatename:?initializeControlList@BfmeAptScreenOnlineLogin@@QAEXXZ=?j_00005f83@@YAXXZ")

class WindowManager
{
public:
	void add(void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3);
};

extern WindowManager *g_theWindowManager;

void BfmeAptScreenOnlineLogin::_bfme_onInitGadget(
	const char *name, void *argument, GameWindow *window)
{
	if(TheBfmeOnlineLogin == 0 || window == 0)
		return;

	prepareGadget(window);

	if(strcmp(name, "OnlineLogin::Password") == 0)
	{
		void *userData = window->winGetUserData();
		m_password = window;
		if(userData != 0)
		{
			((unsigned char *)userData)[0x12] = 1;
			((unsigned short *)((unsigned char *)userData + 0x10))[0] = 0x10;
		}
		setWindowUserFlags(window, 0x40);
		clearPasswordText(UnicodeString::TheEmptyString, true);
		m_initFlags |= 4;
	}
	else if(strcmp(name, "OnlineLogin::Nickname") == 0)
	{
		resetComboBox(window);
		setComboBoxMaxChars(window, 0x0F);
		m_nickname = window;
		m_initFlags |= 2;
	}
	else if(strcmp(name, "OnlineLogin::Email") == 0)
	{
		resetComboBox(window);
		setComboBoxMaxChars(window, 0x10);
		m_email = window;
		m_initFlags |= 1;
	}
	else if(strcmp(name, "OnlineLogin::RememberInfo") == 0)
	{
		m_rememberInfo = window;
		m_initFlags |= 8;
	}
	else if(strcmp(name, "OnlineLogin::ControlList") == 0)
	{
		m_controlList = window;
		initializeControlList();
		m_initFlags |= 0x100;
	}

	if(!m_tabListReady && m_email != 0 && m_nickname != 0 &&
		m_password != 0 && m_rememberInfo != 0)
	{
		GameWindowList tabList;
		tabList.push_front(m_email);
		tabList.push_back(m_password);
		tabList.push_back(m_nickname);
		tabList.push_back(m_email);
		m_tabListReady = 1;
		TheWindowManager->clearTabList();
		TheWindowManager->registerTabList(tabList);
	}

	if(m_firstInit == 1 && m_initFlags == 0x10F)
	{
		m_firstInit = 0;
		unsigned char *context = (unsigned char *)m_context;
		void *parent = *(void **)(context + 0x250);
		g_theWindowManager->add(parent, "CallChild", 1,
			(void *)"EnableButtonDeleteNickname", 0, 0, 0, 0);
	}

	(void)argument;
}
