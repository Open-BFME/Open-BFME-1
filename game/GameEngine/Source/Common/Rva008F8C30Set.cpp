// cl: /O2 /Ob0

class Rva008F8C30
{
	char m_lead[0x64];
	int m_64;
	char m_mid[4];
	int m_6c;

public:
	void set(int a, int b);
};

void Rva008F8C30::set(int a, int b)
{
	m_64 = a;
	m_6c = b;
}
