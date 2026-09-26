// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva007F76F0Vector;

class Rva00802240Host
{
public:
	int rva007F76F0( Rva007F76F0Vector *vector, const char *key );
};

class Rva00801340Owner
{
public:
	void *lookup2A8( const char *key );

	char m_pad00[ 4 ];
	Rva00802240Host *m_base;
	char m_pad08[ 0x34 - 8 ];
	void **m_entries;
};

void *Rva00801340Owner::lookup2A8( const char *key )
{
	if( m_entries )
	{
		Rva00802240Host *base = m_base;
		int index = base->rva007F76F0(
			(Rva007F76F0Vector *)((char *)base + 0x2a8), key );
		if( index != -1 )
			return m_entries[index];
	}
	return 0;
}
