// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// AptOnlineQuickMatch::InitGadgets callback, retail 0x00558FB0 (244 bytes).
// The selector strings are the five OnlineQuickMatch gadget names in BFME's
// retail string table.  The callback stores each supplied window in the
// embedded gadget state and refreshes the screen's window-manager layout.

class GameWindow {};

extern "C" int __cdecl strcmp(const char *left, const char *right);

class BfmeAptGameWindow
{
public:
	virtual void slot00();

	// The callback closes/re-registers the owning APT layout through the
	// window manager after each gadget is discovered.
	unsigned char m_beforeLayout[0x30];
	void *m_layout; // +0x34
	unsigned char m_afterLayout[0x08];
};

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();

private:
	unsigned char m_unmodelled[0x10];
};

class Gen_004b5a80
{
public:
	void *m(int value);
};

class GameWindowManager
{
public:
	void refreshLayout(void *layout);
};

extern GameWindowManager *TheWindowManager;
extern void gadgetComboBoxReset(GameWindow *window);

#pragma comment(linker, "/alternatename:?refreshLayout@GameWindowManager@@QAEXPAX@Z=?j_000412c2@@YAXXZ")
#pragma comment(linker, "/alternatename:?gadgetComboBoxReset@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")

class BfmeAptScreenOnlineQuickMatch : public BfmeAptGameWindow
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	QuickMatchPreferences m_preferences;
	unsigned char m_ready;
	unsigned char m_startRequested;
	unsigned char m_pad56;
	unsigned char m_pad57;
	int m_flags;
	struct GadgetState
	{
		GameWindow *m_color;
		GameWindow *m_numPlayers;
		GameWindow *m_side;
		GameWindow *m_connectionSpeed;
		GameWindow *m_ladder;
	} m_gadgets;
};

class OnlineQuickMatchColorSetup
{
public:
	void setup();
};

#pragma comment(linker, "/alternatename:?setup@OnlineQuickMatchColorSetup@@QAEXXZ=?j_00005f3d@@YAXXZ")

void BfmeAptScreenOnlineQuickMatch::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window)
{
	if( window == 0 )
		return;

	if( strcmp( name, "OnlineQuickMatch::Color" ) == 0 )
	{
		((Gen_004b5a80 *)&m_gadgets)->m((int)window);
		((OnlineQuickMatchColorSetup *)this)->setup();
		m_flags |= 1;
	}
	else if( strcmp( name, "OnlineQuickMatch::NumOfPlayers" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_numPlayers = window;
		m_flags |= 4;
	}
	else if( strcmp( name, "OnlineQuickMatch::Side" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_side = window;
		m_flags |= 0x20;
	}
	else if( strcmp( name, "OnlineQuickMatch::ConnectionSpeed" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_connectionSpeed = window;
		m_flags |= 0x40;
	}
	else if( strcmp( name, "OnlineQuickMatch::Ladder" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_ladder = window;
		m_flags |= 0x80;
	}

	TheWindowManager->refreshLayout(m_layout);
}
