// cl: /DNDEBUG /MD /EHsc
// Open-BFME: readAdditionalDisconnectsFromUserFile, retail 0x004DB0B0, 858 bytes.
// Converted from gen-dump d_004db0b0. ZH twin is static getTotalDisconnectsFromFile
// in PopupPlayerInfo.cpp. BFME takes the player id in ECX (__fastcall), formats
// LoTRB4MEOnline\MiscPref%d.ini, loads UserPreferences, and sums atoi of keys
// "0".."5". Named by the already-matched GetAdditionalDisconnectsFromUserFile
// thunk at 0x004DB4E0, which mov ecx,id / call this body.

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
	void format( AsciiString fmt, ... ) throw();
};

struct PreferenceNode
{
	char m_pad[ 0x14 ];
	StringInlineData<char> *m_data;
};

__forceinline const char *prefStr( PreferenceNode *node )
{
	StringInlineData<char> *data = node->m_data;
	return data ? data->m_text : (const char *)0x0107388B;
}

class PreferenceMap
{
public:
	PreferenceNode *find( const AsciiString &key ) const throw();
	PreferenceNode *m_end;
	int m_count;
	int m_cmp;
};

class UserPreferences
{
public:
	UserPreferences() throw();
	virtual ~UserPreferences();
	virtual bool load( AsciiString fname ) throw();

	PreferenceMap m_map;
	AsciiString m_filename;
};

int __fastcall readAdditionalDisconnectsFromUserFile( int playerID )
{
	int retval = 0;
	if ( playerID == 0 )
		return 0;

	UserPreferences pref;
	AsciiString userPrefFilename;
	userPrefFilename.format( AsciiString( "LoTRB4MEOnline\\MiscPref%d.ini" ), playerID );
	pref.load( userPrefFilename );

	if ( pref.m_map.find( "0" ) != pref.m_map.m_end )
		retval = atoi( prefStr( pref.m_map.find( "0" ) ) );
	if ( pref.m_map.find( "1" ) != pref.m_map.m_end )
		retval += atoi( prefStr( pref.m_map.find( "1" ) ) );
	if ( pref.m_map.find( "2" ) != pref.m_map.m_end )
		retval += atoi( prefStr( pref.m_map.find( "2" ) ) );
	if ( pref.m_map.find( "3" ) != pref.m_map.m_end )
		retval += atoi( prefStr( pref.m_map.find( "3" ) ) );
	if ( pref.m_map.find( "4" ) != pref.m_map.m_end )
		retval += atoi( prefStr( pref.m_map.find( "4" ) ) );
	if ( pref.m_map.find( "5" ) != pref.m_map.m_end )
		retval += atoi( prefStr( pref.m_map.find( "5" ) ) );

	return retval;
}
