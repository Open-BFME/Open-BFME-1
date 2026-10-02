// cl: /O2 /Ob0

// Retail global at 0x0112C6F4, recorded as ?g_bfmeVftUUA@@3PAPAXA.
extern void *g_bfmeVftUUA[];

class Rva00803080
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00803080 &set(int a);
};

Rva00803080 &Rva00803080::set(int a)
{
	m_04 = a;
	m_00 = (void *)g_bfmeVftUUA;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	return *this;
}
