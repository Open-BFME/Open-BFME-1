// ??0Rva00899560Value@@QAE@H@Z
// Open-BFME7: Apt script value base constructor (118 B): stores the type in
// the low six bits, clears the transient bits, sets bit 15, and for types
// other than 10 and 28 marks the value pooled (bit 30) and hands it to the
// idle-hook pool, whose addPooled clears the pooled bit when it is full.
// The failure path living inside the pool method is what places the
// success block after the failure block.
struct Rva00899560Value { virtual ~Rva00899560Value(); unsigned int m_flags; Rva00899560Value(int type); };
struct Rva00899560Pool {
	int m_capacity; int m_count; Rva00899560Value** m_items;
	bool add(Rva00899560Value* v) { if (m_count < m_capacity) { m_items[m_count] = v; m_count++; return true; } return false; }
	void addPooled(Rva00899560Value* v) { int& count = m_count; if (count >= m_capacity) { v->m_flags &= 0xBFFFFFFF; return; } m_items[count] = v; count++; }
};
extern Rva00899560Pool* g_rva8CD130IdleHook;
Rva00899560Value::Rva00899560Value(int type)
{
	unsigned int flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
	m_flags = flags;
	if (type != 0x1c && type != 0xa) {
		m_flags = flags | 0x40000000;
		g_rva8CD130IdleHook->addPooled(this);
	} else {
		m_flags = flags & 0xBFFFFFFF;
	}
}
