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
public:
	void *m_vptr;
	Rva003525E0Pair m_04;
	char m_0C;
	char m_0D;
	char m_0E;
};

class Rva00354BC0
{
	int m_00;
	void *m_vptr;
	Rva003525E0Pair m_08;
	char m_10;
	char m_11;
	char m_12;

public:
	Rva00354BC0(const Rva003529B0 *other);
};

Rva00354BC0::Rva00354BC0(const Rva003529B0 *other)
	: m_08(*(other ? &other->m_04 : 0))
{
	m_vptr = (void *)0x010E855C;
	m_10 = other->m_0C;
	m_11 = other->m_0D;
	m_12 = 0;
}
