// cl: /O2 /Ob0

class Rva008AD000
{
	int m_00;
	int m_vals[0x200];

public:
	unsigned char has(int v);
};

unsigned char Rva008AD000::has(int v)
{
	for (int i = 0; i < 0x200; i++)
	{
		if (m_vals[i] == v)
			return 1;
	}
	return 0;
}
