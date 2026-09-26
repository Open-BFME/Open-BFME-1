// cl: /O2 /Ob0

class Rva007F0210
{
	int m_00;
	int m_04;
	int m_08;

public:
	Rva007F0210 &set(int a, int b);
};

Rva007F0210 &Rva007F0210::set(int a, int b)
{
	m_00 = a;
	m_08 = b;
	m_04 = 0x0107301C;
	return *this;
}
