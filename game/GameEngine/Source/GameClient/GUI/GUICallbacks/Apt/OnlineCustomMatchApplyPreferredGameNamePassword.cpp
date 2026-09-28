// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::applyPreferredGameNamePassword, retail
// 0x0053B980, 458 bytes. If the bool is set, CustomMatchPreferences at
// this+0x174 getAsciiString (+0x18) reads PreferedGameName (default
// GameSpyInfo getLocalName at +0x68) and PreferedGamePassword (default
// TheEmptyString), then UnicodeString::translate into the two locals.
// Otherwise findSelectedStagingRoom copies the wide string at room+0x418.
// Both text entries (+0x1A0 / +0x1A4) take GadgetTextEntrySetText;
// winEnable(name, arg) and winEnable(password, true). Flag at +0x1D6 = 1.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );

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
	static const AsciiString TheEmptyString;

	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void translate( const AsciiString &src );
};

class GameWindow
{
public:
	int winEnable( bool enable );
};

class GameSpyStagingRoom
{
public:
	UnicodeString getGameName();
};

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 );
	virtual AsciiString getLocalName() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class CustomMatchPreferences
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual AsciiString getAsciiString( AsciiString key, AsciiString defaultValue ) const;
};

void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyPreferredGameNamePassword( bool fromPrefs );
	GameSpyStagingRoom *findSelectedStagingRoom();

private:
	unsigned char m_head[ 0x174 ];
	CustomMatchPreferences m_prefs;
	unsigned char m_mid[ 0x1A0 - 0x178 ];
	GameWindow *m_nameEntry;
	GameWindow *m_passwordEntry;
	unsigned char m_tail[ 0x1D6 - 0x1A8 ];
	unsigned char m_namePasswordApplied;
};

void BfmeAptScreenOnlineCustomMatch::applyPreferredGameNamePassword( bool fromPrefs )
{
	if( !m_nameEntry )
		return;

	UnicodeString passwordText;
	UnicodeString nameText;
	if( fromPrefs )
	{
		nameText.translate( m_prefs.getAsciiString(
			AsciiString( "PreferedGameName" ), TheGameSpyInfo->getLocalName() ) );
		passwordText.translate( m_prefs.getAsciiString(
			AsciiString( "PreferedGamePassword" ), AsciiString::TheEmptyString ) );
	}
	else
	{
		GameSpyStagingRoom *room = findSelectedStagingRoom();
		if( room )
			nameText.set( room->getGameName() );
	}

	m_namePasswordApplied = 1;
	GadgetTextEntrySetText( m_nameEntry, nameText );
	m_nameEntry->winEnable( fromPrefs );
	m_passwordEntry->winEnable( true );
	GadgetTextEntrySetText( m_passwordEntry, passwordText );
}
