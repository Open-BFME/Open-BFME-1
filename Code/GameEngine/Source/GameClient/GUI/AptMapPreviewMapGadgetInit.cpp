// cl: /DNDEBUG /MD /EHsc
//
// AptMapPreview::mapGadgetInit, retail 0x00521990, 261 bytes.
// AptMapPreview::initGadgets at 0x00521AE0 pushes the selector string
// "AptMapPreview::MapGadgetInit" at 0x00521AFD and loads this body's ILT thunk
// 0x00036DF9 thirty-one bytes later, which is what names it.
//
// The APT movie calls this once per gadget it declares. Four gadget names
// reach a window into the preview object: MapInfo at +0x0C, MapDescription at
// +0x10, MapPicture at +0x08 and CurrentMap at +0x04. CurrentMap also copies
// up to eight of its child windows into the array at +0x14 and hides each one.
// AptMapPreviewSetMapPicture.cpp at 0x00520E70 witnesses the Image at +0x34,
// which is where that array stops.

typedef bool Bool;

extern "C" int strcmp( const char *left, const char *right );
#pragma intrinsic( strcmp )

class Image;
class BfmeObjENK;
class AsciiString;

// Every branch below ends in the 391-byte body at retail 0x005217A0, reached
// through ILT 0x0003EC57. reverse/symbols.csv already pins that thunk as
// AsciiStringTarget::assign, so this source calls it under the pinned name.
// The callee takes the preview object in ECX and the AsciiString the preview
// keeps at offset zero on the stack, which is why both operands are `this`.
class AsciiStringTarget
{
public:
	void assign( const AsciiString &value );
};

class GameWindow
{
public:
	GameWindow *winGetChild( void );
	GameWindow *winGetNext( void );
	int winHide( Bool hide );
};

void bfmeGoENK( BfmeObjENK *window, char enable );
void BfmeGadgetListBoxSetAudioFeedback( GameWindow *listbox, Bool enable );

// Layout witnessed by AptMapPreviewSetMapPicture.cpp at 0x00520E70 and by the
// picture callback at 0x005204F0.
class AptMapPreview
{
public:
	void mapGadgetInit( const char *name, void *userData, GameWindow *window );

private:
	char m_unmodelled00[ 4 ];
	GameWindow *m_currentMap;
	GameWindow *m_mapPicture;
	GameWindow *m_mapInfo;
	GameWindow *m_mapDescription;
	GameWindow *m_children[ 8 ];
	const Image *m_picture;
	bool m_pictureOwned;
};

void AptMapPreview::mapGadgetInit( const char *name, void *userData,
	GameWindow *window )
{
	(void)userData;
	if ( window == 0 )
		return;

	if ( strcmp( name, "MapInfo" ) == 0 )
	{
		m_mapInfo = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapInfo, true );
	}
	else if ( strcmp( name, "MapDescription" ) == 0 )
	{
		m_mapDescription = window;
		bfmeGoENK( (BfmeObjENK *)window, 1 );
		BfmeGadgetListBoxSetAudioFeedback( m_mapDescription, true );
	}
	else if ( strcmp( name, "MapPicture" ) == 0 )
	{
		m_mapPicture = window;
	}
	else if ( strcmp( name, "CurrentMap" ) == 0 )
	{
		m_currentMap = window;
		int count = 0;
		GameWindow *child = window->winGetChild();
		if ( child != 0 )
		{
			GameWindow **slot = m_children;
			do
			{
				if ( count >= 8 )
					break;
				*slot = child;
				++count;
				++slot;
				child->winHide( true );
				child = child->winGetNext();
			}
			while ( child != 0 );
		}
	}

	( (AsciiStringTarget *)this )->assign( *(const AsciiString *)this );
}
