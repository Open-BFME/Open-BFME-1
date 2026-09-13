// ?release@Rva00899560Value@@UAEXXZ
// partial score=0.99 date=2026-09-12
// ?release@Rva00899560Value@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc
// Apt value slot 1 (vtables 0x01135D68 / 0x011360A8). Saturating 12-bit
// refcount decrement; on the transition to zero a one-shot (bit 30) insert
// into g_rva8CD130IdleHook. Slot 2 is tail-called when the idle pool is full.
//
// 120 B, 1 non-reloc byte: second registry compare is cmp esi,[eax]
// (count vs m_capacity) where retail has redundant cmp esi,edi (count vs
// the cap snapshot). Snapshot-vs-snapshot complementary compares fold to 97 B.

class Rva00899560Value;

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_items;
};

extern Rva00899560Pool *g_rva8CD130IdleHook;

class Rva00899560Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void idle();

	union
	{
		unsigned int m_flags;
		struct
		{
			unsigned short m_low;
			unsigned short m_count;
		};
	};
};

void Rva00899560Value::release()
{
	unsigned int bits;
	unsigned int index = m_count;
	index &= 0xFFF;
	index--;

	unsigned int slot = index;
	if (index > 0xFFF)
		slot = 0xFFF;

	bits = *(volatile unsigned int *)&m_flags;
	bits = (bits & 0xF000FFFF) | (slot << 16);
	m_flags = bits;

	if (index != 0)
		return;

	if ((unsigned char)(bits >> 30) & 1)
		return;

	bits |= 0x40000000;
	m_flags = bits;

	Rva00899560Pool *registry = g_rva8CD130IdleHook;
	const int *tp = &registry->m_count;
	int cap = *(volatile int *)&registry->m_capacity;
	int count = tp[0];
	if (count < cap)
	{
		if (count >= registry->m_capacity)
		{
			bits &= ~0x40000000;
			m_flags = bits;
		}
		else
		{
			registry->m_items[count] = this;
			int next = registry->m_count;
			registry->m_count = next + 1;
		}
	}
	else
		idle();
}
