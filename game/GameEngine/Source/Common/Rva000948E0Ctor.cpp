// cl: /O2 /Ob0

extern "C" const void *bfmeVftOverridable[];
#pragma comment(linker, "/alternatename:_bfmeVftOverridable=??_7Overridable@@6B@")

class Rva000948E0
{
	void *m_vptr;
	int m_04;
	char m_08;

public:
	Rva000948E0(int dummy);
};

Rva000948E0::Rva000948E0(int)
{
	m_vptr = (void *)bfmeVftOverridable;
	m_04 = 0;
	m_08 = 0;
}
