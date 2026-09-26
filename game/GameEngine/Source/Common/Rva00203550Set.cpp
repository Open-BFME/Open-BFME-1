// cl: /O2 /Ob0

class Rva00203550
{
	int m_00;

public:
	Rva00203550 &set(int unused, int bit);
};

Rva00203550 &Rva00203550::set(int, int bit)
{
	m_00 = 1 << (bit & 31);
	return *this;
}
