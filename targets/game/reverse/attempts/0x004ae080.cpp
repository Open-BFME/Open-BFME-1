// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
// partial score=0.85 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ControlBarSchemeManager::setControlBarSchemeByPlayer -- retail 0x004AE080, 590 B.
//
// Identity: ControlBar::setControlBarSchemeByPlayer (0x0049F8B0) forwards here
// through ILT 0x0001EF33, and the body is Zero Hour's
// ControlBarSchemeManager::setControlBarSchemeByPlayer: the PopupCommunicator
// NAMEKEY, the NonCommand_Communicator / NonCommand_BriefingHistory buttons
// chosen on TheRecorder->isMultiplayer(), the Observer fallback side and the
// "Default" scheme. BFME reads the side straight from Player+0x28. The string,
// list and scheme views are the ones the matched sibling
// setControlBarSchemeByPlayerTemplate (0x004ADE40) uses.

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

class ControlBarSchemeAsciiString;

template <typename T>
class StringBase
{
public:
	void concat(const T *text, int length);
	void set(const T *text, int length);
	int compare(const StringBase<T> &other) const;

private:
	friend class ControlBarSchemeAsciiString;
	StringBase(const StringBase<T> &source);
	StringBase(const T *text);
	~StringBase();
	void releaseBuffer();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void _slot0(void) {}
	virtual void _slot1(void) {}
	virtual void _slot2(void) {}
	virtual void _slot3(void) {}
	virtual void _slot4(void) {}
	virtual void _slot5(void) {}
	virtual void _slot6(void) {}
	virtual void _slot7(void) {}
	virtual void _slot8(void) {}
	virtual void _slot9(void) {}
	virtual void _slot10(void) {}
	virtual UnsignedInt getWidth(void);
	virtual UnsignedInt getHeight(void);
};

extern Display *TheDisplay;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct RealCoord2D
{
	Real x;
	Real y;
};

class ControlBarSchemeAsciiString
{
public:
	ControlBarSchemeAsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	ControlBarSchemeAsciiString(const ControlBarSchemeAsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~ControlBarSchemeAsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text, int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}
	bool isEmpty(void) const
	{
		return m_text == 0 || *(const UnsignedShort *)(m_text + 4) == 0;
	}
	Int compare(const ControlBarSchemeAsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(*(const StringBase<char> *)&other);
	}
	Int getLength(void) const
	{
		return m_text ? *(const UnsignedShort *)(m_text + 4) : 0;
	}
	const char *str(void) const
	{
		return m_text ? m_text + 8 : "";
	}
	Int compareNoCase(const ControlBarSchemeAsciiString &other) const
	{
		Int otherLen = other.getLength();
		const char *otherText = other.str();
		Int thisLen = getLength();
		const char *thisText = str();
		Int shorter = thisLen < otherLen ? thisLen : otherLen;

		Int difference = _memicmp(thisText, otherText, shorter);
		if(difference != 0)
			return difference;
		return thisLen - otherLen;
	}

private:
	char *m_text;
};

typedef _STL::list<class ControlBarScheme *> ControlBarSchemeList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
public:
	ControlBarSchemeAsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	ControlBarSchemeAsciiString m_side;

	void init(void);
};

class AsciiString;
class GameWindow;
class CommandButton;
class Player;
class ControlBarSchemeManager;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// Only slot 0xDC (winGetWindowFromId) is used here.
class GameWindowManager
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0; virtual void slot0B0() = 0;
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0;
};

class RecorderClass
{
public:
	Bool isMultiplayer(void);
};

class ControlBar
{
	friend class ControlBarSchemeManager;
public:
	const CommandButton *findCommandButton(const AsciiString &name);
private:
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern RecorderClass *TheRecorder;
extern ControlBar *TheControlBar;

class ControlBarSchemeManager
{
public:
	void setControlBarSchemeByPlayer(Player *p);
	ControlBarScheme *findControlBarScheme(ControlBarSchemeAsciiString name);

private:
	ControlBarScheme *m_currentScheme;
	RealCoord2D m_multiplyer;
	ControlBarSchemeList m_schemeList;
};

// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
void ControlBarSchemeManager::setControlBarSchemeByPlayer(Player *p)
{
	GameWindow *communicatorButton = TheWindowManager->winGetWindowFromId( 0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator") );
	if (communicatorButton && TheControlBar)
	{
		if (TheRecorder->isMultiplayer())
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton((const AsciiString &)ControlBarSchemeAsciiString("NonCommand_Communicator")) );
		else
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton((const AsciiString &)ControlBarSchemeAsciiString("NonCommand_BriefingHistory")) );
	}

	if(!p)
		return;
	ControlBarSchemeAsciiString side = *(const ControlBarSchemeAsciiString *)((const char *)p + 0x28);
	ControlBarScheme *currentScheme = m_currentScheme;
	if(currentScheme && (currentScheme->m_side.compare(side) == 0))
	{
		currentScheme->init();
		return;
	}

	// if we don't have a side, set it to Observer shell
	if(side.isEmpty())
		side.set("Observer", 8);
	ControlBarScheme *tempScheme = 0;
	ControlBarSchemeList::iterator it = m_schemeList.begin();
	while(it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if(!CBScheme)
		{
			++it;
			continue;
		}
		if(CBScheme->m_side.compareNoCase(side) == 0)
		{
			if(!tempScheme || tempScheme->m_ScreenCreationRes.x < CBScheme->m_ScreenCreationRes.x)
				tempScheme = CBScheme;
		}
		++it;
	}

	if(tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (Real)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (Real)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if(m_currentScheme)
		m_currentScheme->init();
}
