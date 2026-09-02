// cl: /DNDEBUG /MD
//
// Retail 0x0050FF30: the non-virtual update(Int percent) of the APT-era map
// transfer load screen, driven from _doFileTransfer (ZH FileTransfer.cpp:54
// and 124).  The body inlines ZH MapTransferLoadScreen::update on top of
// LoadScreen::update: pump the network, clear the cursor tooltip, service the
// OS, update both window managers, then update and draw the display.  The
// percent argument and this are unused.  No /EHsc: retail carries the
// by-value stash without a registered handler, the exception-disabled model.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update( int mode );  // +0x28
};

struct RGBColor;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Mouse.h
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

extern NetworkInterface *TheNetwork;
extern Mouse *TheMouse;
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;
extern Display *TheDisplay;

class GameInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MapTransferLoadScreen
{
public:
	void update( int percent );
};

// ?update@MapTransferLoadScreen@@QAEXH@Z
void MapTransferLoadScreen::update( int )
{
	if( TheNetwork )
		TheNetwork->update( 0 );

	TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, 0, 1.0f );
	TheGameEngine->serviceWindowsOS();
	TheWindowManager->update();
	g_theWindowManager->update();
	TheDisplay->update();
	TheDisplay->draw();
}
