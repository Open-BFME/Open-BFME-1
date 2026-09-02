// ?gen002EADF0@@YAXPAX0H0@Z
// partial score=0.98 date=2026-09-02
// cl: /O2 /Ob0

class Rva002EADF0Elem
{
public:
	Rva002EADF0Elem(const Rva002EADF0Elem &);
	~Rva002EADF0Elem();

private:
	char m_bfmeBody[20];
};

void gen002EADF0Helper(void *a, Rva002EADF0Elem *p, Rva002EADF0Elem *q,
	Rva002EADF0Elem val, void *c, int zero);

void gen002EADF0(void *a, void *b, int, void *c)
{
	Rva002EADF0Elem *p = (Rva002EADF0Elem *)b - 1;
	gen002EADF0Helper(a, p, p, *p, c, 0);
}
