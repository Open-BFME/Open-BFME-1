// cl: /O2 /DNDEBUG /MD
// ?equals@Rva0013ABC0Table@@QAEDPAV1@@Z
// Element-wise multibyte-string equality over two same-sized tables.
// Identity unrecovered; named from the address.

extern "C" __declspec( dllimport ) int __cdecl _mbscmp(
	const unsigned char *left, const unsigned char *right );

class Rva0013ABC0Table
{
public:
	char equals( Rva0013ABC0Table *o );

private:
	void *m_vtable;
	const unsigned char **m_items;
	int m_count;
};

char Rva0013ABC0Table::equals( Rva0013ABC0Table *o )
{
	int n = m_count;

	if( n == o->m_count )
	{
		int i = 0;

		if( n > 0 )
		{
			do
			{
				const unsigned char *right = o->m_items[ i ];
				const unsigned char *left = m_items[ i ];

				if( _mbscmp( left, right ) != 0 )
					return 0;

				++i;
			}
			while( i < m_count );
		}

		return 1;
	}

	return 0;
}
