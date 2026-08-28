class BfmeThingBHA
{
public:
	void bfmeDoBHA(void *sub, int flag);
	void bfmeGoBHA(void *what);
	unsigned char m_bfmeHead[8];
	void *m_bfmeSub;
	unsigned char m_bfmeGap[0x14];
	void *m_bfmeSaved;
};

void BfmeThingBHA::bfmeGoBHA(void *what)
{
	m_bfmeSaved = what;
	bfmeDoBHA(m_bfmeSub, 1);
}
