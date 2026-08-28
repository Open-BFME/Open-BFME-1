extern "C" unsigned char bfmeVftVH[];

void bfmeFreeVH(void *what);

class BfmeSubVH
{
public:
	virtual void bfmeReleaseVH(int what);
};

class BfmeThingVH
{
public:
	void *bfmeKillVH(int flags);
	void *m_bfmeVft;
	BfmeSubVH *m_bfmeSub;
};

void *BfmeThingVH::bfmeKillVH(int flags)
{
	BfmeSubVH *sub = m_bfmeSub;
	m_bfmeVft = bfmeVftVH;
	if (sub != 0)
		sub->bfmeReleaseVH(1);
	if ((flags & 1) != 0)
		bfmeFreeVH(this);
	return this;
}
