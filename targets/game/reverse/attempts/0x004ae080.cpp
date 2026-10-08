// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
// partial score=0.9932 date=2026-10-08
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/controlbarvtables /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp
// Open-BFME: ControlBarSchemeManager::setControlBarSchemeByPlayer, retail
// 0x004AE080, 590 bytes.
//
// ControlBar::setControlBarSchemeByPlayer (0x0049F8B0) forwards here through
// ILT 0x0001EF33, and the body is Zero Hour's
// ControlBarSchemeManager::setControlBarSchemeByPlayer: the PopupCommunicator
// NAMEKEY, the NonCommand_Communicator / NonCommand_BriefingHistory buttons
// chosen on TheRecorder->isMultiplayer(), the Observer fallback side and the
// "Default" scheme. The string, list and scheme views are the ones the matched
// sibling setControlBarSchemeByPlayerTemplate (0x004ADE40) uses.
//
// Two BFME-specific points the reference does not show.
//
// The player's side string is read at +0x28: +00CF `add eax,0x28` on the
// incoming Player* and one copy constructor at +00D7, whose releaseBuffer at
// +0234 is the scope-exit cleanup. Generals spells the read
// `AsciiString side = p->getSide()`
// (inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/Common/Player.h:225)
// and returns by value, which would build a temporary and copy it twice; the
// single copy constructor here is one object constructed straight from the
// member, so the accessor returns a reference. The accessor is defined in the
// class body on purpose: the same declaration defined out of line as `inline`
// compiles this expression to a different frame allocation.
//
// `tempScheme` is the dead incoming parameter slot. The incoming Player* is
// last read at +00D2 (the copy source), and every later use of that slot is
// the scheme pointer: the NULL at +012E, the loop's reads and the fild scratch
// at +01CA. Reusing the parameter home for it puts `side` in the bottom frame
// slot, which is where retail keeps it.

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

class AsciiString;

template <typename T>
class StringBase
{
public:
	void concat(const T *text, int length);
	void set(const T *text, int length);
	int compare(const StringBase<T> &other) const;

private:
	friend class AsciiString;
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

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~AsciiString()
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
	Int compare(const AsciiString &other) const
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
	Int compareNoCase(const AsciiString &other) const
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
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;

	void init(void);
};

class GameWindow;
class CommandButton;

// The side string the scheme list is matched against, at Player+0x28.
class Player
{
public:
	const AsciiString &getSide(void) const
	{
		return *(const AsciiString *)((const char *)this + 0x28);
	}
};

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
	ControlBarScheme *findControlBarScheme(AsciiString name);

private:
	ControlBarScheme *m_currentScheme;
	RealCoord2D m_multiplyer;
	ControlBarSchemeList m_schemeList;
};

void ControlBarSchemeManager::setControlBarSchemeByPlayer(Player *p)
{
	GameWindow *communicatorButton = TheWindowManager->winGetWindowFromId( 0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator") );
	if (communicatorButton && TheControlBar)
	{
		if (TheRecorder->isMultiplayer())
		{
			AsciiString a("NonCommand_Communicator");
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton(a) );
		}
		else
		{
			AsciiString a("NonCommand_BriefingHistory");
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton(a) );
		}
	}
	if(!p)
		return;
	// Block-scoped on purpose: a function-scope `side` stops VC7.1 from
	// giving the two communicator strings one frame slot.
	{
	AsciiString side = p->getSide();
	ControlBarScheme *currentScheme = m_currentScheme;
	if(currentScheme && (currentScheme->m_side.compare(side) == 0))
	{
		currentScheme->init();
		return;
	}
	if(side.isEmpty())
		side.set("Observer", 8);
	// The incoming Player* is dead from the copy above, so its parameter home
	// carries the best-matching scheme from here on.
	Player *&tempScheme = p;
	tempScheme = 0;
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
			if(!tempScheme || ((ControlBarScheme *)tempScheme)->m_ScreenCreationRes.x < CBScheme->m_ScreenCreationRes.x)
				tempScheme = (Player *)CBScheme;
		}
		++it;
	}
	if(tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (Real)((ControlBarScheme *)tempScheme)->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (Real)((ControlBarScheme *)tempScheme)->m_ScreenCreationRes.y;
		m_currentScheme = (ControlBarScheme *)tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if(m_currentScheme)
		m_currentScheme->init();
	}
}
