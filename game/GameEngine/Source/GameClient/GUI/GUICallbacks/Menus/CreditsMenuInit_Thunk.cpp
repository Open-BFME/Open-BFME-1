// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BFME CreditsMenu initialization at retail 0x004C6C60.
// The parent-window literal and the Credits audio event prove the callback
// identity. The local views preserve BFME's vtable slots and retail ABI.

typedef bool Bool;
typedef int Int;

#define TRUE true
#define FALSE false

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Shell
{
public:
	Bool showShellMap(Bool useShellMap);
};

extern Shell *TheShell;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	void releaseBuffer();

protected:
	char *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class CreditsManager
{
public:
	CreditsManager();
	virtual ~CreditsManager();
	virtual void init();
	virtual void load();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual void draw();

private:
	char m_unmodelled[0x40];
};

extern CreditsManager *TheCredits;

class GameWindow
{
};

static NameKeyType parentMainMenuID = NAMEKEY_INVALID;
static GameWindow *parentMainMenu = 0;

class WindowLayout
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void hide(Bool hidden);
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84();
	virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC();
	virtual Int winSetFocus(GameWindow *window);
	virtual void slotB4(); virtual void slotB8();
	virtual void slotBC(); virtual void slotC0();
	virtual void slotC4(); virtual void slotC8();
	virtual void slotCC(); virtual void slotD0();
	virtual void slotD4(); virtual void slotD8();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
};

extern GameWindowManager *TheWindowManager;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, Int extra);
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio(Bool enabled);

private:
	char m_unmodelled[0x6C];
};

class Rva005A00B0AudioClient
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40();
	virtual void addAudioEvent(const AudioEventRTS *event);
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void removeAudioEvent(Int, Int, Int);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

// ?CreditsMenuInit@@YAXPAVWindowLayout@@PAX@Z
void CreditsMenuInit(WindowLayout *layout, void *)
{
	TheShell->showShellMap(FALSE);

	if (TheCredits)
		delete TheCredits;

	TheCredits = new CreditsManager;
	TheCredits->load();
	TheCredits->init();

	{
		AsciiString name("CreditsMenu.wnd:ParentCreditsWindow");
		parentMainMenuID = TheNameKeyGenerator->nameToKey(name.str());
	}

	parentMainMenu = TheWindowManager->winGetWindowFromId(0, parentMainMenuID);
	layout->hide(FALSE);
	TheWindowManager->winSetFocus(parentMainMenu);

	TheAudioClientUpdate->removeAudioEvent(2, 1, 0);
	AudioEventRTS event(AsciiString("Credits"), 2);
	event.setIsLogicalAudio(TRUE);
	TheAudioClientUpdate->addAudioEvent(&event);
}
