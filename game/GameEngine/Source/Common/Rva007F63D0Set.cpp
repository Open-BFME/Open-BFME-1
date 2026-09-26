// cl: /O2 /Ob0

struct Rva007F63D0Src
{
	char pad[0x0C];
	int m_0C;
};

class Rva007F63D0
{
	char pad[0x24];
	int m_24;

public:
	void set(int *a, const Rva007F63D0Src *b, int unused);
};

void Rva007F63D0::set(int *a, const Rva007F63D0Src *b, int)
{
	if (!a)
	{
		if (b)
			m_24 = b->m_0C;
	}
}
