// cl: /O2 /Ob0

// Retail stores 0x00265150's vftable pointer directly; the vftable symbol is
// compiler-emitted, so __identifier spells it and the char array type keeps the
// decay-to-pointer a plain int would lose.
extern "C" const char __identifier("??_7Rva00265150RJFilter@@6B@")[];

class Rva00201EE0
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;

public:
	Rva00201EE0 &set(int a, int b, char c);
};

Rva00201EE0 &Rva00201EE0::set(int a, int b, char c)
{
	m_08 = a;
	m_04 = 0;
	m_00 = (void *)__identifier("??_7Rva00265150RJFilter@@6B@");
	m_0C = b;
	m_10 = c;
	return *this;
}
