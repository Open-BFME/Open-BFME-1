extern "C" unsigned char bfmeVftVG[];

void bfmeFreeVG(void *what);

class BfmeThingVG
{
public:
	void *bfmeKillVG(int flags);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x34];
	void *m_bfmeOne;
	void *m_bfmeTwo;
	void *m_bfmeThree;
};

void *BfmeThingVG::bfmeKillVG(int flags)
{
	m_bfmeTwo = 0;
	m_bfmeThree = 0;
	m_bfmeOne = 0;
	m_bfmeVft = bfmeVftVG;
	if ((flags & 1) != 0)
		bfmeFreeVG(this);
	return this;
}
