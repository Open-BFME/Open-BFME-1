// cl: /DNDEBUG /MD
//
// Retail 0x003D5FC0: release the fixed cell-info slots and the optional
// overflow list, retaining the number of released entries.

typedef int Int;

extern void j_0004a561(void);
extern void j_000135ac(void);

typedef Int (__cdecl *BfmeRelease)(void *value);

class PathfindCellInfoPool
{
public:
	void reset(void);

private:
	char m_pad00[0x34];
	void *m_slots[0x200];
	Int m_slotCount;                         // +0x834
	void *m_overflow;                        // +0x838
	char m_pad83c[4];
	Int m_releasedCount;                     // +0x840
};

// ?reset@PathfindCellInfoPool@@QAEXXZ
void PathfindCellInfoPool::reset(void)
{
	Int released = 0;
	void **slot = m_slots;
	for (Int i = 0; i < 0x200; ++i)
	{
		released += ((BfmeRelease)j_0004a561)(*slot);
		*slot = 0;
		++slot;
	}

	m_slotCount = 0x200;
	if (m_overflow != 0)
	{
		released += ((BfmeRelease)j_000135ac)(m_overflow);
		m_overflow = 0;
	}

	m_releasedCount += released;
}
