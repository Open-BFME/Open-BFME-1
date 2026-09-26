class BfmeRefCHA
{
public:
	void bfmeDtorCHA();
};

class BfmeThingCHA
{
public:
	void bfmeGoCHA(BfmeRefCHA *what);
	BfmeRefCHA *m_bfmeRef;
};

void bfmeFreeCHA(void *what);

void BfmeThingCHA::bfmeGoCHA(BfmeRefCHA *what)
{
	BfmeRefCHA *cur = m_bfmeRef;
	if (what != cur)
	{
		if (cur != 0)
		{
			cur->bfmeDtorCHA();
			bfmeFreeCHA(cur);
		}
		m_bfmeRef = what;
	}
}
