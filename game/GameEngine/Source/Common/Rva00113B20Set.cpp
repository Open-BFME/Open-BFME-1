// cl: /O2 /Ob0

extern "C" const void *bfmeVftRva00605710Root[];
#pragma comment(linker, "/alternatename:_bfmeVftRva00605710Root=??_7Rva00605710Root@@6B@")

class Rva00113B20
{
	void *m_vptr;
	int m_04;

public:
	Rva00113B20 &set(int a);
};

Rva00113B20 &Rva00113B20::set(int a)
{
	m_vptr = (void *)bfmeVftRva00605710Root;
	m_04 = a;
	return *this;
}
