// cl: /DNDEBUG /MD /EHsc
// ?hideWindows@@YAXH@Z
// ScoreScreen hideWindows, retail 0x004E3150, 1186 bytes.
// ZH twin: pos<0||pos>=8 returns; for i=pos..7 winHide(TRUE) on the 11
// ScoreScreen.wnd:*%d windows (BuildingsDestroyed is written twice, as in ZH).

typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
	const char *str( void ) const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class GameWindow
{
public:
	int winHide( int hide );
};

typedef int NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class GameWindowManager
{
public:
	virtual void bfmeSlot00( void ) = 0;
	virtual void bfmeSlot01( void ) = 0;
	virtual void bfmeSlot02( void ) = 0;
	virtual void bfmeSlot03( void ) = 0;
	virtual void bfmeSlot04( void ) = 0;
	virtual void bfmeSlot05( void ) = 0;
	virtual void bfmeSlot06( void ) = 0;
	virtual void bfmeSlot07( void ) = 0;
	virtual void bfmeSlot08( void ) = 0;
	virtual void bfmeSlot09( void ) = 0;
	virtual void bfmeSlot10( void ) = 0;
	virtual void bfmeSlot11( void ) = 0;
	virtual void bfmeSlot12( void ) = 0;
	virtual void bfmeSlot13( void ) = 0;
	virtual void bfmeSlot14( void ) = 0;
	virtual void bfmeSlot15( void ) = 0;
	virtual void bfmeSlot16( void ) = 0;
	virtual void bfmeSlot17( void ) = 0;
	virtual void bfmeSlot18( void ) = 0;
	virtual void bfmeSlot19( void ) = 0;
	virtual void bfmeSlot20( void ) = 0;
	virtual void bfmeSlot21( void ) = 0;
	virtual void bfmeSlot22( void ) = 0;
	virtual void bfmeSlot23( void ) = 0;
	virtual void bfmeSlot24( void ) = 0;
	virtual void bfmeSlot25( void ) = 0;
	virtual void bfmeSlot26( void ) = 0;
	virtual void bfmeSlot27( void ) = 0;
	virtual void bfmeSlot28( void ) = 0;
	virtual void bfmeSlot29( void ) = 0;
	virtual void bfmeSlot30( void ) = 0;
	virtual void bfmeSlot31( void ) = 0;
	virtual void bfmeSlot32( void ) = 0;
	virtual void bfmeSlot33( void ) = 0;
	virtual void bfmeSlot34( void ) = 0;
	virtual void bfmeSlot35( void ) = 0;
	virtual void bfmeSlot36( void ) = 0;
	virtual void bfmeSlot37( void ) = 0;
	virtual void bfmeSlot38( void ) = 0;
	virtual void bfmeSlot39( void ) = 0;
	virtual void bfmeSlot40( void ) = 0;
	virtual void bfmeSlot41( void ) = 0;
	virtual void bfmeSlot42( void ) = 0;
	virtual void bfmeSlot43( void ) = 0;
	virtual void bfmeSlot44( void ) = 0;
	virtual void bfmeSlot45( void ) = 0;
	virtual void bfmeSlot46( void ) = 0;
	virtual void bfmeSlot47( void ) = 0;
	virtual void bfmeSlot48( void ) = 0;
	virtual void bfmeSlot49( void ) = 0;
	virtual void bfmeSlot50( void ) = 0;
	virtual void bfmeSlot51( void ) = 0;
	virtual void bfmeSlot52( void ) = 0;
	virtual void bfmeSlot53( void ) = 0;
	virtual void bfmeSlot54( void ) = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id ) = 0;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern GameWindow *parent;

enum { MAX_SLOTS = 8 };

void hideWindows( Int pos )
{
	if( pos < 0 || pos >= MAX_SLOTS )
		return;

	AsciiString winName;
	GameWindow *win;
	for( Int i = pos; i < MAX_SLOTS; ++i )
	{
		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextPlayer%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextObserver%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsBuilt%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsLost%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsDestroyed%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsBuilt%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsLost%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsDestroyed%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsDestroyed%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextResources%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );

		winName.format( (AsciiString)"ScoreScreen.wnd:GameWindowWinner%d", i );
		win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
		win->winHide( 1 );
	}
}
