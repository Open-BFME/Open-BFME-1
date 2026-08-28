class BfmeRefCHC
{
public:
	void bfmeDtorCHC();
};

class BfmeThingCHC
{
public:
	void bfmeGoCHC(BfmeRefCHC *what);
	BfmeRefCHC *m_bfmeRef;
};

void bfmeFreeCHC(void *what);

void BfmeThingCHC::bfmeGoCHC(BfmeRefCHC *what)
{
	BfmeRefCHC *cur = m_bfmeRef;
	if (what != cur)
	{
		if (cur != 0)
		{
			cur->bfmeDtorCHC();
			bfmeFreeCHC(cur);
		}
		m_bfmeRef = what;
	}
}
