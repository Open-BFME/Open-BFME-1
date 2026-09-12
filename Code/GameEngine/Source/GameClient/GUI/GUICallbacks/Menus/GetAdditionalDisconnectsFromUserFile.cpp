// ?GetAdditionalDisconnectsFromUserFile@@YAXPAVPSPlayerStats@@@Z
// BFME retail 0x004DB560 (1205 bytes); caller SendStatsToOtherPlayers via ILT 0x00023F8D.
// The body is the BFME typed PSPlayerStats* overload.  It uses the local
// UserPreferences and GameSpyInfo views from the retail call sequence.
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <map>

extern "C" int (__cdecl *__imp__atoi)( const char * );

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

int __fastcall readAdditionalDisconnectsFromUserFile( int playerID );

typedef std::map<int, unsigned> BfmeIntUMap;

class PSPlayerStats
{
public:
	int id;
	char m_pad[ 0xB8 - 4 ];
	BfmeIntUMap discons;
	BfmeIntUMap desyncs;
};

typedef int (__fastcall *BfmeGetDisconnectCount)( void *queue );
typedef void (__fastcall *BfmeClearDisconnectCount)( void *queue );

struct GameSpyInfoVtbl
{
	void *m_before[ 0x170 / sizeof( void * ) ];
	BfmeGetDisconnectCount getAdditionalDisconnects;
	BfmeClearDisconnectCount clearAdditionalDisconnects;
};

struct GameSpyInfo
{
	GameSpyInfoVtbl *m_vtbl;
	__forceinline int getAdditionalDisconnects() { return m_vtbl->getAdditionalDisconnects( this ); }
	__forceinline void clearAdditionalDisconnects() { m_vtbl->clearAdditionalDisconnects( this ); }
};

extern GameSpyInfo *TheGameSpyInfo;

// ?GetAdditionalDisconnectsFromUserFile@@YAXPAVPSPlayerStats@@@Z
void GetAdditionalDisconnectsFromUserFile( PSPlayerStats *stats )
{
	if ( !stats || stats->id == 0 )
		return;

	if ( TheGameSpyInfo->getAdditionalDisconnects() > 0
		&& !readAdditionalDisconnectsFromUserFile( stats->id ) )
		TheGameSpyInfo->clearAdditionalDisconnects();

	if ( TheGameSpyInfo->getAdditionalDisconnects() < 1 )
		return;

	UserPreferences pref;
	AsciiString userPrefFilename;
	userPrefFilename.format( AsciiString( "LoTRB4MEOnline\\MiscPref%d.ini" ), stats->id );
	pref.load( userPrefFilename );

	if ( pref.m_map.find( "0" ) != pref.m_map.m_end )
	{
		stats->desyncs[ 2 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "0" ) ) ) );
	}
	if ( pref.m_map.find( "1" ) != pref.m_map.m_end )
	{
		stats->desyncs[ 3 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "1" ) ) ) );
	}
	if ( pref.m_map.find( "2" ) != pref.m_map.m_end )
	{
		stats->desyncs[ 4 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "2" ) ) ) );
	}
	if ( pref.m_map.find( "3" ) != pref.m_map.m_end )
	{
		stats->discons[ 2 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "3" ) ) ) );
	}
	if ( pref.m_map.find( "4" ) != pref.m_map.m_end )
	{
		stats->discons[ 3 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "4" ) ) ) );
	}
	if ( pref.m_map.find( "5" ) != pref.m_map.m_end )
	{
		stats->discons[ 4 ] += (unsigned)abs( (*__imp__atoi)( prefStr( pref.m_map.find( "5" ) ) ) );
	}
}
