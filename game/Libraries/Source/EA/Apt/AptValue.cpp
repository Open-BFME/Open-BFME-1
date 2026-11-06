// cl: /DNDEBUG /MD /EHsc
// RVA 008991E0: slot 1 of the address-qualified value family. The twelve-bit
// reference count saturates on underflow; a transition to zero registers the
// value once, or dispatches slot 2 when the root registry is full.
// See targets/game/reverse/identity_evidence/008991e0-inline-root-pool.md.

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
struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_items;
	__forceinline int addPooled(Rva00899560Value *value)
	{
		int &count = m_count;
		if (count >= m_capacity)
		{
			value->m_flags &= 0xBFFFFFFF;
			return -1;
		}
		m_items[count] = value;
		return m_count++;
	}
};

extern Rva00899560Pool *g_rva01337810GcRoots;

void Rva00899560Value::release()
{
	unsigned int bits;
	unsigned int index = m_count;
	index &= 0xFFF;
	index--;

	unsigned int slot = index;
	if (index > 0xFFF)
		slot = 0xFFF;

	bits = m_flags;
	bits = (bits & 0xF000FFFF) | (slot << 16);
	m_flags = bits;

	if (index != 0)
		return;

	if ((unsigned char)(bits >> 30) & 1)
		return;

	bits |= 0x40000000;
	m_flags = bits;

	if (g_rva01337810GcRoots->m_count < g_rva01337810GcRoots->m_capacity)
		g_rva01337810GcRoots->addPooled(this);
	else
		idle();
}
