// cl: /O2 /Ob0

struct Rva001BE390Inner
{
	char m_lead[0x44];
	int m_value;
};

class Rva001BE390
{
	char m_lead[0x1EC];
	Rva001BE390Inner *m_inner;

public:
	int get();
};

int Rva001BE390::get()
{
	Rva001BE390Inner *p = m_inner;
	int value = 0;
	if (p)
		value = p->m_value;
	return value;
}
