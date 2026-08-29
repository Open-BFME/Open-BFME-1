// ?d_006a0ef0@@YAXXZ
// partial score=0.85 date=2026-08-28
// ---------------------------------------------------------------------------
// 0x006A0EF0 -- pick the first non-empty slot at or after a hashed start.
//
//     ... div ecx / ... / inc edx / cmp edx,ecx / jae end
//     mov eax,[esi+4] / mov eax,[eax+edx*4] / test eax,eax / je loop
//
// `div` is unsigned, so the seed and the count are both unsigned.  The count is
// computed TWICE -- once as the divisor and once as the loop bound -- so the
// source spells the size expression twice rather than holding one local; and
// the base pointer is re-read on every iteration, which is indexing through the
// container each time rather than through a hoisted pointer.  The result
// register is pre-set to zero before the loop, so the not-found answer is the
// same null the scan was looking for.

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
	unsigned int size( void ) const { return (unsigned int)( m_finish - m_start ); }
	void *m_pad;
	void **m_start;
	void **m_finish;
};

class Rva006A0EF0
{
public:
	void *pick( void ) const;
	Open26A0EF0Owner *m_owner;
	Open26A0EF0Slots *m_slots;
};

// @?pick@Rva006A0EF0@@QBEPAXXZ 0x006A0EF0
void *Rva006A0EF0::pick( void ) const
{
	Open26A0EF0Seed *holder = m_owner->m_seedHolder;
	const Open26A0EF0Slots *slots = m_slots;
	unsigned int seed = (unsigned int)holder;
	if( holder )
		seed = holder->m_seed;
	unsigned int index = seed % slots->size();
	unsigned int count = slots->size();
	void *found = 0;
	while( ++index < count )
	{
		found = slots->m_start[ index ];
		if( found )
			break;
	}
	return found;
}

