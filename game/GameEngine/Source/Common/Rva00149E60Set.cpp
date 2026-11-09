// cl: /O2 /Ob0

void j_00039f04();
void j_0000783d();
void j_0003b9e4();

// Retail VA010956C4: three existing ILT entries (vtable_lookup.py 0x010956C4), the
// vftable of the partition filter stored by the AI and filter constructors.
const void *g_010956C4[3] = {
	reinterpret_cast<const void *>(&j_00039f04),
	reinterpret_cast<const void *>(&j_0000783d),
	reinterpret_cast<const void *>(&j_0003b9e4),
};

class Rva00149E60
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00149E60 &set(int a, int b, int c);
};

Rva00149E60 &Rva00149E60::set(int a, int b, int c)
{
	m_08 = b;
	m_04 = 0;
	m_00 = (void *)g_010956C4;
	m_0C = c;
	m_10 = a;
	return *this;
}
