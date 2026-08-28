extern "C" unsigned char bfmeVftVD[];

void bfmeFreeVD(void *what);

class BfmeThingVD
{
public:
	void *bfmeKillVD(int flags);
	void *m_bfmeVft;
	void *m_bfmeWhat;
	void **m_bfmeSlot;
};

void *BfmeThingVD::bfmeKillVD(int flags)
{
	void **slot = m_bfmeSlot;
	void *what = m_bfmeWhat;
	m_bfmeVft = bfmeVftVD;
	*slot = what;
	if ((flags & 1) != 0)
		bfmeFreeVD(this);
	return this;
}
