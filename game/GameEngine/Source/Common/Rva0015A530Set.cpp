// cl: /O2 /Ob0

class Rva0015A530
{
	int m_00;
	int m_04;

public:
	void set(int x);
};

void Rva0015A530::set(int x)
{
	if (x < 2)
		x = 2;
	else if (x > 6)
		x = 6;
	m_04 = x;
}
