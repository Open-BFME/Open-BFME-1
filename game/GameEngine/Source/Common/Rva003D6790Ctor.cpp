// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" unsigned char bfmeVftVD[];

class Rva003D6790
{
public:
	Rva003D6790(int *a, int *b);

	void *m_vftable;
	int m_4;
	int *m_8;
};

Rva003D6790::Rva003D6790(int *a, int *b)
{
	m_vftable = bfmeVftVD;
	m_8 = a;
	m_4 = *a;
	*a = *b;
}
