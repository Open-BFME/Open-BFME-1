// cl: /O2 /Ob0

struct Rva00214B70Src
{
	char pad[0x74];
	int m_74;
};

class Rva00214B70
{
	char pad[0xE0];
	int m_E0;

public:
	void set(const Rva00214B70Src *p);
};

void Rva00214B70::set(const Rva00214B70Src *p)
{
	if (p)
		m_E0 = p->m_74;
}
