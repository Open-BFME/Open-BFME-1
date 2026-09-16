// ?_bfme_mapGadgetInit@BfmeAptScreenMapPreview@@QAEXPBDPAXPAVGameWindow@@@Z
// partial score=0.82 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// MapPreview.apt gadget registration callback, retail 0x00521990. The map
// preview constructor pushes the selector string "AptMapPreview::MapGadgetInit"
// at retail 0x00521AFD and loads this body ILT thunk right after, so the name
// comes off the binary.
//
// The size is exact at 261 bytes and every instruction matches except two
// register names. Retail keeps this in ebp and the strcmp zero and the child
// counter in ebx, and this build swaps that pair. Seven spellings left the pair
// alone: memcmp in place of strcmp (that one also turns the eight-byte compare
// into repe cmpsd and is wrong), an explicit slot pointer walked with ++, the
// slot pointer declared before the counter, an unsigned counter, the eight-slot
// test as a break inside the loop, the assign receiver cached in a local, and
// the name argument copied to a local.
//
// Two callee names come from the binary. strcmp is the compiler intrinsic, which
// is what gives repe cmpsb with the literal length plus one. The tail call is
// AsciiStringTarget::assign at retail 0x005217A0, pinned at ILT 0x0003EC57 and
// already called that way from Gen00525EE0SetSecondGame.cpp, and the receiver is
// this because the screen keeps its map name string at offset zero.

extern "C" int __cdecl strcmp( const char *left, const char *right );
#pragma intrinsic( strcmp )

typedef bool Bool;

class GameWindow
{
public:
	int winHide( Bool hide );
	GameWindow *winGetChild();
	GameWindow *winGetNext();
};

class BfmeObjENK;

void bfmeGoENK( BfmeObjENK *window, char enable );
void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listbox, Bool enable );

class AsciiString
{
public:
	void *m_data;
};

class AsciiStringTarget
{
public:
	void assign( const AsciiString &value );
};

class BfmeAptScreenMapPreview
{
public:
	void _bfme_mapGadgetInit( const char *name, void *argument, GameWindow *window );

private:
	AsciiString m_mapName;
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_mapSlots[ 8 ];
};

void BfmeAptScreenMapPreview::_bfme_mapGadgetInit( const char *name,
	void *argument, GameWindow *window )
{
	(void)argument;

	if( window == 0 )
		return;

	if( strcmp( name, "MapInfo" ) == 0 )
	{
		m_mapInfo = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapInfo, true );
		( (AsciiStringTarget *)this )->assign( m_mapName );
		return;
	}

	if( strcmp( name, "MapDescription" ) == 0 )
	{
		m_mapDescription = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapDescription, true );
		( (AsciiStringTarget *)this )->assign( m_mapName );
		return;
	}

	if( strcmp( name, "MapPicture" ) == 0 )
	{
		m_mapPicture = window;
		( (AsciiStringTarget *)this )->assign( m_mapName );
		return;
	}

	if( strcmp( name, "CurrentMap" ) == 0 )
	{
		m_currentMap = window;

		int count = 0;
		GameWindow *child = window->winGetChild();

		while( child != 0 && count < 8 )
		{
			m_mapSlots[ count ] = child;
			child->winHide( true );
			++count;
			child = child->winGetNext();
		}
	}

	( (AsciiStringTarget *)this )->assign( m_mapName );
}
