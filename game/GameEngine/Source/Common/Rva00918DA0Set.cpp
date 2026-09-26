// cl: /O2 /Ob0

class Rva00918DA0
{
	char m_pad[0x108];
	int m_108;
	char m_mid[0x158 - 0x10C];
	int m_158;

public:
	void set(int a);
};

void Rva00918DA0::set(int a)
{
	m_108 = a;
	m_158 = a;
}
