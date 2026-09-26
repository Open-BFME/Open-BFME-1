// cl: /O2 /Ob0

struct Rva000A08B0Pod
{
	int a;
	int b;
	int c;
};

class Rva000A08B0
{
	char m_pad[0x34];
	Rva000A08B0Pod m_34;
	char m_40;

public:
	void set(const Rva000A08B0Pod *other);
};

void Rva000A08B0::set(const Rva000A08B0Pod *other)
{
	if (m_40)
		return;
	if (other)
		m_34 = *other;
}
