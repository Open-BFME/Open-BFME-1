// 74-byte linear search and handle forwarder

struct Item00734730
{
	void *m_key;
	char  m_pad04[ 0xE4 ];
};

class Rva00734730
{
public:
	void handle( int index, int arg2 );
	bool findAndSet( void *key, int arg2 );

	char         m_pad00[ 0x208 ];
	Item00734730 m_items[ 1 ];
	char         m_padEnd[ 0x2A79C0 ];
	int          m_count;
};

bool Rva00734730::findAndSet( void *key, int arg2 )
{
	if ( !key )
		return false;
	for ( int i = 0; i < m_count; ++i )
	{
		if ( m_items[ i ].m_key == key )
		{
			handle( i, arg2 );
			return true;
		}
	}
	return false;
}
