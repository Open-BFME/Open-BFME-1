class BfmeGlobalDFF
{
public:
	void bfmeRunDFF(int what, int flag);
};

extern BfmeGlobalDFF *bfmeTheDFF;

void __stdcall bfmeGoDFF(int what)
{
	if (bfmeTheDFF != 0)
		bfmeTheDFF->bfmeRunDFF(what - 1, 0);
}
