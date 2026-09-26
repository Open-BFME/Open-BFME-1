// cl: /O2 /Ob0

class Rva005584F0
{
	char pad[0x3C];
	int m_3C;

public:
	void set(int x);
};

void Rva005584F0::set(int x)
{
	if (!x)
		m_3C = 0;
}
