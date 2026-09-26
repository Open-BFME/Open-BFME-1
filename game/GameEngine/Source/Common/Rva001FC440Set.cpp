// cl: /O2 /Ob0

class Rva001FC440
{
	char pad[0x40];
	int m_40;

public:
	void set(int x);
};

void Rva001FC440::set(int x)
{
	if (x == -1 || x == 1)
	{
		if (m_40 < 0)
			m_40 = 0;
		m_40 += x;
	}
}
