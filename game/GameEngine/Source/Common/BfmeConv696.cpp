class BfmeSubDGE
{
public:
	void bfmeRunDGE(void *b);
};

// Retail calls bfmeFindDGE through the incremental-link thunk at RVA
// 0x0004446D, whose body is the matched thunk `void j_0004446d(void)`
// (game/gen_small/thunks_032.cpp); that is the definition the call resolves
// to, so the call spells it and casts to the stdcall signature EA gave the
// exported name.
extern void j_0004446d();

void __stdcall bfmeGoDGE(void *a, void *b)
{
	BfmeSubDGE *s = ((BfmeSubDGE *(__stdcall *)(void *))j_0004446d)(a);
	if (s != 0)
		s->bfmeRunDGE(b);
}
