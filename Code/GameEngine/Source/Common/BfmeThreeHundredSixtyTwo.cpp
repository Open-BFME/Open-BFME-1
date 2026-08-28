extern "C" unsigned char bfmeVftVE[];

void bfmeFreeVE(void *what);

class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

class BfmeThingVE
{
public:
	void *bfmeKillVE(int flags);
	void *m_bfmeVft;
	BfmeSubVE *m_bfmeSub;
	void *m_bfmeWhat;
};

void *BfmeThingVE::bfmeKillVE(int flags)
{
	void *what = m_bfmeWhat;
	BfmeSubVE *sub = m_bfmeSub;
	m_bfmeVft = bfmeVftVE;
	sub->bfmeDropVE(what);
	if ((flags & 1) != 0)
		bfmeFreeVE(this);
	return this;
}
