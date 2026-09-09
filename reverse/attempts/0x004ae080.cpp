// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
// partial score=0.84 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Ireference/shims/ini /Ireference/shims/controlbarvtables /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

template <typename T> class StringBase
{
public:
	void set(const T *text, Int length);
	Int compare(const StringBase<T> &other) const;
	Int compareNoCase(const StringBase<T> &other) const;

private:
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &source);
	~StringBase();
	void releaseBuffer();
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
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text, Int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}
	bool isEmpty() const
	{
		return m_text == 0 || *(const UnsignedShort *)(m_text + 4) == 0;
	}
	Int compare(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(
			*(const StringBase<char> *)&other);
	}
	Int compareNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&other);
	}

private:
	char *m_text;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;

class GameWindowManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id) = 0;
};

extern GameWindowManager *TheWindowManager;

class RecorderClass
{
public:
	Bool isMultiplayer();
};

extern RecorderClass *TheRecorder;

class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void setControlCommand(GameWindow *window, const CommandButton *commandButton);
};

extern ControlBar *TheControlBar;

class Display
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0;
	virtual UnsignedInt getWidth();
	virtual UnsignedInt getHeight();
};

extern Display *TheDisplay;

class Player;

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

class ControlBarScheme
{
public:
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;

	void init();
};

typedef _STL::list<ControlBarScheme *> ControlBarSchemeList;

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

// ?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z
// The named ControlBar caller and the ZH GeneralsMD implementation establish
// this as the real manager method; this TU keeps the body isolated while the
// surrounding ControlBarScheme source remains unchanged.
void ControlBarSchemeManager::setControlBarSchemeByPlayer(Player *p)
{
	GameWindow *communicatorButton = TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator") );
	if (communicatorButton && TheControlBar)
	{
		if (TheRecorder->isMultiplayer())
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton("NonCommand_Communicator") );
		else
			TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton("NonCommand_BriefingHistory") );
	}

	if(!p)
		return;
	AsciiString side = *(const AsciiString *)((const char *)p + 0x28);
	if(m_currentScheme && (m_currentScheme->m_side.compare(side) == 0))
	{
		m_currentScheme->init();

		return;
	}

	// if we don't have a side, set it to Observer shell
	if(side.isEmpty())
		side.set("Observer", 8);
	ControlBarScheme *tempScheme = NULL;

	ControlBarSchemeList::iterator it = m_schemeList.begin();

	// iterate through the list and return the scheme that we're looking for
	while (it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if( !CBScheme )
		{
			++it;
			continue;
		}
		// find the scheme that best matches our resolution
		if(CBScheme->m_side.compareNoCase( side ) == 0)
		{
			if((!tempScheme || tempScheme->m_ScreenCreationRes.x < CBScheme->m_ScreenCreationRes.x) )
				tempScheme = CBScheme;
		}
		it ++;
	}

	if(tempScheme)
	{
		// setup the multiplyer value
		m_multiplyer.x = TheDisplay->getWidth() / (Real)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (Real)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		// well, we couldn't find
		m_currentScheme = findControlBarScheme("Default");
	}
	if(m_currentScheme)
		m_currentScheme->init();
}
