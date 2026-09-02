// ?pick@Rva006A0EF0@@QBEPAXXZ
// partial score=0.92 date=2026-09-02
// cl: /O2
// ?pick@Rva006A0EF0@@QBEPAXXZ
// 0x006A0EF0 -- pick the first non-empty slot at or after a hashed start.

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
	Open26A0EF0Seed *holder = m_owner->m_seedHolder;
	Open26A0EF0Slots *slots = m_slots;
	unsigned int seed = (unsigned int)holder;
	if( holder )
		seed = holder->m_seed;
	unsigned int index = seed % (unsigned int)( slots->m_finish - slots->m_start );
	unsigned int count = (unsigned int)( slots->m_finish - slots->m_start );
	void *found = 0;
	while( ++index < count && !( found = slots->m_start[ index ] ) )
		;
	return found;
}
