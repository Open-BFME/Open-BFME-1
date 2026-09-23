// ?_bfme_refreshLoginState@BfmeAptScreenOnlineLogin@@QAEXXZ
// partial score=0.9833 date=2026-09-23
// ?_bfme_refreshLoginState@BfmeAptScreenOnlineLogin@@QAEXXZ
//
// Retail ILT 0x000371FF is called by the matched
// BfmeAptScreenOnlineLogin::_bfme_syncLoginGadgets body.  The constructor's
// ILT 0x00010BE0 builds the GameSpyLoginPreferences-shaped member at +0x3C;
// its inherited UserPreferences map is at +0x40 and the five login controls
// are at +0x74..+0x84.
//
// 0x0054FF80 is retained as a neutral typed method: retail calls it with this
// and the two cached AsciiString values, but no named owner is established by
// its ICF-shared body.  Its direct body pin is kept separate from this owner.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

template <typename T> class StringBase
{
friend class AsciiString;
friend class UnicodeString;

private:
	struct Data
	{
		int m_refCount;
		int m_length;
		T m_text[ 1 ];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	StringBase( const T *text );
	~StringBase();
	void releaseBuffer();
	void set( const StringBase<T> &other );

	Data *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	static const UnicodeString TheEmptyString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
};

class GameWindow;
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
bool GetStringFromRegistry( AsciiString path, AsciiString key,
	AsciiString &value );

struct PreferenceNode
{
	unsigned char m_unmodelled[ 0x14 ];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find( const AsciiString &key ) const throw();
	PreferenceNode *end() const { return m_end; }

private:
	PreferenceNode *m_end;
};

// The constructor at 0x005538A0 calls the GameSpyLoginPreferences ctor at
// +0x3C.  The base preference map is the first data member after its vtable;
// the remaining 0x30 bytes are the three proven GameSpy maps.
class GameSpyLoginPreferences
{
public:
	const void *m_vftable;
	PreferenceMap m_preferences;
	unsigned char m_gameSpyMaps[ 0x30 ];
};

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_refreshLoginState();
	void rva0054FF80( AsciiString &lastEmail, AsciiString &lastName );

private:
	const void *m_vftable;
	unsigned char m_unmodelled04[ 0x30 ];
	void *m_context;
	unsigned char m_unmodelled38[ 4 ];
	GameSpyLoginPreferences m_loginPreferences;
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_control80;
	GameWindow *m_control84;
	unsigned char m_unmodelled88[ 0x0D ];
	bool m_needsRefresh;
};

void BfmeAptScreenOnlineLogin::_bfme_refreshLoginState()
{
	if( m_control7C == 0 || m_control74 == 0 || m_control78 == 0 ||
		m_control80 == 0 )
		return;

	GadgetTextEntrySetText( m_control7C, UnicodeString::TheEmptyString );

	AsciiString lastEmail;
	PreferenceNode *it = m_loginPreferences.m_preferences.find(
		AsciiString( "lastEmail" ) );
	if( it != m_loginPreferences.m_preferences.end() )
	{
		lastEmail = it->m_value;
	}
	else
	{
		GetStringFromRegistry(
			AsciiString( (const char *)0x0107301C ),
			AsciiString( "MemberName" ), lastEmail );
	}

	AsciiString lastName;
	it = m_loginPreferences.m_preferences.find( AsciiString( "lastName" ) );
	if( it != m_loginPreferences.m_preferences.end() )
		lastName = it->m_value;

	rva0054FF80( lastEmail, lastName );
	m_needsRefresh = false;
}
