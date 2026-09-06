// cl: /O2 /DNDEBUG /MD

extern "C" __declspec( dllimport ) int __cdecl _mbscmp(
	const unsigned char *left, const unsigned char *right );

class BfmeThingAOB
{
public:
	int bfmeFindAOB( const unsigned char **name );

private:
	void *m_vtable;
	const unsigned char * const *m_names;
	char m_unmodelled[ 8 ];
	int m_count;
};

int BfmeThingAOB::bfmeFindAOB( const unsigned char **name )
{
	for( int i = 0; i < m_count; ++i )
	{
		const unsigned char *argument = *name;
		register const unsigned char *candidate = m_names[ i ];
		if( _mbscmp( candidate, argument ) == 0 )
			return i;
	}
	return -1;
}
