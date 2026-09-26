// cl: /O2 /Ob0

class Rva004C14D0
{
	int m_00;

public:
	Rva004C14D0 &set(int *p, int v);
};

Rva004C14D0 &Rva004C14D0::set(int *p, int v)
{
	*p = 0;
	m_00 = v;
	return *this;
}
