// cl: /O2

class Open26A0EF0Seed
{
public:
	char m_pad[8];
	unsigned int m_seed;
};

class Open26A0EF0Owner
{
public:
	char m_pad[4];
	Open26A0EF0Seed *m_seedHolder;
};

class Open26A0EF0Slots
{
public:
	unsigned int size( void ) const
	{
		return (unsigned int)( m_finish - m_start );
	}

	void *m_pad;
	void **volatile m_start;
	void **volatile m_finish;
};

class Rva006A0EF0
{
public:
	void *pick( void ) const;
	Open26A0EF0Owner *m_owner;
	Open26A0EF0Slots *m_slots;
};

void *Rva006A0EF0::pick( void ) const
{
	Open26A0EF0Slots *slots = m_slots;
	Open26A0EF0Seed *holder = m_owner->m_seedHolder;
	unsigned int seed = (unsigned int)holder;
	if( holder )
		seed = holder->m_seed;
	unsigned int divisor = slots->size();
	unsigned int index = seed % divisor;
	unsigned int count = slots->size();
	void *found = 0;
	while( ++index < count
		&& !( found = slots->m_start[ index ] ) )
		;
	return found;
}
