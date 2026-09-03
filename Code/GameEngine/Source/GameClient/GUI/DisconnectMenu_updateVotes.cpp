// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?updateVotes@DisconnectMenu@@QAEXHH@Z
// DisconnectMenu::updateVotes, retail 0x0050EFB0, 198 bytes.
// BFME writes VotesReceived%d through WindowManager::bfme_setAptText; the
// format string is a by-value UnicodeString. Copy ctor and dtor are inline
// forwarders onto StringBase<unsigned short> so the EH saved-esp store lands
// before mov ecx,esp.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &o ) : StringBase<char>( o ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void updateVotes( int slot, int votes );
};

void DisconnectMenu::updateVotes( int slot, int votes )
{
	AsciiString variableName;
	variableName.format( (AsciiString)"DisconnectScreen::VotesReceived%d", slot );

	UnicodeString text( L" " );
	if( votes )
		text.format( (UnicodeString)L"%d", votes );

	g_theWindowManager->bfme_setAptText( variableName, text );
}
