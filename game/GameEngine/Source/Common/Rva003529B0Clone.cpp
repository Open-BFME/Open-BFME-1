// cl: /O2 /EHsc /MD
// The 0x00352A00 body allocates and copies the 0x000E855C-vtable record.
// The vtable and the exact Rva003529B0 copy constructor at 0x003529B0 identify
// the record. The method name remains address-derived because retail exposes no
// named caller or vtable slot for this non-virtual copy operation.

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	void *m_a;
	void *m_b;
};

class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other)
		: m_pair(*(other ? &other->m_pair : 0))
	{
		m_vptr = (void *)0x010E855C;
		m_0C = other->m_0C;
		m_0D = other->m_0D;
		m_0E = 0;
	}

	Rva003529B0 *rva00352a00() const;

private:
	void *m_vptr;
	Rva003525E0Pair m_pair;
	char m_0C;
	char m_0D;
	char m_0E;
};

Rva003529B0 *Rva003529B0::rva00352a00() const
{
	return new Rva003529B0(this);
}
