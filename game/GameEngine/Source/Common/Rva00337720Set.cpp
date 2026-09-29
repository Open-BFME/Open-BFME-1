// cl: /O2 /Ob0

extern "C" unsigned char bfmeVftVC[];

class Rva00337720
{
	void *m_00;
	int m_04;
	int *m_08;

public:
	Rva00337720 &set(int *p, int *q);
};

Rva00337720 &Rva00337720::set(int *p, int *q)
{
	m_00 = bfmeVftVC;
	m_08 = p;
	m_04 = *p;
	*p = *q;
	return *this;
}
