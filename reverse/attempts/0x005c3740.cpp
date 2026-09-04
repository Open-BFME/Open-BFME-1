// ?reset@Rva005C3740@@QAEXXZ
// partial score=0.98 date=2026-09-04
// ?reset@Rva005C3740@@QAEXXZ
// partial score=0.98 date=2026-09-04
// ?reset@Rva005C3740@@QAEXXZ
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Drain an embedded-sentinel list while count is nonzero, then zero the two
// 14-slot arrays together and the trailing counters.

class Open25C3740Held
{
public:
	virtual void slot00( int flag );
};

class Open25C3740Node
{
public:
	Open25C3740Node *m_next;
	void *m_pad;
	Open25C3740Held *m_value;
};

class Open25C3740List
{
public:
	Open25C3740Node m_head;
};

class Rva005C3740
{
public:
	void reset( void );

	char m_pad[ 0xc ];
	int m_first[ 14 ];
	int m_second[ 14 ];
	int m_at7c;
	Open25C3740List *m_list;
	int m_at84;
	int m_at88;
	int m_count;
	int m_at90;
	int m_at94;
	int m_at98;
};

void Rva005C3740::reset( void )
{
	while ( m_count != 0 )
	{
		Open25C3740List *list = m_list;
		Open25C3740Node *node;
		Open25C3740Held *held;
		if ( *(Open25C3740Node *volatile *)list != (Open25C3740Node *)list )
		{
			node = list->m_head.m_next;
			held = node->m_value;
			if ( held != 0 )
				held->slot00( 1 );
		}
	}

	for ( int slot = 0; slot < 14; ++slot )
	{
		m_first[ slot ] = 0;
		m_second[ slot ] = 0;
	}

	m_at84 = 0;
	m_at88 = 0;
	m_count = 0;
	m_at90 = 0;
	m_at94 = 0;
	m_at98 = 0;
	m_at7c = 0;
}
