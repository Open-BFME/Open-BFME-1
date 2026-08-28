class BfmeSinkBLD
{
public:
	void bfmeDoBLD(void *what, int flag);
};

extern BfmeSinkBLD *g_bfmeSinkBLD;

void __stdcall bfmeGoBLD(void *what)
{
	BfmeSinkBLD *sink = g_bfmeSinkBLD;
	if (sink != 0)
		sink->bfmeDoBLD(what, 0);
}
