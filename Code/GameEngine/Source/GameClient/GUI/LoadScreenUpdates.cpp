// cl: /DNDEBUG /MD
// readable body of ?reset@ShellGameLoadScreen@@UAEXXZ: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?update@LoadScreen@@UAEXH@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?update@ShellGameLoadScreen@@UAEXH@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?update@MultiPlayerLoadScreen@@: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?update@GameSpyLoadScreen@@: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?update@MapTransferLoadScreen@@: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// The load screen's per-frame pump, in all four of its flavours, plus the one
// reset that shares their layout. A load screen is what runs the game while
// nothing else can: LoadScreen::update at 0x004914C0 is the whole frame --
// clear the cursor tooltip, service the OS message queue, update both window
// managers, update and draw the display -- and each subclass wraps it with
// whatever else has to keep breathing while the map loads.
//
//   ShellGameLoadScreen  drives its progress bar and calls up.       0x00491550
//   MultiPlayerLoadScreen reports the local player's progress, over  0x00491EB0
//                        the network if there is one and straight to
//                        the logic if there is not.
//   GameSpyLoadScreen    reports it over the network unconditionally 0x00491F30
//                        -- there always is one -- and pumps it.
//   MapTransferLoadScreen is the odd one: not a LoadScreen subclass  0x0050FF30
//                        at all and not virtual, it inlines the whole
//                        base frame on top of a full network update
//                        because it runs while a map is downloading.
//
// Six files with six partial views of the same classes become one, and the
// views were only ever partial: LoadScreen's own body knew the ready byte at
// +0x0C, the ShellGame reset knew the load-screen window at +0x08, and the
// ShellGame update knew nothing between +0x04 and +0x10 but needed the size to
// reach its progress bar at +0x10. All three statements are in the one layout
// below, and none of the six bodies moved a byte.

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

class GameWindow;
struct RGBColor;

void GadgetProgressBarSetProgress( GameWindow *g, int progress );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
// The union of the two views the six bodies had of this table: MapTransfer's
// full update at +0x28 sat where GameSpy's copy counted an unnamed slot 10.
class NetworkInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8)
	virtual void liteupdate( int mode );              // +0x24
	virtual void update( int mode );                  // +0x28
	BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	BFME_VSLOT(14) BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17)
	BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20) BFME_VSLOT(21)
	BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24) BFME_VSLOT(25)
	BFME_VSLOT(26) BFME_VSLOT(27)
	virtual void updateLoadProgress( int percent );   // +0x70
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4)
	virtual int getLocalSlotNum();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void processProgress( int player, int percent );
};

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
extern GameInfo *TheGameInfo;
extern GameLogic *TheGameLogic;
extern Mouse *TheMouse;
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;
extern Display *TheDisplay;
extern void setFPMode();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
// Slot numbering is vtable 0x010F9B0C, where the ShellGame screen's update is
// slot 1, its already-matched init at 0x004920E0 is slot 2 and its reset is
// slot 3. The three trailing pad bytes are what carry the base to +0x10, where
// every subclass below starts its own members.
class LoadScreen
{
public:
	virtual void slot00();
	virtual void update( int percent );
	virtual void init();
	virtual void reset();

protected:
	unsigned char m_unmodelled_04[4];
	GameWindow *m_loadScreen;					// this+0x08
	unsigned char m_ready;						// this+0x0C
	unsigned char m_unmodelled_0D[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
	virtual void reset();

private:
	GameWindow *m_progressBar;					// this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MultiPlayerLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class GameSpyLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MapTransferLoadScreen
{
public:
	void update( int percent );
};

// ?reset@ShellGameLoadScreen@@UAEXXZ
// Retail 0x00490570, 9 bytes.
void ShellGameLoadScreen::reset()
{
	m_loadScreen = 0;
	m_progressBar = 0;
}

// ?update@LoadScreen@@UAEXH@Z
// Retail 0x004914C0, 109 bytes. percent is unused: the base frame draws
// whatever the subclass already put on the screen. setFPMode runs whether or
// not the screen is ready, which is why it sits outside the test.
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

// ?update@ShellGameLoadScreen@@UAEXH@Z
// Retail 0x00491550, 34 bytes.
void ShellGameLoadScreen::update( int percent )
{
	GadgetProgressBarSetProgress( m_progressBar, percent );
	LoadScreen::update( percent );
}

// ?update@MultiPlayerLoadScreen@@UAEXH@Z
// Retail 0x00491EB0, 97 bytes. Over 100 percent means loading is done and the
// number is no longer a progress report, so it is not sent.
void MultiPlayerLoadScreen::update( int percent )
{
	if( TheNetwork ) {
		if( percent <= 100 )
			TheNetwork->updateLoadProgress( percent );
		TheNetwork->liteupdate( 0 );
	} else {
		if( percent <= 100 )
			TheGameLogic->processProgress( TheGameInfo->getLocalSlotNum(), percent );
	}
	LoadScreen::update( percent );
}

// ?update@GameSpyLoadScreen@@UAEXH@Z
// Retail 0x00491F30, 51 bytes.
void GameSpyLoadScreen::update( int percent )
{
	if( percent <= 100 )
		TheNetwork->updateLoadProgress( percent );
	TheNetwork->liteupdate( 0 );
	LoadScreen::update( percent );
}

// ?update@MapTransferLoadScreen@@QAEXH@Z
// Retail 0x0050FF30, 114 bytes. Driven from _doFileTransfer, and neither
// percent nor this is used: it is the base frame with a full network update in
// front of it, inlined rather than called because this class does not derive
// from LoadScreen.
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
