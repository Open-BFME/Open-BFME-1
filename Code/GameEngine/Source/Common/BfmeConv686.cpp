class BfmeGlobalDFE
{
public:
	void bfmeRunDFE(int what, int flag);
};

extern BfmeGlobalDFE *bfmeTheDFE;

void __stdcall bfmeGoDFE(int what)
{
	if (bfmeTheDFE != 0)
		bfmeTheDFE->bfmeRunDFE(what - 1, 0);
}
