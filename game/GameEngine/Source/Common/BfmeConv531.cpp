class BfmeSinkBUB
{
public:
	bool bfmeAskBUB(void *what);
};

extern BfmeSinkBUB *g_bfmeSinkBUB;

bool __stdcall bfmeGoBUB(void *what)
{
	BfmeSinkBUB *sink = g_bfmeSinkBUB;
	if (sink != 0 && sink->bfmeAskBUB(what))
		return true;
	return false;
}
