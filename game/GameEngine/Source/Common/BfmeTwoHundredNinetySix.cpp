// cl: /Od
// Every word of a run given a block of its own, each block asked for in turn
// and given that word as its only content. What each choice yields is never
// read. The place reached is handed back. Built without optimisation; the
// callee is pinned by address.

void j_00030940(void);
typedef void *(__cdecl *Rva00030940Call)(int kind, void *what);

int **bfmeFillQL(int **first, int **last, int **out)
{
	int **at = out;

	for ( ; first != last; ++first, ++at)
	{
		int *got = (int *)((Rva00030940Call)j_00030940)(4, at);

		(got != 0) ? (*got = *(int *)first, (void *)got) : (void *)0;
	}

	return at;
}
