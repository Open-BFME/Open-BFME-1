// ?go@Rva00802A90Owner@@QAE_NPAURva00802A90Query@@HH@Z
// partial score=0.9 date=2026-09-04
// cl: /GX-
// jabba gamebrowser slot go @ 0x00802A90 (160B).

struct Rva00802A90Elem
{
	char m_head[8];
	int m_key;
	char m_tail[0x80 - 0xC];
};

struct Rva00802A90Query
{
	char m_pad[4];
	int m_key;
};

void __stdcall Rva00801CB0( Rva00802A90Query *q, void *ctx, int flag, int id );

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
	if( (unsigned char)flag )
	{
		if( id != m_token )
			return false;
		int idx = m_index;
		if( idx >= m_count )
			return false;
		Rva00802A90Elem *base = m_base;
		Rva00802A90Elem *elem = (Rva00802A90Elem *)( (char *)base + ( idx << 7 ) );
		if( !elem )
			return false;
		m_index = idx + 1;
		Rva00801CB0( q, m_04, flag, id );
		return m_index >= m_count;
	}
	else
	{
		Rva00802A90Elem *p = m_base;
		Rva00802A90Elem *end = (Rva00802A90Elem *)( (char *)m_base + ( m_count << 7 ) );
		while( p < end )
		{
			if( p->m_key == q->m_key )
			{
				Rva00801CB0( q, m_04, 0, id );
				return false;
			}
			p = (Rva00802A90Elem *)( (char *)p + 0x80 );
		}
		return false;
	}
}
