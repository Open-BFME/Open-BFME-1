class BfmeSinkBMF
{
public:
	void bfmeDoBMF(int what, int flag);
};

extern BfmeSinkBMF *g_bfmeSinkBMF;

void __stdcall bfmeGoBMF(int what)
{
	BfmeSinkBMF *sink = g_bfmeSinkBMF;
	if (sink != 0)
		sink->bfmeDoBMF(what - 1, 1);
}
