// cl: /O2 /Ob0

struct Rva000A00E0Pod
{
	int a;
	int b;
	int c;
};

class Rva000A00E0
{
	char m_pad[0x34];
	Rva000A00E0Pod m_34;

public:
	void set(const Rva000A00E0Pod *other);
};

void Rva000A00E0::set(const Rva000A00E0Pod *other)
{
	if (other)
		m_34 = *other;
}
