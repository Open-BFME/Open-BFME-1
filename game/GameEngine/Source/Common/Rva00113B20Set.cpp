// cl: /O2 /Ob0

class Rva00113B20
{
	void *m_vptr;
	int m_04;

public:
	Rva00113B20 &set(int a);
};

Rva00113B20 &Rva00113B20::set(int a)
{
	m_vptr = (void *)0x0108971C;
	m_04 = a;
	return *this;
}
