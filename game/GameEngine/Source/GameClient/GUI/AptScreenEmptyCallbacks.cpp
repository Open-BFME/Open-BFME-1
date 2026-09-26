// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Three Apt screen callbacks that retail compiled to a bare return, none of
// which carried a ledger row. The campaign review constructor at 0x0050E320
// registers 0x0050DA10 under the selector string
// "AptCampaignReview::InitGadgets", the LAN lobby constructor at 0x00519F90
// registers 0x00516A40 under "AptLanLobby::OnInitialized", and the online
// shell constructor at 0x0055D150 registers 0x0055BD70 under
// "AptOnline::OnInitialized". Each body is the ret alone, three bytes, with
// int3 padding after it.

class GameWindow;

class BfmeAptScreenCampaignReview
{
public:
	void _bfme_initGadgets( const char *name, void *argument, GameWindow *window );
};

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitialized( const char *name );
};

class BfmeAptScreenOnlineShell
{
public:
	void _bfme_onInitialized( const char *name );
};

void BfmeAptScreenCampaignReview::_bfme_initGadgets( const char *name,
	void *argument, GameWindow *window )
{
	(void)name;
	(void)argument;
	(void)window;
}

void BfmeAptScreenLanLobby::_bfme_onInitialized( const char *name )
{
	(void)name;
}

void BfmeAptScreenOnlineShell::_bfme_onInitialized( const char *name )
{
	(void)name;
}
