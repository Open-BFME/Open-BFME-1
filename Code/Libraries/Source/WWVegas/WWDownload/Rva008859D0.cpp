// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) char* __cdecl _strdup( const char* );
extern "C" __declspec(dllimport) int __cdecl sprintf( char*, const char*, ... );
extern "C" __declspec(dllimport) void __cdecl free( void* );

class Rva008859D0Class
{
public:
	char pad0[0x34];
	const char* m_dir34;

	void d_008859d0( const char* name, char* outBuf );
};

void Rva008859D0Class::d_008859d0( const char* name, char* outBuf )
{
	char* dupName = _strdup( name );
	for ( char* p = dupName; *p; ++p )
	{
		if ( *p == '\\' || *p == '.' || *p == ' ' )
		{
			*p = '_';
		}
	}

	sprintf( outBuf, (const char*)0x01132EB8, dupName, m_dir34 );
	free( dupName );
}
