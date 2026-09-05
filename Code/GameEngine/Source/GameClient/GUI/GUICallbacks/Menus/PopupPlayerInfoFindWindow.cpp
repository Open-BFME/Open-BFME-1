// cl: /DNDEBUG /MD /EHsc
// Open-BFME: findWindow, retail 0x004DA630, 235 bytes. Converted from
// gen-dump d_004da630. ZH PopupPlayerInfo.cpp helper: format "%s:%s" from
// two by-value AsciiStrings then TheWindowManager->winGetWindowFromId(parent,
// NAMEKEY). DEBUG_ASSERTLOG compiles out under NDEBUG. 21 callers in
// PopulatePlayerInfoWindows. Vtable slot 0xDC and TheWindowManager CSE before
// nameToKey match hideWindows.cpp.

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

class GameWindow;

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

GameWindow *findWindow( GameWindow *parent, AsciiString baseWindow, AsciiString gadgetName )
{
	AsciiString fullPath;
	fullPath.format( (AsciiString)"%s:%s", baseWindow.str(), gadgetName.str() );
	GameWindow *res = TheWindowManager->winGetWindowFromId( parent, TheNameKeyGenerator->nameToKey( fullPath.str() ) );
	return res;
}
