// cl: /O2 /Ob0

class Rva000E8900
{
	char m_pad[0x12C];
	int m_12C;
	int m_130;
	int m_134;

public:
	void set(int a, int b, int c);
};

void Rva000E8900::set(int a, int b, int c)
{
	m_12C = a;
	m_130 = b;
	m_134 = c;
}
