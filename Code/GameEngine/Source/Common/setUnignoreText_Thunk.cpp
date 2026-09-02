// cl: /DNDEBUG /MD /EHsc

// BFME's callback uses the one-dword retail string layout.  The helper
// constructors and release body are shared retail routines; keeping their
// declarations local preserves the ABI without importing the larger ZH
// AsciiString interface.  As in the retail StringBase/AsciiString pair, the
// copy constructor is an inline forwarder so MSVC records the temporary in
// the EH frame before loading its this pointer.

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase<T> &other);
    void *m_data;
};

class BfmeStringLiteralBase
{
    friend class AsciiString;

private:
    BfmeStringLiteralBase(const char *text);
    ~BfmeStringLiteralBase();
};

class AsciiString
{
public:
    AsciiString() : m_data(0) {}
    AsciiString(const AsciiString &other)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&other);
    }
    AsciiString(const char *text)
    {
        ((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(text);
    }
    ~AsciiString();

    void __cdecl format(AsciiString format, ...);

    const char *str() const
    {
        return m_data ? m_data + 8 : (const char *)0x0107388B;
    }

private:
    void releaseBuffer();
    char *m_data;
};

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class GameWindow;

class WindowLayout
{
public:
	AsciiString getFilename(void);
	GameWindow *getFirstWindow(void)
	{
		return *(GameWindow **)((char *)this + 8);
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
#define WINDOW_MANAGER_SLOT(n) virtual void _wm_##n();
	WINDOW_MANAGER_SLOT(0)  WINDOW_MANAGER_SLOT(1)  WINDOW_MANAGER_SLOT(2)
	WINDOW_MANAGER_SLOT(3)  WINDOW_MANAGER_SLOT(4)  WINDOW_MANAGER_SLOT(5)
	WINDOW_MANAGER_SLOT(6)  WINDOW_MANAGER_SLOT(7)  WINDOW_MANAGER_SLOT(8)
	WINDOW_MANAGER_SLOT(9)  WINDOW_MANAGER_SLOT(10) WINDOW_MANAGER_SLOT(11)
	WINDOW_MANAGER_SLOT(12) WINDOW_MANAGER_SLOT(13) WINDOW_MANAGER_SLOT(14)
	WINDOW_MANAGER_SLOT(15) WINDOW_MANAGER_SLOT(16) WINDOW_MANAGER_SLOT(17)
	WINDOW_MANAGER_SLOT(18) WINDOW_MANAGER_SLOT(19) WINDOW_MANAGER_SLOT(20)
	WINDOW_MANAGER_SLOT(21) WINDOW_MANAGER_SLOT(22) WINDOW_MANAGER_SLOT(23)
	WINDOW_MANAGER_SLOT(24) WINDOW_MANAGER_SLOT(25) WINDOW_MANAGER_SLOT(26)
	WINDOW_MANAGER_SLOT(27) WINDOW_MANAGER_SLOT(28) WINDOW_MANAGER_SLOT(29)
	WINDOW_MANAGER_SLOT(30) WINDOW_MANAGER_SLOT(31) WINDOW_MANAGER_SLOT(32)
	WINDOW_MANAGER_SLOT(33) WINDOW_MANAGER_SLOT(34) WINDOW_MANAGER_SLOT(35)
	WINDOW_MANAGER_SLOT(36) WINDOW_MANAGER_SLOT(37) WINDOW_MANAGER_SLOT(38)
	WINDOW_MANAGER_SLOT(39) WINDOW_MANAGER_SLOT(40) WINDOW_MANAGER_SLOT(41)
	WINDOW_MANAGER_SLOT(42) WINDOW_MANAGER_SLOT(43) WINDOW_MANAGER_SLOT(44)
	WINDOW_MANAGER_SLOT(45) WINDOW_MANAGER_SLOT(46) WINDOW_MANAGER_SLOT(47)
	WINDOW_MANAGER_SLOT(48) WINDOW_MANAGER_SLOT(49) WINDOW_MANAGER_SLOT(50)
	WINDOW_MANAGER_SLOT(51) WINDOW_MANAGER_SLOT(52) WINDOW_MANAGER_SLOT(53)
	WINDOW_MANAGER_SLOT(54)
#undef WINDOW_MANAGER_SLOT
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id);
};

extern GameWindowManager *TheWindowManager;

class GameSpyInfoInterface
{
public:
#define GSI_SLOT(n) virtual void _gsi_##n();
	GSI_SLOT(0)  GSI_SLOT(1)  GSI_SLOT(2)  GSI_SLOT(3)  GSI_SLOT(4)
	GSI_SLOT(5)  GSI_SLOT(6)  GSI_SLOT(7)  GSI_SLOT(8)  GSI_SLOT(9)
	GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14)
	GSI_SLOT(15) GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19)
	GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23) GSI_SLOT(24)
	GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29)
	GSI_SLOT(30) GSI_SLOT(31) GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34)
	GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40) GSI_SLOT(41) GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44)
	GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47) GSI_SLOT(48) GSI_SLOT(49)
	GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52) GSI_SLOT(53) GSI_SLOT(54)
	GSI_SLOT(55) GSI_SLOT(56) GSI_SLOT(57) GSI_SLOT(58) GSI_SLOT(59)
	GSI_SLOT(60) GSI_SLOT(61) GSI_SLOT(62) GSI_SLOT(63) GSI_SLOT(64)
	GSI_SLOT(65) GSI_SLOT(66) GSI_SLOT(67) GSI_SLOT(68) GSI_SLOT(69)
	GSI_SLOT(70) GSI_SLOT(71) GSI_SLOT(72) GSI_SLOT(73) GSI_SLOT(74)
#undef GSI_SLOT
    virtual Bool isSavedIgnored(Int profileID);
    virtual void _gsi_after_saved_0();
    virtual void _gsi_after_saved_1();
    virtual void _gsi_after_saved_2();
    virtual void _gsi_after_saved_3();
    virtual void _gsi_after_saved_4();
    virtual Bool isIgnored(AsciiString nick);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class UnicodeString
{
public:
    UnicodeString(const UnicodeString &other);

private:
    void *m_data;
};

class GameTextInterface
{
public:
#define GAME_TEXT_SLOT(n) virtual void _gt_##n();
	GAME_TEXT_SLOT(0) GAME_TEXT_SLOT(1) GAME_TEXT_SLOT(2)
	GAME_TEXT_SLOT(3) GAME_TEXT_SLOT(4) GAME_TEXT_SLOT(5)
	GAME_TEXT_SLOT(6) GAME_TEXT_SLOT(7) GAME_TEXT_SLOT(8)
	GAME_TEXT_SLOT(9)
#undef GAME_TEXT_SLOT
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

void GadgetRadioSetText(GameWindow *window, UnicodeString text);

// ?setUnignoreText@@YAXPAVWindowLayout@@VAsciiString@@H@Z
void setUnignoreText(WindowLayout *layout, AsciiString nick, Int id)
{
	AsciiString controlName;
	controlName.format(AsciiString("%s:ButtonIgnore"), layout->getFilename().str() + 6);
	NameKeyType windowID = TheNameKeyGenerator->nameToKey(controlName.str());
	GameWindow *window = TheWindowManager->winGetWindowFromId(layout->getFirstWindow(), windowID);
	if (window)
	{
        if (TheGameSpyInfo->isSavedIgnored(id) || TheGameSpyInfo->isIgnored(nick))
            GadgetRadioSetText(window, TheGameText->fetch("GUI:Unignore"));
	}
}
