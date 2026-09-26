class BfmeSubDGI
{
public:
	void bfmeRunDGI(void *b);
};

BfmeSubDGI *__stdcall bfmeFindDGI(void *a);

void __stdcall bfmeGoDGI(void *a, void *b)
{
	BfmeSubDGI *s = bfmeFindDGI(a);
	if (s != 0)
		s->bfmeRunDGI(b);
}
