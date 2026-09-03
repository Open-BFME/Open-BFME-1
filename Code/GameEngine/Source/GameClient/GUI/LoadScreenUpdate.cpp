// cl: /DNDEBUG /MD
// readable body of ?update@LoadScreen@@UAEXH@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// Retail 0x004914C0: BFME LoadScreen::update(Int percent).  Named by the
// already-matched GameSpy/MultiPlayer/MapTransfer load-screen updates, which
// call through ILT 0x00003FE4 onto this body.  ZH LoadScreen.cpp:164 plus
// BFME's ready-byte at +0x0C, TheMouse::setCursorTooltip(TheEmptyString), and
// the second (scripted-UI) window manager.  percent is unused.  No /EHsc:
// retail carries the by-value UnicodeString stash without a registered handler.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

#define BFME_VSLOT(n) virtual void slot##n();

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, int index, const RGBColor *color,
		float delay );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void serviceWindowsOS();  // +0x40
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	virtual void update();  // +0x14
};

// The BFME scripted-UI window manager published at 0x012F19E8.
class WindowManager
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	virtual void update();  // +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	virtual void update();  // +0x14
	BFME_VSLOT(6)
	virtual void draw();    // +0x1C
};

#undef BFME_VSLOT

extern Mouse *TheMouse;
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;
extern Display *TheDisplay;
extern void setFPMode();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class LoadScreen
{
public:
	virtual void update( int percent );

private:
	unsigned char m_unmodelled_04[8];
	unsigned char m_ready;						// this+0x0C
};

void LoadScreen::update( int )
{
	if( m_ready )
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, 0, 1.0f );
		TheGameEngine->serviceWindowsOS();
		TheWindowManager->update();
		g_theWindowManager->update();
		TheDisplay->update();
		TheDisplay->draw();
	}
	setFPMode();
}
