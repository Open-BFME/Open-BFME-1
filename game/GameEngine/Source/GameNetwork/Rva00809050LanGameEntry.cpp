// cl: /O2 /GX-
// Retail 0x00809050 scans the sixteen FESL LAN-game slots, returns an entry
// whose key matches, or creates an entry in the first empty slot.

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class Rva007E86B0Base : public Gen007F0130
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	__forceinline Rva00808CB0LanGameEntry( int sequence )
	{
		m_field08 = 0;
		m_field0c = 0;
		m_field04 = 0;
		m_sequence = sequence;
		m_field14 = 0;
	}

	int m_field08;
	int m_field0c;
	int m_sequence;
	int m_field14;
	char m_tail18[ 8 ];
};

class Rva00803620Sink
{
public:
	Rva00808CB0LanGameEntry *rva00809050( struct Rva00809050Input *input );

	char m_pad00[ 0x14 ];
	int m_nextLanGameId;
	Rva00808CB0LanGameEntry *m_lanGames[ 16 ];
};

struct Rva00809050Input
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
};

Rva00808CB0LanGameEntry *Rva00803620Sink::rva00809050(
	Rva00809050Input *input )
{
	int slot = -1;
	int index = 0;
	Rva00808CB0LanGameEntry *entry;

	for( ; index < 16; ++index )
	{
		entry = m_lanGames[ index ];
		if( entry == 0 )
		{
			slot = index;
		}
		else if( entry->m_field08 == input->m_field08 )
			return entry;
	}

	if( slot == -1 )
		return 0;

	entry = new Rva00808CB0LanGameEntry( ++m_nextLanGameId );
	entry->m_field04 = input->m_field04;
	entry->m_field08 = input->m_field08;
	entry->m_field0c = input->m_field0c;
	m_lanGames[ slot ] = entry;
	return entry;
}
