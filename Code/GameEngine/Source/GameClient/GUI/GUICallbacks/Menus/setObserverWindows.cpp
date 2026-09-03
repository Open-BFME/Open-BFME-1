// cl: /DNDEBUG /MD /EHsc
// ?setObserverWindows@@YAXPAVPlayer@@H@Z
// ScoreScreen setObserverWindows, retail 0x004E3720, 1251 bytes.
// ZH twin: i<0||i>=8 returns; StaticTextPlayer%d from getPlayerDisplayName when
// player else hidden; Observer shown; eight stats hidden (BuildingsDestroyed
// twice); Winner shown with getPlayerTemplate()->getSideIconImage. Template
// getter is the +4 pointer load.

typedef int Int;
typedef unsigned int Color;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class Image;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	const Image *getSideIconImage( void ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	UnicodeString getPlayerDisplayName( void );
	const PlayerTemplate *getPlayerTemplate( void ) const { return m_playerTemplate; }

private:
	void *m_vptr;
	const PlayerTemplate *m_playerTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide( int hide );
	int winGetEnabledTextBorderColor( void );
	void winSetEnabledTextColors( int color, int borderColor );
	int winSetEnabledImage( int index, const Image *image );
};

typedef int NameKeyType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
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

void setObserverWindows( Player *player, Int i )
{
	if( i < 0 || i >= MAX_SLOTS )
		return;

	AsciiString winName;
	GameWindow *win;
	Color color = 0xffffffff;

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextPlayer%d", i );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	if( player )
	{
		GadgetStaticTextSetText( win, player->getPlayerDisplayName() );
		win->winHide( 0 );
		win->winSetEnabledTextColors( color, win->winGetEnabledTextBorderColor() );
	}
	else
	{
		win->winHide( 1 );
	}

	winName.format( (AsciiString)"ScoreScreen.wnd:StaticTextObserver%d", i );
	win = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( winName.str() ) );
	win->winHide( 0 );

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
	win->winHide( 0 );
	const PlayerTemplate *fact = player->getPlayerTemplate();
	if( fact != 0 )
		win->winSetEnabledImage( 0, fact->getSideIconImage() );
}
