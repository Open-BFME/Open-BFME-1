// cl: /O2 /Ob0

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	void *m_a;
	void *m_b;
};

class Rva00354B60
{
	int m_00;
	void *m_vptr;
	Rva003525E0Pair m_08;
	char m_10;
	char m_11;
	char m_12;

public:
	Rva00354B60(int *other);
};

Rva00354B60::Rva00354B60(int *other)
	: m_00(0),
	  m_08(*(++other ? (const Rva003525E0Pair *)(other + 1) : 0))
{
	m_vptr = (void *)0x010E855C;
	m_10 = ((char *)other)[0x0C];
	m_11 = ((char *)other)[0x0D];
	m_12 = 0;
}
