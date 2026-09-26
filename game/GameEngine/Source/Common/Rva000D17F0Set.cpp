// cl: /O2 /Ob0

class Rva000D17F0
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;

public:
	Rva000D17F0 &set(int a);
};

Rva000D17F0 &Rva000D17F0::set(int a)
{
	m_00 = a;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	return *this;
}
