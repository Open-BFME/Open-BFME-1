extern void *g_bfmeWhatBGE;

class BfmeSubBKG
{
public:
	void bfmeDoBKG(void *one, void *two);
};

void __stdcall bfmeGoBKG(BfmeSubBKG *sub, void *what)
{
	sub->bfmeDoBKG(g_bfmeWhatBGE, what);
}
