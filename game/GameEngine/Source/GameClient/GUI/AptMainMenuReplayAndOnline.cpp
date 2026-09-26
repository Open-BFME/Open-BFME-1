// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two BfmeAptScreenMainMenu button handlers with no ledger row: retail
// 0x0051DCF0 and 0x0051DB10. The constructor at 0x0051F3A0 registers them
// under the selector strings "AptMainMenu::LoadReplay" and
// "AptMainMenu::OnlineButtonPressed", and AptMainMenuConstructor.cpp already
// names both methods. Each one first runs the shell music helper at
// 0x0051D590 on this, which Rva0051D590ShellMusic.cpp calls first().

class Rva0051D590
{
public:
	void first();
};

void showAptSaveLoad( void *arg0, int flags, const volatile char extra );

// Retail 0x006304A0, reached through ILT 0x0004B664 and still an unconverted
// dump row, so it is called by its address-derived ledger name.
void d_006304a0( void );
typedef void ( __cdecl *BfmeShowOnlineScreenFn )( int mode );

class BfmeAptScreenMainMenu
{
public:
	void _bfme_loadReplay( const char *name );
	void _bfme_onlineButtonPressed( const char *name );
};

void BfmeAptScreenMainMenu::_bfme_loadReplay( const char *name )
{
	(void)name;
	( (Rva0051D590 *)this )->first();
	showAptSaveLoad( (void *)2, 4, 0 );
}

void BfmeAptScreenMainMenu::_bfme_onlineButtonPressed( const char *name )
{
	(void)name;
	( (Rva0051D590 *)this )->first();
	( (BfmeShowOnlineScreenFn)&d_006304a0 )( 1 );
}
