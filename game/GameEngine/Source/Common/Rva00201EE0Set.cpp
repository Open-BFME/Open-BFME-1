// cl: /O2 /Ob0

extern "C" const void *bfmeVftRva00265150RJFilter[];
#pragma comment(linker, "/alternatename:_bfmeVftRva00265150RJFilter=??_7Rva00265150RJFilter@@6B@")

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
	m_00 = (void *)bfmeVftRva00265150RJFilter;
	m_0C = b;
	m_10 = c;
	return *this;
}
