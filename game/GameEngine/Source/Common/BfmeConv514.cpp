class BfmeSinkBQE
{
public:
	void bfmeDoBQE(void *what);
};

extern BfmeSinkBQE *g_bfmeSinkBQE;

void __stdcall bfmeGoBQE(void *what)
{
	if (what == 0)
		g_bfmeSinkBQE->bfmeDoBQE(0);
}
