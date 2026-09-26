// cl: /O2 /Ob0

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
	void *m_vptr;
	Rva003525E0Pair m_04;
	char m_0C;
	char m_0D;
	char m_0E;

public:
	Rva003529B0(const Rva003529B0 *other);
};

Rva003529B0::Rva003529B0(const Rva003529B0 *other)
	: m_04(*(other ? &other->m_04 : 0))
{
	m_vptr = (void *)0x010E855C;
	m_0C = other->m_0C;
	m_0D = other->m_0D;
	m_0E = 0;
}
