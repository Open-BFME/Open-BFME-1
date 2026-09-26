class BfmeGlobalDFD
{
public:
	void bfmeRunDFD(int what, int flag);
};

extern BfmeGlobalDFD *bfmeTheDFD;

void __stdcall bfmeGoDFD(int what)
{
	if (bfmeTheDFD != 0)
		bfmeTheDFD->bfmeRunDFD(what - 1, 1);
}
