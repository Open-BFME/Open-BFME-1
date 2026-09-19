// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// Retail 0x005199A0: BfmeAptScreenLanLobby destructor.

class AsciiString
{
private:
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase();
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
};

class BfmeObj935C
{
};

class LANAPI
{
public:
	virtual void shutdown(int value);
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
};

class GameEngine;

class GameWindowManager
{
public:
#define GAME_WINDOW_MANAGER_SLOT(N) virtual void slot##N();
	GAME_WINDOW_MANAGER_SLOT(00) GAME_WINDOW_MANAGER_SLOT(01)
	GAME_WINDOW_MANAGER_SLOT(02) GAME_WINDOW_MANAGER_SLOT(03)
	GAME_WINDOW_MANAGER_SLOT(04) GAME_WINDOW_MANAGER_SLOT(05)
	GAME_WINDOW_MANAGER_SLOT(06) GAME_WINDOW_MANAGER_SLOT(07)
	GAME_WINDOW_MANAGER_SLOT(08) GAME_WINDOW_MANAGER_SLOT(09)
	GAME_WINDOW_MANAGER_SLOT(10) GAME_WINDOW_MANAGER_SLOT(11)
	GAME_WINDOW_MANAGER_SLOT(12) GAME_WINDOW_MANAGER_SLOT(13)
	GAME_WINDOW_MANAGER_SLOT(14) GAME_WINDOW_MANAGER_SLOT(15)
	GAME_WINDOW_MANAGER_SLOT(16) GAME_WINDOW_MANAGER_SLOT(17)
	GAME_WINDOW_MANAGER_SLOT(18) GAME_WINDOW_MANAGER_SLOT(19)
	GAME_WINDOW_MANAGER_SLOT(20) GAME_WINDOW_MANAGER_SLOT(21)
	GAME_WINDOW_MANAGER_SLOT(22) GAME_WINDOW_MANAGER_SLOT(23)
	GAME_WINDOW_MANAGER_SLOT(24) GAME_WINDOW_MANAGER_SLOT(25)
	GAME_WINDOW_MANAGER_SLOT(26) GAME_WINDOW_MANAGER_SLOT(27)
	GAME_WINDOW_MANAGER_SLOT(28) GAME_WINDOW_MANAGER_SLOT(29)
	GAME_WINDOW_MANAGER_SLOT(30) GAME_WINDOW_MANAGER_SLOT(31)
	GAME_WINDOW_MANAGER_SLOT(32) GAME_WINDOW_MANAGER_SLOT(33)
	GAME_WINDOW_MANAGER_SLOT(34) GAME_WINDOW_MANAGER_SLOT(35)
	GAME_WINDOW_MANAGER_SLOT(36) GAME_WINDOW_MANAGER_SLOT(37)
	GAME_WINDOW_MANAGER_SLOT(38) GAME_WINDOW_MANAGER_SLOT(39)
	GAME_WINDOW_MANAGER_SLOT(40)
#undef GAME_WINDOW_MANAGER_SLOT
};

class BfmeE976
{
public:
	virtual void slot00();
	virtual void stop();
	~BfmeE976();

private:
	char m_unmodelled[0x130];
};

class LanLobbyUserNamePrefs
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	~LanLobbyUserNamePrefs();

private:
	char m_unmodelled[0x10];
};

class LanLobbyTail
{
public:
	virtual void slot00();
	~LanLobbyTail();

	char m_padding[0x0e];
	unsigned char m_state;
	char m_tail[0x09];
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[0x214];
};

class BfmeAptFunctorMarker
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[0x3c];
};

class BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSecondary()
	{
		*(const void **)this = (const void **)0x01105690;
	}
};

extern LANAPI *TheLAN;
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern void j_0000b42e();
extern void j_00010f8c();
extern void j_0001d9cb();
extern void j_000204c3();
extern void j_00036485();
extern void j_00040db3();
extern void j_0004598f();
void _bfme_closeAptScreen(const AsciiString &name);


class BfmeAptScreenLanLobby;
#define g_bfme935GlobC (*(BfmeAptScreenLanLobby **)0x012f4998)

class __declspec(novtable) BfmeAptScreenLanLobby
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker,
	  public BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenLanLobby();

private:
	BfmeE976 m_subStop;
	LanLobbyUserNamePrefs m_prefs;
	UnicodeString m_name;
	char m_state[0x18];
	LanLobbyTail m_tail;
};

// ??1BfmeAptScreenLanLobby@@UAE@XZ
BfmeAptScreenLanLobby::~BfmeAptScreenLanLobby()
{
	*(const void ***)this = (const void **)0x01105a78;
	*(const void ***)((char *)this + 0x218) = (const void **)0x01105a74;
	*(const void ***)((char *)this + 0x258) = (const void **)0x01105a28;

	if (g_bfme935GlobC == this)
	{
		m_subStop.stop();
		if (TheLAN)
			TheLAN->slot13();
		((void (__fastcall *)(GameEngine *))j_00010f8c)(TheGameEngine);
		if (TheLAN)
		{
			TheLAN->shutdown(1);
		}
		*(volatile unsigned int *)0x012f7730 = 0;

		m_tail.m_state = 0;
		{
			BFMERetailAsciiString name("AptLanLobby::InitGadgets");
			_bfme_closeAptScreen(reinterpret_cast<const AsciiString &>(name));
		}
		((void (__fastcall *)(BfmeAptScreenLanLobby *))j_0001d9cb)(this);
		m_prefs.slot03();
		if (TheWindowManager)
			TheWindowManager->slot40();
		*(volatile unsigned int *)0x012f4998 = 0;
	}
}
