class BfmeSubDGE
{
public:
	void bfmeRunDGE(void *b);
};

BfmeSubDGE *__stdcall bfmeFindDGE(void *a);

void __stdcall bfmeGoDGE(void *a, void *b)
{
	BfmeSubDGE *s = bfmeFindDGE(a);
	if (s != 0)
		s->bfmeRunDGE(b);
}
