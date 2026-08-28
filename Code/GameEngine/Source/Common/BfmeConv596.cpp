class BfmeRefCHB
{
public:
	void bfmeDtorCHB();
};

class BfmeThingCHB
{
public:
	void bfmeGoCHB(BfmeRefCHB *what);
	BfmeRefCHB *m_bfmeRef;
};

void bfmeFreeCHB(void *what);

void BfmeThingCHB::bfmeGoCHB(BfmeRefCHB *what)
{
	BfmeRefCHB *cur = m_bfmeRef;
	if (what != cur)
	{
		if (cur != 0)
		{
			cur->bfmeDtorCHB();
			bfmeFreeCHB(cur);
		}
		m_bfmeRef = what;
	}
}
