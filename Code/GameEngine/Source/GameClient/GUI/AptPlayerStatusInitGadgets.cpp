// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// AptPlayerStatus::InitGadgets, retail 0x0052B020, 196 bytes. The player
// status screen constructor pushes the selector string
// "AptPlayerStatus::InitGadgets" at 0x0052CA9C and loads this body's ILT
// thunk a few bytes later, which is what names it.
//
// The callback takes one mute check box per player slot. It reads the slot
// number off the end of the gadget name, parks the window in the array at
// this+0x268, hides it, and shows it again with the right checked state when
// the slot holds a human player.

extern "C" unsigned strlen( const char *s );
#pragma intrinsic( strlen )

__declspec(dllimport) int __cdecl bfmeCmp1026( char *left, char *right, int count );
__declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

class GameWindow
{
public:
	int winHide( bool hide );
};

class GameSlot
{
public:
	bool isAI( void ) const;

	unsigned char m_head[ 0xA ];
	bool m_isMuted;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot( int index ) const;
};

extern GameInfo *TheGameInfo;

void GadgetCheckBoxSetChecked( GameWindow *window, bool checked );

class AptPlayerStatus
{
public:
	void InitGadgets( const char *name, void *userData, GameWindow *window );

private:
	unsigned char m_head[ 0x268 ];
	GameWindow *m_muteWindows[ 8 ];
	char m_slotNumbers[ 8 ];
};

// ?InitGadgets@AptPlayerStatus@@QAEXPBDPAXPAVGameWindow@@@Z
void AptPlayerStatus::InitGadgets( const char *name, void *userData, GameWindow *window )
{
	const char *const prefix = "PlayerStatus::Mute";
	static const int prefixLength = strlen( prefix );

	(void)userData;
	if ( bfmeCmp1026( (char *)name, (char *)prefix, prefixLength ) != 0 )
		return;

	name += prefixLength;
	int index = bfmeAtoi1027( (char *)name );
	if ( index < 0 || index >= 8 )
		return;

	m_muteWindows[ index ] = window;
	window->winHide( true );

	char slot = m_slotNumbers[ index ];
	if ( slot < 0 )
		return;

	const GameSlot *gameSlot = TheGameInfo->getConstSlot( slot );
	if ( gameSlot == 0 )
		return;
	if ( gameSlot->isAI() )
		return;

	window->winHide( false );
	GadgetCheckBoxSetChecked( window, gameSlot->m_isMuted );
}
