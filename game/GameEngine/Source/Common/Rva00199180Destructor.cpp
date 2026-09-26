// cl: /O2 /EHs-c-

class Rva00199180Held
{
public:
	void release();
};

struct Rva00199180Slot
{
	char m_pad[ 8 ];
	Rva00199180Held *m_held;
	char m_tail[ 0xC ];
};

class Rva00199180Tail
{
public:
	~Rva00199180Tail();
};

class Rva00199180Owner
{
public:
	~Rva00199180Owner();

	Rva00199180Slot *nth( int i )
	{
		if ( i < 0 || i >= m_count )
			return 0;
		return &m_slots[ i ];
	}

private:
	char m_head[ 0x28 ];
	int m_count;
	Rva00199180Slot m_slots[ 1 ];
	char m_mid[ 0x630 - 0x2C - sizeof( Rva00199180Slot ) ];
	Rva00199180Tail m_tail;
};

Rva00199180Owner::~Rva00199180Owner()
{
	int n = m_count;
	int i = 0;
	if ( n > 0 )
	{
		Rva00199180Slot *p = m_slots;
		for ( ; i < n; ++i, ++p )
		{
			Rva00199180Slot *e = nth( i );
			Rva00199180Held *held = e->m_held;
			if ( held )
				held->release();
		}
	}
}
