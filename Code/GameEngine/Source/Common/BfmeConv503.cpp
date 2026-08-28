class BfmeSinkBOE
{
public:
	void bfmeDoBOE(void *one, void *two);
};

extern BfmeSinkBOE *g_bfmeSinkBOE;

void __stdcall bfmeGoBOE(void *one, void *two, void *three, void *four)
{
	BfmeSinkBOE *sink = g_bfmeSinkBOE;
	if (sink != 0)
		sink->bfmeDoBOE(one, two);
}
