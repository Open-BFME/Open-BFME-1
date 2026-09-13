// cl: /DNDEBUG /MD /EHs-c-
//
// Near-twin of R4OptionPreferencesBoolGetters.cpp's get2DShadows (0x000912B0):
// same OptionPreferences boolean-getter skeleton, case-insensitive compare
// branch (102 bytes). Key literal "ShowProps" (read at retail 0x00C76A78,
// same rdata block as "GrassDrawSkip"), byte offset 0x18 into TheGlobalData.

typedef unsigned char Bool;   ///< a byte, not bool: retail never zero-extends the result

extern "C" __declspec( dllimport ) int __cdecl _strcmpi( const char *a, const char *b );

struct CustomAsciiStringShim
{
	void *m_data;
	void init( const char *s );                     ///< body at 0x00888BC0
	void destroy( void );                           ///< body at 0x00887940
};

struct CustomStringDataShim
{
	unsigned char m_header[ 8 ];                    ///< characters follow at +8
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[ 0x14 ];
	CustomStringDataShim *m_value;                  ///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;                    ///< doubles as the end sentinel
	CustomMapNodeShim *find( CustomAsciiStringShim *key );   ///< ILT thunk at 0x0000AEAC
};

struct R4GlobalDataShim { unsigned char m_bytes[ 0x1000 ]; };
extern R4GlobalDataShim *TheGlobalData;             ///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	Bool getShowProps( void );
};

Bool OptionPreferences::getShowProps( void )
{
	CustomAsciiStringShim key;
	key.init( "ShowProps" );
	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)( (unsigned char *)this + 4 );
	CustomMapNodeShim *node = map->find( &key );
	key.destroy();
	if ( node == map->m_header )
		return TheGlobalData->m_bytes[ 0x18 ];
	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)( (unsigned char *)data + 8 ) : "";
	return _strcmpi( text, "yes" ) == 0;
}
