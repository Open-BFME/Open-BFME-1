// ?set@Rva002214F0@@QAEXPAURva002214F0Source@@H0@Z
// partial score=0.79 date=2026-09-10
// cl: /O2 /Ob0

struct Rva002214F0Source
{
	char m_pad[0x74];
	int m_value;
};

class Rva002214F0
{
public:
	void set(Rva002214F0Source *a, int b, Rva002214F0Source *c);

private:
	char m_pad[0x9C];
	int m_9C;
	int m_A0;
	int m_A4;
};

void Rva002214F0::set(Rva002214F0Source *a, int b, Rva002214F0Source *c)
{
	int one = 1;
	const int *maxp = (b > one) ? &b : &one;
	m_A4 = *maxp;
	m_9C = a->m_value;
	m_A0 = c->m_value;
}
