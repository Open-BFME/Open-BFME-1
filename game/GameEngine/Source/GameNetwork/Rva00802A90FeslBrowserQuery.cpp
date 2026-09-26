// cl: /GX-
// ?go@Rva00802A90Owner@@QAE_NPAURva00802A90Query@@HH@Z
// EA FESL gamebrowser query slot at retail 0x00802A90 (160B).

struct Rva00802A90Query;

struct Rva00802A90Elem
{
	void notify( Rva00802A90Query *q, void *ctx, int flag, int id );

	char m_head[8];
	int m_key;
	char m_tail[0x80 - 0xC];
};

struct Rva00802A90Query
{
	char m_pad[4];
	int m_key;
};

// Retail's 0x00801CB0 body is the member implementation reached through
// notify; the generated dump remains its linker-side implementation.
#pragma comment(linker, "/alternatename:?notify@Rva00802A90Elem@@QAEXPAURva00802A90Query@@PAXHH@Z=?d_00801cb0@@YAXXZ")

class Rva00802A90Owner
{
public:
	bool go( Rva00802A90Query *q, int flag, int id );

	void *m_00;
	void *m_04;
	char m_pad08[0x14];
	Rva00802A90Elem *m_base;
	int m_count;
	int m_index;
	int m_token;
};

bool Rva00802A90Owner::go( Rva00802A90Query *q, int flag, int id )
{
	if( *(unsigned char *)&flag )
	{
		int idx;
		Rva00802A90Elem *base;
		Rva00802A90Elem *elem;

		if( id != m_token )
			return false;
		idx = m_index;
		if( idx >= m_count )
			return false;
		base = m_base;
		elem = (Rva00802A90Elem *)( (char *)base + ( idx << 7 ) );
		if( !elem )
			return false;
		m_index = idx + 1;
		elem->notify( q, m_04, flag, id );
		return m_index >= m_count;
	}
	else
	{
		Rva00802A90Elem *p = m_base;
		Rva00802A90Query *query = q;
		int key = query->m_key;
		Rva00802A90Elem *end = (Rva00802A90Elem *)( (char *)m_base + ( m_count << 7 ) );
		while( p < end )
		{
			if( p->m_key == key )
			{
				p->notify( query, m_04, 0, id );
				return false;
			}
			p = (Rva00802A90Elem *)( (char *)p + 0x80 );
		}
		return false;
	}
}
