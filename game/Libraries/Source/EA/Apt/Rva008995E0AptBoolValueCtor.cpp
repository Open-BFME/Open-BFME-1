// ??0Rva008995E0Value@@QAE@_N@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script value constructor (101 B): the base constructor
// (0x00899560, defined in-class so it inlines with a constant type) sets the
// type bits and hands the value to the idle-hook pool, whose addPooled clears
// the pooled bit when full; then the derived class stores its payload.
struct Rva00899560Value;
struct Rva00899560Pool {
	int m_capacity; int m_count; Rva00899560Value** m_items;
	void addPooled(Rva00899560Value* v);
};
extern Rva00899560Pool* g_rva8CD130IdleHook;
struct Rva00899560Value {
	virtual ~Rva00899560Value();
	unsigned int m_flags;
	Rva00899560Value(int type)
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
};
inline void Rva00899560Pool::addPooled(Rva00899560Value* v)
{
	int& count = m_count;
	if (count >= m_capacity) {
		v->m_flags &= 0xBFFFFFFF;
		return;
	}
	m_items[count] = v;
	count++;
}
struct Rva008995E0Value : Rva00899560Value {
	bool m_value;
	Rva008995E0Value(bool value);
};
Rva008995E0Value::Rva008995E0Value(bool value)
	: Rva00899560Value(5), m_value(value)
{
}
