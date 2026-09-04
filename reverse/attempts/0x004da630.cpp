// ?findWindow@@YAPAVGameWindow@@PAV1@VAsciiString@@1@Z
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: findWindow, retail 0x004DA630, 235 bytes. Converted from gen-dump
// d_004da630. ZH PopupPlayerInfo.cpp helper: format "%s:%s" from two by-value
// AsciiStrings then TheWindowManager->winGetWindowFromId(parent, NAMEKEY).
// DEBUG_ASSERTLOG is compiled out under NDEBUG. Callers populate the
// GameSpy/WOL player-info overlay gadgets.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
	char *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
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

// ?findWindow@@YAPAVGameWindow@@PAV1@VAsciiString@@1@Z
GameWindow *findWindow(GameWindow *parent, AsciiString baseWindow, AsciiString gadgetName)
{
	AsciiString fullPath;
	fullPath.format(AsciiString("%s:%s"), baseWindow.str(), gadgetName.str());
	const char *path = fullPath.str();
	GameWindowManager *wm = TheWindowManager;
	NameKeyType id = TheNameKeyGenerator->nameToKey(path);
	return wm->winGetWindowFromId(parent, id);
}
