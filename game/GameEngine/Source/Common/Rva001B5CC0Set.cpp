// cl: /O2 /Ob0

struct Rva001B5CC0Pod
{
	int a;
	int b;
	int c;
};

class Rva001B5CC0
{
	char m_pad[0x14];
	Rva001B5CC0Pod m_14;

public:
	void set(const char *other);
};

void Rva001B5CC0::set(const char *other)
{
	if (other)
		m_14 = *(const Rva001B5CC0Pod *)(other + 0x38);
}
