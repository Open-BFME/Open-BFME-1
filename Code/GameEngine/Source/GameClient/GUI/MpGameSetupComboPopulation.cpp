// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned short WideChar;
typedef int Color;
typedef int Int;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

protected:
	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}
};

class GameWindow;

class GameWindow
{
public:
	int winEnable( bool enable );
	int winBringToTop();
};

class AsciiString;

class UserPreferences
{
public:
	bool getBool( AsciiString key, bool defaultValue );
};

class MpGameSetupPreferences
{
public:
	virtual void slot00() = 0;
	virtual UserPreferences *getPreferences() = 0;
};

template <> class StringBase<char>
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const char *text );
	StringBase( const StringBase<char> &other );
	~StringBase();

public:
	void set( const StringBase<char> &other );

protected:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;

void GadgetComboBoxReset( GameWindow *comboBox );
int GadgetComboBoxAddEntry( GameWindow *comboBox, UnicodeString text, Color color );
void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, Int selected, bool notify = true );

class MpGameSetup
{
public:
	void populateGameType();
	void populateMapType();

private:
	unsigned char m_unmodelled0[ 4 ];
	MpGameSetupPreferences *m_preferences;
	unsigned char m_unmodelled8[ 0x110 ];
	GameWindow *m_mapType;
	GameWindow *m_gameType;
};

// The BFME MpGameSetup game-type selector contains the single HeadToHead
// entry used by this build.
void MpGameSetup::populateGameType()
{
	GameWindow *combo = m_gameType;
	if ( !combo )
		return;

	GadgetComboBoxReset( m_gameType );
	GadgetComboBoxAddEntry( m_gameType, TheGameText->fetch( "Apt:HeadToHead" ),
		*(int *)0x012B76F4 );
	GadgetComboBoxSetSelectedPos( m_gameType, 0, false );
	m_gameType->winEnable( false );
}

void MpGameSetup::populateMapType()
{
	if ( !m_mapType )
		return;

	GadgetComboBoxReset( m_mapType );
	GadgetComboBoxAddEntry( m_mapType, TheGameText->fetch( "Apt:OfficialMaps" ),
		*(int *)0x012B76F4 );
	GadgetComboBoxAddEntry( m_mapType, TheGameText->fetch( "Apt:PlayerMadeMaps" ),
		*(int *)0x012B76F4 );

	AsciiString key( "UseSystemMapDir" );
	bool useSystemMapDir = m_preferences->getPreferences()->getBool( key, true );
	if ( useSystemMapDir )
		GadgetComboBoxSetSelectedPos( m_mapType, 0, false );
	else
		GadgetComboBoxSetSelectedPos( m_mapType, 1, true );
	m_mapType->winBringToTop();
}
