// cl: /O2 /Ob0

class Rva0073C420
{
	char pad[0x2A8];
	int m_2A8;

public:
	void set(int x);
};

void Rva0073C420::set(int x)
{
	if (x <= 1)
		x = 1;
	m_2A8 = x;
}
