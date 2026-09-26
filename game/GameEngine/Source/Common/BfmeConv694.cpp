class BfmeSubDGH
{
public:
	void bfmeRunDGH(void *b);
};

BfmeSubDGH *__stdcall bfmeFindDGH(void *a);

void __stdcall bfmeGoDGH(void *a, void *b)
{
	BfmeSubDGH *s = bfmeFindDGH(a);
	if (s != 0)
		s->bfmeRunDGH(b);
}
