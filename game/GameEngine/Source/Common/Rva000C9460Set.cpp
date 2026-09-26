// cl: /O2 /Ob0

class Rva000C9460
{
	int m_00;
	char m_04;
	int m_08;
	int m_0C;

public:
	Rva000C9460 &set(int a, char b);
};

Rva000C9460 &Rva000C9460::set(int a, char b)
{
	m_00 = a;
	m_04 = b;
	m_08 = 0;
	m_0C = 0;
	return *this;
}
