// cl: /O2 /Ob0

class Rva00382680
{
	char pad[0x14];
	unsigned m_14;

public:
	void set(unsigned x);
};

void Rva00382680::set(unsigned x)
{
	if (x > 0x3FFFFFFF)
		x = 0x3FFFFFFF;
	m_14 = x;
}
