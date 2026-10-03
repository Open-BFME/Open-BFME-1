// cl: /Od
// A block asked for and, when one comes back, given the caller's word as its
// only content. What the choice yields is never read. Built without
// optimisation; the callee is pinned by address.

// Retail calls the ILT thunk at 0x00030940, which gen_small owns as
// ?j_00030940@@YAXXZ; it forwards to 0x004607E0 with the two arguments intact.
void j_00030940(void);
typedef void *(__cdecl *Rva00030940Call)(int kind, unsigned int bytes);

class BfmeThingQG
{
public:
	void bfmeMakeQG(unsigned int bytes, const int *from);
};

void BfmeThingQG::bfmeMakeQG(unsigned int bytes, const int *from)
{
	int *got = (int *)((Rva00030940Call)j_00030940)(4, bytes);

	(got != 0) ? (*got = *from, (void *)got) : (void *)0;
}
