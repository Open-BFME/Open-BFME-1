// 74-byte linear search and handle forwarder

struct Item00734730
{
	void *m_key;
	char  m_pad04[ 0xE4 ];
};

// The matched hit at 0x00734730 dispatches through the retail ILT at
// 0x00049DD7 to the tree-buffer record update at 0x00733F50, whose ledger
// name is ?handle@Rva00733F50@@QAEXHH@Z (defined in
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DTreeBufferRva00733F50.cpp).  Declare that class here so the call
// spells the real owner instead of a local namesake.
class Rva00733F50
{
public:
	void handle( int index, int arg2 );
};

class Rva00734730
{
public:
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
			((Rva00733F50 *)this)->handle( i, arg2 );
			return true;
		}
	}
	return false;
}
