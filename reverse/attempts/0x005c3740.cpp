// ?d_005c3740@@YAXXZ
// partial score=0.97 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x005C3740 -- drain a list, then zero everything.
//
//     mov eax,[esi+0x80] / cmp [eax],eax / je / mov ecx,[eax] / mov ecx,[ecx+8]
//     ... push 1 / call [edx] ... cmp [esi+0x8c],edi / jne <top>
//
// `cmp [eax],eax` compares the list's first link against the list's own
// address, which is the emptiness test of an EMBEDDED sentinel.  The drain
// re-reads the count every turn and the list pointer with it, because the
// deleting destructor is what removes the entry.
//
// The zeroing afterwards is ONE loop writing two slots a turn -- `[eax-0x38]`
// and `[eax]`, fourteen times -- so the two arrays are cleared together rather
// than one after the other.

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

// @?reset@Rva005C3740@@QAEXXZ 0x005C3740
void Rva005C3740::reset( void )
{
	while( m_count != 0 )
	{
		Open25C3740List *list = m_list;
		if( list->m_head.m_next != (Open25C3740Node *)list )
		{
			Open25C3740Held *held = list->m_head.m_next->m_value;
			if( held != 0 )
				held->slot00( 1 );
		}
	}

	for( int slot = 0; slot < 14; ++slot )
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

