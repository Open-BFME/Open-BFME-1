// cl: /O2 /Ob0

class Rva004784F0
{
	char pad[0x1AC];
	int m_1AC;
	int m_1B0;

public:
	void get(int *a, int *b);
};

void Rva004784F0::get(int *a, int *b)
{
	if (a)
	{
		if (b)
		{
			*a = m_1AC;
			*b = m_1B0;
		}
	}
}
