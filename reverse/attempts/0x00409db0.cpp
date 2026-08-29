// ?d_00409db0@@YAXXZ
// partial score=0.98 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x00409DB0 -- retire the run when it has outlived its budget, then collect a
// holder that has reported state 3.
//
// Every failure in the first chain jumps to the SAME place -- the start of the
// second half -- so the whole first half is one `if` with four `&&` terms, not
// four nested statements with their own exits.  `dec eax / jne` is a compare
// against one, and the budget test is unsigned.

class Open2409DB0Holder
{
public:
	virtual void slot00( int reason );

	char m_pad[ 4 ];
	int m_state;
};

class Rva00409DB0
{
public:
	void update( unsigned int now );

	char m_pad[ 4 ];
	unsigned char m_active;
	char m_pad2[ 7 ];
	int m_count;
	char m_pad3[ 4 ];
	unsigned int m_limit;
	Open2409DB0Holder *m_holder;
	char m_pad4[ 0x34 - 0x1c ];
	int m_second;
	int m_first;
};

// @?update@Rva00409DB0@@QAEXI@Z 0x00409DB0
void Rva00409DB0::update( unsigned int now )
{
	if( m_active != 0 && ( m_first == 0 || m_second == 0 ) &&
		now > m_limit && m_count - 1 == 0 )
	{
		if( m_holder != 0 )
			m_holder->m_state = 2;
		m_active = 0;
	}

	if( m_holder != 0 && m_holder->m_state == 3 )
	{
		m_holder->slot00( 1 );
		m_holder = 0;
	}
}
