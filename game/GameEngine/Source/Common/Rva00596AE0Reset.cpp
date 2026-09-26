// cl: /O2 /Ob0

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

void bfmeNote1029( int index, char value );

class Rva00596AE0Member
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void release();
};

class Rva00596AE0Queue
{
public:
	void clear();

private:
	char m_storage[ 4 ];
};

class Rva00596AE0
{
public:
	void reset();

private:
	char m_pad00[ 0x10 ];
	Rva00596AE0Member *m_member;
	char m_pad18[ 4 ];
	char m_flags[ 6 ];
	char m_pad1e[ 2 ];
	Rva00596AE0Queue m_queue;
	char m_pad24[ 0x27 ];
	volatile char m_ready;
	char m_pad4c[ 0x41c ];
	volatile char m_active;
	char m_pad469[ 3 ];
	int m_value46c;
	int m_value470;
	int m_value474;
	volatile int m_value478;
};

// ?reset@Rva00596AE0@@QAEXXZ
void Rva00596AE0::reset()
{
	for ( int i = 0; i < 6; ++i )
	{
		bfmeNote1029( i, 0 );
		m_flags[ i ] = 0;
	}

	if ( m_member != 0 )
		m_member->release();

	m_queue.clear();
	m_ready = 1;
	_ReadWriteBarrier();
	m_active = 0;
	m_value478 = 0;
	m_value46c = -2;
	m_value470 = -2;
	m_value474 = -2;
}
