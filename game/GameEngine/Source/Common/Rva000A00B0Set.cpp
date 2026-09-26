// cl: /O2 /Ob0

struct Rva000A00B0Pod
{
	int a;
	int b;
	int c;
};

class Rva000A00B0
{
	char m_pad[0x24];
	Rva000A00B0Pod m_24;

public:
	void set(const Rva000A00B0Pod *other);
};

void Rva000A00B0::set(const Rva000A00B0Pod *other)
{
	if (other)
		m_24 = *other;
}
