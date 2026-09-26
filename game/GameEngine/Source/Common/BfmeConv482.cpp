extern void *g_bfmeWhatBKG;

class BfmeSubBKG
{
public:
	void bfmeDoBKG(void *one, void *two);
};

void __stdcall bfmeGoBKG(BfmeSubBKG *sub, void *what)
{
	sub->bfmeDoBKG(g_bfmeWhatBKG, what);
}
