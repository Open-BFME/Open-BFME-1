// cl: /O2 /Ob0

class Rva000CBDA0
{
	int m_00;
	int m_04;
	int m_08;

public:
	Rva000CBDA0 &set(int a);
};

Rva000CBDA0 &Rva000CBDA0::set(int a)
{
	m_00 = a;
	m_04 = 0;
	m_08 = 0x7FFFFFFE;
	return *this;
}
