// cl: /DNDEBUG /MD /EHsc
// ?populateSideInfo@@YAXVUnicodeString@@PAUScoreGather@@HI@Z
// ScoreScreen populateSideInfo, retail 0x004E3D40, 1714 bytes.
// ZH twin in ScoreScreen.cpp: pos<0||pos>8 returns; StaticTextPlayer%d = side;
// Observer hidden; eight stats formatted L%d from ScoreGather; GameWindowWinner%d
// image. By-value UnicodeString / AsciiString format args use inline StringBase
// forwarders so the EH saved-esp store lands before mov ecx,esp.

typedef int Int;
typedef unsigned int Color;

struct AsciiStringData
{
	int m_refCount;
	int m_length;
	char m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

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

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
};

class Image;

struct ScoreGather
{
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed;
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed;
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
	const Image *m_sideImage;
};

class GameWindow
{
public:
	int winHide( int hide );
	int winGetEnabledTextBorderColor( void );
	void winSetEnabledTextColors( int color, int borderColor );
	int winSetEnabledImage( int index, const Image *image );
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

void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );

enum { MAX_SLOTS = 8 };

void populateSideInfo( UnicodeString side, ScoreGather *sg, Int pos, Color color )
{
	if( pos < 0 || pos > MAX_SLOTS )
		return;

	AsciiString winName;
	UnicodeString winValue;
	GameWindow *win;

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextPlayer%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	GadgetStaticTextSetText( win, side );
	win->winHide( 0 );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextObserver%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	win->winHide( 1 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsBuilt%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalUnitsBuilt );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsLost%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalUnitsLost );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextUnitsDestroyed%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalUnitsDestroyed );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsBuilt%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalBuildingsBuilt );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsLost%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalBuildingsLost );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextBuildingsDestroyed%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalBuildingsDestroyed );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextResources%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	winValue.format( (UnicodeString)L"%d", sg->m_totalMoneyEarned );
	GadgetStaticTextSetText( win, winValue );
	win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	win->winHide( 0 );

	winName.format( (AsciiString)"ScoreScreen.wnd:GameWindowWinner%d", pos );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	if( sg->m_sideImage )
	{
		win->winHide( 0 );
		win->winSetEnabledImage( 0, sg->m_sideImage );
	}
}
