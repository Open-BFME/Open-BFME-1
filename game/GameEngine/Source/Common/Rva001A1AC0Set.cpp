// cl: /O2 /Ob0

class Rva001A1AC0
{
	char m_pad[0x1C];
	int m_1C;
	int m_20;
	int m_24;

public:
	void set(int a, int b, int c);
};

void Rva001A1AC0::set(int a, int b, int c)
{
	m_1C = a;
	m_20 = b;
	m_24 = c;
}
