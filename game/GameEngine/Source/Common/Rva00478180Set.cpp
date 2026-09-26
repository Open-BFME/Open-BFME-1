// cl: /O2 /Ob0

class Rva00478180
{
	char m_pad[0x24];
	int m_24;
	int m_28;

public:
	int set(int a, int b);
};

int Rva00478180::set(int a, int b)
{
	m_24 = a;
	m_28 = b;
	return 0;
}
