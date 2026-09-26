// cl: /O2 /Ob0

struct Rva000C9E50Vec
{
	int a;
	int b;
	int c;
};

class Rva000C9E50
{
	int m_00;
	int m_04;
	Rva000C9E50Vec m_08;

public:
	Rva000C9E50 &set(int a, Rva000C9E50Vec v);
};

Rva000C9E50 &Rva000C9E50::set(int a, Rva000C9E50Vec v)
{
	m_00 = a;
	m_08 = v;
	return *this;
}
