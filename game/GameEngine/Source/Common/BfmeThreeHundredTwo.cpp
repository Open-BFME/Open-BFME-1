// cl: /Od
// A counted run of blocks, each asked for in turn and given the same word as
// its only content. What each choice yields is never read. The place reached is
// handed back. Built without optimisation; the callee is pinned by address.

void j_00030940(void);
typedef void *(__cdecl *Rva00030940Call)(int kind, void *what);

int **bfmeFillQT(int **out, unsigned int many, int **from)
{
	int **at = out;

	for ( ; many > 0; --many, ++at)
	{
		int *got = (int *)((Rva00030940Call)j_00030940)(4, at);

		(got != 0) ? (*got = *(int *)from, (void *)got) : (void *)0;
	}

	return at;
}
