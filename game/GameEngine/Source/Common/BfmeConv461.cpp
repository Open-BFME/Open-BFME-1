extern void *g_bfmeWhatBGE;

class BfmeSubBGE
{
public:
	void bfmeDoBGE(void *what, int flag);
};

void __stdcall bfmeGoBGE(BfmeSubBGE *sub)
{
	sub->bfmeDoBGE(g_bfmeWhatBGE, 0);
}
