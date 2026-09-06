// ?bfmeFindAOB@BfmeThingAOB@@QAEHPAPBE@Z
// partial score=0.98 date=2026-09-05
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec( dllimport ) int __cdecl _mbscmp(
	const unsigned char *left, const unsigned char *right );

class BfmeThingAOB
{
public:
	int bfmeFindAOB( const unsigned char **name );
private:
	void *m_vtable;
	const unsigned char **m_names;
	char m_unmodelled[ 8 ];
	int m_count;
};

// ?bfmeFindAOB@BfmeThingAOB@@QAEHPAPBE@Z
int BfmeThingAOB::bfmeFindAOB( const unsigned char **name )
{
	for( int i = 0; i < m_count; ++i )
	{
		if( _mbscmp( m_names[ i ], *name ) == 0 )
			return i;
	}
	return -1;
}
